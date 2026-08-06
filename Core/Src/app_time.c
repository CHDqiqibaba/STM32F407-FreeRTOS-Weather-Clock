#include "app_time.h"
#include "app_log.h"
#include "esp_at.h"
#include "rtc.h"
#include "ui_app.h"
#include "ui_msg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static uint8_t App_TimeMonthFromString(const char *mon)
{
    if (strcmp(mon, "Jan") == 0) return 1;
    if (strcmp(mon, "Feb") == 0) return 2;
    if (strcmp(mon, "Mar") == 0) return 3;
    if (strcmp(mon, "Apr") == 0) return 4;
    if (strcmp(mon, "May") == 0) return 5;
    if (strcmp(mon, "Jun") == 0) return 6;
    if (strcmp(mon, "Jul") == 0) return 7;
    if (strcmp(mon, "Aug") == 0) return 8;
    if (strcmp(mon, "Sep") == 0) return 9;
    if (strcmp(mon, "Oct") == 0) return 10;
    if (strcmp(mon, "Nov") == 0) return 11;
    if (strcmp(mon, "Dec") == 0) return 12;

    return 0;
}

static uint8_t App_TimeWeekFromString(const char *week)
{
    if (strcmp(week, "Mon") == 0) return RTC_WEEKDAY_MONDAY;
    if (strcmp(week, "Tue") == 0) return RTC_WEEKDAY_TUESDAY;
    if (strcmp(week, "Wed") == 0) return RTC_WEEKDAY_WEDNESDAY;
    if (strcmp(week, "Thu") == 0) return RTC_WEEKDAY_THURSDAY;
    if (strcmp(week, "Fri") == 0) return RTC_WEEKDAY_FRIDAY;
    if (strcmp(week, "Sat") == 0) return RTC_WEEKDAY_SATURDAY;
    if (strcmp(week, "Sun") == 0) return RTC_WEEKDAY_SUNDAY;

    return RTC_WEEKDAY_MONDAY;
}

static const char *App_TimeWeekName(uint8_t weekday)
{
    switch (weekday)
    {
        case RTC_WEEKDAY_MONDAY:    return "MON";
        case RTC_WEEKDAY_TUESDAY:   return "TUE";
        case RTC_WEEKDAY_WEDNESDAY: return "WED";
        case RTC_WEEKDAY_THURSDAY:  return "THU";
        case RTC_WEEKDAY_FRIDAY:    return "FRI";
        case RTC_WEEKDAY_SATURDAY:  return "SAT";
        case RTC_WEEKDAY_SUNDAY:    return "SUN";
        default:                    return "--";
    }
}

void App_Time_MarkRTCValid(void)
{
#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
    uint32_t readback;
#endif

    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, APP_RTC_BKP_REG, APP_RTC_BKP_MAGIC);

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
    readback = HAL_RTCEx_BKUPRead(&hrtc, APP_RTC_BKP_REG);

    APP_LOG_DEBUG("RTC BKP mark saved: 0x%08lX\r\n",
                  (unsigned long)APP_RTC_BKP_MAGIC);
    APP_LOG_DEBUG("RTC BKP readback: 0x%08lX\r\n",
                  (unsigned long)readback);
#endif
}

static uint8_t App_Time_IsLeapYear(uint16_t year)
{
    if ((year % 400U) == 0U)
    {
        return 1;
    }

    if ((year % 100U) == 0U)
    {
        return 0;
    }

    return (uint8_t)((year % 4U) == 0U);
}

static uint8_t App_Time_DaysInMonth(uint16_t year, uint8_t month)
{
    static const uint8_t days_table[12] =
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month < 1U || month > 12U)
    {
        return 0;
    }

    if (month == 2U && App_Time_IsLeapYear(year))
    {
        return 29;
    }

    return days_table[month - 1U];
}

static uint32_t App_Time_DateTimeToUnixLocal(uint16_t year,
                                             uint8_t month,
                                             uint8_t day,
                                             uint8_t hour,
                                             uint8_t min,
                                             uint8_t sec)
{
    uint32_t days = 0;
    uint16_t y;
    uint8_t m;

    for (y = 1970U; y < year; y++)
    {
        days += App_Time_IsLeapYear(y) ? 366UL : 365UL;
    }

    for (m = 1U; m < month; m++)
    {
        days += App_Time_DaysInMonth(year, m);
    }

    days += (uint32_t)(day - 1U);

    return days * 86400UL +
           (uint32_t)hour * 3600UL +
           (uint32_t)min * 60UL +
           (uint32_t)sec;
}

