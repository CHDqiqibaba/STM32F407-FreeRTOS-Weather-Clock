#include "ui_app.h"
#include "app_log.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include <stdio.h>
#include <string.h>

static lv_ui *s_ui = NULL;

#define UI_REQ_WEATHER_REFRESH       ((EventBits_t)(1UL << 0))
#define UI_REQ_SENSOR_REFRESH        ((EventBits_t)(1UL << 1))
#define UI_REQ_MANUAL_SAVE           ((EventBits_t)(1UL << 2))
#define UI_REQ_TIME_SYNC             ((EventBits_t)(1UL << 3))
#define UI_REQ_WIFI_CONNECT          ((EventBits_t)(1UL << 4))
#define UI_REQ_CLEAR_LOG             ((EventBits_t)(1UL << 5))
#define UI_REQ_BRIGHTNESS_CHANGED    ((EventBits_t)(1UL << 6))

static EventGroupHandle_t s_request_events = NULL;
static volatile EventBits_t s_request_bits_before_scheduler = 0;
static volatile uint8_t s_brightness_percent = 80;

static char s_log_lines[UI_APP_LOG_MAX_LINES][96];
static uint8_t s_log_count = 0;
static lv_obj_t *s_bound_log_list = NULL;

/* AHT20 最近一次读取成功的数据 */
static uint8_t s_aht20_data_valid = 0;
static int32_t s_last_aht20_temp_x100 = 0;
static uint32_t s_last_aht20_humi_x100 = 0;

/* LPS22HH 最近一次读取成功的数据 */
static uint8_t s_lps22hh_data_valid = 0;
static int32_t s_last_lps22hh_pressure_x100 = 0;

/* LIS2DH12 最近一次读取成功的数据 */
static uint8_t s_lis2dh12_data_valid = 0;
static int32_t s_last_lis2dh12_x_mg = 0;
static int32_t s_last_lis2dh12_y_mg = 0;
static int32_t s_last_lis2dh12_z_mg = 0;
static int32_t s_last_lis2dh12_motion = 0;

/* OPT3001 最近一次读取成功的数据 */
static uint8_t s_opt3001_data_valid = 0;
static uint32_t s_last_opt3001_lux_x100 = 0;

/* 天气时钟 最近一次读取成功的数据 */
static uint8_t s_weather_data_valid = 0;
static UI_Weather_t s_last_weather;

static uint8_t s_time_data_valid = 0;
static UI_Time_t s_last_time;

static uint8_t s_date_data_valid = 0;
static UI_Date_t s_last_date;
static char s_last_week[8];

static lv_obj_t *s_bound_home_weather = NULL;
static lv_obj_t *s_bound_weather_refresh = NULL;
static lv_obj_t *s_bound_sensor_refresh = NULL;
static lv_obj_t *s_bound_log_save = NULL;
static lv_obj_t *s_bound_sync_time = NULL;
static lv_obj_t *s_bound_connect_wifi = NULL;
static lv_obj_t *s_bound_clear_log = NULL;
static lv_obj_t *s_bound_brightness_slider = NULL;

static uint8_t UI_ObjIsReady(lv_obj_t *obj)
{
    return (obj != NULL && lv_obj_is_valid(obj));
}

static uint8_t UI_App_IsSchedulerRunning(void)
{
    return (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED);
}

static void UI_RequestInit(void)
{
    if (s_request_events == NULL)
    {
        s_request_events = xEventGroupCreate();
        if (s_request_events == NULL)
        {
            APP_LOG_ERROR("[UI] Request EventGroup create failed\r\n");
        }
        configASSERT(s_request_events != NULL);
    }
}

static void UI_RequestSet(EventBits_t bit)
{
    UI_RequestInit();

    if (s_request_events != NULL && UI_App_IsSchedulerRunning())
    {
        (void)xEventGroupSetBits(s_request_events, bit);
    }
    else
    {
        s_request_bits_before_scheduler |= bit;
    }
}

static uint8_t UI_RequestTake(EventBits_t bit)
{
    EventBits_t bits;

    UI_RequestInit();

    if (s_request_events != NULL && UI_App_IsSchedulerRunning())
    {
        bits = xEventGroupClearBits(s_request_events, bit);
        return ((bits & bit) != 0U);
    }

    bits = s_request_bits_before_scheduler;
    s_request_bits_before_scheduler &= ~bit;
    return ((bits & bit) != 0U);
}

