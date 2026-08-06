#ifndef APP_LOG_H
#define APP_LOG_H

#include <stdio.h>

#define APP_LOG_LEVEL_NONE   0
#define APP_LOG_LEVEL_ERROR  1
#define APP_LOG_LEVEL_BOOT   2
#define APP_LOG_LEVEL_INFO   3
#define APP_LOG_LEVEL_DEBUG  4

#ifndef APP_LOG_LEVEL
#define APP_LOG_LEVEL APP_LOG_LEVEL_BOOT
#endif

#ifndef APP_LOG_UART_TIMEOUT_MS
#define APP_LOG_UART_TIMEOUT_MS 10U
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_ERROR)
#define APP_LOG_ERROR(...)   printf(__VA_ARGS__)
#else
#define APP_LOG_ERROR(...)   ((void)0)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_BOOT)
#define APP_LOG_BOOT(...)    printf(__VA_ARGS__)
#else
#define APP_LOG_BOOT(...)    ((void)0)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_INFO)
#define APP_LOG_INFO(...)    printf(__VA_ARGS__)
#else
#define APP_LOG_INFO(...)    ((void)0)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
#define APP_LOG_DEBUG(...)   printf(__VA_ARGS__)
#else
#define APP_LOG_DEBUG(...)   ((void)0)
#endif

#endif
