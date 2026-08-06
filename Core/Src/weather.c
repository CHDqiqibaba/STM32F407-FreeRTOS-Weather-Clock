#include "weather.h"
#include "app_log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static uint8_t Weather_FindStringValue(const char *json,
                                       const char *key,
                                       char *out,
                                       uint16_t out_size)
{
    char pattern[32];
    const char *start;
    const char *end;
    uint16_t len;

    if (json == NULL || key == NULL || out == NULL || out_size == 0)
    {
        return 1;
    }

    snprintf(pattern, sizeof(pattern), "\"%s\":\"", key);

    start = strstr(json, pattern);
    if (start == NULL)
    {
        return 2;
    }

    start += strlen(pattern);

    end = strchr(start, '\"');
    if (end == NULL)
    {
        return 3;
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

static void Weather_MakeUpdateTime(const char *last_update,
                                   char *update_time,
                                   uint16_t update_time_size)
{
    const char *t_pos;

    if (last_update == NULL || update_time == NULL || update_time_size < 6)
    {
        return;
    }

    t_pos = strchr(last_update, 'T');

    if (t_pos == NULL)
    {
        strncpy(update_time, "--:--", update_time_size - 1);
        update_time[update_time_size - 1] = '\0';
        return;
    }

    update_time[0] = t_pos[1];
    update_time[1] = t_pos[2];
    update_time[2] = ':';
    update_time[3] = t_pos[4];
    update_time[4] = t_pos[5];
    update_time[5] = '\0';
}

uint8_t Weather_ParseNowResponse(const char *response, Weather_Now_t *weather)
{
    const char *json;
    char temp_buf[8];

    if (response == NULL || weather == NULL)
    {
        return 1;
    }

    memset(weather, 0, sizeof(Weather_Now_t));
    memset(temp_buf, 0, sizeof(temp_buf));

    /*
     * ESP 可能返回：
     * +HTTPCGET:261,{"results":[...]}
     * OK
     *
     * 所以先定位真正 JSON 内容。
     */
    json = strstr(response, "\"results\"");
    if (json == NULL)
    {
        return 2;
    }

    if (Weather_FindStringValue(json, "name",
                                weather->city,
                                sizeof(weather->city)) != 0)
    {
        return 3;
    }

    if (Weather_FindStringValue(json, "text",
                                weather->text,
                                sizeof(weather->text)) != 0)
    {
        return 4;
    }

    if (Weather_FindStringValue(json, "code",
                                weather->code,
                                sizeof(weather->code)) != 0)
    {
        return 5;
    }

    if (Weather_FindStringValue(json, "temperature",
                                temp_buf,
                                sizeof(temp_buf)) != 0)
    {
        return 6;
    }

    weather->temperature = (int16_t)atoi(temp_buf);

    if (Weather_FindStringValue(json, "last_update",
                                weather->last_update,
                                sizeof(weather->last_update)) != 0)
    {
        return 7;
    }

    Weather_MakeUpdateTime(weather->last_update,
                           weather->update_time,
                           sizeof(weather->update_time));

    return 0;
}

void Weather_PrintNow(const Weather_Now_t *weather)
{
    if (weather == NULL)
    {
        return;
    }

    APP_LOG_DEBUG("Weather now:\r\n");
    APP_LOG_DEBUG("city        : %s\r\n", weather->city);
    APP_LOG_DEBUG("weather     : %s\r\n", weather->text);
    APP_LOG_DEBUG("code        : %s\r\n", weather->code);
    APP_LOG_DEBUG("temperature : %d C\r\n", weather->temperature);
    APP_LOG_DEBUG("last_update : %s\r\n", weather->last_update);
    APP_LOG_DEBUG("update_time : %s\r\n", weather->update_time);
}