static void UI_ClearInvalidBoundObjects(void)
{
    if (s_bound_home_weather != NULL && !lv_obj_is_valid(s_bound_home_weather))
    {
        s_bound_home_weather = NULL;
    }

    if (s_bound_weather_refresh != NULL && !lv_obj_is_valid(s_bound_weather_refresh))
    {
        s_bound_weather_refresh = NULL;
    }

    if (s_bound_sensor_refresh != NULL && !lv_obj_is_valid(s_bound_sensor_refresh))
    {
        s_bound_sensor_refresh = NULL;
    }

    if (s_bound_log_list != NULL && !lv_obj_is_valid(s_bound_log_list))
    {
        s_bound_log_list = NULL;
    }

    if (s_bound_log_save != NULL && !lv_obj_is_valid(s_bound_log_save))
    {
        s_bound_log_save = NULL;
    }

    if (s_bound_sync_time != NULL && !lv_obj_is_valid(s_bound_sync_time))
    {
        s_bound_sync_time = NULL;
    }

    if (s_bound_connect_wifi != NULL && !lv_obj_is_valid(s_bound_connect_wifi))
    {
        s_bound_connect_wifi = NULL;
    }

    if (s_bound_clear_log != NULL && !lv_obj_is_valid(s_bound_clear_log))
    {
        s_bound_clear_log = NULL;
    }

    if (s_bound_brightness_slider != NULL && !lv_obj_is_valid(s_bound_brightness_slider))
    {
        s_bound_brightness_slider = NULL;
    }
}

static void UI_SetLabel(lv_obj_t *label, const char *text)
{
    if (label == NULL || text == NULL)
    {
        return;
    }

    if (!lv_obj_is_valid(label))
    {
        return;
    }

    lv_label_set_text(label, text);
}


//调整温湿度格式
static void UI_FormatTemp(char *buf, uint16_t size, int32_t temp_x100)
{
    int32_t abs_temp = temp_x100;

    if (abs_temp < 0)
    {
        abs_temp = -abs_temp;
    }

    snprintf(buf,
             size,
             "%s%ld.%02ld C",
             (temp_x100 < 0) ? "-" : "",
             (long)(abs_temp / 100),
             (long)(abs_temp % 100));
}

static void UI_FormatHumi(char *buf, uint16_t size, uint32_t humi_x100)
{
    snprintf(buf,
             size,
             "%lu.%02lu %%",
             (unsigned long)(humi_x100 / 100),
             (unsigned long)(humi_x100 % 100));
}

static void UI_FormatPressure(char *buf, uint16_t size, int32_t pressure_x100)
{
    int32_t abs_value = pressure_x100;

    if (abs_value < 0)
    {
        abs_value = -abs_value;
    }

    snprintf(buf,
             size,
             "%s%ld.%02ld hPa",
             (pressure_x100 < 0) ? "-" : "",
             (long)(abs_value / 100),
             (long)(abs_value % 100));
}

static void UI_FormatMotion(char *buf, uint16_t size, int32_t motion)
{
    snprintf(buf,
             size,
             "%s",
             (motion != 0) ? "Moving" : "Stable");
}

static void UI_FormatLux(char *buf, uint16_t size, uint32_t lux_x100)
{
    snprintf(buf,
             size,
             "%lu.%02lu lx",
             (unsigned long)(lux_x100 / 100),
             (unsigned long)(lux_x100 % 100));
}

static void UI_FormatWeatherCard(char *buf,
                                 uint16_t size,
                                 const UI_Weather_t *weather)
{
    if (buf == NULL || size == 0)
    {
        return;
    }

    if (weather == NULL)
    {
        snprintf(buf, size, "--\n--\n--C");
        return;
    }

    snprintf(buf,
             size,
             "%s\n%s\n%dC",
             (weather->city[0] != '\0') ? weather->city : "--",
             (weather->weather[0] != '\0') ? weather->weather : "--",
             weather->temperature);
}

static void UI_FormatWeatherTemp(char *buf, uint16_t size, int16_t temperature)
{
    if (buf == NULL || size == 0)
    {
        return;
    }

    snprintf(buf,
             size,
             "%dC",
             temperature);
}

static void UI_FormatNetState(char *buf,
                              uint16_t size,
                              UI_NetState_t net_state)
{
    if (buf == NULL || size == 0)
    {
        return;
    }

    snprintf(buf,
             size,
             "%s",
             (net_state == UI_NET_CONNECTED) ? "Connected" : "Disconnected");
}


static void UI_FormatTextOrDefault(char *buf,
                                   uint16_t size,
                                   const char *text,
                                   const char *default_text)
{
    if (buf == NULL || size == 0)
    {
        return;
    }

    if (text != NULL && text[0] != '\0')
    {
        snprintf(buf, size, "%s", text);
    }
    else
    {
        snprintf(buf, size, "%s", (default_text != NULL) ? default_text : "--");
    }
}

static void UI_FormatTime(char *buf, uint16_t size, const UI_Time_t *time)
{
    if (buf == NULL || size == 0)
    {
        return;
    }

    if (time == NULL)
    {
        snprintf(buf, size, "--:--:--");
        return;
    }

    snprintf(buf,
             size,
             "%02u:%02u:%02u",
             time->hour,
             time->min,
             time->sec);
}

