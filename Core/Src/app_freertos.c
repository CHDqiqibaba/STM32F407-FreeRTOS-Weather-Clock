#include "app_freertos.h"

#include <stdio.h>
#include <stdint.h>

#include "task.h"

#include "app_log.h"
#include "app_tasks.h"
#include "esp_at.h"
#include "iwdg.h"
#include "ui_msg.h"

#define UI_TASK_STACK_WORDS         2048
#define NETWORK_TASK_STACK_WORDS    1536
#define SENSOR_TASK_STACK_WORDS     1024
#define STORAGE_TASK_STACK_WORDS    1024
#define MONITOR_TASK_STACK_WORDS    512

#define MONITOR_STARTUP_DELAY_MS    3000U
#define MONITOR_CHECK_WINDOW_MS     1000U
#define MONITOR_PERIOD_MS           2000U


static EventGroupHandle_t AppEventGroup;

static TaskHandle_t UiTaskHandle;
static TaskHandle_t NetworkTaskHandle;
static TaskHandle_t SensorTaskHandle;
static TaskHandle_t StorageTaskHandle;
static TaskHandle_t MonitorTaskHandle;

static void UiTask(void *argument);
static void NetworkTask(void *argument);
static void SensorTask(void *argument);
static void StorageTask(void *argument);
static void MonitorTask(void *argument);
static void App_UpdateWifiEventBit(void);
static void App_Monitor_ReportFault(EventBits_t missing_bits);
static void App_Monitor_FeedWatchdog(void);
static void App_CheckCreateResult(BaseType_t ret, const char *name);

EventGroupHandle_t App_FreeRTOS_GetEventGroup(void)
{
    return AppEventGroup;
}

void App_FreeRTOS_Init(void)
{
    BaseType_t ret;

    APP_LOG_BOOT("FreeRTOS init start\r\n");

    UI_Msg_Init();
    APP_LOG_BOOT("UI message queue OK\r\n");

    AppEventGroup = xEventGroupCreate();
    if (AppEventGroup == NULL)
    {
        APP_LOG_ERROR("EventGroup create failed\r\n");
    }
    configASSERT(AppEventGroup != NULL);
    APP_LOG_BOOT("EventGroup create OK\r\n");

    ret = xTaskCreate(UiTask,
                      "UI",
                      UI_TASK_STACK_WORDS,
                      NULL,
                      5,
                      &UiTaskHandle);
    App_CheckCreateResult(ret, "UI");

    ret = xTaskCreate(NetworkTask,
                      "Network",
                      NETWORK_TASK_STACK_WORDS,
                      NULL,
                      3,
                      &NetworkTaskHandle);
    App_CheckCreateResult(ret, "Network");

    ret = xTaskCreate(SensorTask,
                      "Sensor",
                      SENSOR_TASK_STACK_WORDS,
                      NULL,
                      2,
                      &SensorTaskHandle);
    App_CheckCreateResult(ret, "Sensor");

    ret = xTaskCreate(StorageTask,
                      "Storage",
                      STORAGE_TASK_STACK_WORDS,
                      NULL,
                      1,
                      &StorageTaskHandle);
    App_CheckCreateResult(ret, "Storage");

    ret = xTaskCreate(MonitorTask,
                      "Monitor",
                      MONITOR_TASK_STACK_WORDS,
                      NULL,
                      4,
                      &MonitorTaskHandle);
    App_CheckCreateResult(ret, "Monitor");

    HAL_IWDG_Refresh(&hiwdg);
    APP_LOG_BOOT("FreeRTOS init done\r\n");
}

static void UiTask(void *argument)
{
    (void)argument;

    for (;;)
    {
        App_Task_UI();
        xEventGroupSetBits(AppEventGroup, APP_EVENT_UI_ALIVE);
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

static void NetworkTask(void *argument)
{
    (void)argument;

    /* Let the UI draw the first screen before running slow ESP-AT commands. */
    vTaskDelay(pdMS_TO_TICKS(500));

    ESP_AT_SetNotifyTask(xTaskGetCurrentTaskHandle());
    App_NetworkStartup();

    for (;;)
    {
        App_Task_Network();
        App_UpdateWifiEventBit();
        ESP_AT_WaitForRx(pdMS_TO_TICKS(100));
        xEventGroupSetBits(AppEventGroup, APP_EVENT_NETWORK_ALIVE);
    }
}

static void SensorTask(void *argument)
{
    (void)argument;

    for (;;)
    {
        App_Task_Sensor();
        xEventGroupSetBits(AppEventGroup, APP_EVENT_SENSOR_ALIVE);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

static void StorageTask(void *argument)
{
    (void)argument;

    for (;;)
    {
        App_Task_Storage();
        xEventGroupSetBits(AppEventGroup, APP_EVENT_STORAGE_ALIVE);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

static void MonitorTask(void *argument)
{
    EventBits_t bits;
    EventBits_t missing_bits;

    (void)argument;

    vTaskDelay(pdMS_TO_TICKS(MONITOR_STARTUP_DELAY_MS));

    for (;;)
    {
        xEventGroupClearBits(AppEventGroup, APP_EVENT_ALIVE_MASK);
        vTaskDelay(pdMS_TO_TICKS(MONITOR_CHECK_WINDOW_MS));

        bits = xEventGroupGetBits(AppEventGroup);
        missing_bits = APP_EVENT_ALIVE_MASK & (~bits);

        if (missing_bits == 0)
        {
            App_Monitor_FeedWatchdog();
        }
        else
        {
            App_Monitor_ReportFault(missing_bits);
        }

        vTaskDelay(pdMS_TO_TICKS(MONITOR_PERIOD_MS));
    }
}

static void App_UpdateWifiEventBit(void)
{
    if (App_IsWifiConnected())
    {
        xEventGroupSetBits(AppEventGroup, APP_EVENT_WIFI_CONNECTED);
    }
    else
    {
        xEventGroupClearBits(AppEventGroup, APP_EVENT_WIFI_CONNECTED);
    }
}

static void App_Monitor_ReportFault(EventBits_t missing_bits)
{
    if ((missing_bits & APP_EVENT_UI_ALIVE) != 0)
    {
        APP_LOG_ERROR("Monitor fault: UI task no alive\r\n");
    }

    if ((missing_bits & APP_EVENT_NETWORK_ALIVE) != 0)
    {
        APP_LOG_ERROR("Monitor fault: Network task no alive\r\n");
    }

    if ((missing_bits & APP_EVENT_SENSOR_ALIVE) != 0)
    {
        APP_LOG_ERROR("Monitor fault: Sensor task no alive\r\n");
    }

    if ((missing_bits & APP_EVENT_STORAGE_ALIVE) != 0)
    {
        APP_LOG_ERROR("Monitor fault: Storage task no alive\r\n");
    }
}

static void App_Monitor_FeedWatchdog(void)
{
    HAL_IWDG_Refresh(&hiwdg);
}

static void App_CheckCreateResult(BaseType_t ret, const char *name)
{
    if (ret != pdPASS)
    {
        APP_LOG_ERROR("%s task create failed\r\n", name);
    }
    else
    {
        APP_LOG_BOOT("%s task create OK\r\n", name);
    }

    configASSERT(ret == pdPASS);
}

