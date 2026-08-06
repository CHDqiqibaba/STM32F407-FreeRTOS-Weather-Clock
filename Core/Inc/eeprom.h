#ifndef __EEPROM_H
#define __EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#define EEPROM_CONFIG_VERSION       2U

typedef enum
{
    EEPROM_EVENT_INFO = 0,
    EEPROM_EVENT_WIFI,
    EEPROM_EVENT_WEATHER,
    EEPROM_EVENT_SENSOR,
    EEPROM_EVENT_EEPROM,
    EEPROM_EVENT_TIME,
    EEPROM_EVENT_ERROR
} EEPROM_EventType_t;

typedef struct
{
    uint32_t magic;
    uint16_t version;

    uint8_t brightness_percent;
    uint8_t auto_brightness;

    uint16_t weather_interval_min;
    uint16_t sensor_interval_sec;
    uint16_t history_save_interval_sec;

    char wifi_ssid[32];
    char weather_city[24];

    uint16_t checksum;
    uint16_t reserved;
} EEPROM_AppConfig_t;

typedef struct
{
    uint32_t magic;
    uint32_t sequence;

    uint32_t tick_ms;
    uint32_t unix_time;

    int32_t temperature_x100;
    uint32_t humidity_x100;
    int32_t pressure_x100;
    uint32_t lux_x100;

    int32_t acc_x_mg;
    int32_t acc_y_mg;
    int32_t acc_z_mg;
    uint8_t motion;

    int16_t weather_temperature;

    uint8_t reserved8;
    uint16_t checksum;
} EEPROM_HistoryRecord_t;

/* 兼容你之前的函数名 */
typedef EEPROM_HistoryRecord_t EEPROM_EnvRecord_t;

typedef struct
{
    uint32_t magic;
    uint32_t sequence;

    uint32_t tick_ms;
    uint32_t unix_time;

    uint8_t type;
    char text[48];

    uint8_t reserved8;
    uint16_t checksum;
} EEPROM_EventRecord_t;

uint8_t EEPROM_Init(void);

uint8_t EEPROM_ReadBytes(uint16_t mem_addr, uint8_t *data, uint16_t len);
uint8_t EEPROM_WriteBytes(uint16_t mem_addr, const uint8_t *data, uint16_t len);

/* 配置区 */
void EEPROM_LoadDefaultConfig(EEPROM_AppConfig_t *config);
uint8_t EEPROM_LoadConfig(EEPROM_AppConfig_t *config);
uint8_t EEPROM_SaveConfig(const EEPROM_AppConfig_t *config);

/* 历史区 */
uint8_t EEPROM_SaveHistoryRecord(const EEPROM_HistoryRecord_t *record);
uint8_t EEPROM_ReadLatestHistoryRecord(EEPROM_HistoryRecord_t *record);
uint8_t EEPROM_ReadHistoryRecordByIndex(uint32_t back_index,
                                        EEPROM_HistoryRecord_t *record);

/* 事件区 */
uint8_t EEPROM_SaveEventLog(EEPROM_EventType_t type,
                            const char *text,
                            uint32_t tick_ms,
                            uint32_t unix_time);

uint8_t EEPROM_ReadLatestEventLog(EEPROM_EventRecord_t *record);
uint8_t EEPROM_ReadEventLogByIndex(uint32_t back_index,
                                   EEPROM_EventRecord_t *record);

/* 兼容旧接口 */
uint8_t EEPROM_SaveEnvRecord(int32_t temperature_x100,
                             uint32_t humidity_x100,
                             uint32_t tick_ms);

uint8_t EEPROM_ReadLatestEnvRecord(EEPROM_EnvRecord_t *record);

void EEPROM_PrintEnvRecord(const EEPROM_EnvRecord_t *record);
void EEPROM_PrintEventRecord(const EEPROM_EventRecord_t *record);

#ifdef __cplusplus
}
#endif

#endif