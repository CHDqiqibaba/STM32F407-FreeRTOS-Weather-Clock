#include "app_tasks.h"

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

#include "aht20.h"
#include "lps22hh.h"
#include "lis2dh12.h"
#include "opt3001.h"
#include "weather.h"
#include "app_log.h"
#include "app_time.h"

#include "lcd_st7789.h"
#include "font.h"
#include "eeprom.h"
#include "esp_at.h"
#include "ft5336.h"

#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lcd_backlight.h"
#include "ui_app.h"
#include "ui_msg.h"

#define WIFI_SSID       "iphone 15"
#define WIFI_PASSWORD   "zhangfeifan"

#define WEATHER_URL_FMT "https://api.seniverse.com/v3/weather/now.json?key=SYgba612KT1UrfQkA&location=%s&language=en&unit=c"

#define NET_AT_TIMEOUT_MS              1000U
#define NET_WIFI_TIMEOUT_MS            20000U
#define NET_HTTP_TIMEOUT_MS            30000U
#define NET_HTTP_AT_TIMEOUT_MS         (NET_HTTP_TIMEOUT_MS + 1000U)
#define NET_SNTP_CONFIG_TIMEOUT_MS     3000U
#define NET_SNTP_GET_TIMEOUT_MS        1500U
#define NET_SNTP_RETRY_MAX             8U
#define NET_SNTP_RETRY_DELAY_MS        1000U
#define NET_SNTP_FIRST_DELAY_MS        1000U
#define NET_RECONNECT_DELAY_1_MS       5000U
#define NET_RECONNECT_DELAY_2_MS       15000U
#define NET_RECONNECT_DELAY_3_MS       30000U
#define NET_WIFI_CHECK_PERIOD_MS       30000U

#define APP_WEATHER_INTERVAL_MIN_DEFAULT        60U
#define APP_WEATHER_INTERVAL_MIN_MIN            5U
#define APP_WEATHER_INTERVAL_MIN_MAX            180U

#define APP_SENSOR_INTERVAL_SEC_DEFAULT         600U
#define APP_SENSOR_INTERVAL_SEC_MIN             10U
#define APP_SENSOR_INTERVAL_SEC_MAX             3600U

#define APP_HISTORY_INTERVAL_SEC_DEFAULT        3600U
#define APP_HISTORY_INTERVAL_SEC_MIN            300U
#define APP_HISTORY_INTERVAL_SEC_MAX            65535U

#define APP_BRIGHTNESS_PERCENT_DEFAULT          80U
#define APP_BRIGHTNESS_PERCENT_MIN              5U
#define APP_BRIGHTNESS_PERCENT_MAX              100U

#define APP_WEATHER_CITY_DEFAULT                "beijing"

#define APP_SENSOR_VALID_AHT20                  (1U << 0)
#define APP_SENSOR_VALID_LPS22HH                (1U << 1)
#define APP_SENSOR_VALID_LIS2DH12               (1U << 2)
#define APP_SENSOR_VALID_OPT3001                (1U << 3)
#define APP_SENSOR_MUTEX_TIMEOUT_MS             1000U

AHT20_Data_t aht20_data;
LPS22HH_Data_t lps22hh_data;
LIS2DH12_Data_t lis2dh12_data;
OPT3001_Data_t opt3001_data;

Weather_Now_t weather_now;
UI_Weather_t ui_weather;

static uint32_t time_ui_last_tick = 0;
lv_ui guider_ui;
uint8_t wifi_ok = 0;
uint8_t brightness_percent;

EEPROM_AppConfig_t app_config;
EEPROM_HistoryRecord_t latest_history;
EEPROM_EventRecord_t latest_event;

static uint8_t config_dirty = 0;
static uint32_t config_dirty_tick = 0;
static uint8_t sensor_valid_mask = 0;
static uint32_t sensor_snapshot_tick = 0;
static uint32_t sensor_next_sample_tick = 0;
static uint32_t storage_next_history_tick = 0;
static SemaphoreHandle_t sensor_mutex = NULL;
static uint8_t sensor_init_attempted = 0;
static uint8_t sensor_init_ok_mask = 0;

typedef enum
{
    APP_NET_STATE_IDLE = 0,
    APP_NET_STATE_DELAY,
    APP_NET_STATE_AT_TEST_START,
    APP_NET_STATE_AT_TEST_WAIT,
    APP_NET_STATE_ECHO_OFF_START,
    APP_NET_STATE_ECHO_OFF_WAIT,
    APP_NET_STATE_SET_MODE_START,
    APP_NET_STATE_SET_MODE_WAIT,
    APP_NET_STATE_WIFI_START,
    APP_NET_STATE_WIFI_WAIT,
    APP_NET_STATE_SNTP_CFG_START,
    APP_NET_STATE_SNTP_CFG_WAIT,
    APP_NET_STATE_SNTP_GET_START,
    APP_NET_STATE_SNTP_GET_WAIT,
    APP_NET_STATE_WEATHER_START,
    APP_NET_STATE_WEATHER_WAIT,
    APP_NET_STATE_QUERY_SSID_START,
    APP_NET_STATE_QUERY_SSID_WAIT,
    APP_NET_STATE_QUERY_IP_START,
    APP_NET_STATE_QUERY_IP_WAIT,
    APP_NET_STATE_WIFI_CHECK_START,
    APP_NET_STATE_WIFI_CHECK_WAIT
} App_NetState_t;

typedef enum
{
    APP_NET_FLOW_NONE = 0,
    APP_NET_FLOW_CONNECT,
    APP_NET_FLOW_TIME_SYNC,
    APP_NET_FLOW_WEATHER,
    APP_NET_FLOW_WIFI_CHECK
} App_NetFlow_t;

static App_NetState_t net_state = APP_NET_STATE_IDLE;
static App_NetFlow_t net_flow = APP_NET_FLOW_NONE;
static App_NetState_t net_delay_next_state = APP_NET_STATE_IDLE;
static uint32_t net_delay_start_tick = 0;
static uint32_t net_delay_ms = 0;

static uint8_t net_pending_connect = 0;
static uint8_t net_pending_connect_time = 0;
static uint8_t net_pending_connect_weather = 0;
static uint8_t net_pending_time_sync = 0;
static uint8_t net_pending_weather = 0;

static uint8_t net_connect_time_after_ok = 0;
static uint8_t net_connect_weather_after_ok = 0;
static uint8_t net_weather_after_time = 0;
static uint8_t net_sntp_attempt = 0;
static uint8_t net_auto_reconnect_enable = 1;
static uint8_t net_reconnect_index = 0;
static uint32_t net_next_reconnect_tick = 0;
static uint32_t net_next_wifi_check_tick = 0;
static uint32_t net_next_weather_tick = 0;

static char net_cmd_buf[512];
static char net_weather_url[220];
static char net_weather_response[1024];
static char net_time_response[256];

static void App_Net_Process(void);
static void App_Net_StartPendingIfIdle(void);
static void App_Net_RequestConnect(uint8_t sync_time_after_ok,
                                   uint8_t refresh_weather_after_ok);
static void App_Net_RequestTimeSync(void);
static void App_Net_RequestWeather(void);
static void App_Net_StartConnectFlow(void);
static void App_Net_StartTimeFlow(uint8_t weather_after_time);
static void App_Net_StartWeatherFlow(void);
static void App_Net_FinishFlow(void);
static void App_Net_FinishTimeFlow(void);
static void App_Net_StartDelay(App_NetState_t next_state, uint32_t delay_ms);
static uint8_t App_Net_StartCommand(const char *cmd,
                                    const char *expect,
                                    uint32_t timeout_ms,
                                    App_NetState_t wait_state);
