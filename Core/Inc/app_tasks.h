#ifndef APP_TASKS_H
#define APP_TASKS_H

#include <stdint.h>

void App_Tasks_InitBeforeScheduler(void);

void App_Task_UI(void);
void App_Task_Network(void);
void App_Task_Sensor(void);
void App_Task_Storage(void);

uint8_t App_NetworkStartup(void);
uint8_t App_IsWifiConnected(void);

#endif