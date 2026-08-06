#ifndef __UI_APP_H__
#define __UI_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "gui_guider.h"

#define UI_APP_LOG_MAX_LINES  7

typedef enum
{
    UI_NET_DISCONNECTED = 0,
    UI_NET_CONNECTED
} UI_NetState_t;

typedef enum
{
    UI_SAVE_UNKNOWN = 0,
    UI_SAVE_OK,
    UI_SAVE_FAILED
} UI_SaveState_t;

typedef enum
{
    UI_EVENT_INFO = 0,
    UI_EVENT_WIFI,
    UI_EVENT_WEATHER,
    UI_EVENT_SENSOR,
    UI_EVENT_EEPROM,
    UI_EVENT_ERROR
} UI_EventType_t;

typedef struct
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} UI_Time_t;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    const char *week;
} UI_Date_t;

typedef struct
{
    char city[24];
    char weather[24];
    int16_t temperature;
    char last_update[24];
    char ip[24];
    char ssid[32];        // 新增：真实 WiFi 名称
    UI_NetState_t net_state;
} UI_Weather_t;

typedef struct
{
    int32_t temp_x100;
    uint32_t humi_x100;
    uint32_t light_lx;
    int32_t pressure_x100;
    char motion[16];
    UI_SaveState_t save_state;
} UI_Sensor_t;

typedef struct
{
    uint32_t sequence;
    int32_t temp_x100;
    uint32_t humi_x100;
    uint32_t uptime_ms;
    uint32_t unix_time;
    char time_text[24];
    bool valid;
} UI_Record_t;

typedef struct
{
    char ssid[32];
    uint8_t brightness_percent;
    char version[16];
} UI_Settings_t;

typedef struct
{
    UI_Time_t time;
    UI_Date_t date;
    UI_Weather_t weather;
    UI_Sensor_t sensor;
    UI_Record_t latest_record;
    UI_Settings_t settings;
} UI_AppData_t;

void UI_App_Init(lv_ui *ui);
void UI_App_Process(void);

void UI_App_UpdateAll(const UI_AppData_t *data);

void UI_App_UpdateTime(const UI_Time_t *time);
void UI_App_UpdateDate(const UI_Date_t *date);

void UI_App_UpdateSensor(const UI_Sensor_t *sensor);


void UI_App_UpdateAHT20(int32_t temp_x100, uint32_t humi_x100);
void UI_App_UpdateLPS22HH(int32_t pressure_x100);
void UI_App_UpdateLIS2DH12(int32_t x_mg, int32_t y_mg, int32_t z_mg, int32_t motion);
void UI_App_UpdateOPT3001(uint32_t lux_x100);

void UI_App_UpdateWeather(const UI_Weather_t *weather);
	
void UI_App_ShowSensorError(void);
void UI_App_ShowWeatherError(const char *text);

void UI_App_UpdateLatestRecord(const UI_Record_t *record);
void UI_App_UpdateSettings(const UI_Settings_t *settings);

void UI_App_AddLog(UI_EventType_t type, const char *text);
void UI_App_ClearLog(void);


uint8_t UI_App_TakeWeatherRefreshRequest(void);
uint8_t UI_App_TakeSensorRefreshRequest(void);
uint8_t UI_App_TakeManualSaveRequest(void);
uint8_t UI_App_TakeTimeSyncRequest(void);
uint8_t UI_App_TakeWifiConnectRequest(void);
uint8_t UI_App_TakeClearLogRequest(void);
uint8_t UI_App_TakeBrightnessChanged(uint8_t *brightness_percent);

#ifdef __cplusplus
}
#endif

#endif