static void App_Net_BuildWeatherUrl(char *url, uint16_t url_size);
static void App_Net_PeriodicWeatherProcess(void);
static uint8_t App_Net_IsBusy(void);
static uint8_t App_Net_IsConnecting(void);
static uint8_t App_Net_ResultIsError(ESP_AT_AsyncResult_t result);
static const char *App_Net_ResultName(ESP_AT_AsyncResult_t result);
static void App_Net_HandleWifiFail(const char *reason);
static void App_Net_HandleTimeFail(const char *reason);
static void App_Net_HandleWeatherFail(const char *reason);
static void App_Net_HandleWeatherResponse(void);
static void App_Net_PostWeatherDone(void);
static void App_Net_AutoReconnectProcess(void);
static void App_Net_AutoWifiCheckProcess(void);
static void App_Net_ScheduleReconnect(void);
static void App_Net_ResetReconnect(void);
static uint32_t App_Net_GetReconnectDelay(void);
static uint16_t App_ClampU16(uint16_t value,
                             uint16_t min_value,
                             uint16_t max_value,
                             uint16_t default_value);
static uint32_t App_ConfigWeatherPeriodMs(void);
static uint32_t App_ConfigSensorPeriodMs(void);
static uint32_t App_ConfigHistoryPeriodMs(void);
static const char *App_ConfigWeatherCity(void);
static uint8_t App_ClampBrightness(uint8_t percent);
static void App_NormalizeConfig(uint8_t save_if_changed);
static uint32_t App_GetUnixTimeOrZero(void);
static void App_AddLog(UI_EventType_t ui_type,
                       EEPROM_EventType_t eeprom_type,
                       const char *text);
static uint8_t App_SaveCurrentHistory(void);
static void App_UpdateLatestRecordFromHistory(const EEPROM_HistoryRecord_t *history);
static uint8_t App_ReadSensorsToLatest(void);
static uint8_t App_FillHistoryFromLatestData(EEPROM_HistoryRecord_t *record);
static void App_Sensor_InitDevices(void);
static void App_Sensor_PeriodicProcess(void);
static void App_Storage_PeriodicHistoryProcess(void);
static uint8_t App_TimeExpired(uint32_t now, uint32_t target);
static void App_CopyText(char *dst, uint16_t dst_size, const char *src);
static uint8_t App_SensorMutexInit(void);
static uint8_t App_SensorLock(void);
static void App_SensorUnlock(void);

static uint8_t App_IsSchedulerRunning(void)
{
    return (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED);
}

static uint8_t App_SensorMutexInit(void)
{
    if (sensor_mutex == NULL)
    {
        sensor_mutex = xSemaphoreCreateMutex();
        if (sensor_mutex == NULL)
        {
            APP_LOG_ERROR("Sensor mutex create failed\r\n");
            return 1;
        }
    }

    return 0;
}

static uint8_t App_SensorLock(void)
{
    if (App_SensorMutexInit() != 0)
    {
        return 1;
    }

    if (!App_IsSchedulerRunning())
    {
        return 0;
    }

    if (xSemaphoreTake(sensor_mutex,
                       pdMS_TO_TICKS(APP_SENSOR_MUTEX_TIMEOUT_MS)) != pdTRUE)
    {
        APP_LOG_ERROR("Sensor mutex take timeout\r\n");
        return 2;
    }

    return 0;
}

static void App_SensorUnlock(void)
{
    if (sensor_mutex == NULL)
    {
        return;
    }

    if (!App_IsSchedulerRunning())
    {
        return;
    }

    (void)xSemaphoreGive(sensor_mutex);
}

static void App_Sensor_InitDevices(void)
{
    uint8_t init_aht20;
    uint8_t init_lps22hh;
    uint8_t init_lis2dh12;
    uint8_t init_opt3001;

    if (sensor_init_attempted)
    {
        return;
    }

    sensor_init_attempted = 1;
    sensor_init_ok_mask = 0;

    APP_LOG_BOOT("Sensor init start\r\n");

    if (App_SensorLock() != 0)
    {
        APP_LOG_ERROR("Sensor init skipped: I2C busy\r\n");
        return;
    }

    HAL_I2C_DeInit(&hi2c2);
    MX_I2C2_Init();

    APP_LOG_BOOT("AHT20 init start\r\n");
    init_aht20 = AHT20_Init();
    if (init_aht20 == 0U)
    {
        sensor_init_ok_mask |= APP_SENSOR_VALID_AHT20;
        APP_LOG_BOOT("AHT20 init OK\r\n");
    }
    else
    {
        APP_LOG_ERROR("AHT20 init failed, code=%u\r\n", init_aht20);
    }

    APP_LOG_BOOT("LPS22HH init start\r\n");
    init_lps22hh = LPS22HH_Init();
    if (init_lps22hh == 0U)
    {
        sensor_init_ok_mask |= APP_SENSOR_VALID_LPS22HH;
        APP_LOG_BOOT("LPS22HH init OK\r\n");
    }
    else
    {
        APP_LOG_ERROR("LPS22HH init failed, code=%u\r\n", init_lps22hh);
    }

    APP_LOG_BOOT("LIS2DH12 init start\r\n");
    init_lis2dh12 = LIS2DH12_Init();
    if (init_lis2dh12 == 0U)
    {
        sensor_init_ok_mask |= APP_SENSOR_VALID_LIS2DH12;
        APP_LOG_BOOT("LIS2DH12 init OK\r\n");
    }
    else
    {
        APP_LOG_ERROR("LIS2DH12 init failed, code=%u\r\n", init_lis2dh12);
    }

    APP_LOG_BOOT("OPT3001 init start\r\n");
    init_opt3001 = OPT3001_Init();
    if (init_opt3001 == 0U)
    {
        sensor_init_ok_mask |= APP_SENSOR_VALID_OPT3001;
        APP_LOG_BOOT("OPT3001 init OK\r\n");
    }
    else
    {
        APP_LOG_ERROR("OPT3001 init failed, code=%u\r\n", init_opt3001);
    }

    App_SensorUnlock();

    if (sensor_init_ok_mask == (APP_SENSOR_VALID_AHT20 |
                                APP_SENSOR_VALID_LPS22HH |
                                APP_SENSOR_VALID_LIS2DH12 |
                                APP_SENSOR_VALID_OPT3001))
    {
        APP_LOG_BOOT("Sensor init done\r\n");
    }
    else
    {
        APP_LOG_ERROR("Sensor init partial, mask=0x%02X\r\n", sensor_init_ok_mask);
    }
}

static void App_CopyText(char *dst, uint16_t dst_size, const char *src)
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

static uint8_t App_TimeExpired(uint32_t now, uint32_t target)
{
    return ((int32_t)(now - target) >= 0);
}

static uint16_t App_ClampU16(uint16_t value,
                             uint16_t min_value,
                             uint16_t max_value,
                             uint16_t default_value)
{
    if (value == 0U)
    {
        return default_value;
    }

    if (value < min_value)
    {
        return min_value;
    }

    if (value > max_value)
    {
        return max_value;
    }

    return value;
}

static uint32_t App_ConfigWeatherPeriodMs(void)
{
    uint16_t min;

    min = App_ClampU16(app_config.weather_interval_min,
                       APP_WEATHER_INTERVAL_MIN_MIN,
                       APP_WEATHER_INTERVAL_MIN_MAX,
                       APP_WEATHER_INTERVAL_MIN_DEFAULT);

    return (uint32_t)min * 60UL * 1000UL;
}

static uint32_t App_ConfigSensorPeriodMs(void)
{
    uint16_t sec;

    sec = App_ClampU16(app_config.sensor_interval_sec,
                       APP_SENSOR_INTERVAL_SEC_MIN,
                       APP_SENSOR_INTERVAL_SEC_MAX,
                       APP_SENSOR_INTERVAL_SEC_DEFAULT);

    return (uint32_t)sec * 1000UL;
}

static uint32_t App_ConfigHistoryPeriodMs(void)
{
    uint16_t sec;

    sec = App_ClampU16(app_config.history_save_interval_sec,
                       APP_HISTORY_INTERVAL_SEC_MIN,
                       APP_HISTORY_INTERVAL_SEC_MAX,
                       APP_HISTORY_INTERVAL_SEC_DEFAULT);

    return (uint32_t)sec * 1000UL;
}

static const char *App_ConfigWeatherCity(void)
{
    app_config.weather_city[sizeof(app_config.weather_city) - 1U] = '\0';

    if (app_config.weather_city[0] == '\0')
    {
        return APP_WEATHER_CITY_DEFAULT;
    }

    return app_config.weather_city;
}

static uint8_t App_ClampBrightness(uint8_t percent)
{
    if (percent < APP_BRIGHTNESS_PERCENT_MIN)
    {
        return APP_BRIGHTNESS_PERCENT_MIN;
    }

    if (percent > APP_BRIGHTNESS_PERCENT_MAX)
    {
        return APP_BRIGHTNESS_PERCENT_MAX;
    }

    return percent;
}

static void App_NormalizeConfig(uint8_t save_if_changed)
{
    uint8_t changed = 0;
    uint16_t value;
    uint8_t brightness;

    if (app_config.brightness_percent == 0U ||
        app_config.brightness_percent > APP_BRIGHTNESS_PERCENT_MAX)
    {
        app_config.brightness_percent = APP_BRIGHTNESS_PERCENT_DEFAULT;
        changed = 1;
    }

    brightness = App_ClampBrightness(app_config.brightness_percent);
    if (app_config.brightness_percent != brightness)
    {
        app_config.brightness_percent = brightness;
        changed = 1;
    }

    value = App_ClampU16(app_config.weather_interval_min,
                         APP_WEATHER_INTERVAL_MIN_MIN,
                         APP_WEATHER_INTERVAL_MIN_MAX,
                         APP_WEATHER_INTERVAL_MIN_DEFAULT);
    if (app_config.weather_interval_min != value)
    {
        app_config.weather_interval_min = value;
        changed = 1;
    }

    value = App_ClampU16(app_config.sensor_interval_sec,
                         APP_SENSOR_INTERVAL_SEC_MIN,
                         APP_SENSOR_INTERVAL_SEC_MAX,
                         APP_SENSOR_INTERVAL_SEC_DEFAULT);
    if (app_config.sensor_interval_sec != value)
    {
        app_config.sensor_interval_sec = value;
        changed = 1;
    }

    value = App_ClampU16(app_config.history_save_interval_sec,
                         APP_HISTORY_INTERVAL_SEC_MIN,
                         APP_HISTORY_INTERVAL_SEC_MAX,
                         APP_HISTORY_INTERVAL_SEC_DEFAULT);
    if (app_config.history_save_interval_sec != value)
    {
        app_config.history_save_interval_sec = value;
        changed = 1;
    }

    app_config.weather_city[sizeof(app_config.weather_city) - 1U] = '\0';
    if (app_config.weather_city[0] == '\0')
    {
        App_CopyText(app_config.weather_city,
                     sizeof(app_config.weather_city),
                     APP_WEATHER_CITY_DEFAULT);
        changed = 1;
    }

    if (changed && save_if_changed)
    {
        if (EEPROM_SaveConfig(&app_config) == 0)
        {
            APP_LOG_BOOT("EEPROM config normalized\r\n");
        }
        else
        {
            APP_LOG_ERROR("EEPROM config normalize save failed\r\n");
        }
    }
}

static uint32_t App_GetUnixTimeOrZero(void)
{
    uint32_t unix_time = 0;

    (void)App_Time_GetUnix(&unix_time);

    return unix_time;
}

static void App_Net_BuildWeatherUrl(char *url, uint16_t url_size)
{
    if (url == NULL || url_size == 0U)
    {
        return;
    }

    snprintf(url,
             url_size,
             WEATHER_URL_FMT,
             App_ConfigWeatherCity());
}

static void App_Net_PeriodicWeatherProcess(void)
{
    uint32_t now;
    uint32_t period_ms;

    if (!wifi_ok || App_Net_IsBusy())
    {
        return;
    }

    now = HAL_GetTick();
    period_ms = App_ConfigWeatherPeriodMs();

    if (net_next_weather_tick == 0U)
    {
        net_next_weather_tick = now + period_ms;
        return;
    }

    if (!App_TimeExpired(now, net_next_weather_tick))
    {
        return;
    }

    net_next_weather_tick = now + period_ms;
    App_Net_RequestWeather();
}

static uint8_t App_ReadSensorsToLatest(void)
{
    AHT20_Data_t new_aht20 = {0};
    LPS22HH_Data_t new_lps22hh = {0};
    LIS2DH12_Data_t new_lis2dh12 = {0};
    OPT3001_Data_t new_opt3001 = {0};
    uint8_t result_AHT20;
    uint8_t result_LPS22HH;
    uint8_t result_LIS2DH12;
    uint8_t result_OPT3001;
    uint8_t valid_mask = 0;
    uint32_t snapshot_tick;

    if (!sensor_init_attempted)
    {
        App_Sensor_InitDevices();
    }

    if (sensor_init_ok_mask == 0U)
    {
        APP_LOG_ERROR("Sensor read skipped: init failed\r\n");
        App_AddLog(UI_EVENT_ERROR,
                   EEPROM_EVENT_ERROR,
                   "Sensor init failed");
        return 3;
    }

    if (App_SensorLock() != 0)
    {
        App_AddLog(UI_EVENT_ERROR,
                   EEPROM_EVENT_ERROR,
                   "Sensor I2C busy");
        return 2;
    }

    result_AHT20 = ((sensor_init_ok_mask & APP_SENSOR_VALID_AHT20) != 0U) ?
                   AHT20_Read(&new_aht20) : 0xFFU;
    result_LPS22HH = ((sensor_init_ok_mask & APP_SENSOR_VALID_LPS22HH) != 0U) ?
                     LPS22HH_Read(&new_lps22hh) : 0xFFU;
    result_LIS2DH12 = ((sensor_init_ok_mask & APP_SENSOR_VALID_LIS2DH12) != 0U) ?
                      LIS2DH12_Read(&new_lis2dh12) : 0xFFU;
    result_OPT3001 = ((sensor_init_ok_mask & APP_SENSOR_VALID_OPT3001) != 0U) ?
                     OPT3001_Read(&new_opt3001) : 0xFFU;

    App_SensorUnlock();

    if (result_AHT20 == 0)
    {
        valid_mask |= APP_SENSOR_VALID_AHT20;
    }

    if (result_LPS22HH == 0)
    {
        valid_mask |= APP_SENSOR_VALID_LPS22HH;
    }

    if (result_LIS2DH12 == 0)
    {
        valid_mask |= APP_SENSOR_VALID_LIS2DH12;
    }

    if (result_OPT3001 == 0)
    {
        valid_mask |= APP_SENSOR_VALID_OPT3001;
    }

    if (valid_mask == 0U)
    {
        APP_LOG_ERROR("All sensor read failed\r\n");
        App_AddLog(UI_EVENT_ERROR,
                   EEPROM_EVENT_ERROR,
                   "All sensor read failed");
        return 1;
    }

    snapshot_tick = HAL_GetTick();

    taskENTER_CRITICAL();
    if ((valid_mask & APP_SENSOR_VALID_AHT20) != 0U)
    {
        aht20_data = new_aht20;
    }

    if ((valid_mask & APP_SENSOR_VALID_LPS22HH) != 0U)
    {
        lps22hh_data = new_lps22hh;
    }

    if ((valid_mask & APP_SENSOR_VALID_LIS2DH12) != 0U)
    {
        lis2dh12_data = new_lis2dh12;
    }

    if ((valid_mask & APP_SENSOR_VALID_OPT3001) != 0U)
    {
        opt3001_data = new_opt3001;
    }

    sensor_valid_mask = valid_mask;
    sensor_snapshot_tick = snapshot_tick;
    taskEXIT_CRITICAL();

    if (result_AHT20 == 0)
    {
        AHT20_PrintValue(&new_aht20);
        UI_Msg_PostAHT20(new_aht20.temperature_x100,
                         new_aht20.humidity_x100);
    }
    else
    {
        APP_LOG_ERROR("AHT20 read failed, code=%u\r\n", result_AHT20);
    }

    if (result_LPS22HH == 0)
    {
        LPS22HH_PrintValue(&new_lps22hh);
        UI_Msg_PostLPS22HH(new_lps22hh.pressure_x100);
    }
    else
    {
        APP_LOG_ERROR("LPS22HH read failed, code=%u\r\n", result_LPS22HH);
    }

    if (result_LIS2DH12 == 0)
    {
        LIS2DH12_PrintValue(&new_lis2dh12);
        UI_Msg_PostLIS2DH12(new_lis2dh12.x_mg,
                            new_lis2dh12.y_mg,
                            new_lis2dh12.z_mg,
                            new_lis2dh12.motion);
    }
    else
    {
        APP_LOG_ERROR("LIS2DH12 read failed, code=%u\r\n", result_LIS2DH12);
    }

    if (result_OPT3001 == 0)
    {
        OPT3001_PrintValue(&new_opt3001);
        UI_Msg_PostOPT3001(new_opt3001.lux_x100);
    }
    else
    {
        APP_LOG_ERROR("OPT3001 read failed, code=%u\r\n", result_OPT3001);
    }

    return 0;
}

