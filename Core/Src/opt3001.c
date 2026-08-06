#include "opt3001.h"
#include "app_log.h"
#include <stdio.h>

#define OPT3001_ADDR                    (0x44 << 1)

/* Register address */
#define OPT3001_REG_RESULT              0x00
#define OPT3001_REG_CONFIG              0x01
#define OPT3001_REG_LOW_LIMIT           0x02
#define OPT3001_REG_HIGH_LIMIT          0x03
#define OPT3001_REG_MANUFACTURER_ID     0x7E
#define OPT3001_REG_DEVICE_ID           0x7F

/* ID value */
#define OPT3001_MANUFACTURER_ID_VALUE   0x5449
#define OPT3001_DEVICE_ID_VALUE         0x3001

/*
 * CONFIG register:
 *
 * RN[15:12] = 1100 : automatic full-scale range
 * CT[11]    = 1    : conversion time 800ms
 * M[10:9]   = 11   : continuous conversions
 * L[4]      = 1    : latched interrupt mode, not important if INT is unused
 *
 * 0xC000 = auto range
 * 0x0800 = 800ms conversion time
 * 0x0600 = continuous conversion
 * 0x0010 = latch bit default style
 *
 * 0xCE10 = auto range + 800ms + continuous
 */
#define OPT3001_CONFIG_CONTINUOUS       0xCE10

static uint8_t OPT3001_ReadReg16(uint8_t reg, uint16_t *value)
{
    uint8_t rx_data[2] = {0};

    if (value == NULL)
    {
        return 10;
    }

    if (HAL_I2C_Mem_Read(&hi2c2,
                         OPT3001_ADDR,
                         reg,
                         I2C_MEMADD_SIZE_8BIT,
                         rx_data,
                         2,
                         100) != HAL_OK)
    {
        return 1;
    }

    /*
     * OPT3001 register data is MSB first.
     */
    *value = ((uint16_t)rx_data[0] << 8) | rx_data[1];

    return 0;
}

static uint8_t OPT3001_WriteReg16(uint8_t reg, uint16_t value)
{
    uint8_t tx_data[2];

    tx_data[0] = (uint8_t)(value >> 8);
    tx_data[1] = (uint8_t)(value & 0xFF);

    if (HAL_I2C_Mem_Write(&hi2c2,
                          OPT3001_ADDR,
                          reg,
                          I2C_MEMADD_SIZE_8BIT,
                          tx_data,
                          2,
                          100) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

uint8_t OPT3001_Init(void)
{
    uint16_t manufacturer_id = 0;
    uint16_t device_id = 0;

    if (OPT3001_ReadReg16(OPT3001_REG_MANUFACTURER_ID, &manufacturer_id) != 0)
    {
        return 1;
    }

    if (manufacturer_id != OPT3001_MANUFACTURER_ID_VALUE)
    {
        return 2;
    }

    if (OPT3001_ReadReg16(OPT3001_REG_DEVICE_ID, &device_id) != 0)
    {
        return 3;
    }

    if (device_id != OPT3001_DEVICE_ID_VALUE)
    {
        return 4;
    }

    if (OPT3001_WriteReg16(OPT3001_REG_CONFIG,
                           OPT3001_CONFIG_CONTINUOUS) != 0)
    {
        return 5;
    }

    /*
     * First conversion needs time.
     * 800ms mode gives better accuracy.
     */
    HAL_Delay(900);

    return 0;
}

uint8_t OPT3001_Read(OPT3001_Data_t *data)
{
    uint16_t raw = 0;
    uint8_t exponent;
    uint16_t mantissa;
    uint32_t lux_x100;

    if (data == NULL)
    {
        return 10;
    }

    if (OPT3001_ReadReg16(OPT3001_REG_RESULT, &raw) != 0)
    {
        return 1;
    }

    exponent = (uint8_t)((raw >> 12) & 0x0F);
    mantissa = raw & 0x0FFF;

    /*
     * lux = mantissa * 0.01 * 2^exponent
     *
     * Store lux * 100:
     * lux_x100 = mantissa * 2^exponent
     */
    lux_x100 = ((uint32_t)mantissa) << exponent;

    data->raw = raw;
    data->exponent = exponent;
    data->mantissa = mantissa;
    data->lux_x100 = lux_x100;

    return 0;
}

void OPT3001_PrintValue(const OPT3001_Data_t *data)
{
    if (data == NULL)
    {
        return;
    }

    APP_LOG_DEBUG("OPT3001 Light: %lu.%02lu lx, raw=0x%04X, exp=%u, mant=%u\r\n",
                  (unsigned long)(data->lux_x100 / 100),
                  (unsigned long)(data->lux_x100 % 100),
                  data->raw,
                  data->exponent,
                  data->mantissa);
}
