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



void setup_scr_screen_set(lv_ui *ui)
{
    //Write codes screen_set
    ui->screen_set = lv_obj_create(NULL);
    ui->screen_set_del = false;
    lv_obj_set_size(ui->screen_set, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_set, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_cont_set
    ui->screen_set_cont_set = lv_obj_create(ui->screen_set);
    lv_obj_set_pos(ui->screen_set_cont_set, 0, 0);
    lv_obj_set_size(ui->screen_set_cont_set, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_set_cont_set, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_set_cont_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_cont_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_cont_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_cont_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_cont_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_set
    ui->screen_set_btn_set_set = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_set, 192, 272);
    lv_obj_set_size(ui->screen_set_btn_set_set, 48, 48);
    ui->screen_set_btn_set_set_label = lv_label_create(ui->screen_set_btn_set_set);
    lv_label_set_text(ui->screen_set_btn_set_set_label, "Set");
    lv_label_set_long_mode(ui->screen_set_btn_set_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_set_label, LV_PCT(100));

    //Write style for screen_set_btn_set_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_set, 121, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_btn_set_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_btn_set_set, lv_color_hex(0xe40022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_btn_set_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_log
    ui->screen_set_btn_set_log = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_log, 144, 272);
    lv_obj_set_size(ui->screen_set_btn_set_log, 48, 48);
    ui->screen_set_btn_set_log_label = lv_label_create(ui->screen_set_btn_set_log);
    lv_label_set_text(ui->screen_set_btn_set_log_label, "Log");
    lv_label_set_long_mode(ui->screen_set_btn_set_log_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_log_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_log, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_log_label, LV_PCT(100));

    //Write style for screen_set_btn_set_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_log, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_btn_set_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_btn_set_log, lv_color_hex(0xe40098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_btn_set_log, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_log, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_sensor
    ui->screen_set_btn_set_sensor = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_sensor, 96, 272);
    lv_obj_set_size(ui->screen_set_btn_set_sensor, 48, 48);
    ui->screen_set_btn_set_sensor_label = lv_label_create(ui->screen_set_btn_set_sensor);
    lv_label_set_text(ui->screen_set_btn_set_sensor_label, "Sensor");
    lv_label_set_long_mode(ui->screen_set_btn_set_sensor_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_sensor_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_sensor, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_sensor_label, LV_PCT(100));

    //Write style for screen_set_btn_set_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_sensor, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_btn_set_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_btn_set_sensor, lv_color_hex(0xe47900), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_btn_set_sensor, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_sensor, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_sensor, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_sensor, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_weather
    ui->screen_set_btn_set_weather = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_weather, 49, 272);
    lv_obj_set_size(ui->screen_set_btn_set_weather, 48, 48);
    ui->screen_set_btn_set_weather_label = lv_label_create(ui->screen_set_btn_set_weather);
    lv_label_set_text(ui->screen_set_btn_set_weather_label, "Weather");
    lv_label_set_long_mode(ui->screen_set_btn_set_weather_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_weather_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_weather, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_weather_label, LV_PCT(100));

    //Write style for screen_set_btn_set_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_btn_set_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_btn_set_weather, lv_color_hex(0xb9e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_btn_set_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_weather, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_home
    ui->screen_set_btn_set_home = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_home, 0, 272);
    lv_obj_set_size(ui->screen_set_btn_set_home, 48, 48);
    ui->screen_set_btn_set_home_label = lv_label_create(ui->screen_set_btn_set_home);
    lv_label_set_text(ui->screen_set_btn_set_home_label, "Home");
    lv_label_set_long_mode(ui->screen_set_btn_set_home_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_home_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_home, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_home_label, LV_PCT(100));

    //Write style for screen_set_btn_set_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_btn_set_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_btn_set_home, lv_color_hex(0x55e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_btn_set_home, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_home, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_cont_set_top
    ui->screen_set_cont_set_top = lv_obj_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_cont_set_top, 0, 0);
    lv_obj_set_size(ui->screen_set_cont_set_top, 240, 25);
    lv_obj_set_scrollbar_mode(ui->screen_set_cont_set_top, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_set_cont_set_top, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_cont_set_top, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_cont_set_top, lv_color_hex(0x898989), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_cont_set_top, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_cont_set_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_clear
    ui->screen_set_btn_set_clear = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_clear, 128, 231);
    lv_obj_set_size(ui->screen_set_btn_set_clear, 100, 23);
    ui->screen_set_btn_set_clear_label = lv_label_create(ui->screen_set_btn_set_clear);
    lv_label_set_text(ui->screen_set_btn_set_clear_label, "Clear Log");
    lv_label_set_long_mode(ui->screen_set_btn_set_clear_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_clear_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_clear, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_clear_label, LV_PCT(100));

    //Write style for screen_set_btn_set_clear, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_clear, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_clear, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_clear, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_clear, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_clear, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_clear, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_clear, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_clear, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_label_set_version
    ui->screen_set_label_set_version = lv_label_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_label_set_version, 16, 193);
    lv_obj_set_size(ui->screen_set_label_set_version, 100, 30);
    lv_label_set_text(ui->screen_set_label_set_version, "Version");
    lv_label_set_long_mode(ui->screen_set_label_set_version, LV_LABEL_LONG_WRAP);

    //Write style for screen_set_label_set_version, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label_set_version, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_label_set_version, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_label_set_version, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_label_set_version, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label_set_version, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_label_set_version, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_label_set_version, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_label_set_version, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_label_set_version, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_label_set_version, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_sync_time
    ui->screen_set_btn_set_sync_time = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_sync_time, 10, 231);
    lv_obj_set_size(ui->screen_set_btn_set_sync_time, 100, 23);
    ui->screen_set_btn_set_sync_time_label = lv_label_create(ui->screen_set_btn_set_sync_time);
    lv_label_set_text(ui->screen_set_btn_set_sync_time_label, "Sync Time");
    lv_label_set_long_mode(ui->screen_set_btn_set_sync_time_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_sync_time_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_sync_time, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_sync_time_label, LV_PCT(100));

    //Write style for screen_set_btn_set_sync_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_sync_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_sync_time, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_sync_time, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_sync_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_sync_time, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_sync_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_sync_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_sync_time, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_sync_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_sync_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_label_set_version_value
    ui->screen_set_label_set_version_value = lv_label_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_label_set_version_value, 130, 194);
    lv_obj_set_size(ui->screen_set_label_set_version_value, 100, 30);
    lv_label_set_text(ui->screen_set_label_set_version_value, "V1.0");
    lv_label_set_long_mode(ui->screen_set_label_set_version_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_set_label_set_version_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label_set_version_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_label_set_version_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_label_set_version_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_label_set_version_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label_set_version_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_label_set_version_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_label_set_version_value, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_label_set_version_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_label_set_version_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_label_set_version_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_label_set_lcd_brightness
    ui->screen_set_label_set_lcd_brightness = lv_label_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_label_set_lcd_brightness, 20, 127);
    lv_obj_set_size(ui->screen_set_label_set_lcd_brightness, 100, 30);
    lv_label_set_text(ui->screen_set_label_set_lcd_brightness, "LCD Brightness");
    lv_label_set_long_mode(ui->screen_set_label_set_lcd_brightness, LV_LABEL_LONG_WRAP);

    //Write style for screen_set_label_set_lcd_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label_set_lcd_brightness, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_label_set_lcd_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_label_set_lcd_brightness, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_label_set_lcd_brightness, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label_set_lcd_brightness, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_label_set_lcd_brightness, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_label_set_lcd_brightness, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_label_set_lcd_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_label_set_lcd_brightness, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_label_set_lcd_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_label_set_lcd_brightness_value
    ui->screen_set_label_set_lcd_brightness_value = lv_label_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_label_set_lcd_brightness_value, 131, 127);
    lv_obj_set_size(ui->screen_set_label_set_lcd_brightness_value, 100, 30);
    lv_label_set_text(ui->screen_set_label_set_lcd_brightness_value, "80%");
    lv_label_set_long_mode(ui->screen_set_label_set_lcd_brightness_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_set_label_set_lcd_brightness_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label_set_lcd_brightness_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_label_set_lcd_brightness_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_label_set_lcd_brightness_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_label_set_lcd_brightness_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label_set_lcd_brightness_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_label_set_lcd_brightness_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_label_set_lcd_brightness_value, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_label_set_lcd_brightness_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_label_set_lcd_brightness_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_label_set_lcd_brightness_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_label_set_wifi
    ui->screen_set_label_set_wifi = lv_label_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_label_set_wifi, 20, 51);
    lv_obj_set_size(ui->screen_set_label_set_wifi, 100, 30);
    lv_label_set_text(ui->screen_set_label_set_wifi, "WiFi SSID");
    lv_label_set_long_mode(ui->screen_set_label_set_wifi, LV_LABEL_LONG_WRAP);

    //Write style for screen_set_label_set_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label_set_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_label_set_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_label_set_wifi, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_label_set_wifi, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label_set_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_label_set_wifi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_label_set_wifi, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_label_set_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_label_set_wifi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_label_set_wifi_value
    ui->screen_set_label_set_wifi_value = lv_label_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_label_set_wifi_value, 126, 51);
    lv_obj_set_size(ui->screen_set_label_set_wifi_value, 100, 30);
    lv_label_set_text(ui->screen_set_label_set_wifi_value, "iphone 15");
    lv_label_set_long_mode(ui->screen_set_label_set_wifi_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_set_label_set_wifi_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label_set_wifi_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_set_label_set_wifi_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_set_label_set_wifi_value, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_set_label_set_wifi_value, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label_set_wifi_value, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_label_set_wifi_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_label_set_wifi_value, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_label_set_wifi_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_label_set_wifi_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_label_set_wifi_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_set_slider_set_brightness
    ui->screen_set_slider_set_brightness = lv_slider_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_slider_set_brightness, 31, 171);
    lv_obj_set_size(ui->screen_set_slider_set_brightness, 160, 8);
    lv_slider_set_range(ui->screen_set_slider_set_brightness, 0, 100);
    lv_slider_set_mode(ui->screen_set_slider_set_brightness, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_set_slider_set_brightness, 80, LV_ANIM_OFF);

    //Write style for screen_set_slider_set_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_slider_set_brightness, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_slider_set_brightness, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_slider_set_brightness, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_slider_set_brightness, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_set_slider_set_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_slider_set_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_set_slider_set_brightness, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_slider_set_brightness, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_slider_set_brightness, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_slider_set_brightness, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_slider_set_brightness, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_set_slider_set_brightness, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_slider_set_brightness, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_slider_set_brightness, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_slider_set_brightness, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_slider_set_brightness, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_set_btn_set_connectwifi
    ui->screen_set_btn_set_connectwifi = lv_button_create(ui->screen_set_cont_set);
    lv_obj_set_pos(ui->screen_set_btn_set_connectwifi, 37, 89);
    lv_obj_set_size(ui->screen_set_btn_set_connectwifi, 173, 22);
    ui->screen_set_btn_set_connectwifi_label = lv_label_create(ui->screen_set_btn_set_connectwifi);
    lv_label_set_text(ui->screen_set_btn_set_connectwifi_label, "reconnect WiFi");
    lv_label_set_long_mode(ui->screen_set_btn_set_connectwifi_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_set_btn_set_connectwifi_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_set_btn_set_connectwifi, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_set_btn_set_connectwifi_label, LV_PCT(100));

    //Write style for screen_set_btn_set_connectwifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_set_btn_set_connectwifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_btn_set_connectwifi, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_set_connectwifi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_set_btn_set_connectwifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_btn_set_connectwifi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_set_btn_set_connectwifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_set_btn_set_connectwifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_set_btn_set_connectwifi, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_set_btn_set_connectwifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_set_btn_set_connectwifi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_set.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_set);

    //Init events for screen.
    events_init_screen_set(ui);
}