static uint8_t App_FillHistoryFromLatestData(EEPROM_HistoryRecord_t *record)
{
    AHT20_Data_t snapshot_aht20 = {0};
    LPS22HH_Data_t snapshot_lps22hh = {0};
    LIS2DH12_Data_t snapshot_lis2dh12 = {0};
    OPT3001_Data_t snapshot_opt3001 = {0};
    uint8_t valid_mask;
    uint32_t snapshot_tick;
    int16_t weather_temperature;

    if (record == NULL)
    {
        return 1;
    }

    taskENTER_CRITICAL();
    valid_mask = sensor_valid_mask;
    snapshot_tick = sensor_snapshot_tick;
    snapshot_aht20 = aht20_data;
    snapshot_lps22hh = lps22hh_data;
    snapshot_lis2dh12 = lis2dh12_data;
    snapshot_opt3001 = opt3001_data;
    weather_temperature = weather_now.temperature;
    taskEXIT_CRITICAL();

    if (valid_mask == 0U)
    {
        return 2;
    }

    memset(record, 0, sizeof(*record));

    record->tick_ms = snapshot_tick;
    if (record->tick_ms == 0U)
    {
        record->tick_ms = HAL_GetTick();
    }

    record->unix_time = App_GetUnixTimeOrZero();

    if ((valid_mask & APP_SENSOR_VALID_AHT20) != 0U)
    {
        record->temperature_x100 = snapshot_aht20.temperature_x100;
        record->humidity_x100 = snapshot_aht20.humidity_x100;
    }

    if ((valid_mask & APP_SENSOR_VALID_LPS22HH) != 0U)
    {
        record->pressure_x100 = snapshot_lps22hh.pressure_x100;
    }

    if ((valid_mask & APP_SENSOR_VALID_LIS2DH12) != 0U)
    {
        record->acc_x_mg = snapshot_lis2dh12.x_mg;
        record->acc_y_mg = snapshot_lis2dh12.y_mg;
        record->acc_z_mg = snapshot_lis2dh12.z_mg;
        record->motion = (uint8_t)snapshot_lis2dh12.motion;
    }

    if ((valid_mask & APP_SENSOR_VALID_OPT3001) != 0U)
    {
        record->lux_x100 = snapshot_opt3001.lux_x100;
    }

    record->weather_temperature = weather_temperature;

    return 0;
}

static void App_Sensor_PeriodicProcess(void)
{
    uint32_t now;
    uint32_t period_ms;

    now = HAL_GetTick();
    period_ms = App_ConfigSensorPeriodMs();

    if (sensor_next_sample_tick == 0U)
    {
        sensor_next_sample_tick = now;
    }

    if (!App_TimeExpired(now, sensor_next_sample_tick))
    {
        return;
    }

    sensor_next_sample_tick = now + period_ms;

    if (App_ReadSensorsToLatest() == 0)
    {
        APP_LOG_INFO("Sensor auto updated\r\n");
    }
}

static void App_Storage_PeriodicHistoryProcess(void)
{
    uint32_t now;
    uint32_t period_ms;

    now = HAL_GetTick();
    period_ms = App_ConfigHistoryPeriodMs();

    if (storage_next_history_tick == 0U)
    {
        storage_next_history_tick = now + period_ms;
        return;
    }

    if (!App_TimeExpired(now, storage_next_history_tick))
    {
        return;
    }

    storage_next_history_tick = now + period_ms;

    if (App_SaveCurrentHistory() == 0)
    {
        APP_LOG_INFO("History auto saved to EEPROM\r\n");
        App_AddLog(UI_EVENT_EEPROM,
                   EEPROM_EVENT_EEPROM,
                   "History auto saved");

        if (EEPROM_ReadLatestHistoryRecord(&latest_history) == 0)
        {
            App_UpdateLatestRecordFromHistory(&latest_history);
        }
    }
    else
    {
        APP_LOG_ERROR("History auto save failed\r\n");
        App_AddLog(UI_EVENT_ERROR,
                   EEPROM_EVENT_ERROR,
                   "History auto save failed");
    }
}

static uint32_t App_Net_GetReconnectDelay(void)
{
    if (net_reconnect_index == 0)
    {
        return NET_RECONNECT_DELAY_1_MS;
    }

    if (net_reconnect_index == 1)
    {
        return NET_RECONNECT_DELAY_2_MS;
    }

    return NET_RECONNECT_DELAY_3_MS;
}

static void App_Net_ScheduleReconnect(void)
{
    uint32_t delay_ms;

    if (!net_auto_reconnect_enable)
    {
        return;
    }

    delay_ms = App_Net_GetReconnectDelay();
    net_next_reconnect_tick = HAL_GetTick() + delay_ms;
    net_next_wifi_check_tick = 0;

    if (net_reconnect_index < 2)
    {
        net_reconnect_index++;
    }

    UI_Msg_PostLog(UI_EVENT_WIFI, "WiFi reconnect scheduled");
}

static void App_Net_ResetReconnect(void)
{
    net_reconnect_index = 0;
    net_next_reconnect_tick = 0;
    net_next_wifi_check_tick = HAL_GetTick() + NET_WIFI_CHECK_PERIOD_MS;
}

static void App_AddLog(UI_EventType_t ui_type,
                       EEPROM_EventType_t eeprom_type,
                       const char *text)
{
    if (text == NULL)
    {
        return;
    }

    if (App_IsSchedulerRunning())
    {
        UI_Msg_PostLog(ui_type, text);
    }
    else
    {
        UI_App_AddLog(ui_type, text);
    }

    EEPROM_SaveEventLog(eeprom_type,
                        text,
                        HAL_GetTick(),
                        App_GetUnixTimeOrZero());
}

static void App_UpdateSettingsUI(void)
{
    UI_Settings_t settings;

    memset(&settings, 0, sizeof(settings));

    App_CopyText(settings.ssid, sizeof(settings.ssid), WIFI_SSID);
    settings.brightness_percent = app_config.brightness_percent;
    App_CopyText(settings.version, sizeof(settings.version), "V1.0");

    if (App_IsSchedulerRunning())
    {
        UI_Msg_PostSettings(&settings);
    }
    else
    {
        UI_App_UpdateSettings(&settings);
    }
}

static uint8_t App_SaveCurrentHistory(void)
{
    EEPROM_HistoryRecord_t record;

    memset(&record, 0, sizeof(record));

    if (sensor_valid_mask == 0U)
    {
        if (App_ReadSensorsToLatest() != 0)
        {
            return 1;
        }
    }

    if (App_FillHistoryFromLatestData(&record) != 0)
    {
        return 2;
    }

    return EEPROM_SaveHistoryRecord(&record);
}

static void App_UpdateLatestRecordFromHistory(const EEPROM_HistoryRecord_t *history)
{
    UI_Record_t ui_record;

    if (history == NULL)
    {
        return;
    }

    memset(&ui_record, 0, sizeof(ui_record));

    ui_record.valid = true;
    ui_record.sequence = history->sequence;
    ui_record.temp_x100 = history->temperature_x100;
    ui_record.humi_x100 = history->humidity_x100;
    ui_record.uptime_ms = history->tick_ms;
    ui_record.unix_time = history->unix_time;
    (void)App_Time_FormatUnixLocal(history->unix_time,
                                   ui_record.time_text,
                                   sizeof(ui_record.time_text));

    if (App_IsSchedulerRunning())
    {
        UI_Msg_PostLatestRecord(&ui_record);
    }
    else
    {
        UI_App_UpdateLatestRecord(&ui_record);
    }
}

static uint8_t App_Net_IsBusy(void)
{
    return (net_state != APP_NET_STATE_IDLE);
}

static uint8_t App_Net_IsConnecting(void)
{
    return (net_flow == APP_NET_FLOW_CONNECT);
}

static uint8_t App_Net_ResultIsError(ESP_AT_AsyncResult_t result)
{
    return (result != ESP_AT_ASYNC_BUSY &&
            result != ESP_AT_ASYNC_OK &&
            result != ESP_AT_ASYNC_IDLE);
}

static const char *App_Net_ResultName(ESP_AT_AsyncResult_t result)
{
    switch (result)
    {
        case ESP_AT_ASYNC_OK:          return "OK";
        case ESP_AT_ASYNC_ERROR:       return "ERROR";
        case ESP_AT_ASYNC_FAIL:        return "FAIL";
        case ESP_AT_ASYNC_OVERFLOW:    return "OVERFLOW";
        case ESP_AT_ASYNC_TIMEOUT:     return "TIMEOUT";
        case ESP_AT_ASYNC_SEND_ERROR:  return "SEND_ERROR";
        case ESP_AT_ASYNC_PARAM_ERROR: return "PARAM_ERROR";
        case ESP_AT_ASYNC_IDLE:        return "IDLE";
        default:                       return "BUSY";
    }
}

static uint8_t App_Net_StartCommand(const char *cmd,
                                    const char *expect,
                                    uint32_t timeout_ms,
                                    App_NetState_t wait_state)
{
    uint8_t ret;

    ret = ESP_AT_AsyncStart(cmd, expect, timeout_ms);
    if (ret != 0)
    {
        APP_LOG_ERROR("ESP async start failed, code=%u\r\n", ret);
        return ret;
    }

    net_state = wait_state;
    return 0;
}

static void App_Net_StartDelay(App_NetState_t next_state, uint32_t delay_ms)
{
    net_delay_next_state = next_state;
    net_delay_ms = delay_ms;
    net_delay_start_tick = HAL_GetTick();
    net_state = APP_NET_STATE_DELAY;
}

static void App_Net_FinishFlow(void)
{
    net_flow = APP_NET_FLOW_NONE;
    net_connect_time_after_ok = 0;
    net_connect_weather_after_ok = 0;
    net_weather_after_time = 0;
    net_sntp_attempt = 0;
    net_state = APP_NET_STATE_IDLE;

    App_Net_StartPendingIfIdle();
}

static void App_Net_FinishTimeFlow(void)
{
    if (net_weather_after_time)
    {
        net_weather_after_time = 0;
        App_Net_StartWeatherFlow();
    }
    else
    {
        App_Net_FinishFlow();
    }
}

static void App_Net_StartConnectFlow(void)
{
    wifi_ok = 0;
    net_flow = APP_NET_FLOW_CONNECT;
    net_connect_time_after_ok = net_pending_connect_time;
    net_connect_weather_after_ok = net_pending_connect_weather;
    net_pending_connect_time = 0;
    net_pending_connect_weather = 0;

    UI_Msg_PostLog(UI_EVENT_WIFI, "WiFi connecting");
    APP_LOG_INFO("WiFi connecting\r\n");

    net_state = APP_NET_STATE_AT_TEST_START;
}

static void App_Net_StartTimeFlow(uint8_t weather_after_time)
{
    net_flow = APP_NET_FLOW_TIME_SYNC;
    net_weather_after_time = weather_after_time;
    net_sntp_attempt = 0;

    UI_Msg_PostLog(UI_EVENT_INFO, "Time sync start");
    APP_LOG_INFO("Time sync start\r\n");

    net_state = APP_NET_STATE_SNTP_CFG_START;
}

static void App_Net_StartWeatherFlow(void)
{
    net_flow = APP_NET_FLOW_WEATHER;

    memset(net_weather_response, 0, sizeof(net_weather_response));
    memset(&weather_now, 0, sizeof(weather_now));
    memset(&ui_weather, 0, sizeof(ui_weather));

    UI_Msg_PostLog(UI_EVENT_WEATHER, "Weather refresh start");
    APP_LOG_INFO("Weather refresh start\r\n");

    net_state = APP_NET_STATE_WEATHER_START;
}

static void App_Net_StartPendingIfIdle(void)
{
    if (App_Net_IsBusy())
    {
        return;
    }

    if (net_pending_connect)
    {
        net_pending_connect = 0;
        App_Net_StartConnectFlow();
        return;
    }

    if (net_pending_time_sync)
    {
        net_pending_time_sync = 0;

        if (wifi_ok)
        {
            App_Net_StartTimeFlow(0);
        }
        else
        {
            APP_LOG_ERROR("Time sync failed: WiFi not connected\r\n");
            UI_Msg_PostLog(UI_EVENT_ERROR, "Time sync failed: WiFi off");
            App_Net_StartPendingIfIdle();
        }

        return;
    }

    if (net_pending_weather)
    {
        net_pending_weather = 0;

        if (wifi_ok)
        {
            App_Net_StartWeatherFlow();
        }
        else
        {
            APP_LOG_ERROR("Weather refresh failed: WiFi not connected\r\n");
            UI_Msg_PostWeatherError("WiFi Error");
            UI_Msg_PostLog(UI_EVENT_ERROR, "Weather refresh failed: WiFi off");
            App_Net_StartPendingIfIdle();
        }
    }

    App_Net_AutoWifiCheckProcess();
    App_Net_AutoReconnectProcess();
}

static void App_Net_RequestConnect(uint8_t sync_time_after_ok,
                                   uint8_t refresh_weather_after_ok)
{
    net_pending_connect = 1;
    net_pending_connect_time = (uint8_t)(net_pending_connect_time || sync_time_after_ok);
    net_pending_connect_weather = (uint8_t)(net_pending_connect_weather || refresh_weather_after_ok);

    if (App_Net_IsBusy())
    {
        UI_Msg_PostLog(UI_EVENT_WIFI, "WiFi request queued");
    }

    App_Net_StartPendingIfIdle();
}

