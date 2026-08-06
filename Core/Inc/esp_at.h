#ifndef __ESP_AT_H
#define __ESP_AT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

#define ESP_AT_RX_CHUNK_SIZE   128
#define ESP_AT_RESPONSE_SIZE   4096

typedef enum
{
    ESP_AT_ASYNC_IDLE = 0,
    ESP_AT_ASYNC_BUSY,
    ESP_AT_ASYNC_OK,
    ESP_AT_ASYNC_ERROR,
    ESP_AT_ASYNC_FAIL,
    ESP_AT_ASYNC_OVERFLOW,
    ESP_AT_ASYNC_TIMEOUT,
    ESP_AT_ASYNC_SEND_ERROR,
    ESP_AT_ASYNC_PARAM_ERROR
} ESP_AT_AsyncResult_t;

uint8_t ESP_AT_Init(void);

uint8_t ESP_AT_SendRaw(const char *data);
uint8_t ESP_AT_SendCommand(const char *cmd);
uint8_t ESP_AT_Command(const char *cmd, const char *expect, uint32_t timeout_ms);

void ESP_AT_SetNotifyTask(TaskHandle_t task);
void ESP_AT_WaitForRx(TickType_t max_wait_ticks);
uint8_t ESP_AT_AsyncStart(const char *cmd, const char *expect, uint32_t timeout_ms);
ESP_AT_AsyncResult_t ESP_AT_AsyncPoll(void);
uint8_t ESP_AT_AsyncIsBusy(void);
void ESP_AT_AsyncCancel(void);

uint8_t ESP_AT_Test(void);
uint8_t ESP_AT_EchoOff(void);
uint8_t ESP_AT_SetStationMode(void);
uint8_t ESP_AT_ConnectWifi(const char *ssid, const char *password, uint32_t timeout_ms);
uint8_t ESP_AT_HttpGet(const char *url, char *response, uint16_t response_size, uint32_t timeout_ms);

uint8_t ESP_AT_SNTPConfig(void);
uint8_t ESP_AT_GetSNTPTime(char *response, uint16_t response_size, uint32_t timeout_ms);

void ESP_AT_GetLastResponse(char *buf, uint16_t size);

void ESP_AT_ClearResponse(void);
const char *ESP_AT_GetResponse(void);
uint16_t ESP_AT_GetResponseLength(void);
uint8_t ESP_AT_ParseQuotedValue(const char *src, const char *key,
                                char *out, uint16_t out_size);

void ESP_AT_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size);

uint8_t ESP_AT_GetWifiSSID(char *ssid, uint16_t size, uint32_t timeout_ms);
uint8_t ESP_AT_GetStationIP(char *ip, uint16_t size, uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif



