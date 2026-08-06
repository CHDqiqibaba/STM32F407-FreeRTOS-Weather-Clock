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



void setup_scr_screen_home(lv_ui *ui)
{
    //Write codes screen_home
    ui->screen_home = lv_obj_create(NULL);
    ui->screen_home_del = false;
    lv_obj_set_size(ui->screen_home, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_home, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_cont_home
    ui->screen_home_cont_home = lv_obj_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_cont_home, 0, 0);
    lv_obj_set_size(ui->screen_home_cont_home, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_home_cont_home, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_cont_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_cont_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_cont_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_cont_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_cont_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_home_weekday
    ui->screen_home_label_home_weekday = lv_label_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_label_home_weekday, 180, 91);
    lv_obj_set_size(ui->screen_home_label_home_weekday, 50, 36);
    lv_label_set_text(ui->screen_home_label_home_weekday, "MON");
    lv_label_set_long_mode(ui->screen_home_label_home_weekday, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_home_weekday, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_home_weekday, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_home_weekday, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_home_weekday, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_home_weekday, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_home_weekday, 159, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_label_home_weekday, lv_color_hex(0x00ffe0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_label_home_weekday, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_home_weekday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_btn_home_home
    ui->screen_home_btn_home_home = lv_button_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_btn_home_home, 0, 272);
    lv_obj_set_size(ui->screen_home_btn_home_home, 48, 48);
    ui->screen_home_btn_home_home_label = lv_label_create(ui->screen_home_btn_home_home);
    lv_label_set_text(ui->screen_home_btn_home_home_label, "Home");
    lv_label_set_long_mode(ui->screen_home_btn_home_home_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_home_btn_home_home_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_home_btn_home_home, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_home_btn_home_home_label, LV_PCT(100));

    //Write style for screen_home_btn_home_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home_btn_home_home, 112, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_btn_home_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_home_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_btn_home_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_btn_home_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_btn_home_home, lv_color_hex(0x55e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_btn_home_home, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_btn_home_home, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_btn_home_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_btn_home_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_btn_home_home, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_btn_home_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_btn_home_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_btn_home_weather
    ui->screen_home_btn_home_weather = lv_button_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_btn_home_weather, 48, 272);
    lv_obj_set_size(ui->screen_home_btn_home_weather, 48, 48);
    ui->screen_home_btn_home_weather_label = lv_label_create(ui->screen_home_btn_home_weather);
    lv_label_set_text(ui->screen_home_btn_home_weather_label, "Weather");
    lv_label_set_long_mode(ui->screen_home_btn_home_weather_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_home_btn_home_weather_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_home_btn_home_weather, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_home_btn_home_weather_label, LV_PCT(100));

    //Write style for screen_home_btn_home_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home_btn_home_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_btn_home_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_home_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_btn_home_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_btn_home_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_btn_home_weather, lv_color_hex(0xb9e400), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_btn_home_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_btn_home_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_btn_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_btn_home_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_btn_home_weather, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_btn_home_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_btn_home_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_btn_home_sensor
    ui->screen_home_btn_home_sensor = lv_button_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_btn_home_sensor, 96, 272);
    lv_obj_set_size(ui->screen_home_btn_home_sensor, 48, 48);
    ui->screen_home_btn_home_sensor_label = lv_label_create(ui->screen_home_btn_home_sensor);
    lv_label_set_text(ui->screen_home_btn_home_sensor_label, "Sensor");
    lv_label_set_long_mode(ui->screen_home_btn_home_sensor_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_home_btn_home_sensor_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_home_btn_home_sensor, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_home_btn_home_sensor_label, LV_PCT(100));

    //Write style for screen_home_btn_home_sensor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home_btn_home_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_btn_home_sensor, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_home_sensor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_btn_home_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_btn_home_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_btn_home_sensor, lv_color_hex(0xe47900), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_btn_home_sensor, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_btn_home_sensor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_btn_home_sensor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_btn_home_sensor, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_btn_home_sensor, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_btn_home_sensor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_btn_home_sensor, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_btn_home_log
    ui->screen_home_btn_home_log = lv_button_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_btn_home_log, 144, 272);
    lv_obj_set_size(ui->screen_home_btn_home_log, 48, 48);
    ui->screen_home_btn_home_log_label = lv_label_create(ui->screen_home_btn_home_log);
    lv_label_set_text(ui->screen_home_btn_home_log_label, "Log");
    lv_label_set_long_mode(ui->screen_home_btn_home_log_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_home_btn_home_log_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_home_btn_home_log, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_home_btn_home_log_label, LV_PCT(100));

    //Write style for screen_home_btn_home_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home_btn_home_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_btn_home_log, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_home_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_btn_home_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_btn_home_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_btn_home_log, lv_color_hex(0xe40098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_btn_home_log, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_btn_home_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_btn_home_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_btn_home_log, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_btn_home_log, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_btn_home_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_btn_home_log, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_btn_home_set
    ui->screen_home_btn_home_set = lv_button_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_btn_home_set, 192, 272);
    lv_obj_set_size(ui->screen_home_btn_home_set, 48, 48);
    ui->screen_home_btn_home_set_label = lv_label_create(ui->screen_home_btn_home_set);
    lv_label_set_text(ui->screen_home_btn_home_set_label, "Set");
    lv_label_set_long_mode(ui->screen_home_btn_home_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_home_btn_home_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_home_btn_home_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_home_btn_home_set_label, LV_PCT(100));

    //Write style for screen_home_btn_home_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home_btn_home_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_btn_home_set, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_home_set, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_btn_home_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_btn_home_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_btn_home_set, lv_color_hex(0xe40022), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_btn_home_set, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_btn_home_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_btn_home_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_btn_home_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_btn_home_set, &lv_font_SourceHanSerifSC_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_btn_home_set, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_btn_home_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_datetext_home_data
    ui->screen_home_datetext_home_data = lv_label_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_datetext_home_data, 48, 91);
    lv_obj_set_size(ui->screen_home_datetext_home_data, 130, 36);
    lv_label_set_text(ui->screen_home_datetext_home_data, "2026/07/08");
    lv_obj_set_style_text_align(ui->screen_home_datetext_home_data, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->screen_home_datetext_home_data, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->screen_home_datetext_home_data, screen_home_datetext_home_data_event_handler, LV_EVENT_ALL, NULL);

    //Write style for screen_home_datetext_home_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_home_datetext_home_data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_datetext_home_data, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_datetext_home_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_datetext_home_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_datetext_home_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_datetext_home_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_datetext_home_data, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_datetext_home_data, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_home_datetext_home_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_datetext_home_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_datetext_home_data, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_datetext_home_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_datetext_home_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_datetext_home_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_home_weather
    ui->screen_home_label_home_weather = lv_label_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_label_home_weather, 45, 131);
    lv_obj_set_size(ui->screen_home_label_home_weather, 150, 60);
    lv_label_set_text(ui->screen_home_label_home_weather, "--");
    lv_label_set_long_mode(ui->screen_home_label_home_weather, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_home_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_home_weather, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_label_home_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_label_home_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_label_home_weather, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_home_weather, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_home_weather, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_home_weather, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_home_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_home_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_home_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_home_outdoor_temp
    ui->screen_home_label_home_outdoor_temp = lv_label_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_label_home_outdoor_temp, 20, 200);
    lv_obj_set_size(ui->screen_home_label_home_outdoor_temp, 100, 40);
    lv_label_set_text(ui->screen_home_label_home_outdoor_temp, "--");
    lv_label_set_long_mode(ui->screen_home_label_home_outdoor_temp, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_home_outdoor_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_home_outdoor_temp, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_label_home_outdoor_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_label_home_outdoor_temp, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_label_home_outdoor_temp, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_home_outdoor_temp, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_home_outdoor_temp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_home_outdoor_temp, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_home_outdoor_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_home_outdoor_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_home_outdoor_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_home_outdoor_humi
    ui->screen_home_label_home_outdoor_humi = lv_label_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_label_home_outdoor_humi, 120, 200);
    lv_obj_set_size(ui->screen_home_label_home_outdoor_humi, 100, 40);
    lv_label_set_text(ui->screen_home_label_home_outdoor_humi, "--");
    lv_label_set_long_mode(ui->screen_home_label_home_outdoor_humi, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_home_outdoor_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_home_outdoor_humi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_home_label_home_outdoor_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_home_label_home_outdoor_humi, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_home_label_home_outdoor_humi, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_home_outdoor_humi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_home_outdoor_humi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_home_outdoor_humi, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_home_outdoor_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_home_outdoor_humi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_home_outdoor_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_home_time
    ui->screen_home_label_home_time = lv_label_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_label_home_time, 30, 45);
    lv_obj_set_size(ui->screen_home_label_home_time, 191, 32);
    lv_label_set_text(ui->screen_home_label_home_time, "label_home_time");
    lv_label_set_long_mode(ui->screen_home_label_home_time, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_home_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_home_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_home_time, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_home_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_home_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_home_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_cont_home_top
    ui->screen_home_cont_home_top = lv_obj_create(ui->screen_home_cont_home);
    lv_obj_set_pos(ui->screen_home_cont_home_top, 0, 0);
    lv_obj_set_size(ui->screen_home_cont_home_top, 240, 25);
    lv_obj_set_scrollbar_mode(ui->screen_home_cont_home_top, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_cont_home_top, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_cont_home_top, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_cont_home_top, lv_color_hex(0xd3d3d3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_cont_home_top, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_cont_home_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_home_wifi_ok
    ui->screen_home_img_home_wifi_ok = lv_image_create(ui->screen_home_cont_home_top);
    lv_obj_set_pos(ui->screen_home_img_home_wifi_ok, 0, 0);
    lv_obj_set_size(ui->screen_home_img_home_wifi_ok, 25, 25);
    lv_obj_add_flag(ui->screen_home_img_home_wifi_ok, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_home_wifi_ok, &_wifi_ok_RGB565A8_25x25);
    lv_image_set_pivot(ui->screen_home_img_home_wifi_ok, 50,50);
    lv_image_set_rotation(ui->screen_home_img_home_wifi_ok, 0);

    //Write style for screen_home_img_home_wifi_ok, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_home_wifi_ok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_home_wifi_ok, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_home_update_time
    ui->screen_home_label_home_update_time = lv_label_create(ui->screen_home_cont_home_top);
    lv_obj_set_pos(ui->screen_home_label_home_update_time, 80, 0);
    lv_obj_set_size(ui->screen_home_label_home_update_time, 100, 25);
    lv_label_set_text(ui->screen_home_label_home_update_time, "update_time");
    lv_label_set_long_mode(ui->screen_home_label_home_update_time, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_home_update_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_home_update_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_home_update_time, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_home_update_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_home_update_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_home_update_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_home.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_home);

    //Init events for screen.
    events_init_screen_home(ui);
}