static void App_Net_RequestTimeSync(void)
{
    if (!wifi_ok && !App_Net_IsConnecting())
    {
        APP_LOG_ERROR("Time sync failed: WiFi not connected\r\n");
        UI_Msg_PostLog(UI_EVENT_ERROR, "Time sync failed: WiFi off");
        return;
    }

    net_pending_time_sync = 1;

    if (App_Net_IsBusy())
    {
        UI_Msg_PostLog(UI_EVENT_INFO, "Time sync queued");
    }

    App_Net_StartPendingIfIdle();
}

static void App_Net_RequestWeather(void)
{
    if (!wifi_ok && !App_Net_IsConnecting())
    {
        APP_LOG_ERROR("Weather refresh failed: WiFi not connected\r\n");
        UI_Msg_PostWeatherError("WiFi Error");
        UI_Msg_PostLog(UI_EVENT_ERROR, "Weather refresh failed: WiFi off");
        return;
    }

    net_pending_weather = 1;

    if (App_Net_IsBusy())
    {
        UI_Msg_PostLog(UI_EVENT_WEATHER, "Weather request queued");
    }

    App_Net_StartPendingIfIdle();
}

static void App_Net_AutoReconnectProcess(void)
{
    uint32_t now;

    if (!net_auto_reconnect_enable || wifi_ok || App_Net_IsBusy())
    {
        return;
    }

    if (net_next_reconnect_tick == 0)
    {
        App_Net_ScheduleReconnect();
        return;
    }

    now = HAL_GetTick();
    if (!App_TimeExpired(now, net_next_reconnect_tick))
    {
        return;
    }

    net_next_reconnect_tick = 0;
    net_pending_connect_time = 1;
    net_pending_connect_weather = 1;

    App_Net_StartConnectFlow();
}

static void App_Net_AutoWifiCheckProcess(void)
{
    uint32_t now;

    if (!wifi_ok || App_Net_IsBusy())
    {
        return;
    }

    if (net_next_wifi_check_tick == 0)
    {
        net_next_wifi_check_tick = HAL_GetTick() + NET_WIFI_CHECK_PERIOD_MS;
        return;
    }

    now = HAL_GetTick();
    if (!App_TimeExpired(now, net_next_wifi_check_tick))
    {
        return;
    }

    net_next_wifi_check_tick = 0;
    net_flow = APP_NET_FLOW_WIFI_CHECK;
    net_state = APP_NET_STATE_WIFI_CHECK_START;
}

static void App_Net_HandleWifiFail(const char *reason)
{
    wifi_ok = 0;

    APP_LOG_ERROR("WiFi connect failed: %s\r\n", reason);
    App_AddLog(UI_EVENT_ERROR, EEPROM_EVENT_ERROR, "WiFi connect failed");
    UI_Msg_PostWeatherError("WiFi Error");
    UI_Msg_PostTimeRefresh();

    App_Net_ScheduleReconnect();
    App_Net_FinishFlow();
}

static void App_Net_HandleTimeFail(const char *reason)
{
    APP_LOG_ERROR("Time sync failed: %s\r\n", reason);
    UI_Msg_PostLog(UI_EVENT_ERROR, "Time sync failed");

    App_Net_FinishTimeFlow();
}

static void App_Net_HandleWeatherFail(const char *reason)
{
    APP_LOG_ERROR("Weather refresh failed: %s\r\n", reason);
    UI_Msg_PostWeatherError("HTTP Error");
    App_AddLog(UI_EVENT_ERROR, EEPROM_EVENT_ERROR, "Weather HTTP failed");

    App_Net_FinishFlow();
}

static void App_Net_HandleWeatherResponse(void)
{
    uint8_t ret;

    ESP_AT_GetLastResponse(net_weather_response, sizeof(net_weather_response));

    APP_LOG_DEBUG("Weather raw response:\r\n%s\r\n", net_weather_response);

    ret = Weather_ParseNowResponse(net_weather_response, &weather_now);
    if (ret != 0)
    {
        APP_LOG_ERROR("Weather parse failed, code=%u\r\n", ret);
        UI_Msg_PostWeatherError("Parse Error");
        App_AddLog(UI_EVENT_ERROR, EEPROM_EVENT_ERROR, "Weather parse failed");
        App_Net_FinishFlow();
        return;
    }

    Weather_PrintNow(&weather_now);

    App_CopyText(ui_weather.city,
                 sizeof(ui_weather.city),
                 weather_now.city);

    App_CopyText(ui_weather.weather,
                 sizeof(ui_weather.weather),
                 weather_now.text);

    App_CopyText(ui_weather.last_update,
                 sizeof(ui_weather.last_update),
                 weather_now.update_time);

    App_CopyText(ui_weather.ssid, sizeof(ui_weather.ssid), "--");
    App_CopyText(ui_weather.ip, sizeof(ui_weather.ip), "--");

    ui_weather.temperature = weather_now.temperature;
    ui_weather.net_state = UI_NET_CONNECTED;

    net_state = APP_NET_STATE_QUERY_SSID_START;
}

static void App_Net_PostWeatherDone(void)
{
    UI_Msg_PostWeather(&ui_weather);
    App_AddLog(UI_EVENT_WEATHER, EEPROM_EVENT_WEATHER, "Weather updated");
    net_next_weather_tick = HAL_GetTick() + App_ConfigWeatherPeriodMs();
    App_Net_FinishFlow();
}

