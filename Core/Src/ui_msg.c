#include "ui_msg.h"

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "app_log.h"
#include "app_time.h"

#define UI_MSG_QUEUE_LEN 16
#define UI_MSG_SEND_TIMEOUT_MS 10

static QueueHandle_t s_ui_msg_queue;

static void UI_Msg_CopyText(char *dst, uint16_t dst_size, const char *src)
{
    if (dst == NULL || dst_size == 0)
    {
        return;
    }

    dst[0] = '\0';

    if (src == NULL)
    {
        return;
    }

    strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

void UI_Msg_Init(void)
{
    s_ui_msg_queue = xQueueCreate(UI_MSG_QUEUE_LEN, sizeof(UI_Msg_t));
    if (s_ui_msg_queue == NULL)
    {
        APP_LOG_ERROR("UI message queue create failed\r\n");
    }
    configASSERT(s_ui_msg_queue != NULL);
}

uint8_t UI_Msg_Post(const UI_Msg_t *msg)
{
    if (msg == NULL || s_ui_msg_queue == NULL)
    {
        return 1;
    }

    if (xQueueSend(s_ui_msg_queue,
                   msg,
                   pdMS_TO_TICKS(UI_MSG_SEND_TIMEOUT_MS)) != pdPASS)
    {
        return 2;
    }

    return 0;
}

uint8_t UI_Msg_PostLog(UI_EventType_t type, const char *text)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_LOG_ADD;
    msg.data.log.type = type;
    UI_Msg_CopyText(msg.data.log.text,
                    sizeof(msg.data.log.text),
                    text);

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostWeather(const UI_Weather_t *weather)
{
    UI_Msg_t msg;

    if (weather == NULL)
    {
        return 1;
    }

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_WEATHER_UPDATE;
    msg.data.weather = *weather;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostWeatherError(const char *text)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_WEATHER_ERROR;
    UI_Msg_CopyText(msg.data.weather_error.text,
                    sizeof(msg.data.weather_error.text),
                    text);

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostAHT20(int32_t temp_x100, uint32_t humi_x100)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_AHT20_UPDATE;
    msg.data.aht20.temp_x100 = temp_x100;
    msg.data.aht20.humi_x100 = humi_x100;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostLPS22HH(int32_t pressure_x100)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_LPS22HH_UPDATE;
    msg.data.lps22hh.pressure_x100 = pressure_x100;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostLIS2DH12(int32_t x_mg,
                            int32_t y_mg,
                            int32_t z_mg,
                            int32_t motion)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_LIS2DH12_UPDATE;
    msg.data.lis2dh12.x_mg = x_mg;
    msg.data.lis2dh12.y_mg = y_mg;
    msg.data.lis2dh12.z_mg = z_mg;
    msg.data.lis2dh12.motion = motion;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostOPT3001(uint32_t lux_x100)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_OPT3001_UPDATE;
    msg.data.opt3001.lux_x100 = lux_x100;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostLatestRecord(const UI_Record_t *record)
{
    UI_Msg_t msg;

    if (record == NULL)
    {
        return 1;
    }

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_LATEST_RECORD_UPDATE;
    msg.data.record = *record;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostSettings(const UI_Settings_t *settings)
{
    UI_Msg_t msg;

    if (settings == NULL)
    {
        return 1;
    }

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_SETTINGS_UPDATE;
    msg.data.settings = *settings;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostClearLog(void)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_CLEAR_LOG;

    return UI_Msg_Post(&msg);
}

uint8_t UI_Msg_PostTimeRefresh(void)
{
    UI_Msg_t msg;

    memset(&msg, 0, sizeof(msg));
    msg.type = UI_MSG_TIME_REFRESH;

    return UI_Msg_Post(&msg);
}

void UI_Msg_Process(void)
{
    UI_Msg_t msg;

    while (s_ui_msg_queue != NULL &&
           xQueueReceive(s_ui_msg_queue, &msg, 0) == pdPASS)
    {
        switch (msg.type)
        {
            case UI_MSG_LOG_ADD:
                UI_App_AddLog(msg.data.log.type, msg.data.log.text);
                break;

            case UI_MSG_WEATHER_UPDATE:
                UI_App_UpdateWeather(&msg.data.weather);
                break;

            case UI_MSG_WEATHER_ERROR:
                UI_App_ShowWeatherError(msg.data.weather_error.text);
                break;

            case UI_MSG_AHT20_UPDATE:
                UI_App_UpdateAHT20(msg.data.aht20.temp_x100,
                                   msg.data.aht20.humi_x100);
                break;

            case UI_MSG_LPS22HH_UPDATE:
                UI_App_UpdateLPS22HH(msg.data.lps22hh.pressure_x100);
                break;

            case UI_MSG_LIS2DH12_UPDATE:
                UI_App_UpdateLIS2DH12(msg.data.lis2dh12.x_mg,
                                      msg.data.lis2dh12.y_mg,
                                      msg.data.lis2dh12.z_mg,
                                      msg.data.lis2dh12.motion);
                break;

            case UI_MSG_OPT3001_UPDATE:
                UI_App_UpdateOPT3001(msg.data.opt3001.lux_x100);
                break;

            case UI_MSG_LATEST_RECORD_UPDATE:
                UI_App_UpdateLatestRecord(&msg.data.record);
                break;

            case UI_MSG_SETTINGS_UPDATE:
                UI_App_UpdateSettings(&msg.data.settings);
                break;

            case UI_MSG_CLEAR_LOG:
                UI_App_ClearLog();
                break;

            case UI_MSG_TIME_REFRESH:
                App_UpdateTimeUI();
                break;

            default:
                break;
        }
    }
}
