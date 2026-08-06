#ifndef __LCD_BACKLIGHT_H
#define __LCD_BACKLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>

void LCD_Backlight_Init(void);
void LCD_Backlight_SetPercent(uint8_t percent);
uint8_t LCD_Backlight_GetPercent(void);

#ifdef __cplusplus
}
#endif

#endif