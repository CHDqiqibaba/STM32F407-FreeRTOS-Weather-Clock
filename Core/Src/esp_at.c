#include "esp_at.h"

#include "stream_buffer.h"
#include <string.h>
#include <stdio.h>

#define ESP_AT_RX_STREAM_SIZE       ESP_AT_RESPONSE_SIZE
#define ESP_AT_RX_TRIGGER_LEVEL     1
#define ESP_AT_EXPECT_SIZE          32
#define ESP_AT_POLL_WAIT_MS         20
#define ESP_AT_NOTIFY_RX            (1UL << 0)
#define ESP_AT_NOTIFY_OVERFLOW      (1UL << 1)

static uint8_t esp_rx_buf[ESP_AT_RX_CHUNK_SIZE];
static char esp_response_buf[ESP_AT_RESPONSE_SIZE + 1];
static uint16_t esp_response_len = 0;
static volatile uint8_t esp_response_overflow = 0;

static StreamBufferHandle_t esp_rx_stream = NULL;
static TaskHandle_t esp_notify_task = NULL;

static uint8_t esp_async_busy = 0;
static char esp_expect_buf[ESP_AT_EXPECT_SIZE];
static uint32_t esp_async_start_tick = 0;
static uint32_t esp_async_timeout_ms = 0;

static uint8_t ESP_AT_IsSchedulerRunning(void)
{
    return (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED);
}

static uint8_t ESP_AT_TimeExpired(uint32_t now, uint32_t start, uint32_t timeout_ms)
{
    return ((int32_t)(now - start) >= (int32_t)timeout_ms);
}

static void ESP_AT_ResetResponseBuffer(void)
{
    __disable_irq();

    esp_response_len = 0;
    esp_response_overflow = 0;
    esp_response_buf[0] = '\0';

    __enable_irq();
}

static void ESP_AT_CopyExpect(const char *expect)
{
    memset(esp_expect_buf, 0, sizeof(esp_expect_buf));

    if (expect != NULL)
    {
        strncpy(esp_expect_buf, expect, sizeof(esp_expect_buf) - 1);
    }
}

static void ESP_AT_AppendResponse(const uint8_t *data, uint16_t len)
{
    uint16_t free_size;
    uint16_t copy_size;

    if (data == NULL || len == 0)
    {
        return;
    }

    free_size = ESP_AT_RESPONSE_SIZE - esp_response_len;
    copy_size = (len < free_size) ? len : free_size;

    if (copy_size > 0)
    {
        memcpy(&esp_response_buf[esp_response_len], data, copy_size);
        esp_response_len += copy_size;
        esp_response_buf[esp_response_len] = '\0';
    }

    if (copy_size < len)
    {
        esp_response_overflow = 1;
    }
}

static void ESP_AT_DrainRxStream(void)
{
    uint8_t tmp[64];
    size_t rx_len;

    if (esp_rx_stream == NULL || esp_notify_task == NULL)
    {
        return;
    }

    do
    {
        rx_len = xStreamBufferReceive(esp_rx_stream,
                                      tmp,
                                      sizeof(tmp),
                                      0);

        if (rx_len > 0)
        {
            ESP_AT_AppendResponse(tmp, (uint16_t)rx_len);
        }
    } while (rx_len > 0);
}

static uint8_t ESP_AT_ResultToCode(ESP_AT_AsyncResult_t result)
{
    switch (result)
    {
        case ESP_AT_ASYNC_OK:
            return 0;
        case ESP_AT_ASYNC_ERROR:
            return 2;
        case ESP_AT_ASYNC_FAIL:
            return 3;
        case ESP_AT_ASYNC_OVERFLOW:
            return 4;
        case ESP_AT_ASYNC_TIMEOUT:
            return 5;
        case ESP_AT_ASYNC_SEND_ERROR:
            return 1;
        case ESP_AT_ASYNC_PARAM_ERROR:
            return 1;
        default:
            return 6;
    }
}