static void App_Time_UnixLocalToDateTime(uint32_t local_seconds,
                                         AppTime_t *time)
{
    uint32_t days;
    uint32_t remain;
    uint16_t year;
    uint16_t year_days;
    uint8_t month;
    uint8_t dim;

    if (time == NULL)
    {
        return;
    }

    memset(time, 0, sizeof(*time));

    days = local_seconds / 86400UL;
    remain = local_seconds % 86400UL;

    time->hour = (uint8_t)(remain / 3600UL);
    remain %= 3600UL;
    time->min = (uint8_t)(remain / 60UL);
    time->sec = (uint8_t)(remain % 60UL);

    year = 1970U;
    while (1)
    {
        year_days = App_Time_IsLeapYear(year) ? 366U : 365U;

        if (days < year_days)
        {
            break;
        }

        days -= year_days;
        year++;
    }

    month = 1U;
    while (month <= 12U)
    {
        dim = App_Time_DaysInMonth(year, month);

        if (days < dim)
        {
            break;
        }

        days -= dim;
        month++;
    }

    time->year = year;
    time->month = month;
    time->day = (uint8_t)(days + 1U);
}

uint8_t App_Time_GetUnix(uint32_t *unix_time)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_date = {0};
    uint32_t local_seconds;
    uint16_t year;
    uint8_t days_in_month;

    if (unix_time == NULL)
    {
        return 1;
    }

    *unix_time = 0;

    if (HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN) != HAL_OK)
    {
        return 2;
    }

    if (HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN) != HAL_OK)
    {
        return 3;
    }

    year = (uint16_t)(2000U + rtc_date.Year);
    days_in_month = App_Time_DaysInMonth(year, rtc_date.Month);

    if (year < 2024U ||
        days_in_month == 0U ||
        rtc_date.Date < 1U ||
        rtc_date.Date > days_in_month ||
        rtc_time.Hours > 23U ||
        rtc_time.Minutes > 59U ||
        rtc_time.Seconds > 59U)
    {
        return 4;
    }

    local_seconds = App_Time_DateTimeToUnixLocal(year,
                                                 rtc_date.Month,
                                                 rtc_date.Date,
                                                 rtc_time.Hours,
                                                 rtc_time.Minutes,
                                                 rtc_time.Seconds);

    if (local_seconds < APP_TIMEZONE_OFFSET_SEC)
    {
        return 5;
    }

    *unix_time = local_seconds - APP_TIMEZONE_OFFSET_SEC;
    return 0;
}

uint8_t App_Time_FormatUnixLocal(uint32_t unix_time,
                                 char *buf,
                                 uint16_t buf_size)
{
    AppTime_t time;
    uint32_t local_seconds;

    if (buf == NULL || buf_size == 0U)
    {
        return 1;
    }

    if (unix_time == 0U)
    {
        snprintf(buf, buf_size, "--");
        return 2;
    }

    local_seconds = unix_time + APP_TIMEZONE_OFFSET_SEC;
    App_Time_UnixLocalToDateTime(local_seconds, &time);

    snprintf(buf,
             buf_size,
             "%04u-%02u-%02u %02u:%02u",
             time.year,
             time.month,
             time.day,
             time.hour,
             time.min);

    return 0;
}

static uint8_t App_ParseSNTPTime(const char *response, AppTime_t *time)
{
    const char *p;
    const char *scan;
    char week_str[4] = {0};
    char mon_str[4] = {0};
    int day;
    int hour;
    int min;
    int sec;
    int year;
    uint8_t month;
    uint8_t days_in_month;
    uint8_t last_error = 2;

    if (response == NULL || time == NULL)
    {
        return 1;
    }

    scan = response;

    while ((p = strstr(scan, "+CIPSNTPTIME:")) != NULL)
    {
        p += strlen("+CIPSNTPTIME:");

        while (*p == ' ')
        {
            p++;
        }

        if (sscanf(p,
                   "%3s %3s %d %d:%d:%d %d",
                   week_str,
                   mon_str,
                   &day,
                   &hour,
                   &min,
                   &sec,
                   &year) != 7)
        {
            last_error = 3;
            scan = p;
            continue;
        }

        month = App_TimeMonthFromString(mon_str);
        if (month == 0)
        {
            last_error = 4;
            scan = p;
            continue;
        }

        if (year < 2024)
        {
            last_error = 5;
            scan = p;
            continue;
        }

        days_in_month = App_Time_DaysInMonth((uint16_t)year, month);
        if (days_in_month == 0U ||
            day < 1 ||
            day > days_in_month ||
            hour < 0 ||
            hour > 23 ||
            min < 0 ||
            min > 59 ||
            sec < 0 ||
            sec > 59)
        {
            last_error = 6;
            scan = p;
            continue;
        }

        time->year = (uint16_t)year;
        time->month = month;
        time->day = (uint8_t)day;
        time->hour = (uint8_t)hour;
        time->min = (uint8_t)min;
        time->sec = (uint8_t)sec;
        time->weekday = App_TimeWeekFromString(week_str);

        return 0;
    }

    return last_error;
}