static void UI_FormatDate(char *buf, uint16_t size, const UI_Date_t *date)
{
    if (buf == NULL || size == 0)
    {
        return;
    }

    if (date == NULL)
    {
        snprintf(buf, size, "----/--/--");
        return;
    }

    snprintf(buf,
             size,
             "%04u/%02u/%02u",
             date->year,
             date->month,
             date->day);
}

static void UI_FormatUptime(char *buf, uint16_t size, uint32_t uptime_ms)
{
    uint32_t total_sec;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;

    if (buf == NULL || size == 0)
    {
        return;
    }

    total_sec = uptime_ms / 1000U;
    hour = total_sec / 3600U;
    min = (total_sec % 3600U) / 60U;
    sec = total_sec % 60U;

    snprintf(buf,
             size,
             "%02lu:%02lu:%02lu",
             (unsigned long)hour,
             (unsigned long)min,
             (unsigned long)sec);
}


static void UI_ApplyLatestAHT20(void)
{
    char temp_buf[24];
    char humi_buf[24];

    if (s_ui == NULL || !s_aht20_data_valid)
    {
        return;
    }

    UI_FormatTemp(
        temp_buf,
        sizeof(temp_buf),
        s_last_aht20_temp_x100
    );

    UI_FormatHumi(
        humi_buf,
        sizeof(humi_buf),
        s_last_aht20_humi_x100
    );

    UI_SetLabel(
        s_ui->screen_sensor_label_sensor_temp_value,
        temp_buf
    );

    UI_SetLabel(
        s_ui->screen_sensor_label_sensor_humidity_value,
        humi_buf
    );
		UI_SetLabel(s_ui->screen_home_label_home_outdoor_temp, temp_buf);
		UI_SetLabel(s_ui->screen_home_label_home_outdoor_humi, humi_buf);
}


static void UI_ApplyLatestLPS22HH(void)
{
    char pressure_buf[24];

    if (s_ui == NULL || !s_lps22hh_data_valid)
    {
        return;
    }

    UI_FormatPressure(
        pressure_buf,
        sizeof(pressure_buf),
        s_last_lps22hh_pressure_x100
    );
    UI_SetLabel(
        s_ui->screen_sensor_label_sensor_air_value,
        pressure_buf
    );
}

static void UI_ApplyLatestLIS2DH12(void)
{
    char motion_buf[24];

    if (s_ui == NULL || !s_lis2dh12_data_valid)
    {
        return;
    }

    UI_FormatMotion(motion_buf,
                    sizeof(motion_buf),
                    s_last_lis2dh12_motion);

    UI_SetLabel(s_ui->screen_sensor_label_sensor_motion_value,
                motion_buf);
}

static void UI_ApplyLatestOPT3001(void)
{
    char lux_buf[24];

    if (s_ui == NULL || !s_opt3001_data_valid)
    {
        return;
    }

    UI_FormatLux(lux_buf,
                 sizeof(lux_buf),
                 s_last_opt3001_lux_x100);

    UI_SetLabel(s_ui->screen_sensor_label_sensor_light_value,
                lux_buf);
}

