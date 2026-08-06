#include "lcd_st7789.h"
#include "spi.h"
#include "gpio.h"
#include <stdio.h>

static void LCD_CS_LOW(void)
{
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

static void LCD_CS_HIGH(void)
{
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static void LCD_DC_CMD(void)
{
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
}

static void LCD_DC_DATA(void)
{
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
}

static void LCD_RST_LOW(void)
{
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
}

static void LCD_RST_HIGH(void)
{
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
}

static void LCD_BL_ON(void)
{
    //HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_SET);
}

static void LCD_WriteCommand(uint8_t cmd)
{
    LCD_DC_CMD();
    LCD_CS_LOW();
    HAL_SPI_Transmit(&hspi2, &cmd, 1, 100);
    LCD_CS_HIGH();
}

static void LCD_WriteData(uint8_t data)
{
    LCD_DC_DATA();
    LCD_CS_LOW();
    HAL_SPI_Transmit(&hspi2, &data, 1, 100);
    LCD_CS_HIGH();
}

static void LCD_WriteDataBuffer(const uint8_t *data, uint16_t len)
{
    LCD_DC_DATA();
    LCD_CS_LOW();
    HAL_SPI_Transmit(&hspi2, (uint8_t *)data, len, 100);
    LCD_CS_HIGH();
}

static void LCD_WriteColorRaw(uint16_t color)
{
    uint8_t data[2];

    data[0] = (uint8_t)(color >> 8);
    data[1] = (uint8_t)(color & 0xFF);

    HAL_SPI_Transmit(&hspi2, data, 2, 100);
}

static uint8_t LCD_InRange(uint16_t x0, uint16_t y0,
                           uint16_t x1, uint16_t y1)
{
    if (x0 >= LCD_WIDTH || y0 >= LCD_HEIGHT)
    {
        return 0;
    }

    if (x1 >= LCD_WIDTH || y1 >= LCD_HEIGHT)
    {
        return 0;
    }

    if (x1 < x0 || y1 < y0)
    {
        return 0;
    }

    return 1;
}

static void LCD_Reset(void)
{
    LCD_RST_HIGH();
    HAL_Delay(10);

    LCD_RST_LOW();
    HAL_Delay(20);

    LCD_RST_HIGH();
    HAL_Delay(120);
}

static void LCD_SetAddressWindow(uint16_t x0, uint16_t y0,
                                 uint16_t x1, uint16_t y1)
{
    uint8_t data[4];

    LCD_WriteCommand(0x2A);
    data[0] = (uint8_t)(x0 >> 8);
    data[1] = (uint8_t)(x0 & 0xFF);
    data[2] = (uint8_t)(x1 >> 8);
    data[3] = (uint8_t)(x1 & 0xFF);
    LCD_WriteDataBuffer(data, 4);

    LCD_WriteCommand(0x2B);
    data[0] = (uint8_t)(y0 >> 8);
    data[1] = (uint8_t)(y0 & 0xFF);
    data[2] = (uint8_t)(y1 >> 8);
    data[3] = (uint8_t)(y1 & 0xFF);
    LCD_WriteDataBuffer(data, 4);

    LCD_WriteCommand(0x2C);
}

void LCD_Init(void)
{
    LCD_BL_ON();
    LCD_CS_HIGH();
    LCD_Reset();

    LCD_WriteCommand(0x11);
    HAL_Delay(120);

    LCD_WriteCommand(0x36);
    LCD_WriteData(0x00);

    LCD_WriteCommand(0x3A);
    LCD_WriteData(0x55);

    LCD_WriteCommand(0x21);

    LCD_WriteCommand(0x13);

    LCD_WriteCommand(0x29);
    HAL_Delay(20);

    LCD_FillColor(LCD_COLOR_BLACK);
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (!LCD_InRange(x, y, x, y))
    {
        return;
    }

    LCD_SetAddressWindow(x, y, x, y);

    LCD_DC_DATA();
    LCD_CS_LOW();
    LCD_WriteColorRaw(color);
    LCD_CS_HIGH();
}

void LCD_FillColor(uint16_t color)
{
    LCD_FillBlockColor(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, color);
}

void LCD_FillBlockColor(uint16_t x0, uint16_t y0,
                        uint16_t x1, uint16_t y1,
                        uint16_t color)
{
    uint32_t pixels;

    if (!LCD_InRange(x0, y0, x1, y1))
    {
        return;
    }

    pixels = (uint32_t)(x1 - x0 + 1) * (uint32_t)(y1 - y0 + 1);

    LCD_SetAddressWindow(x0, y0, x1, y1);

    LCD_DC_DATA();
    LCD_CS_LOW();

    while (pixels--)
    {
        LCD_WriteColorRaw(color);
    }

    LCD_CS_HIGH();
}

void LCD_ShowAsciiChar(uint16_t x, uint16_t y, char ch,
                       uint16_t color, uint16_t bg_color,
                       const font_t *font)
{
    uint16_t fheight;
    uint16_t fwidth;
    uint16_t bytes_per_row;
    const uint8_t *model;

    if (font == NULL || font->model == NULL)
    {
        return;
    }

    if (ch < ' ' || ch > '~')
    {
        ch = '?';
    }

    fheight = font->height;
    fwidth = font->height / 2;
    bytes_per_row = (fwidth + 7) / 8;

    if (!LCD_InRange(x, y, x + fwidth - 1, y + fheight - 1))
    {
        return;
    }

    model = font->model + (ch - ' ') * fheight * bytes_per_row;

    LCD_SetAddressWindow(x, y, x + fwidth - 1, y + fheight - 1);

    LCD_DC_DATA();
    LCD_CS_LOW();

    for (uint16_t row = 0; row < fheight; row++)
    {
        const uint8_t *row_data = model + row * bytes_per_row;

        for (uint16_t col = 0; col < fwidth; col++)
        {
            uint8_t pixel;

            pixel = row_data[col / 8] & (1 << (7 - col % 8));

            if (pixel)
            {
                LCD_WriteColorRaw(color);
            }
            else
            {
                LCD_WriteColorRaw(bg_color);
            }
        }
    }

    LCD_CS_HIGH();
}

void LCD_ShowString(uint16_t x, uint16_t y, const char *str,
                    uint16_t color, uint16_t bg_color,
                    const font_t *font)
{
    uint16_t start_x = x;
    uint16_t fwidth;
    uint16_t fheight;

    if (str == NULL || font == NULL)
    {
        return;
    }

    fheight = font->height;
    fwidth = font->height / 2;

    while (*str)
    {
        if (*str == '\n')
        {
            x = start_x;
            y += fheight;
            str++;
            continue;
        }

        if (x + fwidth > LCD_WIDTH)
        {
            x = start_x;
            y += fheight;
        }

        if (y + fheight > LCD_HEIGHT)
        {
            return;
        }

        LCD_ShowAsciiChar(x, y, *str, color, bg_color, font);

        x += fwidth;
        str++;
    }
}

void LCD_ShowTemperature(uint16_t x, uint16_t y,
                         int32_t temperature_x100,
                         uint16_t color, uint16_t bg_color,
                         const font_t *font)
{
    char buf[32];
    int32_t temp_abs = temperature_x100;

    if (temp_abs < 0)
    {
        temp_abs = -temp_abs;
    }

    snprintf(buf, sizeof(buf), "TEMP:%s%ld.%02ld C",
             (temperature_x100 < 0) ? "-" : "",
             (long)(temp_abs / 100),
             (long)(temp_abs % 100));

    LCD_ShowString(x, y, buf, color, bg_color, font);
}

void LCD_ShowTempHumi(uint16_t x, uint16_t y,
                      int32_t temperature_x100,
                      uint32_t humidity_x100,
                      uint16_t color, uint16_t bg_color,
                      const font_t *font)
{
    char buf[32];
    int32_t temp_abs = temperature_x100;
    uint16_t line_height;

    if (font == NULL)
    {
        return;
    }

    line_height = font->height + 4;

    if (temp_abs < 0)
    {
        temp_abs = -temp_abs;
    }

    snprintf(buf, sizeof(buf), "TEMP:%s%ld.%02ld C",
             (temperature_x100 < 0) ? "-" : "",
             (long)(temp_abs / 100),
             (long)(temp_abs % 100));

    LCD_ShowString(x, y, buf, color, bg_color, font);

    snprintf(buf, sizeof(buf), "HUMI:%lu.%02lu %%RH",
             (unsigned long)(humidity_x100 / 100),
             (unsigned long)(humidity_x100 % 100));

    LCD_ShowString(x, y + line_height, buf, color, bg_color, font);
}

//Ôö¼ÓlvglÇý¶¯
void LCD_DrawRGB565Area(uint16_t x0, uint16_t y0,
                        uint16_t x1, uint16_t y1,
                        const uint8_t *data,
                        uint32_t len)
{
    LCD_SetAddressWindow(x0, y0, x1, y1);

    LCD_DC_DATA();
    LCD_CS_LOW();

    HAL_SPI_Transmit(&hspi2, (uint8_t *)data, len, 1000);

    LCD_CS_HIGH();
}