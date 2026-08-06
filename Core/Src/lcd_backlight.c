#include "lcd_backlight.h"
#include "tim.h"

static uint8_t s_backlight_percent = 80;

void LCD_Backlight_Init(void)
{
    HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
    LCD_Backlight_SetPercent(s_backlight_percent);
}

void LCD_Backlight_SetPercent(uint8_t percent)
{
    uint32_t arr;
    uint32_t pulse;

    if (percent > 100)
    {
        percent = 100;
    }

    s_backlight_percent = percent;

    arr = __HAL_TIM_GET_AUTORELOAD(&htim9);

    /*
     * ARR = 99 Ê±£¬ARR + 1 = 100¡£
     * percent = 80 -> pulse = 80¡£
     */
    pulse = ((arr + 1U) * percent) / 100U;

    __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, pulse);
}

uint8_t LCD_Backlight_GetPercent(void)
{
    return s_backlight_percent;
}