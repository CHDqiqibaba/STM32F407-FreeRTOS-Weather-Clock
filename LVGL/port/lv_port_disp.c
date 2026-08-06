#include "lvgl.h"
#include "lv_port_disp.h"
#include "lcd_st7789.h"

#define LCD_HOR_RES      240
#define LCD_VER_RES      320
#define LVGL_BUF_LINES   40

static uint8_t lvgl_buf1[LCD_HOR_RES * LVGL_BUF_LINES * 2];

static void lvgl_flush_cb(lv_display_t *disp,
                          const lv_area_t *area,
                          uint8_t *px_map)
{
    int32_t x1 = area->x1;
    int32_t y1 = area->y1;
    int32_t x2 = area->x2;
    int32_t y2 = area->y2;

    if (x2 < 0 || y2 < 0 || x1 >= LCD_HOR_RES || y1 >= LCD_VER_RES)
    {
        lv_display_flush_ready(disp);
        return;
    }

    uint32_t width = x2 - x1 + 1;
    uint32_t height = y2 - y1 + 1;
    uint32_t pixel_count = width * height;

    lv_draw_sw_rgb565_swap(px_map, pixel_count);

    LCD_DrawRGB565Area((uint16_t)x1,
                       (uint16_t)y1,
                       (uint16_t)x2,
                       (uint16_t)y2,
                       px_map,
                       pixel_count * 2);

    lv_display_flush_ready(disp);
}

void LV_PortDisp_Init(void)
{
    lv_display_t *disp;

    disp = lv_display_create(LCD_HOR_RES, LCD_VER_RES);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);

    lv_display_set_buffers(disp,
                           lvgl_buf1,
                           NULL,
                           sizeof(lvgl_buf1),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(disp, lvgl_flush_cb);
}