static void App_Net_Process(void)
{
    ESP_AT_AsyncResult_t result;
    uint8_t ret;

    switch (net_state)
    {
        case APP_NET_STATE_IDLE:
            App_Net_StartPendingIfIdle();
            break;

        case APP_NET_STATE_DELAY:
            if (App_TimeExpired(HAL_GetTick(),
                                net_delay_start_tick + net_delay_ms))
            {
                net_state = net_delay_next_state;
            }
            break;

        case APP_NET_STATE_AT_TEST_START:
            ret = App_Net_StartCommand("AT",
                                       "OK",
                                       NET_AT_TIMEOUT_MS,
                                       APP_NET_STATE_AT_TEST_WAIT);
            if (ret != 0)
            {
                App_Net_HandleWifiFail("AT test start failed");
            }
            break;

        case APP_NET_STATE_AT_TEST_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                APP_LOG_INFO("ESP AT OK\r\n");
                net_state = APP_NET_STATE_ECHO_OFF_START;
            }
            else
            {
                APP_LOG_ERROR("ESP AT failed: %s\r\n", App_Net_ResultName(result));
                App_Net_HandleWifiFail(App_Net_ResultName(result));
            }
            break;

        case APP_NET_STATE_ECHO_OFF_START:
            ret = App_Net_StartCommand("ATE0",
                                       "OK",
                                       NET_AT_TIMEOUT_MS,
                                       APP_NET_STATE_ECHO_OFF_WAIT);
            if (ret != 0)
            {
                net_state = APP_NET_STATE_SET_MODE_START;
            }
            break;

        case APP_NET_STATE_ECHO_OFF_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                APP_LOG_INFO("ESP echo off OK\r\n");
            }
            else
            {
                APP_LOG_ERROR("ESP echo off failed: %s\r\n", App_Net_ResultName(result));
            }

            net_state = APP_NET_STATE_SET_MODE_START;
            break;

        case APP_NET_STATE_SET_MODE_START:
            ret = App_Net_StartCommand("AT+CWMODE=1",
                                       "OK",
                                       NET_AT_TIMEOUT_MS,
                                       APP_NET_STATE_SET_MODE_WAIT);
            if (ret != 0)
            {
                App_Net_HandleWifiFail("set mode start failed");
            }
            break;

        case APP_NET_STATE_SET_MODE_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                net_state = APP_NET_STATE_WIFI_START;
            }
            else
            {
                App_Net_HandleWifiFail(App_Net_ResultName(result));
            }
            break;

        case APP_NET_STATE_WIFI_START:
            snprintf(net_cmd_buf,
                     sizeof(net_cmd_buf),
                     "AT+CWJAP=\"%s\",\"%s\"",
                     WIFI_SSID,
                     WIFI_PASSWORD);

            ret = App_Net_StartCommand(net_cmd_buf,
                                       "OK",
                                       NET_WIFI_TIMEOUT_MS,
                                       APP_NET_STATE_WIFI_WAIT);
            if (ret != 0)
            {
                App_Net_HandleWifiFail("connect start failed");
            }
            break;

        case APP_NET_STATE_WIFI_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                wifi_ok = 1;
                App_Net_ResetReconnect();
                APP_LOG_INFO("WiFi connected\r\n");
                App_AddLog(UI_EVENT_WIFI, EEPROM_EVENT_WIFI, "WiFi connected");

                if (net_connect_time_after_ok)
                {
                    App_Net_StartTimeFlow(net_connect_weather_after_ok);
                }
                else if (net_connect_weather_after_ok)
                {
                    App_Net_StartWeatherFlow();
                }
                else
                {
                    App_Net_FinishFlow();
                }
            }
            else
            {
                App_Net_HandleWifiFail(App_Net_ResultName(result));
            }
            break;

        case APP_NET_STATE_SNTP_CFG_START:
            ret = App_Net_StartCommand("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\",\"pool.ntp.org\"",
                                       "OK",
                                       NET_SNTP_CONFIG_TIMEOUT_MS,
                                       APP_NET_STATE_SNTP_CFG_WAIT);
            if (ret != 0)
            {
                App_Net_HandleTimeFail("SNTP config start failed");
            }
            break;

        case APP_NET_STATE_SNTP_CFG_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                App_Net_StartDelay(APP_NET_STATE_SNTP_GET_START,
                                   NET_SNTP_FIRST_DELAY_MS);
            }
            else
            {
                App_Net_HandleTimeFail(App_Net_ResultName(result));
            }
            break;

        case APP_NET_STATE_SNTP_GET_START:
            net_sntp_attempt++;
            ret = App_Net_StartCommand("AT+CIPSNTPTIME?",
                                       "OK",
                                       NET_SNTP_GET_TIMEOUT_MS,
                                       APP_NET_STATE_SNTP_GET_WAIT);
            if (ret != 0)
            {
                App_Net_HandleTimeFail("SNTP get start failed");
            }
            break;

        case APP_NET_STATE_SNTP_GET_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                ESP_AT_GetLastResponse(net_time_response, sizeof(net_time_response));
                APP_LOG_DEBUG("SNTP raw response:\r\n%s\r\n", net_time_response);

                ret = App_ApplySNTPResponse(net_time_response);
                if (ret == 0)
                {
                    APP_LOG_INFO("RTC sync OK\r\n");
                    UI_Msg_PostTimeRefresh();
                    UI_Msg_PostLog(UI_EVENT_INFO, "Time sync OK");
                    App_Net_FinishTimeFlow();
                }
                else if (net_sntp_attempt < NET_SNTP_RETRY_MAX)
                {
                    APP_LOG_ERROR("SNTP parse/apply failed, code=%u, retry\r\n", ret);
                    APP_LOG_ERROR("SNTP response: %s\r\n", net_time_response);
                    App_Net_StartDelay(APP_NET_STATE_SNTP_GET_START,
                                       NET_SNTP_RETRY_DELAY_MS);
                }
                else
                {
                    APP_LOG_ERROR("SNTP parse/apply failed, code=%u\r\n", ret);
                    APP_LOG_ERROR("SNTP response: %s\r\n", net_time_response);
                    App_Net_HandleTimeFail("SNTP parse failed");
                }
            }
            else if (App_Net_ResultIsError(result) &&
                     net_sntp_attempt < NET_SNTP_RETRY_MAX)
            {
                APP_LOG_ERROR("SNTP get failed: %s, retry\r\n", App_Net_ResultName(result));
                App_Net_StartDelay(APP_NET_STATE_SNTP_GET_START,
                                   NET_SNTP_RETRY_DELAY_MS);
            }
            else
            {
                App_Net_HandleTimeFail(App_Net_ResultName(result));
            }
            break;

        case APP_NET_STATE_WEATHER_START:
            App_Net_BuildWeatherUrl(net_weather_url, sizeof(net_weather_url));

            snprintf(net_cmd_buf,
                     sizeof(net_cmd_buf),
                     "AT+HTTPCGET=\"%s\",2048,4096,%lu",
                     net_weather_url,
                     (unsigned long)NET_HTTP_TIMEOUT_MS);

            ret = App_Net_StartCommand(net_cmd_buf,
                                       "OK",
                                       NET_HTTP_AT_TIMEOUT_MS,
                                       APP_NET_STATE_WEATHER_WAIT);
            if (ret != 0)
            {
                App_Net_HandleWeatherFail("HTTP start failed");
            }
            break;

        case APP_NET_STATE_WEATHER_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                App_Net_HandleWeatherResponse();
            }
            else
            {
                App_Net_HandleWeatherFail(App_Net_ResultName(result));
            }
            break;

        case APP_NET_STATE_QUERY_SSID_START:
            ret = App_Net_StartCommand("AT+CWSTATE?",
                                       "OK",
                                       NET_AT_TIMEOUT_MS,
                                       APP_NET_STATE_QUERY_SSID_WAIT);
            if (ret != 0)
            {
                App_CopyText(ui_weather.ssid, sizeof(ui_weather.ssid), "--");
                net_state = APP_NET_STATE_QUERY_IP_START;
            }
            break;

        case APP_NET_STATE_QUERY_SSID_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                if (ESP_AT_ParseQuotedValue(ESP_AT_GetResponse(),
                                            "+CWSTATE:",
                                            ui_weather.ssid,
                                            sizeof(ui_weather.ssid)) != 0)
                {
                    App_CopyText(ui_weather.ssid, sizeof(ui_weather.ssid), "--");
                }
            }
            else
            {
                App_CopyText(ui_weather.ssid, sizeof(ui_weather.ssid), "--");
            }

            net_state = APP_NET_STATE_QUERY_IP_START;
            break;

        case APP_NET_STATE_QUERY_IP_START:
            ret = App_Net_StartCommand("AT+CIFSR",
                                       "OK",
                                       NET_AT_TIMEOUT_MS,
                                       APP_NET_STATE_QUERY_IP_WAIT);
            if (ret != 0)
            {
                App_CopyText(ui_weather.ip, sizeof(ui_weather.ip), "--");
                App_Net_PostWeatherDone();
            }
            break;

        case APP_NET_STATE_QUERY_IP_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK)
            {
                if (ESP_AT_ParseQuotedValue(ESP_AT_GetResponse(),
                                            "+CIFSR:STAIP",
                                            ui_weather.ip,
                                            sizeof(ui_weather.ip)) != 0)
                {
                    App_CopyText(ui_weather.ip, sizeof(ui_weather.ip), "--");
                }
            }
            else
            {
                App_CopyText(ui_weather.ip, sizeof(ui_weather.ip), "--");
            }

            App_Net_PostWeatherDone();
            break;

        case APP_NET_STATE_WIFI_CHECK_START:
            ret = App_Net_StartCommand("AT+CWSTATE?",
                                       "OK",
                                       NET_AT_TIMEOUT_MS,
                                       APP_NET_STATE_WIFI_CHECK_WAIT);
            if (ret != 0)
            {
                wifi_ok = 0;
                App_Net_ScheduleReconnect();
                App_Net_FinishFlow();
            }
            break;

        case APP_NET_STATE_WIFI_CHECK_WAIT:
            result = ESP_AT_AsyncPoll();
            if (result == ESP_AT_ASYNC_BUSY)
            {
                break;
            }

            if (result == ESP_AT_ASYNC_OK &&
                strstr(ESP_AT_GetResponse(), "+CWSTATE:2") != NULL)
            {
                wifi_ok = 1;
                net_next_wifi_check_tick = HAL_GetTick() + NET_WIFI_CHECK_PERIOD_MS;
            }
            else
            {
                wifi_ok = 0;
                APP_LOG_ERROR("WiFi disconnected, reconnect scheduled\r\n");
                UI_Msg_PostLog(UI_EVENT_WIFI, "WiFi disconnected");
                App_Net_ScheduleReconnect();
            }

            App_Net_FinishFlow();
            break;

        default:
            net_state = APP_NET_STATE_IDLE;
            break;
    }
}

