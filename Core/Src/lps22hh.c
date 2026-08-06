#include "lps22hh.h"
#include "app_log.h"
#include <stdio.h>

#define LPS22HH_ADDR              (0x5C << 1)

/* Register address */
#define LPS22HH_REG_WHO_AM_I      0x0F
#define LPS22HH_REG_CTRL_REG1     0x10
#define LPS22HH_REG_CTRL_REG2     0x11
#define LPS22HH_REG_STATUS        0x27

#define LPS22HH_REG_PRESS_OUT_XL  0x28
#define LPS22HH_REG_PRESS_OUT_L   0x29
#define LPS22HH_REG_PRESS_OUT_H   0x2A

#define LPS22HH_REG_TEMP_OUT_L    0x2B
#define LPS22HH_REG_TEMP_OUT_H    0x2C

/* WHO_AM_I value */
#define LPS22HH_WHO_AM_I_VALUE    0xB3

/*
 * CTRL_REG1:
 * ODR[6:4] = 000: power-down / one-shot mode
 * BDU bit  = 1  : block data update
 *
 * BDU = bit1 = 0x02
 */
#define LPS22HH_CTRL_REG1_POWER_DOWN_BDU  0x02

/*
 * CTRL_REG2:
 * bit7 BOOT
 * bit6 INT_H_L
 * bit5 PP_OD
 * bit4 IF_ADD_INC
 * bit3 reserved
 * bit2 SWRESET
 * bit1 LOW_NOISE_EN
 * bit0 ONE_SHOT
 */
#define LPS22HH_CTRL_REG2_IF_ADD_INC      0x10
#define LPS22HH_CTRL_REG2_SWRESET         0x04
#define LPS22HH_CTRL_REG2_ONE_SHOT        0x01

/*
 * STATUS register:
 * bit1 T_DA: temperature data available
 * bit0 P_DA: pressure data available
 */
#define LPS22HH_STATUS_T_DA               0x02
#define LPS22HH_STATUS_P_DA               0x01

#define LPS22HH_READ_TIMEOUT_MS           100

