#include "eeprom.h"
#include "app_log.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define EEPROM_I2C_ADDR              (0x50 << 1)

#define EEPROM_TOTAL_SIZE            65536U
#define EEPROM_PAGE_SIZE             128U

#define EEPROM_HEADER_ADDR           0x0000U
#define EEPROM_CONFIG_ADDR           0x0100U
#define EEPROM_HISTORY_START_ADDR    0x0400U
#define EEPROM_EVENT_START_ADDR      0xC000U

#define EEPROM_HEADER_MAGIC          0x45455048U  /* "EEPH" */
#define EEPROM_CONFIG_MAGIC          0x43464731U  /* "CFG1" */
#define EEPROM_HISTORY_MAGIC         0x48495354U  /* "HIST" */
#define EEPROM_EVENT_MAGIC           0x45564E54U  /* "EVNT" */

#define EEPROM_LAYOUT_VERSION        1U
#define EEPROM_MUTEX_TIMEOUT_MS      500U

typedef struct
{
    uint32_t magic;
    uint16_t layout_version;
    uint16_t header_size;

    uint32_t next_history_sequence;
    uint32_t next_event_sequence;

    uint16_t checksum;
    uint16_t reserved;
} EEPROM_Header_t;

static uint32_t eeprom_next_history_sequence = 0;
static uint32_t eeprom_next_event_sequence = 0;
static SemaphoreHandle_t eeprom_mutex = NULL;

static uint8_t EEPROM_IsSchedulerRunning(void)
{
    return (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED);
}

static uint8_t EEPROM_MutexInit(void)
{
    if (eeprom_mutex == NULL)
    {
        eeprom_mutex = xSemaphoreCreateRecursiveMutex();
        if (eeprom_mutex == NULL)
        {
            APP_LOG_ERROR("EEPROM mutex create failed\r\n");
            return 1;
        }
    }

    return 0;
}

static uint8_t EEPROM_Lock(void)
{
    if (EEPROM_MutexInit() != 0)
    {
        return 1;
    }

    if (!EEPROM_IsSchedulerRunning())
    {
        return 0;
    }

    if (xSemaphoreTakeRecursive(eeprom_mutex,
                                pdMS_TO_TICKS(EEPROM_MUTEX_TIMEOUT_MS)) != pdTRUE)
    {
        APP_LOG_ERROR("EEPROM mutex take timeout\r\n");
        return 2;
    }

    return 0;
}

static void EEPROM_Unlock(void)
{
    if (eeprom_mutex == NULL)
    {
        return;
    }

    if (!EEPROM_IsSchedulerRunning())
    {
        return;
    }

    (void)xSemaphoreGiveRecursive(eeprom_mutex);
}

static uint16_t EEPROM_Checksum16(const uint8_t *data, uint16_t len)
{
    uint32_t sum = 0;
    uint16_t i;

    if (data == NULL)
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        sum += data[i];
    }

    return (uint16_t)sum;
}

static uint32_t EEPROM_GetHistoryCapacity(void)
{
    return (EEPROM_EVENT_START_ADDR - EEPROM_HISTORY_START_ADDR) /
           sizeof(EEPROM_HistoryRecord_t);
}

static uint32_t EEPROM_GetEventCapacity(void)
{
    return (EEPROM_TOTAL_SIZE - EEPROM_EVENT_START_ADDR) /
           sizeof(EEPROM_EventRecord_t);
}

static uint8_t EEPROM_WaitReady(void)
{
    uint8_t i;

    for (i = 0; i < 50; i++)
    {
        if (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_I2C_ADDR, 1, 100) == HAL_OK)
        {
            return 0;
        }

        HAL_Delay(1);
    }

    return 1;
}