static uint8_t App_SetRTC(const AppTime_t *time)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_date = {0};

    if (time == NULL)
    {
        return 1;
    }

    rtc_time.Hours = time->hour;
    rtc_time.Minutes = time->min;
    rtc_time.Seconds = time->sec;
    rtc_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    rtc_time.StoreOperation = RTC_STOREOPERATION_RESET;

    rtc_date.WeekDay = time->weekday;
    rtc_date.Month = time->month;
    rtc_date.Date = time->day;
    rtc_date.Year = (uint8_t)(time->year - 2000);

    if (HAL_RTC_SetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN) != HAL_OK)
    {
        return 2;
    }

    if (HAL_RTC_SetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN) != HAL_OK)
    {
        return 3;
    }

    App_Time_MarkRTCValid();

    return 0;
}

uint8_t App_ApplySNTPResponse(const char *response)
{
    AppTime_t time;
    uint8_t ret;

    if (response == NULL)
    {
        return 1;
    }

    memset(&time, 0, sizeof(time));

    ret = App_ParseSNTPTime(response, &time);
    if (ret != 0)
    {
        return ret;
    }

    ret = App_SetRTC(&time);
    if (ret != 0)
    {
        return (uint8_t)(10 + ret);
    }

    return 0;
}

uint8_t App_SyncTimeFromESP(void)
{
    char response[128];
    AppTime_t time;
    uint8_t ret;
    uint8_t retry;

    memset(response, 0, sizeof(response));
    memset(&time, 0, sizeof(time));

    ret = ESP_AT_SNTPConfig();
    if (ret != 0)
    {
        APP_LOG_ERROR("SNTP config failed, code=%u\r\n", ret);
        UI_Msg_PostLog(UI_EVENT_ERROR, "SNTP config failed");
        return 1;
    }

    for (retry = 0; retry < 2; retry++)
    {
        memset(response, 0, sizeof(response));

        ret = ESP_AT_GetSNTPTime(response, sizeof(response), 1500);
        if (ret == 0)
        {
            APP_LOG_DEBUG("SNTP raw response:\r\n%s\r\n", response);

            ret = App_ParseSNTPTime(response, &time);
            if (ret == 0)
            {
                ret = App_SetRTC(&time);
                if (ret == 0)
                {
                    APP_LOG_INFO("RTC sync OK\r\n");

                    UI_Msg_PostTimeRefresh();

                    UI_Msg_PostLog(UI_EVENT_INFO, "Time sync OK");
                    return 0;
                }

                APP_LOG_ERROR("RTC set failed, code=%u\r\n", ret);
                UI_Msg_PostLog(UI_EVENT_ERROR, "RTC set failed");
                return 2;
            }

            APP_LOG_ERROR("SNTP parse failed, code=%u\r\n", ret);
        }
        else
        {
            APP_LOG_ERROR("SNTP get failed, code=%u\r\n", ret);
        }

        HAL_Delay(200);
    }

    UI_Msg_PostLog(UI_EVENT_ERROR, "Time sync failed");
    return 3;
}

void App_UpdateTimeUI(void)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_date = {0};
    UI_Time_t ui_time;
    UI_Date_t ui_date;

    if (HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN) != HAL_OK)
    {
        return;
    }

    if (HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN) != HAL_OK)
    {		
        return;
    }
		
    ui_time.hour = rtc_time.Hours;
    ui_time.min = rtc_time.Minutes;
    ui_time.sec = rtc_time.Seconds;

    ui_date.year = 2000 + rtc_date.Year;
    ui_date.month = rtc_date.Month;
    ui_date.day = rtc_date.Date;
    ui_date.week = App_TimeWeekName(rtc_date.WeekDay);

    UI_App_UpdateTime(&ui_time);
    UI_App_UpdateDate(&ui_date);
}