static uint8_t LPS22HH_ReadReg(uint8_t reg, uint8_t *data, uint16_t len)
{
    if (data == NULL)
    {
        return 10;
    }

    if (HAL_I2C_Mem_Read(&hi2c2,
                         LPS22HH_ADDR,
                         reg,
                         I2C_MEMADD_SIZE_8BIT,
                         data,
                         len,
                         100) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

static uint8_t LPS22HH_WriteReg(uint8_t reg, uint8_t value)
{
    if (HAL_I2C_Mem_Write(&hi2c2,
                          LPS22HH_ADDR,
                          reg,
                          I2C_MEMADD_SIZE_8BIT,
                          &value,
                          1,
                          100) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

uint8_t LPS22HH_Init(void)
{
    uint8_t id = 0;
    uint8_t ctrl2 = 0;

    if (LPS22HH_ReadReg(LPS22HH_REG_WHO_AM_I, &id, 1) != 0)
    {
        return 1;
    }

    if (id != LPS22HH_WHO_AM_I_VALUE)
    {
        return 2;
    }

    /*
     * Enable register address auto-increment.
     * Read-modify-write avoids clearing other CTRL_REG2 bits.
     */
    if (LPS22HH_ReadReg(LPS22HH_REG_CTRL_REG2, &ctrl2, 1) != 0)
    {
        return 3;
    }

    ctrl2 |= LPS22HH_CTRL_REG2_IF_ADD_INC;

    if (LPS22HH_WriteReg(LPS22HH_REG_CTRL_REG2, ctrl2) != 0)
    {
        return 4;
    }

    /*
     * Power-down / one-shot mode + BDU.
     * In this mode, sensor measures only when ONE_SHOT is set.
     */
    if (LPS22HH_WriteReg(LPS22HH_REG_CTRL_REG1,
                         LPS22HH_CTRL_REG1_POWER_DOWN_BDU) != 0)
    {
        return 5;
    }

    HAL_Delay(10);

    return 0;
}

static uint8_t LPS22HH_TriggerOneShot(void)
{
    uint8_t ctrl2 = 0;

    if (LPS22HH_ReadReg(LPS22HH_REG_CTRL_REG2, &ctrl2, 1) != 0)
    {
        return 1;
    }

    ctrl2 |= LPS22HH_CTRL_REG2_ONE_SHOT;

    if (LPS22HH_WriteReg(LPS22HH_REG_CTRL_REG2, ctrl2) != 0)
    {
        return 2;
    }

    return 0;
}

static uint8_t LPS22HH_WaitDataReady(void)
{
    uint8_t status = 0;
    uint32_t start_tick = HAL_GetTick();

    while (1)
    {
        if (LPS22HH_ReadReg(LPS22HH_REG_STATUS, &status, 1) != 0)
        {
            return 1;
        }

        if ((status & (LPS22HH_STATUS_P_DA | LPS22HH_STATUS_T_DA)) ==
            (LPS22HH_STATUS_P_DA | LPS22HH_STATUS_T_DA))
        {
            return 0;
        }

        if ((HAL_GetTick() - start_tick) > LPS22HH_READ_TIMEOUT_MS)
        {
            return 2;
        }

        HAL_Delay(1);
    }
}

uint8_t LPS22HH_Read(LPS22HH_Data_t *data)
{
    uint8_t rx_data[5] = {0};
    int32_t raw_pressure;
    int16_t raw_temperature;

    if (data == NULL)
    {
        return 10;
    }

    /*
     * Trigger one-shot measurement.
     */
    if (LPS22HH_TriggerOneShot() != 0)
    {
        return 1;
    }

    /*
     * Wait until pressure and temperature are ready.
     */
    if (LPS22HH_WaitDataReady() != 0)
    {
        return 2;
    }

    /*
     * Read 5 consecutive bytes:
     * 0x28 PRESS_OUT_XL
     * 0x29 PRESS_OUT_L
     * 0x2A PRESS_OUT_H
     * 0x2B TEMP_OUT_L
     * 0x2C TEMP_OUT_H
     */
    if (LPS22HH_ReadReg(LPS22HH_REG_PRESS_OUT_XL, rx_data, 5) != 0)
    {
        return 3;
    }

    raw_pressure = ((int32_t)rx_data[2] << 16) |
                   ((int32_t)rx_data[1] << 8)  |
                   ((int32_t)rx_data[0]);

    /*
     * Pressure is 24-bit signed data.
     * If bit23 is 1, extend sign to 32-bit.
     */
    if (raw_pressure & 0x00800000)
    {
        raw_pressure |= 0xFF000000;
    }

    raw_temperature = (int16_t)(((uint16_t)rx_data[4] << 8) |
                                 (uint16_t)rx_data[3]);

    /*
     * LPS22HH pressure sensitivity:
     * pressure_hPa = raw_pressure / 4096
     *
     * Store hPa * 100:
     * pressure_x100 = raw_pressure * 100 / 4096
     */
    data->pressure_x100 = (int32_t)(((int64_t)raw_pressure * 100) / 4096);

    /*
     * Temperature sensitivity:
     * temperature_C = raw_temperature / 100
     *
     * Store C * 100, so raw_temperature is already x100.
     */
    data->temperature_x100 = (int32_t)raw_temperature;

    return 0;
}

void LPS22HH_PrintValue(const LPS22HH_Data_t *data)
{
    int32_t pressure_abs;
    int32_t temp_abs;

    if (data == NULL)
    {
        return;
    }

    pressure_abs = data->pressure_x100;
    temp_abs = data->temperature_x100;

    if (pressure_abs < 0)
    {
        pressure_abs = -pressure_abs;
    }

    if (temp_abs < 0)
    {
        temp_abs = -temp_abs;
    }

    APP_LOG_DEBUG("Pressure: %s%ld.%02ld hPa, Temp: %s%ld.%02ld C\r\n",
                  (data->pressure_x100 < 0) ? "-" : "",
                  (long)(pressure_abs / 100),
                  (long)(pressure_abs % 100),
                  (data->temperature_x100 < 0) ? "-" : "",
                  (long)(temp_abs / 100),
                  (long)(temp_abs % 100));
}
