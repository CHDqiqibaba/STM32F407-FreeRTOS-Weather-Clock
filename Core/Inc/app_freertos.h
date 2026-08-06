#ifndef APP_FREERTOS_H
#define APP_FREERTOS_H

#include "FreeRTOS.h"
#include "event_groups.h"

#define APP_EVENT_UI_ALIVE          ( 1UL << 0 )
#define APP_EVENT_WIFI_CONNECTED    ( 1UL << 1 )
#define APP_EVENT_NETWORK_ALIVE     ( 1UL << 2 )
#define APP_EVENT_SENSOR_ALIVE      ( 1UL << 3 )
#define APP_EVENT_STORAGE_ALIVE     ( 1UL << 4 )
#define APP_EVENT_ALIVE_MASK        ( APP_EVENT_UI_ALIVE      | \
                                      APP_EVENT_NETWORK_ALIVE | \
                                      APP_EVENT_SENSOR_ALIVE  | \
                                      APP_EVENT_STORAGE_ALIVE )

void App_FreeRTOS_Init(void);
EventGroupHandle_t App_FreeRTOS_GetEventGroup(void);

#endif