uint8_t ESP_AT_Init(void)
{
    if (esp_rx_stream == NULL)
    {
        esp_rx_stream = xStreamBufferCreate(ESP_AT_RX_STREAM_SIZE,
                                            ESP_AT_RX_TRIGGER_LEVEL);
        if (esp_rx_stream == NULL)
        {
            return 2;
        }
    }

    ESP_AT_ClearResponse();

    if (HAL_UARTEx_ReceiveToIdle_IT(&huart2,
                                    esp_rx_buf,
                                    sizeof(esp_rx_buf)) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

void ESP_AT_SetNotifyTask(TaskHandle_t task)
{
    esp_notify_task = task;
}

void ESP_AT_WaitForRx(TickType_t max_wait_ticks)
{
    uint32_t notify_value;

    if (!ESP_AT_IsSchedulerRunning() || max_wait_ticks == 0)
    {
        return;
    }

    (void)xTaskNotifyWait(0,
                          ESP_AT_NOTIFY_RX | ESP_AT_NOTIFY_OVERFLOW,
                          &notify_value,
                          max_wait_ticks);
}

void ESP_AT_ClearResponse(void)
{
    ESP_AT_ResetResponseBuffer();

    if (esp_rx_stream != NULL && esp_notify_task != NULL)
    {
        (void)xStreamBufferReset(esp_rx_stream);
    }
}

const char *ESP_AT_GetResponse(void)
{
    ESP_AT_DrainRxStream();
    return esp_response_buf;
}

uint16_t ESP_AT_GetResponseLength(void)
{
    ESP_AT_DrainRxStream();
    return esp_response_len;
}

uint8_t ESP_AT_SendRaw(const char *data)
{
    uint16_t len;

    if (data == NULL)
    {
        return 1;
    }

    len = (uint16_t)strlen(data);

    if (HAL_UART_Transmit(&huart2,
                          (uint8_t *)data,
                          len,
                          1000) != HAL_OK)
    {
        return 2;
    }

    return 0;
}

uint8_t ESP_AT_SendCommand(const char *cmd)
{
    if (cmd == NULL)
    {
        return 1;
    }

    if (HAL_UART_Transmit(&huart2,
                          (uint8_t *)cmd,
                          (uint16_t)strlen(cmd),
                          1000) != HAL_OK)
    {
        return 2;
    }

    if (HAL_UART_Transmit(&huart2,
                          (uint8_t *)"\r\n",
                          2,
                          1000) != HAL_OK)
    {
        return 3;
    }

    return 0;
}

uint8_t ESP_AT_AsyncStart(const char *cmd, const char *expect, uint32_t timeout_ms)
{
    if (cmd == NULL || timeout_ms == 0)
    {
        return 1;
    }

    if (esp_rx_stream == NULL)
    {
        return 2;
    }

    if (esp_async_busy)
    {
        return 3;
    }

    ESP_AT_ClearResponse();
    ESP_AT_CopyExpect(expect);

    esp_async_start_tick = HAL_GetTick();
    esp_async_timeout_ms = timeout_ms;
    esp_async_busy = 1;

    if (ESP_AT_SendCommand(cmd) != 0)
    {
        esp_async_busy = 0;
        return 4;
    }

    return 0;
}

ESP_AT_AsyncResult_t ESP_AT_AsyncPoll(void)
{
    if (!esp_async_busy)
    {
        return ESP_AT_ASYNC_IDLE;
    }

    ESP_AT_DrainRxStream();

    if (esp_response_overflow)
    {
        esp_async_busy = 0;
        return ESP_AT_ASYNC_OVERFLOW;
    }

    if (strstr(esp_response_buf, "ERROR") != NULL)
    {
        esp_async_busy = 0;
        return ESP_AT_ASYNC_ERROR;
    }

    if (strstr(esp_response_buf, "FAIL") != NULL)
    {
        esp_async_busy = 0;
        return ESP_AT_ASYNC_FAIL;
    }

    if (esp_expect_buf[0] != '\0')
    {
        if (strstr(esp_response_buf, esp_expect_buf) != NULL)
        {
            esp_async_busy = 0;
            return ESP_AT_ASYNC_OK;
        }
    }

    if (ESP_AT_TimeExpired(HAL_GetTick(),
                           esp_async_start_tick,
                           esp_async_timeout_ms))
    {
        esp_async_busy = 0;
        return ESP_AT_ASYNC_TIMEOUT;
    }

    return ESP_AT_ASYNC_BUSY;
}

uint8_t ESP_AT_AsyncIsBusy(void)
{
    return esp_async_busy;
}

void ESP_AT_AsyncCancel(void)
{
    esp_async_busy = 0;
    ESP_AT_CopyExpect(NULL);
}

uint8_t ESP_AT_Command(const char *cmd, const char *expect, uint32_t timeout_ms)
{
    uint8_t ret;
    ESP_AT_AsyncResult_t result;

    ret = ESP_AT_AsyncStart(cmd, expect, timeout_ms);
    if (ret != 0)
    {
        return ret;
    }

    for (;;)
    {
        result = ESP_AT_AsyncPoll();
        if (result != ESP_AT_ASYNC_BUSY)
        {
            return ESP_AT_ResultToCode(result);
        }

        if (ESP_AT_IsSchedulerRunning())
        {
            ESP_AT_WaitForRx(pdMS_TO_TICKS(ESP_AT_POLL_WAIT_MS));
        }
        else
        {
            HAL_Delay(1);
        }
    }
}

uint8_t ESP_AT_ParseQuotedValue(const char *src, const char *key,
                                char *out, uint16_t out_size)
{
    const char *p;
    const char *start;
    const char *end;
    uint16_t len;

    if (src == NULL || key == NULL || out == NULL || out_size == 0)
    {
        return 1;
    }

    p = strstr(src, key);
    if (p == NULL)
    {
        return 2;
    }

    start = strchr(p, '"');
    if (start == NULL)
    {
        return 3;
    }

    start++;
    end = strchr(start, '"');
    if (end == NULL)
    {
        return 4;
    }

    len = (uint16_t)(end - start);
    if (len >= out_size)
    {
        len = out_size - 1;
    }

    memcpy(out, start, len);
    out[len] = '\0';

    return 0;
}

uint8_t ESP_AT_GetWifiSSID(char *ssid, uint16_t size, uint32_t timeout_ms)
{
    uint8_t ret;

    if (ssid == NULL || size == 0)
    {
        return 1;
    }

    ssid[0] = '\0';

    ret = ESP_AT_Command("AT+CWSTATE?", "OK", timeout_ms);
    if (ret != 0)
    {
        return ret;
    }

    return ESP_AT_ParseQuotedValue(ESP_AT_GetResponse(), "+CWSTATE:", ssid, size);
}

uint8_t ESP_AT_GetStationIP(char *ip, uint16_t size, uint32_t timeout_ms)
{
    uint8_t ret;

    if (ip == NULL || size == 0)
    {
        return 1;
    }

    ip[0] = '\0';

    ret = ESP_AT_Command("AT+CIFSR", "OK", timeout_ms);
    if (ret != 0)
    {
        return ret;
    }

    return ESP_AT_ParseQuotedValue(ESP_AT_GetResponse(), "+CIFSR:STAIP", ip, size);
}

uint8_t ESP_AT_Test(void)
{
    return ESP_AT_Command("AT", "OK", 1000);
}

uint8_t ESP_AT_EchoOff(void)
{
    return ESP_AT_Command("ATE0", "OK", 1000);
}

uint8_t ESP_AT_SetStationMode(void)
{
    return ESP_AT_Command("AT+CWMODE=1", "OK", 1000);
}

uint8_t ESP_AT_ConnectWifi(const char *ssid, const char *password, uint32_t timeout_ms)
{
    char cmd[256];

    if (ssid == NULL || password == NULL)
    {
        return 1;
    }

    snprintf(cmd,
             sizeof(cmd),
             "AT+CWJAP=\"%s\",\"%s\"",
             ssid,
             password);

    return ESP_AT_Command(cmd, "OK", timeout_ms);
}

void ESP_AT_GetLastResponse(char *buf, uint16_t size)
{
    uint16_t copy_len;

    if (buf == NULL || size == 0)
    {
        return;
    }

    ESP_AT_DrainRxStream();

    __disable_irq();

    copy_len = esp_response_len;

    if (copy_len >= size)
    {
        copy_len = size - 1;
    }

    memcpy(buf, esp_response_buf, copy_len);

    __enable_irq();

    buf[copy_len] = '\0';
}

uint8_t ESP_AT_HttpGet(const char *url, char *response, uint16_t response_size, uint32_t timeout_ms)
{
    char cmd[512];
    uint8_t ret;

    if (url == NULL || response == NULL || response_size == 0)
    {
        return 1;
    }

    response[0] = '\0';

    snprintf(cmd,
             sizeof(cmd),
             "AT+HTTPCGET=\"%s\",2048,4096,%lu",
             url,
             (unsigned long)timeout_ms);

    ret = ESP_AT_Command(cmd, "OK", timeout_ms + 1000);
    if (ret != 0)
    {
        return ret;
    }

    ESP_AT_GetLastResponse(response, response_size);

    return 0;
}

uint8_t ESP_AT_SNTPConfig(void)
{
    return ESP_AT_Command(
        "AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\",\"pool.ntp.org\"",
        "OK",
        3000
    );
}

uint8_t ESP_AT_GetSNTPTime(char *response, uint16_t response_size, uint32_t timeout_ms)
{
    uint8_t ret;

    if (response == NULL || response_size == 0)
    {
        return 1;
    }

    response[0] = '\0';

    ret = ESP_AT_Command("AT+CIPSNTPTIME?", "OK", timeout_ms);
    if (ret != 0)
    {
        return ret;
    }

    ESP_AT_GetLastResponse(response, response_size);

    return 0;
}

void ESP_AT_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size)
{
    BaseType_t higher_priority_task_woken = pdFALSE;
    size_t send_len;

    if (huart->Instance != USART2)
    {
        return;
    }

    if (size > sizeof(esp_rx_buf))
    {
        size = sizeof(esp_rx_buf);
    }

    if (esp_notify_task == NULL)
    {
        ESP_AT_AppendResponse(esp_rx_buf, size);
    }
    else if (esp_rx_stream != NULL && size > 0)
    {
        send_len = xStreamBufferSendFromISR(esp_rx_stream,
                                            esp_rx_buf,
                                            size,
                                            &higher_priority_task_woken);

        if (send_len < size)
        {
            esp_response_overflow = 1;

            if (esp_notify_task != NULL)
            {
                (void)xTaskNotifyFromISR(esp_notify_task,
                                         ESP_AT_NOTIFY_OVERFLOW,
                                         eSetBits,
                                         &higher_priority_task_woken);
            }
        }

        if (esp_notify_task != NULL)
        {
            (void)xTaskNotifyFromISR(esp_notify_task,
                                     ESP_AT_NOTIFY_RX,
                                     eSetBits,
                                     &higher_priority_task_woken);
        }
    }
    else
    {
        esp_response_overflow = 1;
    }

    HAL_UARTEx_ReceiveToIdle_IT(&huart2,
                                esp_rx_buf,
                                sizeof(esp_rx_buf));

    portYIELD_FROM_ISR(higher_priority_task_woken);
}
