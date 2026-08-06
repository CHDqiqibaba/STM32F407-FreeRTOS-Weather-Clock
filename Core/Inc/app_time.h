#ifndef __APP_TIME_H
#define __APP_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>

#define APP_TIMEZONE_OFFSET_SEC    (8UL * 3600UL)
#define APP_RTC_BKP_REG            RTC_BKP_DR0
#define APP_RTC_BKP_MAGIC          0xA55A5AA5UL

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t weekday;
} AppTime_t;

uint8_t App_SyncTimeFromESP(void);
uint8_t App_ApplySNTPResponse(const char *response);
void App_Time_MarkRTCValid(void);
uint8_t App_Time_GetUnix(uint32_t *unix_time);
uint8_t App_Time_FormatUnixLocal(uint32_t unix_time,
                                 char *buf,
                                 uint16_t buf_size);
void App_UpdateTimeUI(void);

#ifdef __cplusplus
}
#endif

#endif
