#include "lis2dh12.h"
#include "app_log.h"
#include <stdio.h>

#define LIS2DH12_ADDR                    (0x18 << 1)

/* Register address */
#define LIS2DH12_REG_WHO_AM_I            0x0F
#define LIS2DH12_REG_CTRL_REG1           0x20
#define LIS2DH12_REG_CTRL_REG4           0x23
#define LIS2DH12_REG_STATUS_REG          0x27

#define LIS2DH12_REG_OUT_X_L             0x28
#define LIS2DH12_REG_OUT_X_H             0x29
#define LIS2DH12_REG_OUT_Y_L             0x2A
#define LIS2DH12_REG_OUT_Y_H             0x2B
#define LIS2DH12_REG_OUT_Z_L             0x2C
#define LIS2DH12_REG_OUT_Z_H             0x2D

/* WHO_AM_I value */
#define LIS2DH12_WHO_AM_I_VALUE          0x33

/*
 * CTRL_REG1:
 * ODR[7:4] = 0010 : 10Hz
 * LPen     = 0    : normal mode
 * Zen/Yen/Xen = 1 : enable X/Y/Z
 *
 * 0x20 = 10Hz
 * 0x07 = X/Y/Z enable
 * 0x27 = 10Hz + X/Y/Z enable
 */
#define LIS2DH12_CTRL_REG1_10HZ_XYZ      0x27

/*
 * CTRL_REG4:
 * BDU bit7 = 1 : block data update
 * FS[5:4] = 00: +/-2g
 * HR bit3 = 1 : high resolution mode
 *
 * 0x80 = BDU
 * 0x08 = HR
 * 0x88 = BDU + HR + +/-2g
 */
#define LIS2DH12_CTRL_REG4_2G_HR_BDU     0x88

/*
 * STATUS_REG:
 * bit3 ZYXDA = 1 means new X/Y/Z data available
 */
#define LIS2DH12_STATUS_ZYXDA            0x08

/*
 * I2C multi-byte read auto increment.
 * ST sensors usually use bit7 of register address for address auto-increment.
 */
#define LIS2DH12_AUTO_INCREMENT          0x80

/*
 * Motion threshold.
 * Unit: mg
 *
 * diff = |x_now - x_last| + |y_now - y_last| + |z_now - z_last|
 * If diff > threshold, treat as moving.
 */
#define LIS2DH12_MOTION_THRESHOLD_MG     180

static uint8_t s_last_valid = 0;
static int32_t s_last_x_mg = 0;
static int32_t s_last_y_mg = 0;
static int32_t s_last_z_mg = 0;

static int32_t LIS2DH12_Abs(int32_t value)
{
    return (value < 0) ? -value : value;
}

static uint8_t LIS2DH12_ReadReg(uint8_t reg, uint8_t *data, uint16_t len)
{
    if (data == NULL)
    {
        return 10;
    }

    if (len > 1)
    {
        reg |= LIS2DH12_AUTO_INCREMENT;
    }

    if (HAL_I2C_Mem_Read(&hi2c2,
                         LIS2DH12_ADDR,
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

static uint8_t LIS2DH12_WriteReg(uint8_t reg, uint8_t value)
{
    if (HAL_I2C_Mem_Write(&hi2c2,
                          LIS2DH12_ADDR,
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

uint8_t LIS2DH12_Init(void)
{
    uint8_t id = 0;

    if (LIS2DH12_ReadReg(LIS2DH12_REG_WHO_AM_I, &id, 1) != 0)
    {
        return 1;
    }

    if (id != LIS2DH12_WHO_AM_I_VALUE)
    {
        return 2;
    }

    if (LIS2DH12_WriteReg(LIS2DH12_REG_CTRL_REG1,
                          LIS2DH12_CTRL_REG1_10HZ_XYZ) != 0)
    {
        return 3;
    }

    if (LIS2DH12_WriteReg(LIS2DH12_REG_CTRL_REG4,
                          LIS2DH12_CTRL_REG4_2G_HR_BDU) != 0)
    {
        return 4;
    }

    s_last_valid = 0;

    HAL_Delay(20);

    return 0;
}

uint8_t LIS2DH12_Read(LIS2DH12_Data_t *data)
{
    uint8_t status = 0;
    uint8_t rx_data[6] = {0};

    int16_t raw_x;
    int16_t raw_y;
    int16_t raw_z;

    int32_t x_mg;
    int32_t y_mg;
    int32_t z_mg;

    uint32_t diff;

    if (data == NULL)
    {
        return 10;
    }

    if (LIS2DH12_ReadReg(LIS2DH12_REG_STATUS_REG, &status, 1) != 0)
    {
        return 1;
    }

    if ((status & LIS2DH12_STATUS_ZYXDA) == 0)
    {
        return 2;
    }

    /*
     * Read 6 consecutive bytes:
     * 0x28 OUT_X_L
     * 0x29 OUT_X_H
     * 0x2A OUT_Y_L
     * 0x2B OUT_Y_H
     * 0x2C OUT_Z_L
     * 0x2D OUT_Z_H
     */
    if (LIS2DH12_ReadReg(LIS2DH12_REG_OUT_X_L, rx_data, 6) != 0)
    {
        return 3;
    }

    /*
     * LIS2DH12 high-resolution mode:
     * output data is left-aligned in 16-bit register pair.
     * For +/-2g high-resolution mode:
     * after >> 4, 1 LSB approximately equals 1 mg.
     */
    raw_x = (int16_t)(((uint16_t)rx_data[1] << 8) | rx_data[0]);
    raw_y = (int16_t)(((uint16_t)rx_data[3] << 8) | rx_data[2]);
    raw_z = (int16_t)(((uint16_t)rx_data[5] << 8) | rx_data[4]);

    x_mg = raw_x >> 4;
    y_mg = raw_y >> 4;
    z_mg = raw_z >> 4;

    data->x_mg = x_mg;
    data->y_mg = y_mg;
    data->z_mg = z_mg;

    if (s_last_valid == 0)
    {
        diff = 0;
        data->motion = LIS2DH12_MOTION_STABLE;
        s_last_valid = 1;
    }
    else
    {
        diff = (uint32_t)(LIS2DH12_Abs(x_mg - s_last_x_mg) +
                          LIS2DH12_Abs(y_mg - s_last_y_mg) +
                          LIS2DH12_Abs(z_mg - s_last_z_mg));

        if (diff > LIS2DH12_MOTION_THRESHOLD_MG)
        {
            data->motion = LIS2DH12_MOTION_MOVING;
        }
        else
        {
            data->motion = LIS2DH12_MOTION_STABLE;
        }
    }

    data->diff_mg = diff;

    s_last_x_mg = x_mg;
    s_last_y_mg = y_mg;
    s_last_z_mg = z_mg;

    return 0;
}

void LIS2DH12_PrintValue(const LIS2DH12_Data_t *data)
{
    if (data == NULL)
    {
        return;
    }

    APP_LOG_DEBUG("LIS2DH12 X:%ld mg, Y:%ld mg, Z:%ld mg, diff:%lu mg, Motion:%s\r\n",
                  (long)data->x_mg,
                  (long)data->y_mg,
                  (long)data->z_mg,
                  (unsigned long)data->diff_mg,
                  (data->motion == LIS2DH12_MOTION_MOVING) ? "Moving" : "Stable");
}