uint8_t EEPROM_ReadBytes(uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    uint8_t result = 0;

    if (data == NULL)
    {
        return 1;
    }

    if (((uint32_t)mem_addr + len) > EEPROM_TOTAL_SIZE)
    {
        return 2;
    }

    if (EEPROM_Lock() != 0)
    {
        return 4;
    }

    if (HAL_I2C_Mem_Read(&hi2c1,
                         EEPROM_I2C_ADDR,
                         mem_addr,
                         I2C_MEMADD_SIZE_16BIT,
                         data,
                         len,
                         200) != HAL_OK)
    {
        result = 3;
    }

    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_WriteBytes(uint16_t mem_addr, const uint8_t *data, uint16_t len)
{
    uint16_t write_len;
    uint16_t page_remain;
    uint8_t result = 0;

    if (data == NULL)
    {
        return 1;
    }

    if (((uint32_t)mem_addr + len) > EEPROM_TOTAL_SIZE)
    {
        return 2;
    }

    if (EEPROM_Lock() != 0)
    {
        return 5;
    }

    while (len > 0)
    {
        page_remain = EEPROM_PAGE_SIZE - (mem_addr % EEPROM_PAGE_SIZE);
        write_len = (len < page_remain) ? len : page_remain;

        if (HAL_I2C_Mem_Write(&hi2c1,
                              EEPROM_I2C_ADDR,
                              mem_addr,
                              I2C_MEMADD_SIZE_16BIT,
                              (uint8_t *)data,
                              write_len,
                              200) != HAL_OK)
        {
            result = 3;
            break;
        }

        if (EEPROM_WaitReady() != 0)
        {
            result = 4;
            break;
        }

        mem_addr += write_len;
        data += write_len;
        len -= write_len;
    }

    EEPROM_Unlock();
    return result;
}

static uint8_t EEPROM_ReadHeader(EEPROM_Header_t *header)
{
    uint16_t checksum;
    uint16_t check_len;

    if (header == NULL)
    {
        return 1;
    }

    if (EEPROM_ReadBytes(EEPROM_HEADER_ADDR,
                         (uint8_t *)header,
                         sizeof(EEPROM_Header_t)) != 0)
    {
        return 2;
    }

    if (header->magic != EEPROM_HEADER_MAGIC)
    {
        return 3;
    }

    if (header->layout_version != EEPROM_LAYOUT_VERSION)
    {
        return 4;
    }

    check_len = (uint16_t)offsetof(EEPROM_Header_t, checksum);
    checksum = EEPROM_Checksum16((uint8_t *)header, check_len);

    if (checksum != header->checksum)
    {
        return 5;
    }

    return 0;
}

static uint8_t EEPROM_WriteHeader(void)
{
    EEPROM_Header_t header;
    uint16_t check_len;

    memset(&header, 0, sizeof(header));

    header.magic = EEPROM_HEADER_MAGIC;
    header.layout_version = EEPROM_LAYOUT_VERSION;
    header.header_size = sizeof(EEPROM_Header_t);
    header.next_history_sequence = eeprom_next_history_sequence;
    header.next_event_sequence = eeprom_next_event_sequence;

    check_len = (uint16_t)offsetof(EEPROM_Header_t, checksum);
    header.checksum = EEPROM_Checksum16((uint8_t *)&header, check_len);

    return EEPROM_WriteBytes(EEPROM_HEADER_ADDR,
                             (uint8_t *)&header,
                             sizeof(header));
}

void EEPROM_LoadDefaultConfig(EEPROM_AppConfig_t *config)
{
    uint16_t check_len;

    if (config == NULL)
    {
        return;
    }

    memset(config, 0, sizeof(EEPROM_AppConfig_t));

    config->magic = EEPROM_CONFIG_MAGIC;
    config->version = EEPROM_CONFIG_VERSION;

    config->brightness_percent = 80;
    config->auto_brightness = 0;

    config->weather_interval_min = 60;
    config->sensor_interval_sec = 600;
    config->history_save_interval_sec = 3600;

    strncpy(config->weather_city, "beijing", sizeof(config->weather_city) - 1);

    check_len = (uint16_t)offsetof(EEPROM_AppConfig_t, checksum);
    config->checksum = EEPROM_Checksum16((uint8_t *)config, check_len);
}

uint8_t EEPROM_LoadConfig(EEPROM_AppConfig_t *config)
{
    uint16_t checksum;
    uint16_t check_len;
    uint8_t result = 0;

    if (config == NULL)
    {
        return 1;
    }

    if (EEPROM_Lock() != 0)
    {
        return 6;
    }

    if (EEPROM_ReadBytes(EEPROM_CONFIG_ADDR,
                         (uint8_t *)config,
                         sizeof(EEPROM_AppConfig_t)) != 0)
    {
        result = 2;
        goto exit;
    }

    if (config->magic != EEPROM_CONFIG_MAGIC)
    {
        result = 3;
        goto exit;
    }

    if (config->version != EEPROM_CONFIG_VERSION)
    {
        result = 4;
        goto exit;
    }

    check_len = (uint16_t)offsetof(EEPROM_AppConfig_t, checksum);
    checksum = EEPROM_Checksum16((uint8_t *)config, check_len);

    if (checksum != config->checksum)
    {
        result = 5;
    }

exit:
    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_SaveConfig(const EEPROM_AppConfig_t *config)
{
    EEPROM_AppConfig_t temp;
    uint16_t check_len;
    uint8_t result;

    if (config == NULL)
    {
        return 1;
    }

    if (EEPROM_Lock() != 0)
    {
        return 5;
    }

    memcpy(&temp, config, sizeof(temp));

    temp.magic = EEPROM_CONFIG_MAGIC;
    temp.version = EEPROM_CONFIG_VERSION;

    if (temp.brightness_percent > 100)
    {
        temp.brightness_percent = 100;
    }

    check_len = (uint16_t)offsetof(EEPROM_AppConfig_t, checksum);
    temp.checksum = EEPROM_Checksum16((uint8_t *)&temp, check_len);

    result = EEPROM_WriteBytes(EEPROM_CONFIG_ADDR,
                               (uint8_t *)&temp,
                               sizeof(temp));

    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_Init(void)
{
    EEPROM_Header_t header;
    EEPROM_AppConfig_t config;
    uint8_t result = 0;

    if (EEPROM_MutexInit() != 0)
    {
        return 4;
    }

    if (EEPROM_Lock() != 0)
    {
        return 5;
    }

    if (EEPROM_WaitReady() != 0)
    {
        result = 1;
        goto exit;
    }

    if (EEPROM_ReadHeader(&header) == 0)
    {
        eeprom_next_history_sequence = header.next_history_sequence;
        eeprom_next_event_sequence = header.next_event_sequence;
    }
    else
    {
        eeprom_next_history_sequence = 0;
        eeprom_next_event_sequence = 0;

        if (EEPROM_WriteHeader() != 0)
        {
            result = 2;
            goto exit;
        }
    }

    /*
     * 如果配置区无效，写入默认配置。
     */
    if (EEPROM_LoadConfig(&config) != 0)
    {
        EEPROM_LoadDefaultConfig(&config);

        if (EEPROM_SaveConfig(&config) != 0)
        {
            result = 3;
        }
    }

exit:
    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_SaveHistoryRecord(const EEPROM_HistoryRecord_t *record)
{
    EEPROM_HistoryRecord_t temp;
    uint32_t capacity;
    uint32_t slot;
    uint16_t mem_addr;
    uint16_t check_len;
    uint8_t result = 0;

    if (record == NULL)
    {
        return 1;
    }

    if (EEPROM_Lock() != 0)
    {
        return 5;
    }

    capacity = EEPROM_GetHistoryCapacity();

    if (capacity == 0)
    {
        result = 2;
        goto exit;
    }

    slot = eeprom_next_history_sequence % capacity;
    mem_addr = (uint16_t)(EEPROM_HISTORY_START_ADDR +
                          slot * sizeof(EEPROM_HistoryRecord_t));

    memcpy(&temp, record, sizeof(temp));

    temp.magic = EEPROM_HISTORY_MAGIC;
    temp.sequence = eeprom_next_history_sequence;

    check_len = (uint16_t)offsetof(EEPROM_HistoryRecord_t, checksum);
    temp.checksum = EEPROM_Checksum16((uint8_t *)&temp, check_len);

    if (EEPROM_WriteBytes(mem_addr,
                          (uint8_t *)&temp,
                          sizeof(temp)) != 0)
    {
        result = 3;
        goto exit;
    }

    eeprom_next_history_sequence++;

    if (EEPROM_WriteHeader() != 0)
    {
        result = 4;
    }

exit:
    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_ReadHistoryRecordByIndex(uint32_t back_index,
                                        EEPROM_HistoryRecord_t *record)
{
    uint32_t capacity;
    uint32_t valid_count;
    uint32_t sequence;
    uint32_t slot;
    uint16_t mem_addr;
    uint16_t checksum;
    uint16_t check_len;
    uint8_t result = 0;

    if (record == NULL)
    {
        return 1;
    }

    if (EEPROM_Lock() != 0)
    {
        return 8;
    }

    capacity = EEPROM_GetHistoryCapacity();

    if (eeprom_next_history_sequence < capacity)
    {
        valid_count = eeprom_next_history_sequence;
    }
    else
    {
        valid_count = capacity;
    }

    if (valid_count == 0)
    {
        result = 2;
        goto exit;
    }

    if (back_index >= valid_count)
    {
        result = 3;
        goto exit;
    }

    sequence = eeprom_next_history_sequence - 1U - back_index;
    slot = sequence % capacity;

    mem_addr = (uint16_t)(EEPROM_HISTORY_START_ADDR +
                          slot * sizeof(EEPROM_HistoryRecord_t));

    if (EEPROM_ReadBytes(mem_addr,
                         (uint8_t *)record,
                         sizeof(EEPROM_HistoryRecord_t)) != 0)
    {
        result = 4;
        goto exit;
    }

    if (record->magic != EEPROM_HISTORY_MAGIC)
    {
        result = 5;
        goto exit;
    }

    if (record->sequence != sequence)
    {
        result = 6;
        goto exit;
    }

    check_len = (uint16_t)offsetof(EEPROM_HistoryRecord_t, checksum);
    checksum = EEPROM_Checksum16((uint8_t *)record, check_len);

    if (checksum != record->checksum)
    {
        result = 7;
    }

exit:
    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_ReadLatestHistoryRecord(EEPROM_HistoryRecord_t *record)
{
    return EEPROM_ReadHistoryRecordByIndex(0, record);
}

uint8_t EEPROM_SaveEventLog(EEPROM_EventType_t type,
                            const char *text,
                            uint32_t tick_ms,
                            uint32_t unix_time)
{
    EEPROM_EventRecord_t record;
    uint32_t capacity;
    uint32_t slot;
    uint16_t mem_addr;
    uint16_t check_len;
    uint8_t result = 0;

    if (text == NULL)
    {
        return 1;
    }

    if (EEPROM_Lock() != 0)
    {
        return 5;
    }

    capacity = EEPROM_GetEventCapacity();

    if (capacity == 0)
    {
        result = 2;
        goto exit;
    }

    slot = eeprom_next_event_sequence % capacity;
    mem_addr = (uint16_t)(EEPROM_EVENT_START_ADDR +
                          slot * sizeof(EEPROM_EventRecord_t));

    memset(&record, 0, sizeof(record));

    record.magic = EEPROM_EVENT_MAGIC;
    record.sequence = eeprom_next_event_sequence;
    record.tick_ms = tick_ms;
    record.unix_time = unix_time;
    record.type = (uint8_t)type;

    strncpy(record.text, text, sizeof(record.text) - 1);

    check_len = (uint16_t)offsetof(EEPROM_EventRecord_t, checksum);
    record.checksum = EEPROM_Checksum16((uint8_t *)&record, check_len);

    if (EEPROM_WriteBytes(mem_addr,
                          (uint8_t *)&record,
                          sizeof(record)) != 0)
    {
        result = 3;
        goto exit;
    }

    eeprom_next_event_sequence++;

    if (EEPROM_WriteHeader() != 0)
    {
        result = 4;
    }

exit:
    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_ReadEventLogByIndex(uint32_t back_index,
                                   EEPROM_EventRecord_t *record)
{
    uint32_t capacity;
    uint32_t valid_count;
    uint32_t sequence;
    uint32_t slot;
    uint16_t mem_addr;
    uint16_t checksum;
    uint16_t check_len;
    uint8_t result = 0;

    if (record == NULL)
    {
        return 1;
    }

    if (EEPROM_Lock() != 0)
    {
        return 8;
    }

    capacity = EEPROM_GetEventCapacity();

    if (eeprom_next_event_sequence < capacity)
    {
        valid_count = eeprom_next_event_sequence;
    }
    else
    {
        valid_count = capacity;
    }

    if (valid_count == 0)
    {
        result = 2;
        goto exit;
    }

    if (back_index >= valid_count)
    {
        result = 3;
        goto exit;
    }

    sequence = eeprom_next_event_sequence - 1U - back_index;
    slot = sequence % capacity;

    mem_addr = (uint16_t)(EEPROM_EVENT_START_ADDR +
                          slot * sizeof(EEPROM_EventRecord_t));

    if (EEPROM_ReadBytes(mem_addr,
                         (uint8_t *)record,
                         sizeof(EEPROM_EventRecord_t)) != 0)
    {
        result = 4;
        goto exit;
    }

    if (record->magic != EEPROM_EVENT_MAGIC)
    {
        result = 5;
        goto exit;
    }

    if (record->sequence != sequence)
    {
        result = 6;
        goto exit;
    }

    check_len = (uint16_t)offsetof(EEPROM_EventRecord_t, checksum);
    checksum = EEPROM_Checksum16((uint8_t *)record, check_len);

    if (checksum != record->checksum)
    {
        result = 7;
    }

exit:
    EEPROM_Unlock();
    return result;
}

uint8_t EEPROM_ReadLatestEventLog(EEPROM_EventRecord_t *record)
{
    return EEPROM_ReadEventLogByIndex(0, record);
}

/*
 * 兼容旧接口：只保存温湿度和 tick。
 */
uint8_t EEPROM_SaveEnvRecord(int32_t temperature_x100,
                             uint32_t humidity_x100,
                             uint32_t tick_ms)
{
    EEPROM_HistoryRecord_t record;

    memset(&record, 0, sizeof(record));

    record.tick_ms = tick_ms;
    record.temperature_x100 = temperature_x100;
    record.humidity_x100 = humidity_x100;

    return EEPROM_SaveHistoryRecord(&record);
}

uint8_t EEPROM_ReadLatestEnvRecord(EEPROM_HistoryRecord_t *record)
{
    return EEPROM_ReadLatestHistoryRecord(record);
}


void EEPROM_PrintEnvRecord(const EEPROM_EnvRecord_t *record)
{
    int32_t temp_abs;
    int32_t pressure_abs;

    if (record == NULL)
    {
        return;
    }

    temp_abs = record->temperature_x100;
    pressure_abs = record->pressure_x100;

    if (temp_abs < 0)
    {
        temp_abs = -temp_abs;
    }

    if (pressure_abs < 0)
    {
        pressure_abs = -pressure_abs;
    }

    APP_LOG_DEBUG("EEPROM latest history:\r\n");
    APP_LOG_DEBUG("seq      : %lu\r\n", (unsigned long)(record->sequence));
    APP_LOG_DEBUG("tick     : %lu ms\r\n", (unsigned long)(record->tick_ms));
    APP_LOG_DEBUG("unix     : %lu\r\n", (unsigned long)(record->unix_time));

    APP_LOG_DEBUG("temp     : %s%ld.%02ld C\r\n",
           (record->temperature_x100 < 0) ? "-" : "",
           (long)(temp_abs / 100),
           (long)(temp_abs % 100));

    APP_LOG_DEBUG("humi     : %lu.%02lu %%RH\r\n",
           (unsigned long)(record->humidity_x100 / 100),
           (unsigned long)(record->humidity_x100 % 100));

    APP_LOG_DEBUG("pressure : %s%ld.%02ld hPa\r\n",
           (record->pressure_x100 < 0) ? "-" : "",
           (long)(pressure_abs / 100),
           (long)(pressure_abs % 100));

    APP_LOG_DEBUG("lux      : %lu.%02lu lx\r\n",
           (unsigned long)(record->lux_x100 / 100),
           (unsigned long)(record->lux_x100 % 100));

    APP_LOG_DEBUG("motion   : %s\r\n", record->motion ? "Moving" : "Stable");
    APP_LOG_DEBUG("weather  : %d C\r\n", record->weather_temperature);
}

void EEPROM_PrintEventRecord(const EEPROM_EventRecord_t *record)
{
    if (record == NULL)
    {
        return;
    }

    APP_LOG_DEBUG("EEPROM latest event:\r\n");
    APP_LOG_DEBUG("seq  : %lu\r\n", (unsigned long)record->sequence);
    APP_LOG_DEBUG("tick : %lu ms\r\n", (unsigned long)record->tick_ms);
    APP_LOG_DEBUG("unix : %lu\r\n", (unsigned long)record->unix_time);
    APP_LOG_DEBUG("type : %u\r\n", record->type);
    APP_LOG_DEBUG("text : %s\r\n", record->text);
}
