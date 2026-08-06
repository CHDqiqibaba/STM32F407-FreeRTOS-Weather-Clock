/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *screen_home;
	bool screen_home_del;
	lv_obj_t *screen_home_cont_home;
	lv_obj_t *screen_home_label_home_weekday;
	lv_obj_t *screen_home_btn_home_home;
	lv_obj_t *screen_home_btn_home_home_label;
	lv_obj_t *screen_home_btn_home_weather;
	lv_obj_t *screen_home_btn_home_weather_label;
	lv_obj_t *screen_home_btn_home_sensor;
	lv_obj_t *screen_home_btn_home_sensor_label;
	lv_obj_t *screen_home_btn_home_log;
	lv_obj_t *screen_home_btn_home_log_label;
	lv_obj_t *screen_home_btn_home_set;
	lv_obj_t *screen_home_btn_home_set_label;
	lv_obj_t *screen_home_datetext_home_data;
	lv_obj_t *screen_home_label_home_weather;
	lv_obj_t *screen_home_label_home_outdoor_temp;
	lv_obj_t *screen_home_label_home_outdoor_humi;
	lv_obj_t *screen_home_label_home_time;
	lv_obj_t *screen_home_cont_home_top;
	lv_obj_t *screen_home_img_home_wifi_ok;
	lv_obj_t *screen_home_label_home_update_time;
	lv_obj_t *screen_weather;
	bool screen_weather_del;
	lv_obj_t *screen_weather_cont_weather;
	lv_obj_t *screen_weather_btn_weather_set;
	lv_obj_t *screen_weather_btn_weather_set_label;
	lv_obj_t *screen_weather_btn_weather_log;
	lv_obj_t *screen_weather_btn_weather_log_label;
	lv_obj_t *screen_weather_btn_weather_sensor;
	lv_obj_t *screen_weather_btn_weather_sensor_label;
	lv_obj_t *screen_weather_btn_weather_weather;
	lv_obj_t *screen_weather_btn_weather_weather_label;
	lv_obj_t *screen_weather_btn_weather_home;
	lv_obj_t *screen_weather_btn_weather_home_label;
	lv_obj_t *screen_weather_cont_weather_top;
	lv_obj_t *screen_weather_label_weather_weather;
	lv_obj_t *screen_weather_btn_weather_refresh;
	lv_obj_t *screen_weather_btn_weather_refresh_label;
	lv_obj_t *screen_weather_label_weather_update;
	lv_obj_t *screen_weather_label_weather_update_value;
	lv_obj_t *screen_weather_label_weather_wifi;
	lv_obj_t *screen_weather_label_weather_ip;
	lv_obj_t *screen_weather_label_weather_wifi_value;
	lv_obj_t *screen_weather_label_weather_ip_value;
	lv_obj_t *screen_sensor;
	bool screen_sensor_del;
	lv_obj_t *screen_sensor_cont_sensor;
	lv_obj_t *screen_sensor_btn_sensor_set;
	lv_obj_t *screen_sensor_btn_sensor_set_label;
	lv_obj_t *screen_sensor_btn_sensor_hlog;
	lv_obj_t *screen_sensor_btn_sensor_hlog_label;
	lv_obj_t *screen_sensor_btn_sensor_sensor;
	lv_obj_t *screen_sensor_btn_sensor_sensor_label;
	lv_obj_t *screen_sensor_btn_sensor_weather;
	lv_obj_t *screen_sensor_btn_sensor_weather_label;
	lv_obj_t *screen_sensor_btn_sensor_home;
	lv_obj_t *screen_sensor_btn_sensor_home_label;
	lv_obj_t *screen_sensor_cont_sensor_top;
	lv_obj_t *screen_sensor_btn_sensor_refresh;
	lv_obj_t *screen_sensor_btn_sensor_refresh_label;
	lv_obj_t *screen_sensor_label_sensor_humidity_value;
	lv_obj_t *screen_sensor_label_sensor_humidity;
	lv_obj_t *screen_sensor_label_sensor_temp_value;
	lv_obj_t *screen_sensor_label_sensor_temp;
	lv_obj_t *screen_sensor_label_sensor_air_value;
	lv_obj_t *screen_sensor_label_sensor_air;
	lv_obj_t *screen_sensor_label_sensor_light_value;
	lv_obj_t *screen_sensor_label_sensor_light;
	lv_obj_t *screen_sensor_label_sensor_motion;
	lv_obj_t *screen_sensor_label_sensor_motion_value;
	lv_obj_t *screen_log;
	bool screen_log_del;
	lv_obj_t *screen_log_cont_log;
	lv_obj_t *screen_log_btn_log_set;
	lv_obj_t *screen_log_btn_log_set_label;
	lv_obj_t *screen_log_btn_log_log;
	lv_obj_t *screen_log_btn_log_log_label;
	lv_obj_t *screen_log_btn_log_sensor;
	lv_obj_t *screen_log_btn_log_sensor_label;
	lv_obj_t *screen_log_btn_log_weather;
	lv_obj_t *screen_log_btn_log_weather_label;
	lv_obj_t *screen_log_btn_log_home;
	lv_obj_t *screen_log_btn_log_home_label;
	lv_obj_t *screen_log_cont_log_top;
	lv_obj_t *screen_log_label_log_last_record;
	lv_obj_t *screen_log_label_log_last_temp;
	lv_obj_t *screen_log_label_log_last_humi;
	lv_obj_t *screen_log_label_log_last_time;
	lv_obj_t *screen_log_btn_log_save;
	lv_obj_t *screen_log_btn_log_save_label;
	lv_obj_t *screen_log_list_log_information;
	lv_obj_t *screen_set;
	bool screen_set_del;
	lv_obj_t *screen_set_cont_set;
	lv_obj_t *screen_set_btn_set_set;
	lv_obj_t *screen_set_btn_set_set_label;
	lv_obj_t *screen_set_btn_set_log;
	lv_obj_t *screen_set_btn_set_log_label;
	lv_obj_t *screen_set_btn_set_sensor;
	lv_obj_t *screen_set_btn_set_sensor_label;
	lv_obj_t *screen_set_btn_set_weather;
	lv_obj_t *screen_set_btn_set_weather_label;
	lv_obj_t *screen_set_btn_set_home;
	lv_obj_t *screen_set_btn_set_home_label;
	lv_obj_t *screen_set_cont_set_top;
	lv_obj_t *screen_set_btn_set_clear;
	lv_obj_t *screen_set_btn_set_clear_label;
	lv_obj_t *screen_set_label_set_version;
	lv_obj_t *screen_set_btn_set_sync_time;
	lv_obj_t *screen_set_btn_set_sync_time_label;
	lv_obj_t *screen_set_label_set_version_value;
	lv_obj_t *screen_set_label_set_lcd_brightness;
	lv_obj_t *screen_set_label_set_lcd_brightness_value;
	lv_obj_t *screen_set_label_set_wifi;
	lv_obj_t *screen_set_label_set_wifi_value;
	lv_obj_t *screen_set_slider_set_brightness;
	lv_obj_t *screen_set_btn_set_connectwifi;
	lv_obj_t *screen_set_btn_set_connectwifi_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_weather(lv_ui *ui);
void setup_scr_screen_sensor(lv_ui *ui);
void setup_scr_screen_log(lv_ui *ui);
void setup_scr_screen_set(lv_ui *ui);
LV_IMAGE_DECLARE(_wifi_ok_RGB565A8_25x25);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_10)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
