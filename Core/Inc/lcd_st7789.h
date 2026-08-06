#ifndef __LCD_ST7789_H
#define __LCD_ST7789_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include "font.h"

#define LCD_WIDTH   240
#define LCD_HEIGHT  320

#define LCD_COLOR_BLACK   0x0000
#define LCD_COLOR_WHITE   0xFFFF
#define LCD_COLOR_RED     0xF800
#define LCD_COLOR_GREEN   0x07E0
#define LCD_COLOR_BLUE    0x001F
#define LCD_COLOR_YELLOW  0xFFE0
#define LCD_COLOR_CYAN    0x07FF
#define LCD_COLOR_MAGENTA 0xF81F
#define LCD_COLOR_GRAY    0x8410


void LCD_Init(void);
void LCD_FillColor(uint16_t color);
void LCD_FillBlockColor(uint16_t x0, uint16_t y0,
                        uint16_t x1, uint16_t y1,
                        uint16_t color);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void LCD_ShowAsciiChar(uint16_t x, uint16_t y, char ch,
                       uint16_t color, uint16_t bg_color,
                       const font_t *font);

void LCD_ShowString(uint16_t x, uint16_t y, const char *str,
                    uint16_t color, uint16_t bg_color,
                    const font_t *font);

void LCD_ShowTemperature(uint16_t x, uint16_t y,
                         int32_t temperature_x100,
                         uint16_t color, uint16_t bg_color,
                         const font_t *font);

void LCD_ShowTempHumi(uint16_t x, uint16_t y,
                      int32_t temperature_x100,
                      uint32_t humidity_x100,
                      uint16_t color, uint16_t bg_color,
                      const font_t *font);

//Ôö¼ÓlvglÇý¶¯
void LCD_DrawRGB565Area(uint16_t x0, uint16_t y0,
                        uint16_t x1, uint16_t y1,
                        const uint8_t *data,
                        uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
