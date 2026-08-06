#include "lvgl.h"
#include "lv_port_indev.h"
#include "ft5336.h"

static void lvgl_touch_read_cb(lv_indev_t *indev,
                               lv_indev_data_t *data)
{
    FT5336_TouchData_t touch;
    static uint16_t last_x = 0;
    static uint16_t last_y = 0;

    (void)indev;

    if (FT5336_ReadTouch(&touch) == 0 && touch.touched)
    {
        last_x = touch.x[0];
        last_y = touch.y[0];

        data->point.x = last_x;
        data->point.y = last_y;
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->point.x = last_x;
        data->point.y = last_y;
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void LV_PortIndev_Init(void)
{
    lv_indev_t *indev;

    indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, lvgl_touch_read_cb);
}