static void UI_ApplyLatestWeather(void)
{
    char weather_buf[64];
    char temp_buf[16];
    char update_buf[24];
    char wifi_buf[16];
    char ip_buf[24];

    if (s_ui == NULL || !s_weather_data_valid)
    {
        return;
    }

    UI_FormatWeatherCard(weather_buf,
                         sizeof(weather_buf),
                         &s_last_weather);

    UI_FormatWeatherTemp(temp_buf,
                         sizeof(temp_buf),
                         s_last_weather.temperature);

    UI_FormatTextOrDefault(update_buf,
                           sizeof(update_buf),
                           s_last_weather.last_update,
                           "--");

    UI_FormatNetState(wifi_buf,
                      sizeof(wifi_buf),
                      s_last_weather.net_state);

    UI_FormatTextOrDefault(ip_buf,
                           sizeof(ip_buf),
                           s_last_weather.ip,
                           "--");

    UI_SetLabel(s_ui->screen_weather_label_weather_weather, weather_buf);
    UI_SetLabel(s_ui->screen_weather_label_weather_update_value, update_buf);
    if (s_last_weather.net_state == UI_NET_CONNECTED)
		{
				UI_SetLabel(s_ui->screen_weather_label_weather_wifi_value,
										s_last_weather.ssid[0] ? s_last_weather.ssid : "Connected");
		}
		else
		{
				UI_SetLabel(s_ui->screen_weather_label_weather_wifi_value, "Disconnected");
		}

		UI_SetLabel(s_ui->screen_weather_label_weather_ip_value,
								s_last_weather.ip[0] ? s_last_weather.ip : "--");

    UI_SetLabel(s_ui->screen_home_label_home_weather, weather_buf);
    UI_SetLabel(s_ui->screen_home_label_home_update_time, update_buf);

    if (s_ui->screen_home_img_home_wifi_ok != NULL &&
        lv_obj_is_valid(s_ui->screen_home_img_home_wifi_ok))
    {
        if (s_last_weather.net_state == UI_NET_CONNECTED)
        {
            lv_obj_clear_flag(s_ui->screen_home_img_home_wifi_ok, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
            lv_obj_add_flag(s_ui->screen_home_img_home_wifi_ok, LV_OBJ_FLAG_HIDDEN);
        }
    }
}


static void UI_ApplyLatestTime(void)
{
    char time_buf[16];

    if (s_ui == NULL || !s_time_data_valid)
    {
        return;
    }

    UI_FormatTime(time_buf,
                  sizeof(time_buf),
                  &s_last_time);

    UI_SetLabel(s_ui->screen_home_label_home_time, time_buf);
}

static void UI_ApplyLatestDate(void)
{
    char date_buf[24];

    if (s_ui == NULL || !s_date_data_valid)
    {
        return;
    }

    UI_FormatDate(date_buf,
                  sizeof(date_buf),
                  &s_last_date);

    UI_SetLabel(s_ui->screen_home_datetext_home_data, date_buf);

    if (s_last_week[0] != '\0')
    {
        UI_SetLabel(s_ui->screen_home_label_home_weekday, s_last_week);
    }
    else
    {
        UI_SetLabel(s_ui->screen_home_label_home_weekday, "--");
    }
}


static const char *UI_EventPrefix(UI_EventType_t type)
{
    switch (type)
    {
        case UI_EVENT_WIFI:
            return "[WiFi]";
        case UI_EVENT_WEATHER:
            return "[Weather]";
        case UI_EVENT_SENSOR:
            return "[Sensor]";
        case UI_EVENT_EEPROM:
            return "[EEPROM]";
        case UI_EVENT_ERROR:
            return "[Error]";
        case UI_EVENT_INFO:
        default:
            return "[Info]";
    }
}

static void UI_ListClear(lv_obj_t *list)
{
    if (list == NULL)
    {
        return;
    }

    if (!lv_obj_is_valid(list))
    {
        return;
    }

    lv_obj_clean(list);
}

static void UI_ListAddKeepLast(lv_obj_t *list, const char *text, uint8_t max_lines)
{
    lv_obj_t *item;

    if (list == NULL || text == NULL)
    {
        return;
    }

    if (!lv_obj_is_valid(list))
    {
        return;
    }

    item = lv_list_add_button(list, NULL, text);

    lv_obj_set_style_bg_opa(item, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(item, 0, 0);
    lv_obj_set_style_pad_top(item, 4, 0);
    lv_obj_set_style_pad_bottom(item, 4, 0);

    while (lv_obj_get_child_count(list) > max_lines)
    {
        lv_obj_t *first = lv_obj_get_child(list, 0);

        if (first == NULL || !lv_obj_is_valid(first))
        {
            break;
        }

        lv_obj_delete(first);
    }
}


static void UI_LogCacheAdd(const char *line)
{
    uint8_t i;

    if (line == NULL)
    {
        return;
    }

    if (s_log_count < UI_APP_LOG_MAX_LINES)
    {
        strncpy(s_log_lines[s_log_count],
                line,
                sizeof(s_log_lines[s_log_count]) - 1);

        s_log_lines[s_log_count][sizeof(s_log_lines[s_log_count]) - 1] = '\0';
        s_log_count++;
    }
    else
    {
        for (i = 1; i < UI_APP_LOG_MAX_LINES; i++)
        {
            strncpy(s_log_lines[i - 1],
                    s_log_lines[i],
                    sizeof(s_log_lines[i - 1]) - 1);

            s_log_lines[i - 1][sizeof(s_log_lines[i - 1]) - 1] = '\0';
        }

        strncpy(s_log_lines[UI_APP_LOG_MAX_LINES - 1],
                line,
                sizeof(s_log_lines[UI_APP_LOG_MAX_LINES - 1]) - 1);

        s_log_lines[UI_APP_LOG_MAX_LINES - 1][sizeof(s_log_lines[UI_APP_LOG_MAX_LINES - 1]) - 1] = '\0';
    }
}

static void UI_LogRender(void)
{
    uint8_t i;
    lv_obj_t *list;

    if (s_ui == NULL)
    {
        return;
    }

    list = s_ui->screen_log_list_log_information;

    if (list == NULL || !lv_obj_is_valid(list))
    {
        return;
    }

    UI_ListClear(list);

    for (i = 0; i < s_log_count; i++)
    {
        UI_ListAddKeepLast(list,
                           s_log_lines[i],
                           UI_APP_LOG_MAX_LINES);
    }
}

static void UI_WeatherRefreshEvent(lv_event_t *e)
{
    (void)e;

    UI_RequestSet(UI_REQ_WEATHER_REFRESH);
    UI_App_AddLog(UI_EVENT_WEATHER, "Weather refresh pressed");
}

static void UI_SensorRefreshEvent(lv_event_t *e)
{
    (void)e;

    UI_RequestSet(UI_REQ_SENSOR_REFRESH);
    UI_App_AddLog(UI_EVENT_SENSOR, "Sensor refresh pressed");
}




static void UI_LogSaveEvent(lv_event_t *e)
{
    (void)e;
    UI_RequestSet(UI_REQ_MANUAL_SAVE);
}

static void UI_TimeSyncEvent(lv_event_t *e)
{
    (void)e;

    UI_RequestSet(UI_REQ_TIME_SYNC);
    UI_App_AddLog(UI_EVENT_INFO, "Time sync pressed");
}

static void UI_ConnectWifiEvent(lv_event_t *e)
{
    (void)e;

    UI_RequestSet(UI_REQ_WIFI_CONNECT);
    UI_App_AddLog(UI_EVENT_WIFI, "Connect WiFi pressed");
}

static void UI_ClearLogEvent(lv_event_t *e)
{
    (void)e;
    UI_RequestSet(UI_REQ_CLEAR_LOG);
}

static void UI_BrightnessEvent(lv_event_t *e)
{
    int32_t value;
    lv_obj_t *slider;

    (void)e;

    if (s_ui == NULL)
    {
        return;
    }

    slider = s_ui->screen_set_slider_set_brightness;
    if (!UI_ObjIsReady(slider))
    {
        return;
    }

    value = lv_slider_get_value(slider);

    if (value < 5)
    {
        value = 5;
    }

    if (value > 100)
    {
        value = 100;
    }

    s_brightness_percent = (uint8_t)value;
    UI_RequestSet(UI_REQ_BRIGHTNESS_CHANGED);

    UI_App_UpdateSettings(NULL);
}


static void UI_BindEvents(void)
{
    lv_obj_t *obj;

    if (s_ui == NULL)
    {
        return;
    }

    UI_ClearInvalidBoundObjects();

		 /*
     * Home 页面创建后。
     */
		obj = s_ui->screen_home_label_home_weather;

		if (UI_ObjIsReady(obj) && obj != s_bound_home_weather)
		{
				s_bound_home_weather = obj;

				UI_ApplyLatestTime();
				UI_ApplyLatestDate();
				UI_ApplyLatestWeather();
				UI_ApplyLatestAHT20();

				APP_LOG_DEBUG("[UI] Home applied\r\n");
		}
		
    /*
     * Weather 页面创建后，绑定刷新天气按钮。
     */
    obj = s_ui->screen_weather_btn_weather_refresh;

		if (UI_ObjIsReady(obj) && obj != s_bound_weather_refresh)
		{
				lv_obj_add_event_cb(obj,
														UI_WeatherRefreshEvent,
														LV_EVENT_CLICKED,
														NULL);

				s_bound_weather_refresh = obj;
				UI_ApplyLatestWeather();

				APP_LOG_DEBUG("[UI] Weather refresh button bound\r\n");
		}

    /*
     * Sensor 页面创建后，绑定刷新传感器按钮。
     */
    obj = s_ui->screen_sensor_btn_sensor_refresh;

    if (UI_ObjIsReady(obj) && obj != s_bound_sensor_refresh)
    {
        lv_obj_add_event_cb(obj,
                            UI_SensorRefreshEvent,
                            LV_EVENT_CLICKED,
                            NULL);

        s_bound_sensor_refresh = obj;
				UI_ApplyLatestAHT20();
				UI_ApplyLatestLPS22HH();
				UI_ApplyLatestLIS2DH12();
				UI_ApplyLatestOPT3001();
        APP_LOG_DEBUG("[UI] Sensor refresh button bound\r\n");
    }

		/*
		 * Log 页面创建后，恢复日志列表。
		 */
		obj = s_ui->screen_log_list_log_information;

		if (UI_ObjIsReady(obj) && obj != s_bound_log_list)
		{
				s_bound_log_list = obj;
				UI_LogRender();

				APP_LOG_DEBUG("[UI] Log list restored\r\n");
		}
		
    /*
     * Log 页面创建后，绑定保存按钮。
     */
    obj = s_ui->screen_log_btn_log_save;

    if (UI_ObjIsReady(obj) && obj != s_bound_log_save)
    {
        lv_obj_add_event_cb(obj,
                            UI_LogSaveEvent,
                            LV_EVENT_CLICKED,
                            NULL);

        s_bound_log_save = obj;
        APP_LOG_DEBUG("[UI] Log save button bound\r\n");
    }

    /*
     * Set 页面创建后，绑定同步时间按钮。
     */
    obj = s_ui->screen_set_btn_set_sync_time;

    if (UI_ObjIsReady(obj) && obj != s_bound_sync_time)
    {
        lv_obj_add_event_cb(obj,
                            UI_TimeSyncEvent,
                            LV_EVENT_CLICKED,
                            NULL);

        s_bound_sync_time = obj;
        APP_LOG_DEBUG("[UI] Sync time button bound\r\n");
    }
		
		/*
		 * Set 页面创建后，绑定 Connect WiFi 按钮。
		 */

		obj = s_ui->screen_set_btn_set_connectwifi;

		if (UI_ObjIsReady(obj) &&  obj != s_bound_connect_wifi)
		{
				lv_obj_add_event_cb(obj,
														UI_ConnectWifiEvent,
														LV_EVENT_CLICKED,
														NULL);

				s_bound_connect_wifi = obj;
				APP_LOG_DEBUG("[UI] Connect WiFi button bound\r\n");
		}

    /*
     * Set 页面创建后，绑定清除按钮。
     */
    obj = s_ui->screen_set_btn_set_clear;

    if (UI_ObjIsReady(obj) && obj != s_bound_clear_log)
    {
        lv_obj_add_event_cb(obj,
                            UI_ClearLogEvent,
                            LV_EVENT_CLICKED,
                            NULL);

        s_bound_clear_log = obj;
        APP_LOG_DEBUG("[UI] Clear button bound\r\n");
    }

    /*
     * Set 页面和 Slider 创建后：
     * 1. 设置范围；
     * 2. 设置初始值；
     * 3. 绑定值变化事件。
     */
    /*
		 * Set 页面和 Slider 创建后：
		 * 1. 检查旧对象是否已经失效；
		 * 2. 设置范围；
		 * 3. 恢复当前亮度值；
		 * 4. 绑定值变化事件。
		 */
			obj = s_ui->screen_set_slider_set_brightness;

			if (UI_ObjIsReady(obj) && obj != s_bound_brightness_slider)
			{
					lv_slider_set_range(obj, 5, 100);

					lv_slider_set_value(obj,
															s_brightness_percent,
															LV_ANIM_OFF);

					lv_obj_add_event_cb(obj,
															UI_BrightnessEvent,
															LV_EVENT_VALUE_CHANGED,
															NULL);

					s_bound_brightness_slider = obj;

					UI_App_UpdateSettings(NULL);

					APP_LOG_DEBUG("[UI] Brightness slider initialized and bound\r\n");
			}
}

void UI_App_Init(lv_ui *ui)
{
    s_ui = ui;

    if (s_ui == NULL)
    {
        APP_LOG_ERROR("[UI] Init failed: ui is NULL\r\n");
        return;
    }

    UI_RequestInit();

    /*
     * 这里只初始化当前已经存在的控件。
     * 尚未创建的页面会在 UI_App_Process() 中处理。
     */
    UI_BindEvents();

    APP_LOG_INFO("[UI] App initialized\r\n");
}


void UI_App_Process(void)
{
    if (s_ui == NULL)
    {
        return;
    }
		/*
     * 预留函数。
     * 后面可以放 WiFi 图标闪烁、动画、弹窗超时关闭等 UI 自己的周期任务。
     */
		
    /*
     * GUI Guider 可能按需创建页面。
     * 每次检查新创建的控件，并只绑定一次。
     */
    UI_BindEvents();
}


void UI_App_UpdateAll(const UI_AppData_t *data)
{
    if (data == NULL)
    {
        return;
    }

    UI_App_UpdateTime(&data->time);
    UI_App_UpdateDate(&data->date);
    UI_App_UpdateWeather(&data->weather);
    UI_App_UpdateSensor(&data->sensor);
    UI_App_UpdateLatestRecord(&data->latest_record);
    UI_App_UpdateSettings(&data->settings);
}

void UI_App_UpdateTime(const UI_Time_t *time)
{
    if (time == NULL)
    {
        return;
    }

    /*
     * 保存最近一次 RTC 读取到的时间。
     * 即使 Home 页面被切走，这个数据也还在。
     */
    s_last_time = *time;
    s_time_data_valid = 1;

    /*
     * 如果 Home 页面当前已经创建，就立即刷新。
     * 如果还没创建，等 UI_BindEvents() 检测到页面后再恢复显示。
     */
    UI_ApplyLatestTime();
}


void UI_App_UpdateDate(const UI_Date_t *date)
{
    if (date == NULL)
    {
        return;
    }

    /*
     * 保存最近一次日期。
     */
    s_last_date = *date;
    s_date_data_valid = 1;

    /*
     * date->week 是 const char *，可能指向外部字符串。
     * 为了安全，复制到 s_last_week 里面保存。
     */
    if (date->week != NULL)
    {
        snprintf(s_last_week,
                 sizeof(s_last_week),
                 "%s",
                 date->week);

        s_last_date.week = s_last_week;
    }
    else
    {
        s_last_week[0] = '\0';
        s_last_date.week = NULL;
    }

    UI_ApplyLatestDate();
}


void UI_App_UpdateWeather(const UI_Weather_t *weather)
{
    if (weather == NULL)
    {
        return;
    }

    memset(&s_last_weather, 0, sizeof(s_last_weather));
    memcpy(&s_last_weather, weather, sizeof(s_last_weather));
    s_weather_data_valid = 1;

    UI_ApplyLatestWeather();
}


//更新温湿度显示
void UI_App_UpdateAHT20(int32_t temp_x100, uint32_t humi_x100)
{
    /*
     * 保存最近一次读取成功的数据。
     * 即使页面被删除，数据变量仍然存在。
     */
    s_last_aht20_temp_x100 = temp_x100;
    s_last_aht20_humi_x100 = humi_x100;
    s_aht20_data_valid = 1;

    /* 更新当前已经创建的 Sensor 页面 */
    UI_ApplyLatestAHT20();
}



//更新气压显示
void UI_App_UpdateLPS22HH(int32_t pressure_x100)
{
    s_last_lps22hh_pressure_x100 = pressure_x100;
    s_lps22hh_data_valid = 1;

    /* 更新当前已经创建的 Sensor 页面 */
    UI_ApplyLatestLPS22HH();
}

void UI_App_UpdateLIS2DH12(int32_t x_mg,
                           int32_t y_mg,
                           int32_t z_mg,
                           int32_t motion)
{	
		(void)x_mg;
    (void)y_mg;
    (void)z_mg;
//    s_last_lis2dh12_x_mg = x_mg;
//    s_last_lis2dh12_y_mg = y_mg;
//    s_last_lis2dh12_z_mg = z_mg;
	
    s_last_lis2dh12_motion = motion;
    s_lis2dh12_data_valid = 1;

    UI_ApplyLatestLIS2DH12();
}

void UI_App_UpdateOPT3001(uint32_t lux_x100)
{
    s_last_opt3001_lux_x100 = lux_x100;
    s_opt3001_data_valid = 1;

    UI_ApplyLatestOPT3001();
}

void UI_App_ShowSensorError(void)
{
    if (s_ui == NULL)
    {
        return;
    }

    UI_SetLabel(s_ui->screen_sensor_label_sensor_temp_value, "--");
    UI_SetLabel(s_ui->screen_sensor_label_sensor_humidity_value, "--");
    UI_SetLabel(s_ui->screen_sensor_label_sensor_air_value, "--");
    UI_SetLabel(s_ui->screen_sensor_label_sensor_motion_value, "--");
    UI_SetLabel(s_ui->screen_sensor_label_sensor_light_value, "--");
}


void UI_App_ShowWeatherError(const char *text)
{
    UI_Weather_t weather;

    memset(&weather, 0, sizeof(weather));

    strncpy(weather.city, "--", sizeof(weather.city) - 1);

    if (text != NULL)
    {
        strncpy(weather.weather, text, sizeof(weather.weather) - 1);
    }
    else
    {
        strncpy(weather.weather, "Error", sizeof(weather.weather) - 1);
    }

    strncpy(weather.last_update, "--", sizeof(weather.last_update) - 1);
    strncpy(weather.ip, "--", sizeof(weather.ip) - 1);

    weather.temperature = 0;
    weather.net_state = UI_NET_DISCONNECTED;

    UI_App_UpdateWeather(&weather);
}



void UI_App_UpdateSensor(const UI_Sensor_t *sensor)
{
    char temp_buf[24];
    char humi_buf[24];
    char pressure_buf[24];
    char line[32];

    if (s_ui == NULL || sensor == NULL)
    {
        return;
    }

    UI_FormatTemp(temp_buf, sizeof(temp_buf), sensor->temp_x100);
    UI_FormatHumi(humi_buf, sizeof(humi_buf), sensor->humi_x100);
    UI_FormatPressure(pressure_buf, sizeof(pressure_buf), sensor->pressure_x100);

    UI_SetLabel(s_ui->screen_sensor_label_sensor_temp_value, temp_buf);
    UI_SetLabel(s_ui->screen_sensor_label_sensor_humidity_value, humi_buf);


    snprintf(line, sizeof(line), "%lu lx", (unsigned long)sensor->light_lx);
    UI_SetLabel(s_ui->screen_sensor_label_sensor_light_value, line);

    UI_SetLabel(s_ui->screen_sensor_label_sensor_air_value, pressure_buf);

    UI_SetLabel(s_ui->screen_sensor_label_sensor_motion_value,
                (sensor->motion[0] != '\0') ? sensor->motion : "Stable");
}





void UI_App_UpdateLatestRecord(const UI_Record_t *record)
{
    char temp_buf[24];
    char humi_buf[24];
    char time_buf[24];
    char line[32];

    if (s_ui == NULL || record == NULL)
    {
        return;
    }

    if (!record->valid)
    {
        UI_SetLabel(s_ui->screen_log_label_log_last_record, "Record\n--");
        UI_SetLabel(s_ui->screen_log_label_log_last_temp, "Temp\n--");
        UI_SetLabel(s_ui->screen_log_label_log_last_humi, "Humidity\n--");
        UI_SetLabel(s_ui->screen_log_label_log_last_time, "Uptime\n--");
        return;
    }

    UI_FormatTemp(temp_buf, sizeof(temp_buf), record->temp_x100);
    UI_FormatHumi(humi_buf, sizeof(humi_buf), record->humi_x100);
    UI_FormatUptime(time_buf, sizeof(time_buf), record->uptime_ms);

    snprintf(line, sizeof(line), "Record\n#%lu", (unsigned long)record->sequence);
    UI_SetLabel(s_ui->screen_log_label_log_last_record, line);

    snprintf(line, sizeof(line), "Temp\n%s", temp_buf);
    UI_SetLabel(s_ui->screen_log_label_log_last_temp, line);

    snprintf(line, sizeof(line), "Humidity\n%s", humi_buf);
    UI_SetLabel(s_ui->screen_log_label_log_last_humi, line);

    if (record->time_text[0] != '\0')
    {
        snprintf(line, sizeof(line), "Time\n%s", record->time_text);
    }
    else
    {
        snprintf(line, sizeof(line), "Uptime\n%s", time_buf);
    }

    UI_SetLabel(s_ui->screen_log_label_log_last_time, line);
}

void UI_App_UpdateSettings(const UI_Settings_t *settings)
{
    char buf[32];

    if (s_ui == NULL)
    {
        return;
    }

    if (settings != NULL)
    {
        if (settings->ssid[0] != '\0')
        {
            UI_SetLabel(s_ui->screen_set_label_set_wifi_value, settings->ssid);
        }

        if (settings->version[0] != '\0')
        {
            UI_SetLabel(s_ui->screen_set_label_set_version_value, settings->version);
        }

        s_brightness_percent = settings->brightness_percent;

        if (s_brightness_percent < 5)
        {
            s_brightness_percent = 5;
        }

        if (s_brightness_percent > 100)
        {
            s_brightness_percent = 100;
        }

        if (s_ui->screen_set_slider_set_brightness != NULL &&
						lv_obj_is_valid(s_ui->screen_set_slider_set_brightness))
				{
						lv_slider_set_value(s_ui->screen_set_slider_set_brightness,
																s_brightness_percent,
																LV_ANIM_OFF);
				}
    }

    snprintf(buf, sizeof(buf), "%u%%", s_brightness_percent);
    UI_SetLabel(s_ui->screen_set_label_set_lcd_brightness_value, buf);
}

void UI_App_AddLog(UI_EventType_t type, const char *text)
{
    char line[96];

    if (text == NULL)
    {
        return;
    }

    snprintf(line,
             sizeof(line),
             "%s %s",
             UI_EventPrefix(type),
             text);

    UI_LogCacheAdd(line);
    UI_LogRender();
}

void UI_App_ClearLog(void)
{
    s_log_count = 0;
    UI_LogRender();
}

uint8_t UI_App_TakeWeatherRefreshRequest(void)
{
    return UI_RequestTake(UI_REQ_WEATHER_REFRESH);
}

uint8_t UI_App_TakeSensorRefreshRequest(void)
{
    return UI_RequestTake(UI_REQ_SENSOR_REFRESH);
}

uint8_t UI_App_TakeManualSaveRequest(void)
{
    return UI_RequestTake(UI_REQ_MANUAL_SAVE);
}

uint8_t UI_App_TakeTimeSyncRequest(void)
{
    return UI_RequestTake(UI_REQ_TIME_SYNC);
}

uint8_t UI_App_TakeWifiConnectRequest(void)
{
    return UI_RequestTake(UI_REQ_WIFI_CONNECT);
}

uint8_t UI_App_TakeClearLogRequest(void)
{
    return UI_RequestTake(UI_REQ_CLEAR_LOG);
}

uint8_t UI_App_TakeBrightnessChanged(uint8_t *brightness_percent)
{
    uint8_t value;

    value = UI_RequestTake(UI_REQ_BRIGHTNESS_CHANGED);

    if (brightness_percent != NULL)
    {
        *brightness_percent = s_brightness_percent;
    }

    return value;
}