void App_Task_Storage(void)
{
    if (UI_App_TakeManualSaveRequest())
    {
        if (App_SaveCurrentHistory() == 0)
        {
            storage_next_history_tick = HAL_GetTick() + App_ConfigHistoryPeriodMs();
            App_AddLog(UI_EVENT_EEPROM, EEPROM_EVENT_EEPROM, "Manual save OK");

            if (EEPROM_ReadLatestHistoryRecord(&latest_history) == 0)
            {
                App_UpdateLatestRecordFromHistory(&latest_history);
            }
        }
        else
        {
            storage_next_history_tick = HAL_GetTick() + App_ConfigHistoryPeriodMs();
            App_AddLog(UI_EVENT_ERROR, EEPROM_EVENT_ERROR, "Manual save failed");
        }
    }

    if (UI_App_TakeClearLogRequest())
    {
        UI_Msg_PostClearLog();

        APP_LOG_INFO("UI log cleared\r\n");

        EEPROM_SaveEventLog(EEPROM_EVENT_INFO,
                            "UI log cleared",
                            HAL_GetTick(),
                            App_GetUnixTimeOrZero());
    }

    if (UI_App_TakeBrightnessChanged(&brightness_percent))
    {
        brightness_percent = App_ClampBrightness(brightness_percent);
        LCD_Backlight_SetPercent(brightness_percent);

        app_config.brightness_percent = brightness_percent;
        config_dirty = 1;
        config_dirty_tick = HAL_GetTick();

        APP_LOG_INFO("LCD brightness: %u%%\r\n", brightness_percent);
    }

    if (config_dirty && (HAL_GetTick() - config_dirty_tick >= 2000))
    {
        config_dirty = 0;

        if (EEPROM_SaveConfig(&app_config) == 0)
        {
            APP_LOG_INFO("Config saved to EEPROM\r\n");
            App_AddLog(UI_EVENT_EEPROM,
                       EEPROM_EVENT_EEPROM,
                       "Config saved");
        }
        else
        {
            APP_LOG_ERROR("Config save failed\r\n");
            App_AddLog(UI_EVENT_ERROR,
                       EEPROM_EVENT_ERROR,
                       "Config save failed");
        }
    }

    App_Storage_PeriodicHistoryProcess();
}

void App_Task_UI(void)
{
    UI_Msg_Process();

    lv_timer_handler();
    UI_App_Process();

    if (HAL_GetTick() - time_ui_last_tick >= 1000)
    {
        time_ui_last_tick = HAL_GetTick();
        App_UpdateTimeUI();
    }
}

uint8_t App_IsWifiConnected(void)
{
    return wifi_ok;
}

uint8_t App_NetworkStartup(void)
{
    App_Net_RequestConnect(1, 1);
    return 0;
}

void App_Task_Network(void)
{
    if (UI_App_TakeTimeSyncRequest())
    {
        App_Net_RequestTimeSync();
    }

    if (UI_App_TakeWifiConnectRequest())
    {
        App_Net_RequestConnect(1, 1);
    }

    if (UI_App_TakeWeatherRefreshRequest())
    {
        App_Net_RequestWeather();
    }

    App_Net_PeriodicWeatherProcess();
    App_Net_Process();
}

void App_Task_Sensor(void)
{
    App_Sensor_InitDevices();

    if (UI_App_TakeSensorRefreshRequest())
    {
        if (App_ReadSensorsToLatest() == 0)
        {
            sensor_next_sample_tick = HAL_GetTick() + App_ConfigSensorPeriodMs();
            App_AddLog(UI_EVENT_SENSOR,
                       EEPROM_EVENT_SENSOR,
                       "Sensor refreshed");
        }
        else
        {
            sensor_next_sample_tick = HAL_GetTick() + App_ConfigSensorPeriodMs();
            App_AddLog(UI_EVENT_ERROR,
                       EEPROM_EVENT_ERROR,
                       "Sensor refresh failed");
        }
    }

    App_Sensor_PeriodicProcess();
}

void App_Tasks_InitBeforeScheduler(void)
{
    uint8_t eeprom_ret;

    APP_LOG_BOOT("App init before scheduler start\r\n");

    LCD_Init();
    APP_LOG_BOOT("LCD init OK\r\n");

    FT5336_Init();
    APP_LOG_BOOT("Touch init OK\r\n");

    LCD_Backlight_Init();
    APP_LOG_BOOT("LCD backlight init OK\r\n");

    if (App_SensorMutexInit() != 0)
    {
        APP_LOG_ERROR("Sensor mutex init failed\r\n");
    }

    if (EEPROM_Init() == 0)
    {
        APP_LOG_BOOT("EEPROM init OK\r\n");

        if (EEPROM_LoadConfig(&app_config) != 0)
        {
            EEPROM_LoadDefaultConfig(&app_config);
            EEPROM_SaveConfig(&app_config);
            APP_LOG_BOOT("EEPROM default config created\r\n");
        }
        else
        {
            APP_LOG_BOOT("EEPROM config loaded\r\n");
        }

        App_NormalizeConfig(1);
        LCD_Backlight_SetPercent(app_config.brightness_percent);
        APP_LOG_BOOT("Config applied, brightness=%u%%\r\n",
                     app_config.brightness_percent);

        eeprom_ret = EEPROM_ReadLatestEventLog(&latest_event);
        if (eeprom_ret == 0)
        {
            EEPROM_PrintEventRecord(&latest_event);
            APP_LOG_BOOT("EEPROM latest event loaded\r\n");
        }
        else
        {
            APP_LOG_BOOT("EEPROM latest event empty, code=%u\r\n", eeprom_ret);
        }
    }
    else
    {
        APP_LOG_ERROR("EEPROM init failed\r\n");

        EEPROM_LoadDefaultConfig(&app_config);
        App_NormalizeConfig(0);
        LCD_Backlight_SetPercent(app_config.brightness_percent);
        APP_LOG_BOOT("Default config applied, brightness=%u%%\r\n",
                     app_config.brightness_percent);
    }

    APP_LOG_BOOT("Sensor init deferred\r\n");

    if (ESP_AT_Init() == 0)
    {
        APP_LOG_BOOT("ESP receive start\r\n");
    }
    else
    {
        APP_LOG_ERROR("ESP receive start failed\r\n");
    }

    APP_LOG_BOOT("LVGL init start\r\n");
    lv_init();
    lv_tick_set_cb(HAL_GetTick);

    LV_PortDisp_Init();
    LV_PortIndev_Init();
    APP_LOG_BOOT("LVGL port init OK\r\n");

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    UI_App_Init(&guider_ui);
    APP_LOG_BOOT("GUI init OK\r\n");

    if (EEPROM_ReadLatestHistoryRecord(&latest_history) == 0)
    {
        EEPROM_PrintEnvRecord(&latest_history);
        App_UpdateLatestRecordFromHistory(&latest_history);
    }

    App_UpdateSettingsUI();
    App_UpdateTimeUI();
    APP_LOG_BOOT("App init before scheduler done\r\n");
}
