/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen_home_btn_home_weather_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_weather, guider_ui.screen_weather_del, &guider_ui.screen_home_del, setup_scr_screen_weather, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_home_btn_home_sensor_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_sensor, guider_ui.screen_sensor_del, &guider_ui.screen_home_del, setup_scr_screen_sensor, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_home_btn_home_log_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_log, guider_ui.screen_log_del, &guider_ui.screen_home_del, setup_scr_screen_log, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_home_btn_home_set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_set, guider_ui.screen_set_del, &guider_ui.screen_home_del, setup_scr_screen_set, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_home (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_home_btn_home_weather, screen_home_btn_home_weather_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_home_btn_home_sensor, screen_home_btn_home_sensor_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_home_btn_home_log, screen_home_btn_home_log_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_home_btn_home_set, screen_home_btn_home_set_event_handler, LV_EVENT_ALL, ui);
}

static void screen_weather_btn_weather_set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_set, guider_ui.screen_set_del, &guider_ui.screen_weather_del, setup_scr_screen_set, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_weather_btn_weather_log_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_log, guider_ui.screen_log_del, &guider_ui.screen_weather_del, setup_scr_screen_log, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_weather_btn_weather_sensor_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_sensor, guider_ui.screen_sensor_del, &guider_ui.screen_weather_del, setup_scr_screen_sensor, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_weather_btn_weather_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_weather_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_weather (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_weather_btn_weather_set, screen_weather_btn_weather_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_weather_btn_weather_log, screen_weather_btn_weather_log_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_weather_btn_weather_sensor, screen_weather_btn_weather_sensor_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_weather_btn_weather_home, screen_weather_btn_weather_home_event_handler, LV_EVENT_ALL, ui);
}

static void screen_sensor_btn_sensor_set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_set, guider_ui.screen_set_del, &guider_ui.screen_sensor_del, setup_scr_screen_set, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_sensor_btn_sensor_hlog_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_log, guider_ui.screen_log_del, &guider_ui.screen_sensor_del, setup_scr_screen_log, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_sensor_btn_sensor_weather_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_weather, guider_ui.screen_weather_del, &guider_ui.screen_sensor_del, setup_scr_screen_weather, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_sensor_btn_sensor_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_sensor_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_sensor (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_sensor_btn_sensor_set, screen_sensor_btn_sensor_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_sensor_btn_sensor_hlog, screen_sensor_btn_sensor_hlog_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_sensor_btn_sensor_weather, screen_sensor_btn_sensor_weather_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_sensor_btn_sensor_home, screen_sensor_btn_sensor_home_event_handler, LV_EVENT_ALL, ui);
}

static void screen_log_btn_log_set_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_set, guider_ui.screen_set_del, &guider_ui.screen_log_del, setup_scr_screen_set, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_log_btn_log_sensor_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_sensor, guider_ui.screen_sensor_del, &guider_ui.screen_log_del, setup_scr_screen_sensor, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_log_btn_log_weather_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_weather, guider_ui.screen_weather_del, &guider_ui.screen_log_del, setup_scr_screen_weather, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_log_btn_log_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_log_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_log (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_log_btn_log_set, screen_log_btn_log_set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_log_btn_log_sensor, screen_log_btn_log_sensor_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_log_btn_log_weather, screen_log_btn_log_weather_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_log_btn_log_home, screen_log_btn_log_home_event_handler, LV_EVENT_ALL, ui);
}

static void screen_set_btn_set_log_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_log, guider_ui.screen_log_del, &guider_ui.screen_set_del, setup_scr_screen_log, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_set_btn_set_sensor_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_sensor, guider_ui.screen_sensor_del, &guider_ui.screen_set_del, setup_scr_screen_sensor, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_set_btn_set_weather_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_weather, guider_ui.screen_weather_del, &guider_ui.screen_set_del, setup_scr_screen_weather, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void screen_set_btn_set_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_set_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_set (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_set_btn_set_log, screen_set_btn_set_log_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_set_btn_set_sensor, screen_set_btn_set_sensor_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_set_btn_set_weather, screen_set_btn_set_weather_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_set_btn_set_home, screen_set_btn_set_home_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
