#include "aht20.h"
#include "app_log.h"
#include <stdio.h>

#define AHT20_ADDR              (0x38 << 1)

#define AHT20_CMD_STATUS        0x71
#define AHT20_CMD_INIT          0xBE
#define AHT20_CMD_TRIGGER       0xAC

#define AHT20_STATUS_BUSY       0x80
#define AHT20_STATUS_CALIBRATED 0x08

static uint8_t AHT20_ReadStatus(uint8_t *status)
{
    uint8_t cmd = AHT20_CMD_STATUS;

    if (HAL_I2C_Master_Transmit(&hi2c2, AHT20_ADDR, &cmd, 1, 100) != HAL_OK)
    {
        return 1;
    }

    if (HAL_I2C_Master_Receive(&hi2c2, AHT20_ADDR, status, 1, 100) != HAL_OK)
    {
        return 2;
    }

    return 0;
}

uint8_t AHT20_Init(void)
{
    uint8_t status = 0;
    uint8_t cmd[3] = {AHT20_CMD_INIT, 0x08, 0x00};

    HAL_Delay(40);

    if (AHT20_ReadStatus(&status) != 0)
    {
        return 1;
    }

    if ((status & AHT20_STATUS_CALIBRATED) == 0)
    {
        if (HAL_I2C_Master_Transmit(&hi2c2, AHT20_ADDR, cmd, 3, 100) != HAL_OK)
        {
            return 2;
        }

        HAL_Delay(10);

        if (AHT20_ReadStatus(&status) != 0)
        {
            return 3;
        }

        if ((status & AHT20_STATUS_CALIBRATED) == 0)
        {
            return 4;
        }
    }

    return 0;
}

uint8_t AHT20_Read(AHT20_Data_t *data)
{
    uint8_t cmd[3] = {AHT20_CMD_TRIGGER, 0x33, 0x00};
    uint8_t rx_data[6] = {0};
    uint32_t raw_humidity;
    uint32_t raw_temperature;

    if (data == NULL)
    {
        return 10;
    }

    if (HAL_I2C_Master_Transmit(&hi2c2, AHT20_ADDR, cmd, 3, 100) != HAL_OK)
    {
        return 1;
    }

    HAL_Delay(80);

    if (HAL_I2C_Master_Receive(&hi2c2, AHT20_ADDR, rx_data, 6, 100) != HAL_OK)
    {
        return 2;
    }

    if (rx_data[0] & AHT20_STATUS_BUSY)
    {
        return 3;
    }

    raw_humidity = ((uint32_t)rx_data[1] << 12) |
                   ((uint32_t)rx_data[2] << 4) |
                   ((uint32_t)rx_data[3] >> 4);

    raw_temperature = (((uint32_t)rx_data[3] & 0x0F) << 16) |
                      ((uint32_t)rx_data[4] << 8) |
                      rx_data[5];

    data->humidity_x100 = (uint32_t)(((uint64_t)raw_humidity * 10000) >> 20);
    data->temperature_x100 = (int32_t)(((uint64_t)raw_temperature * 20000) >> 20) - 5000;

    return 0;
}

void AHT20_PrintValue(const AHT20_Data_t *data)
{
    int32_t temp_abs;

    if (data == NULL)
    {
        return;
    }

    temp_abs = data->temperature_x100;

    if (temp_abs < 0)
    {
        temp_abs = -temp_abs;
    }

    APP_LOG_DEBUG("Temp: %s%ld.%02ld C, Humi: %lu.%02lu %%RH\r\n",
                  (data->temperature_x100 < 0) ? "-" : "",
                  (long)(temp_abs / 100),
                  (long)(temp_abs % 100),
                  (unsigned long)(data->humidity_x100 / 100),
                  (unsigned long)(data->humidity_x100 % 100));
}
