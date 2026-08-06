/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_sensor(lv_ui *ui)
{
    //Write codes screen_sensor
    ui->screen_sensor = lv_obj_create(NULL);
    ui->screen_sensor_del = false;
    lv_obj_set_size(ui->screen_sensor, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_sensor, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_cont_sensor
    ui->screen_sensor_cont_sensor = lv_obj_create(ui->screen_sensor);
    lv_obj_set_pos(ui->screen_sensor_cont_sensor, 0, 0);
    lv_obj_set_size(ui->screen_sensor_cont_sensor, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_sensor_cont_sensor, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sensor_cont_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_cont_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_cont_sensor, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_cont_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_cont_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_btn_sensor_set
    ui->screen_sensor_btn_sensor_set = lv_button_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_btn_sensor_set, 192, 272);
    lv_obj_set_size(ui->screen_sensor_btn_sensor_set, 48, 48);
    ui->screen_sensor_btn_sensor_set_label = lv_label_create(ui->screen_sensor_btn_sensor_set);
    lv_label_set_text(ui->screen_sensor_btn_sensor_set_label, "Set");
    lv_label_set_long_mode(ui->screen_sensor_btn_sensor_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_sensor_btn_sensor_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_sensor_btn_sensor_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_sensor_btn_sensor_set_label, LV_PCT(100));

    //Write style for screen_sensor_btn_sensor_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor_btn_sensor_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_btn_sensor_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_btn_sensor_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_sensor_btn_sensor_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_btn_sensor_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_btn_sensor_set, lv_color_hex(0xe40022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_btn_sensor_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_btn_sensor_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_btn_sensor_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_btn_sensor_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_btn_sensor_set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_btn_sensor_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_btn_sensor_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_btn_sensor_hlog
    ui->screen_sensor_btn_sensor_hlog = lv_button_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_btn_sensor_hlog, 144, 272);
    lv_obj_set_size(ui->screen_sensor_btn_sensor_hlog, 48, 48);
    ui->screen_sensor_btn_sensor_hlog_label = lv_label_create(ui->screen_sensor_btn_sensor_hlog);
    lv_label_set_text(ui->screen_sensor_btn_sensor_hlog_label, "Log");
    lv_label_set_long_mode(ui->screen_sensor_btn_sensor_hlog_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_sensor_btn_sensor_hlog_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_sensor_btn_sensor_hlog, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_sensor_btn_sensor_hlog_label, LV_PCT(100));

    //Write style for screen_sensor_btn_sensor_hlog, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor_btn_sensor_hlog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_btn_sensor_hlog, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_btn_sensor_hlog, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_sensor_btn_sensor_hlog, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_btn_sensor_hlog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_btn_sensor_hlog, lv_color_hex(0xe40098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_btn_sensor_hlog, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_btn_sensor_hlog, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_btn_sensor_hlog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_btn_sensor_hlog, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_btn_sensor_hlog, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_btn_sensor_hlog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_btn_sensor_hlog, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_btn_sensor_sensor
    ui->screen_sensor_btn_sensor_sensor = lv_button_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_btn_sensor_sensor, 96, 272);
    lv_obj_set_size(ui->screen_sensor_btn_sensor_sensor, 48, 48);
    ui->screen_sensor_btn_sensor_sensor_label = lv_label_create(ui->screen_sensor_btn_sensor_sensor);
    lv_label_set_text(ui->screen_sensor_btn_sensor_sensor_label, "Sensor");
    lv_label_set_long_mode(ui->screen_sensor_btn_sensor_sensor_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_sensor_btn_sensor_sensor_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_sensor_btn_sensor_sensor, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_sensor_btn_sensor_sensor_label, LV_PCT(100));

    //Write style for screen_sensor_btn_sensor_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor_btn_sensor_sensor, 123, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_btn_sensor_sensor, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_btn_sensor_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_sensor_btn_sensor_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_btn_sensor_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_btn_sensor_sensor, lv_color_hex(0xe47900), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_btn_sensor_sensor, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_btn_sensor_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_btn_sensor_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_btn_sensor_sensor, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_btn_sensor_sensor, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_btn_sensor_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_btn_sensor_sensor, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_btn_sensor_weather
    ui->screen_sensor_btn_sensor_weather = lv_button_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_btn_sensor_weather, 48, 272);
    lv_obj_set_size(ui->screen_sensor_btn_sensor_weather, 48, 48);
    ui->screen_sensor_btn_sensor_weather_label = lv_label_create(ui->screen_sensor_btn_sensor_weather);
    lv_label_set_text(ui->screen_sensor_btn_sensor_weather_label, "Weather");
    lv_label_set_long_mode(ui->screen_sensor_btn_sensor_weather_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_sensor_btn_sensor_weather_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_sensor_btn_sensor_weather, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_sensor_btn_sensor_weather_label, LV_PCT(100));

    //Write style for screen_sensor_btn_sensor_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor_btn_sensor_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_btn_sensor_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_btn_sensor_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_sensor_btn_sensor_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_btn_sensor_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_btn_sensor_weather, lv_color_hex(0xb9e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_btn_sensor_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_btn_sensor_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_btn_sensor_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_btn_sensor_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_btn_sensor_weather, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_btn_sensor_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_btn_sensor_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_btn_sensor_home
    ui->screen_sensor_btn_sensor_home = lv_button_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_btn_sensor_home, 0, 272);
    lv_obj_set_size(ui->screen_sensor_btn_sensor_home, 48, 48);
    ui->screen_sensor_btn_sensor_home_label = lv_label_create(ui->screen_sensor_btn_sensor_home);
    lv_label_set_text(ui->screen_sensor_btn_sensor_home_label, "Home");
    lv_label_set_long_mode(ui->screen_sensor_btn_sensor_home_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_sensor_btn_sensor_home_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_sensor_btn_sensor_home, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_sensor_btn_sensor_home_label, LV_PCT(100));

    //Write style for screen_sensor_btn_sensor_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor_btn_sensor_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_btn_sensor_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_btn_sensor_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_sensor_btn_sensor_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_btn_sensor_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_btn_sensor_home, lv_color_hex(0x55e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_btn_sensor_home, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_btn_sensor_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_btn_sensor_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_btn_sensor_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_btn_sensor_home, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_btn_sensor_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_btn_sensor_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_cont_sensor_top
    ui->screen_sensor_cont_sensor_top = lv_obj_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_cont_sensor_top, 0, 0);
    lv_obj_set_size(ui->screen_sensor_cont_sensor_top, 240, 25);
    lv_obj_set_scrollbar_mode(ui->screen_sensor_cont_sensor_top, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sensor_cont_sensor_top, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_cont_sensor_top, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_cont_sensor_top, lv_color_hex(0x898989), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_cont_sensor_top, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_cont_sensor_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_btn_sensor_refresh
    ui->screen_sensor_btn_sensor_refresh = lv_button_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_btn_sensor_refresh, 46, 227);
    lv_obj_set_size(ui->screen_sensor_btn_sensor_refresh, 160, 30);
    ui->screen_sensor_btn_sensor_refresh_label = lv_label_create(ui->screen_sensor_btn_sensor_refresh);
    lv_label_set_text(ui->screen_sensor_btn_sensor_refresh_label, "Refresh sensor");
    lv_label_set_long_mode(ui->screen_sensor_btn_sensor_refresh_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_sensor_btn_sensor_refresh_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_sensor_btn_sensor_refresh, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_sensor_btn_sensor_refresh_label, LV_PCT(100));

    //Write style for screen_sensor_btn_sensor_refresh, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sensor_btn_sensor_refresh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sensor_btn_sensor_refresh, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sensor_btn_sensor_refresh, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_sensor_btn_sensor_refresh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_btn_sensor_refresh, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_btn_sensor_refresh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_btn_sensor_refresh, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_btn_sensor_refresh, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_btn_sensor_refresh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_btn_sensor_refresh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_humidity_value
    ui->screen_sensor_label_sensor_humidity_value = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_humidity_value, 146, 67);
    lv_obj_set_size(ui->screen_sensor_label_sensor_humidity_value, 90, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_humidity_value, "--");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_humidity_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_humidity_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_humidity_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_humidity_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_humidity_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_humidity_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_humidity_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_humidity_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_humidity_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_humidity_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_humidity_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_humidity_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_humidity
    ui->screen_sensor_label_sensor_humidity = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_humidity, 5, 66);
    lv_obj_set_size(ui->screen_sensor_label_sensor_humidity, 128, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_humidity, "Indoor Humidity");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_humidity, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_humidity, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_humidity, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_humidity, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_humidity, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_humidity, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_humidity, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_humidity, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_humidity, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_humidity, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_humidity, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_temp_value
    ui->screen_sensor_label_sensor_temp_value = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_temp_value, 144, 33);
    lv_obj_set_size(ui->screen_sensor_label_sensor_temp_value, 90, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_temp_value, "--");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_temp_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_temp_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_temp_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_temp_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_temp_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_temp_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_temp_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_temp_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_temp_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_temp_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_temp_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_temp
    ui->screen_sensor_label_sensor_temp = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_temp, 3, 34);
    lv_obj_set_size(ui->screen_sensor_label_sensor_temp, 128, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_temp, "Indoor Temp");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_temp, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_temp, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_temp, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_temp, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_temp, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_temp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_temp, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_air_value
    ui->screen_sensor_label_sensor_air_value = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_air_value, 150, 159);
    lv_obj_set_size(ui->screen_sensor_label_sensor_air_value, 90, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_air_value, "--");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_air_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_air_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_air_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_air_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_air_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_air_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_air_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_air_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_air_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_air_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_air_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_air_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_air
    ui->screen_sensor_label_sensor_air = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_air, 10, 158);
    lv_obj_set_size(ui->screen_sensor_label_sensor_air, 128, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_air, "Air Pressure");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_air, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_air, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_air, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_air, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_air, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_air, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_air, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_air, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_air, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_air, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_air, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_light_value
    ui->screen_sensor_label_sensor_light_value = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_light_value, 149, 129);
    lv_obj_set_size(ui->screen_sensor_label_sensor_light_value, 90, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_light_value, "--");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_light_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_light_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_light_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_light_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_light_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_light_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_light_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_light_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_light_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_light_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_light_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_light_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_light
    ui->screen_sensor_label_sensor_light = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_light, 9, 128);
    lv_obj_set_size(ui->screen_sensor_label_sensor_light, 128, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_light, "Ambient Light");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_light, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_light, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_light, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_light, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_light, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_light, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_light, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_light, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_motion
    ui->screen_sensor_label_sensor_motion = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_motion, 10, 193);
    lv_obj_set_size(ui->screen_sensor_label_sensor_motion, 128, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_motion, "Air Pressure");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_motion, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_motion, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_motion, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_motion, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_motion, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_motion, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_motion, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_motion, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_motion, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_motion, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_motion, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sensor_label_sensor_motion_value
    ui->screen_sensor_label_sensor_motion_value = lv_label_create(ui->screen_sensor_cont_sensor);
    lv_obj_set_pos(ui->screen_sensor_label_sensor_motion_value, 146, 191);
    lv_obj_set_size(ui->screen_sensor_label_sensor_motion_value, 90, 26);
    lv_label_set_text(ui->screen_sensor_label_sensor_motion_value, "--");
    lv_label_set_long_mode(ui->screen_sensor_label_sensor_motion_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_sensor_label_sensor_motion_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sensor_label_sensor_motion_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sensor_label_sensor_motion_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sensor_label_sensor_motion_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sensor_label_sensor_motion_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sensor_label_sensor_motion_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sensor_label_sensor_motion_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sensor_label_sensor_motion_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sensor_label_sensor_motion_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sensor_label_sensor_motion_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sensor_label_sensor_motion_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_sensor.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_sensor);

    //Init events for screen.
    events_init_screen_sensor(ui);
}
