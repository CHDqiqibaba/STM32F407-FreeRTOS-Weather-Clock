#ifndef __WEATHER_H
#define __WEATHER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>

typedef struct
{
    char city[24];
    char text[24];
    char code[8];
    int16_t temperature;

    char last_update[32];
    char update_time[8];
} Weather_Now_t;

uint8_t Weather_ParseNowResponse(const char *response, Weather_Now_t *weather);
void Weather_PrintNow(const Weather_Now_t *weather);

#ifdef __cplusplus
}
#endif

#endif