#include "ft5336.h"
#include "i2c.h"
#include <string.h>

#define FT5336_ADDR              (0x38 << 1)

#define FT5336_REG_TD_STATUS     0x02
#define FT5336_REG_P1_XH         0x03

#define FT5336_POINT_BYTES       6

#define FT5336_LCD_WIDTH         240
#define FT5336_LCD_HEIGHT        320

#define FT5336_SWAP_XY           0
#define FT5336_MIRROR_X          0
#define FT5336_MIRROR_Y          0

static volatile uint8_t ft5336_irq_flag = 0;

static uint8_t FT5336_ReadReg(uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (buf == NULL || len == 0)
    {
        return 1;
    }

    if (HAL_I2C_Mem_Read(&hi2c3,
                         FT5336_ADDR,
                         reg,
                         I2C_MEMADD_SIZE_8BIT,
                         buf,
                         len,
                         100) != HAL_OK)
    {
        return 2;
    }

    return 0;
}

static void FT5336_CorrectPoint(uint16_t *x, uint16_t *y)
{
#if FT5336_SWAP_XY
    uint16_t temp = *x;
    *x = *y;
    *y = temp;
#endif

#if FT5336_MIRROR_X
    if (*x < FT5336_LCD_WIDTH)
    {
        *x = FT5336_LCD_WIDTH - 1 - *x;
    }
#endif

#if FT5336_MIRROR_Y
    if (*y < FT5336_LCD_HEIGHT)
    {
        *y = FT5336_LCD_HEIGHT - 1 - *y;
    }
#endif

    if (*x >= FT5336_LCD_WIDTH)
    {
        *x = FT5336_LCD_WIDTH - 1;
    }

    if (*y >= FT5336_LCD_HEIGHT)
    {
        *y = FT5336_LCD_HEIGHT - 1;
    }
}

uint8_t FT5336_Init(void)
{
    HAL_Delay(50);

    if (HAL_I2C_IsDeviceReady(&hi2c3, FT5336_ADDR, 3, 100) != HAL_OK)
    {
        return 1;
    }

    ft5336_irq_flag = 0;

    return 0;
}

uint8_t FT5336_ReadTouch(FT5336_TouchData_t *touch)
{
    uint8_t status;
    uint8_t points;
    uint8_t buf[FT5336_MAX_POINTS * FT5336_POINT_BYTES];

    if (touch == NULL)
    {
        return 1;
    }

    memset(touch, 0, sizeof(FT5336_TouchData_t));

    if (FT5336_ReadReg(FT5336_REG_TD_STATUS, &status, 1) != 0)
    {
        return 2;
    }

    points = status & 0x0F;

    if (points == 0)
    {
        touch->touched = 0;
        touch->points = 0;
        return 0;
    }

    if (points > FT5336_MAX_POINTS)
    {
        points = FT5336_MAX_POINTS;
    }

    if (FT5336_ReadReg(FT5336_REG_P1_XH,
                       buf,
                       points * FT5336_POINT_BYTES) != 0)
    {
        return 3;
    }

    touch->touched = 1;
    touch->points = points;

    for (uint8_t i = 0; i < points; i++)
    {
        uint8_t *p = &buf[i * FT5336_POINT_BYTES];

        touch->x[i] = ((uint16_t)(p[0] & 0x0F) << 8) | p[1];
        touch->y[i] = ((uint16_t)(p[2] & 0x0F) << 8) | p[3];

        FT5336_CorrectPoint(&touch->x[i], &touch->y[i]);
    }

    return 0;
}

uint8_t FT5336_IsIntActive(void)
{
    return HAL_GPIO_ReadPin(TOUCH_INT_GPIO_Port, TOUCH_INT_Pin) == GPIO_PIN_RESET;
}

void FT5336_NotifyIrq(void)
{
    ft5336_irq_flag = 1;
}

uint8_t FT5336_GetIrqFlag(void)
{
    return ft5336_irq_flag;
}

void FT5336_ClearIrqFlag(void)
{
    ft5336_irq_flag = 0;
}
