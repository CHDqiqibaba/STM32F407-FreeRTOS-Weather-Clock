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



void setup_scr_screen_log(lv_ui *ui)
{
    //Write codes screen_log
    ui->screen_log = lv_obj_create(NULL);
    ui->screen_log_del = false;
    lv_obj_set_size(ui->screen_log, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_log, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_cont_log
    ui->screen_log_cont_log = lv_obj_create(ui->screen_log);
    lv_obj_set_pos(ui->screen_log_cont_log, 0, 0);
    lv_obj_set_size(ui->screen_log_cont_log, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_log_cont_log, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_log_cont_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_log_cont_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_cont_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_cont_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_btn_log_set
    ui->screen_log_btn_log_set = lv_button_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_btn_log_set, 192, 272);
    lv_obj_set_size(ui->screen_log_btn_log_set, 48, 48);
    ui->screen_log_btn_log_set_label = lv_label_create(ui->screen_log_btn_log_set);
    lv_label_set_text(ui->screen_log_btn_log_set_label, "Set");
    lv_label_set_long_mode(ui->screen_log_btn_log_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_log_btn_log_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_log_btn_log_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_log_btn_log_set_label, LV_PCT(100));

    //Write style for screen_log_btn_log_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log_btn_log_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_btn_log_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_btn_log_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_log_btn_log_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_log_btn_log_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_log_btn_log_set, lv_color_hex(0xe40022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_log_btn_log_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_btn_log_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_btn_log_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_btn_log_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_btn_log_set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_btn_log_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_btn_log_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_btn_log_log
    ui->screen_log_btn_log_log = lv_button_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_btn_log_log, 144, 272);
    lv_obj_set_size(ui->screen_log_btn_log_log, 48, 48);
    ui->screen_log_btn_log_log_label = lv_label_create(ui->screen_log_btn_log_log);
    lv_label_set_text(ui->screen_log_btn_log_log_label, "Log");
    lv_label_set_long_mode(ui->screen_log_btn_log_log_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_log_btn_log_log_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_log_btn_log_log, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_log_btn_log_log_label, LV_PCT(100));

    //Write style for screen_log_btn_log_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log_btn_log_log, 118, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_btn_log_log, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_btn_log_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_log_btn_log_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_log_btn_log_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_log_btn_log_log, lv_color_hex(0xe40098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_log_btn_log_log, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_btn_log_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_btn_log_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_btn_log_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_btn_log_log, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_btn_log_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_btn_log_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_btn_log_sensor
    ui->screen_log_btn_log_sensor = lv_button_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_btn_log_sensor, 96, 272);
    lv_obj_set_size(ui->screen_log_btn_log_sensor, 48, 48);
    ui->screen_log_btn_log_sensor_label = lv_label_create(ui->screen_log_btn_log_sensor);
    lv_label_set_text(ui->screen_log_btn_log_sensor_label, "Sensor");
    lv_label_set_long_mode(ui->screen_log_btn_log_sensor_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_log_btn_log_sensor_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_log_btn_log_sensor, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_log_btn_log_sensor_label, LV_PCT(100));

    //Write style for screen_log_btn_log_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log_btn_log_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_btn_log_sensor, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_btn_log_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_log_btn_log_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_log_btn_log_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_log_btn_log_sensor, lv_color_hex(0xe47900), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_log_btn_log_sensor, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_btn_log_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_btn_log_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_btn_log_sensor, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_btn_log_sensor, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_btn_log_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_btn_log_sensor, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_btn_log_weather
    ui->screen_log_btn_log_weather = lv_button_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_btn_log_weather, 49, 272);
    lv_obj_set_size(ui->screen_log_btn_log_weather, 48, 48);
    ui->screen_log_btn_log_weather_label = lv_label_create(ui->screen_log_btn_log_weather);
    lv_label_set_text(ui->screen_log_btn_log_weather_label, "Weather");
    lv_label_set_long_mode(ui->screen_log_btn_log_weather_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_log_btn_log_weather_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_log_btn_log_weather, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_log_btn_log_weather_label, LV_PCT(100));

    //Write style for screen_log_btn_log_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log_btn_log_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_btn_log_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_btn_log_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_log_btn_log_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_log_btn_log_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_log_btn_log_weather, lv_color_hex(0xb9e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_log_btn_log_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_btn_log_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_btn_log_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_btn_log_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_btn_log_weather, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_btn_log_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_btn_log_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_btn_log_home
    ui->screen_log_btn_log_home = lv_button_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_btn_log_home, 0, 272);
    lv_obj_set_size(ui->screen_log_btn_log_home, 48, 48);
    ui->screen_log_btn_log_home_label = lv_label_create(ui->screen_log_btn_log_home);
    lv_label_set_text(ui->screen_log_btn_log_home_label, "Home");
    lv_label_set_long_mode(ui->screen_log_btn_log_home_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_log_btn_log_home_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_log_btn_log_home, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_log_btn_log_home_label, LV_PCT(100));

    //Write style for screen_log_btn_log_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log_btn_log_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_btn_log_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_btn_log_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_log_btn_log_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_log_btn_log_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_log_btn_log_home, lv_color_hex(0x55e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_log_btn_log_home, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_btn_log_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_btn_log_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_btn_log_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_btn_log_home, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_btn_log_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_btn_log_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_cont_log_top
    ui->screen_log_cont_log_top = lv_obj_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_cont_log_top, 0, 0);
    lv_obj_set_size(ui->screen_log_cont_log_top, 240, 25);
    lv_obj_set_scrollbar_mode(ui->screen_log_cont_log_top, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_log_cont_log_top, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_log_cont_log_top, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_cont_log_top, lv_color_hex(0x898989), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_cont_log_top, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_cont_log_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_label_log_last_record
    ui->screen_log_label_log_last_record = lv_label_create(ui->screen_log_cont_log_top);
    lv_obj_set_pos(ui->screen_log_label_log_last_record, 8, 33);
    lv_obj_set_size(ui->screen_log_label_log_last_record, 34, 25);
    lv_label_set_text(ui->screen_log_label_log_last_record, "-");
    lv_label_set_long_mode(ui->screen_log_label_log_last_record, LV_LABEL_LONG_WRAP);

    //Write style for screen_log_label_log_last_record, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_label_log_last_record, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_label_log_last_record, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_label_log_last_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_label_log_last_record, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_label_log_last_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_label_log_last_temp
    ui->screen_log_label_log_last_temp = lv_label_create(ui->screen_log_cont_log_top);
    lv_obj_set_pos(ui->screen_log_label_log_last_temp, 51, 31);
    lv_obj_set_size(ui->screen_log_label_log_last_temp, 39, 25);
    lv_label_set_text(ui->screen_log_label_log_last_temp, "-");
    lv_label_set_long_mode(ui->screen_log_label_log_last_temp, LV_LABEL_LONG_WRAP);

    //Write style for screen_log_label_log_last_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_label_log_last_temp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_label_log_last_temp, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_label_log_last_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_label_log_last_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_label_log_last_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_label_log_last_humi
    ui->screen_log_label_log_last_humi = lv_label_create(ui->screen_log_cont_log_top);
    lv_obj_set_pos(ui->screen_log_label_log_last_humi, 102, 31);
    lv_obj_set_size(ui->screen_log_label_log_last_humi, 44, 25);
    lv_label_set_text(ui->screen_log_label_log_last_humi, "-");
    lv_label_set_long_mode(ui->screen_log_label_log_last_humi, LV_LABEL_LONG_WRAP);

    //Write style for screen_log_label_log_last_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_label_log_last_humi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_label_log_last_humi, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_label_log_last_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_label_log_last_humi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_label_log_last_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_label_log_last_time
    ui->screen_log_label_log_last_time = lv_label_create(ui->screen_log_cont_log_top);
    lv_obj_set_pos(ui->screen_log_label_log_last_time, 157, 31);
    lv_obj_set_size(ui->screen_log_label_log_last_time, 44, 25);
    lv_label_set_text(ui->screen_log_label_log_last_time, "-");
    lv_label_set_long_mode(ui->screen_log_label_log_last_time, LV_LABEL_LONG_WRAP);

    //Write style for screen_log_label_log_last_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_label_log_last_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_label_log_last_time, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_label_log_last_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_label_log_last_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_label_log_last_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_btn_log_save
    ui->screen_log_btn_log_save = lv_button_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_btn_log_save, 88, 236);
    lv_obj_set_size(ui->screen_log_btn_log_save, 64, 23);
    ui->screen_log_btn_log_save_label = lv_label_create(ui->screen_log_btn_log_save);
    lv_label_set_text(ui->screen_log_btn_log_save_label, "save");
    lv_label_set_long_mode(ui->screen_log_btn_log_save_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_log_btn_log_save_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_log_btn_log_save, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_log_btn_log_save_label, LV_PCT(100));

    //Write style for screen_log_btn_log_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_log_btn_log_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_log_btn_log_save, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_log_btn_log_save, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_log_btn_log_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_log_btn_log_save, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_log_btn_log_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_log_btn_log_save, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_log_btn_log_save, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_log_btn_log_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_log_btn_log_save, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_log_list_log_information
    ui->screen_log_list_log_information = lv_list_create(ui->screen_log_cont_log);
    lv_obj_set_pos(ui->screen_log_list_log_information, 9, 68);
    lv_obj_set_size(ui->screen_log_list_log_information, 225, 162);
    lv_obj_set_scrollbar_mode(ui->screen_log_list_log_information, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_screen_log_list_log_information_main_main_default
    static lv_style_t style_screen_log_list_log_information_main_main_default;
    ui_init_style(&style_screen_log_list_log_information_main_main_default);

    lv_style_set_pad_top(&style_screen_log_list_log_information_main_main_default, 5);
    lv_style_set_pad_left(&style_screen_log_list_log_information_main_main_default, 5);
    lv_style_set_pad_right(&style_screen_log_list_log_information_main_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_log_list_log_information_main_main_default, 5);
    lv_style_set_bg_opa(&style_screen_log_list_log_information_main_main_default, 255);
    lv_style_set_bg_color(&style_screen_log_list_log_information_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_log_list_log_information_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_log_list_log_information_main_main_default, 1);
    lv_style_set_border_opa(&style_screen_log_list_log_information_main_main_default, 255);
    lv_style_set_border_color(&style_screen_log_list_log_information_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_log_list_log_information_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_log_list_log_information_main_main_default, 3);
    lv_style_set_shadow_width(&style_screen_log_list_log_information_main_main_default, 0);
    lv_obj_add_style(ui->screen_log_list_log_information, &style_screen_log_list_log_information_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_log_list_log_information_main_scrollbar_default
    static lv_style_t style_screen_log_list_log_information_main_scrollbar_default;
    ui_init_style(&style_screen_log_list_log_information_main_scrollbar_default);

    lv_style_set_radius(&style_screen_log_list_log_information_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_log_list_log_information_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_log_list_log_information_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_log_list_log_information_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_log_list_log_information, &style_screen_log_list_log_information_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_log_list_log_information_extra_btns_main_default
    static lv_style_t style_screen_log_list_log_information_extra_btns_main_default;
    ui_init_style(&style_screen_log_list_log_information_extra_btns_main_default);

    lv_style_set_pad_top(&style_screen_log_list_log_information_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_screen_log_list_log_information_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_screen_log_list_log_information_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_log_list_log_information_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_screen_log_list_log_information_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_screen_log_list_log_information_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_log_list_log_information_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_log_list_log_information_extra_btns_main_default, 255);
    lv_style_set_radius(&style_screen_log_list_log_information_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_screen_log_list_log_information_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_log_list_log_information_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_log_list_log_information_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_screen_log_list_log_information_extra_texts_main_default
    static lv_style_t style_screen_log_list_log_information_extra_texts_main_default;
    ui_init_style(&style_screen_log_list_log_information_extra_texts_main_default);

    lv_style_set_pad_top(&style_screen_log_list_log_information_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_screen_log_list_log_information_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_screen_log_list_log_information_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_log_list_log_information_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_screen_log_list_log_information_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_screen_log_list_log_information_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_log_list_log_information_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_log_list_log_information_extra_texts_main_default, 255);
    lv_style_set_radius(&style_screen_log_list_log_information_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_screen_log_list_log_information_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_screen_log_list_log_information_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_screen_log_list_log_information_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_log_list_log_information_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //The custom code of screen_log.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_log);

    //Init events for screen.
    events_init_screen_log(ui);
}
