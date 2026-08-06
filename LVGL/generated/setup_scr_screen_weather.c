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



void setup_scr_screen_weather(lv_ui *ui)
{
    //Write codes screen_weather
    ui->screen_weather = lv_obj_create(NULL);
    ui->screen_weather_del = false;
    lv_obj_set_size(ui->screen_weather, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_weather, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_cont_weather
    ui->screen_weather_cont_weather = lv_obj_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_cont_weather, 0, 0);
    lv_obj_set_size(ui->screen_weather_cont_weather, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_weather_cont_weather, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_cont_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_cont_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_cont_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_cont_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_weather_set
    ui->screen_weather_btn_weather_set = lv_button_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_btn_weather_set, 192, 272);
    lv_obj_set_size(ui->screen_weather_btn_weather_set, 48, 48);
    ui->screen_weather_btn_weather_set_label = lv_label_create(ui->screen_weather_btn_weather_set);
    lv_label_set_text(ui->screen_weather_btn_weather_set_label, "Set");
    lv_label_set_long_mode(ui->screen_weather_btn_weather_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_weather_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_weather_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_weather_set_label, LV_PCT(100));

    //Write style for screen_weather_btn_weather_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_weather_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_btn_weather_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_btn_weather_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_weather_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_btn_weather_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_btn_weather_set, lv_color_hex(0xe40022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_btn_weather_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_weather_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_weather_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_weather_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_weather_set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_weather_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_weather_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_weather_log
    ui->screen_weather_btn_weather_log = lv_button_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_btn_weather_log, 144, 272);
    lv_obj_set_size(ui->screen_weather_btn_weather_log, 48, 48);
    ui->screen_weather_btn_weather_log_label = lv_label_create(ui->screen_weather_btn_weather_log);
    lv_label_set_text(ui->screen_weather_btn_weather_log_label, "Log");
    lv_label_set_long_mode(ui->screen_weather_btn_weather_log_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_weather_log_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_weather_log, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_weather_log_label, LV_PCT(100));

    //Write style for screen_weather_btn_weather_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_weather_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_btn_weather_log, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_btn_weather_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_weather_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_btn_weather_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_btn_weather_log, lv_color_hex(0xe40098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_btn_weather_log, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_weather_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_weather_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_weather_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_weather_log, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_weather_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_weather_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_weather_sensor
    ui->screen_weather_btn_weather_sensor = lv_button_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_btn_weather_sensor, 96, 272);
    lv_obj_set_size(ui->screen_weather_btn_weather_sensor, 48, 48);
    ui->screen_weather_btn_weather_sensor_label = lv_label_create(ui->screen_weather_btn_weather_sensor);
    lv_label_set_text(ui->screen_weather_btn_weather_sensor_label, "Sensor");
    lv_label_set_long_mode(ui->screen_weather_btn_weather_sensor_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_weather_sensor_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_weather_sensor, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_weather_sensor_label, LV_PCT(100));

    //Write style for screen_weather_btn_weather_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_weather_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_btn_weather_sensor, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_btn_weather_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_weather_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_btn_weather_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_btn_weather_sensor, lv_color_hex(0xe47900), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_btn_weather_sensor, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_weather_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_weather_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_weather_sensor, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_weather_sensor, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_weather_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_weather_sensor, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_weather_weather
    ui->screen_weather_btn_weather_weather = lv_button_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_btn_weather_weather, 48, 272);
    lv_obj_set_size(ui->screen_weather_btn_weather_weather, 48, 48);
    ui->screen_weather_btn_weather_weather_label = lv_label_create(ui->screen_weather_btn_weather_weather);
    lv_label_set_text(ui->screen_weather_btn_weather_weather_label, "Weather");
    lv_label_set_long_mode(ui->screen_weather_btn_weather_weather_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_weather_weather_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_weather_weather, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_weather_weather_label, LV_PCT(100));

    //Write style for screen_weather_btn_weather_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_weather_weather, 107, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_btn_weather_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_btn_weather_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_weather_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_btn_weather_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_btn_weather_weather, lv_color_hex(0xb9e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_btn_weather_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_weather_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_weather_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_weather_weather, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_weather_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_weather_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_weather_home
    ui->screen_weather_btn_weather_home = lv_button_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_btn_weather_home, 0, 272);
    lv_obj_set_size(ui->screen_weather_btn_weather_home, 48, 48);
    ui->screen_weather_btn_weather_home_label = lv_label_create(ui->screen_weather_btn_weather_home);
    lv_label_set_text(ui->screen_weather_btn_weather_home_label, "Home");
    lv_label_set_long_mode(ui->screen_weather_btn_weather_home_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_weather_home_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_weather_home, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_weather_home_label, LV_PCT(100));

    //Write style for screen_weather_btn_weather_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_weather_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_btn_weather_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_btn_weather_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_weather_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_btn_weather_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_btn_weather_home, lv_color_hex(0x55e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_btn_weather_home, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_weather_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_weather_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_weather_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_weather_home, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_weather_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_weather_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_cont_weather_top
    ui->screen_weather_cont_weather_top = lv_obj_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_cont_weather_top, 0, 0);
    lv_obj_set_size(ui->screen_weather_cont_weather_top, 240, 25);
    lv_obj_set_scrollbar_mode(ui->screen_weather_cont_weather_top, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_cont_weather_top, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_cont_weather_top, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_cont_weather_top, lv_color_hex(0x898989), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_cont_weather_top, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_cont_weather_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_weather
    ui->screen_weather_label_weather_weather = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_weather, 49, 28);
    lv_obj_set_size(ui->screen_weather_label_weather_weather, 150, 60);
    lv_label_set_text(ui->screen_weather_label_weather_weather, "--");
    lv_label_set_long_mode(ui->screen_weather_label_weather_weather, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_weather, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_weather, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_weather, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_weather, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_btn_weather_refresh
    ui->screen_weather_btn_weather_refresh = lv_button_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_btn_weather_refresh, 45, 226);
    lv_obj_set_size(ui->screen_weather_btn_weather_refresh, 160, 30);
    ui->screen_weather_btn_weather_refresh_label = lv_label_create(ui->screen_weather_btn_weather_refresh);
    lv_label_set_text(ui->screen_weather_btn_weather_refresh_label, "Refresh weather");
    lv_label_set_long_mode(ui->screen_weather_btn_weather_refresh_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_weather_btn_weather_refresh_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_weather_btn_weather_refresh, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_weather_btn_weather_refresh_label, LV_PCT(100));

    //Write style for screen_weather_btn_weather_refresh, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather_btn_weather_refresh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_btn_weather_refresh, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_btn_weather_refresh, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_weather_btn_weather_refresh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_btn_weather_refresh, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_btn_weather_refresh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_btn_weather_refresh, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_btn_weather_refresh, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_btn_weather_refresh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_btn_weather_refresh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_update
    ui->screen_weather_label_weather_update = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_update, 6, 107);
    lv_obj_set_size(ui->screen_weather_label_weather_update, 126, 26);
    lv_label_set_text(ui->screen_weather_label_weather_update, "Last  refresh Update: ");
    lv_label_set_long_mode(ui->screen_weather_label_weather_update, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_update, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_update, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_update, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_update, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_update, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_update, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_update, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_update, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_update, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_update, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_update, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_update_value
    ui->screen_weather_label_weather_update_value = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_update_value, 138, 105);
    lv_obj_set_size(ui->screen_weather_label_weather_update_value, 103, 26);
    lv_label_set_text(ui->screen_weather_label_weather_update_value, "--");
    lv_label_set_long_mode(ui->screen_weather_label_weather_update_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_update_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_update_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_update_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_update_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_update_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_update_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_update_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_update_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_update_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_update_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_update_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_wifi
    ui->screen_weather_label_weather_wifi = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_wifi, 9, 143);
    lv_obj_set_size(ui->screen_weather_label_weather_wifi, 115, 26);
    lv_label_set_text(ui->screen_weather_label_weather_wifi, "WiFi");
    lv_label_set_long_mode(ui->screen_weather_label_weather_wifi, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_wifi, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_wifi, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_wifi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_wifi, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_wifi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_ip
    ui->screen_weather_label_weather_ip = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_ip, 7, 184);
    lv_obj_set_size(ui->screen_weather_label_weather_ip, 115, 26);
    lv_label_set_text(ui->screen_weather_label_weather_ip, "IP");
    lv_label_set_long_mode(ui->screen_weather_label_weather_ip, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_ip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_ip, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_ip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_ip, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_ip, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_ip, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_ip, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_ip, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_ip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_ip, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_wifi_value
    ui->screen_weather_label_weather_wifi_value = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_wifi_value, 134, 142);
    lv_obj_set_size(ui->screen_weather_label_weather_wifi_value, 104, 26);
    lv_label_set_text(ui->screen_weather_label_weather_wifi_value, "--");
    lv_label_set_long_mode(ui->screen_weather_label_weather_wifi_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_wifi_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_wifi_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_wifi_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_wifi_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_wifi_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_wifi_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_wifi_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_wifi_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_wifi_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_wifi_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_ip_value
    ui->screen_weather_label_weather_ip_value = lv_label_create(ui->screen_weather_cont_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_ip_value, 137, 186);
    lv_obj_set_size(ui->screen_weather_label_weather_ip_value, 103, 26);
    lv_label_set_text(ui->screen_weather_label_weather_ip_value, "--");
    lv_label_set_long_mode(ui->screen_weather_label_weather_ip_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_weather_label_weather_ip_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_ip_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_weather_label_weather_ip_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_weather_label_weather_ip_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_weather_label_weather_ip_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_ip_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_ip_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_ip_value, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_ip_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_ip_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_ip_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_weather.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_weather);

    //Init events for screen.
    events_init_screen_weather(ui);
}
