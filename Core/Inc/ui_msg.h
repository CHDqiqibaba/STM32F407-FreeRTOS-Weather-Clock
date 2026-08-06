#ifndef __UI_MSG_H
#define __UI_MSG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "ui_app.h"

typedef enum
{
    UI_MSG_LOG_ADD = 0,
    UI_MSG_WEATHER_UPDATE,
    UI_MSG_WEATHER_ERROR,
    UI_MSG_AHT20_UPDATE,
    UI_MSG_LPS22HH_UPDATE,
    UI_MSG_LIS2DH12_UPDATE,
    UI_MSG_OPT3001_UPDATE,
    UI_MSG_LATEST_RECORD_UPDATE,
    UI_MSG_SETTINGS_UPDATE,
    UI_MSG_CLEAR_LOG,
    UI_MSG_TIME_REFRESH
} UI_MsgType_t;

typedef struct
{
    UI_MsgType_t type;

    union
    {
        struct
        {
            UI_EventType_t type;
            char text[64];
        } log;

        UI_Weather_t weather;

        struct
        {
            char text[24];
        } weather_error;

        struct
        {
            int32_t temp_x100;
            uint32_t humi_x100;
        } aht20;

        struct
        {
            int32_t pressure_x100;
        } lps22hh;

        struct
        {
            int32_t x_mg;
            int32_t y_mg;
            int32_t z_mg;
            int32_t motion;
        } lis2dh12;

        struct
        {
            uint32_t lux_x100;
        } opt3001;

        UI_Record_t record;
        UI_Settings_t settings;
    } data;
} UI_Msg_t;

void UI_Msg_Init(void);
void UI_Msg_Process(void);

uint8_t UI_Msg_Post(const UI_Msg_t *msg);
uint8_t UI_Msg_PostLog(UI_EventType_t type, const char *text);
uint8_t UI_Msg_PostWeather(const UI_Weather_t *weather);
uint8_t UI_Msg_PostWeatherError(const char *text);
uint8_t UI_Msg_PostAHT20(int32_t temp_x100, uint32_t humi_x100);
uint8_t UI_Msg_PostLPS22HH(int32_t pressure_x100);
uint8_t UI_Msg_PostLIS2DH12(int32_t x_mg,
                            int32_t y_mg,
                            int32_t z_mg,
                            int32_t motion);
uint8_t UI_Msg_PostOPT3001(uint32_t lux_x100);
uint8_t UI_Msg_PostLatestRecord(const UI_Record_t *record);
uint8_t UI_Msg_PostSettings(const UI_Settings_t *settings);
uint8_t UI_Msg_PostClearLog(void);
uint8_t UI_Msg_PostTimeRefresh(void);

#ifdef __cplusplus
}
#endif

#endif
