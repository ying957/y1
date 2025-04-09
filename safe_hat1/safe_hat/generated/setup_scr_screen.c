/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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



void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 800, 480);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x6df5fb), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_1,
	ui->screen_img_1 = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_1, &_bck_alpha_480x400);//替换图片处
	lv_img_set_pivot(ui->screen_img_1, 50,50);
	lv_img_set_angle(ui->screen_img_1, 0);
	lv_obj_set_pos(ui->screen_img_1, 101, 41);
	lv_obj_set_size(ui->screen_img_1, 480, 400);

	//Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_imgbtn_1
	ui->screen_imgbtn_1 = lv_imgbtn_create(ui->screen);
	lv_obj_add_flag(ui->screen_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_lb_alpha_61x53, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_jy_alpha_61x53, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_jy_alpha_61x53, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_lb_alpha_61x53, NULL);
	ui->screen_imgbtn_1_label = lv_label_create(ui->screen_imgbtn_1);
	lv_label_set_text(ui->screen_imgbtn_1_label, "");
	lv_label_set_long_mode(ui->screen_imgbtn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_imgbtn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_imgbtn_1, 717, 385);
	lv_obj_set_size(ui->screen_imgbtn_1, 61, 53);

	//Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_spangroup_1
	ui->screen_spangroup_1 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_1, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_1, LV_SPAN_MODE_BREAK);
	//create span 
	ui->screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(ui->screen_spangroup_1_span, "time");
	lv_style_set_text_color(&ui->screen_spangroup_1_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&ui->screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&ui->screen_spangroup_1_span->style, &lv_font_montserratMedium_17);
	lv_obj_set_pos(ui->screen_spangroup_1, 8, 8);
	lv_obj_set_size(ui->screen_spangroup_1, 130, 20);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_1_main_main_default
	static lv_style_t style_screen_spangroup_1_main_main_default;
	ui_init_style(&style_screen_spangroup_1_main_main_default);
	
	lv_style_set_border_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_1, &style_screen_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_1);

	//Write codes screen_imgbtn_2
	ui->screen_imgbtn_2 = lv_imgbtn_create(ui->screen);
	lv_obj_add_flag(ui->screen_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_start_alpha_64x59, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, &_stop_alpha_64x59, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_stop_alpha_64x59, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_start_alpha_64x59, NULL);
	ui->screen_imgbtn_2_label = lv_label_create(ui->screen_imgbtn_2);
	lv_label_set_text(ui->screen_imgbtn_2_label, "");
	lv_label_set_long_mode(ui->screen_imgbtn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_imgbtn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_imgbtn_2, 589, 379);
	lv_obj_set_size(ui->screen_imgbtn_2, 64, 59);

	//Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_ddlist_1
	ui->screen_ddlist_1 = lv_dropdown_create(ui->screen);
	lv_dropdown_set_options(ui->screen_ddlist_1, "list1\nlist2\nlist3");
	lv_obj_set_pos(ui->screen_ddlist_1, 662, 14);
	lv_obj_set_size(ui->screen_ddlist_1, 130, 30);

	//Write style for screen_ddlist_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_ddlist_1, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_ddlist_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_ddlist_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_ddlist_1, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_ddlist_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ddlist_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_ddlist_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_ddlist_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_screen_ddlist_1_extra_list_selected_checked
	static lv_style_t style_screen_ddlist_1_extra_list_selected_checked;
	ui_init_style(&style_screen_ddlist_1_extra_list_selected_checked);
	
	lv_style_set_border_width(&style_screen_ddlist_1_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_ddlist_1_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_ddlist_1), &style_screen_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_ddlist_1_extra_list_main_default
	static lv_style_t style_screen_ddlist_1_extra_list_main_default;
	ui_init_style(&style_screen_ddlist_1_extra_list_main_default);
	
	lv_style_set_max_height(&style_screen_ddlist_1_extra_list_main_default, 90);
	lv_style_set_text_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_ddlist_1_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_text_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_width(&style_screen_ddlist_1_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0xffffff));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_ddlist_1), &style_screen_ddlist_1_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_ddlist_1_extra_list_scrollbar_default
	static lv_style_t style_screen_ddlist_1_extra_list_scrollbar_default;
	ui_init_style(&style_screen_ddlist_1_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_ddlist_1), &style_screen_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_btn_1
	ui->screen_btn_1 = lv_btn_create(ui->screen);
	ui->screen_btn_1_label = lv_label_create(ui->screen_btn_1);
	lv_label_set_text(ui->screen_btn_1_label, "qiehuan");
	lv_label_set_long_mode(ui->screen_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_1, 589, 298);
	lv_obj_set_size(ui->screen_btn_1, 100, 37);

	//Write style for screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_imgbtn_3
	ui->screen_imgbtn_3 = lv_imgbtn_create(ui->screen);
	lv_obj_add_flag(ui->screen_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, &_phone_alpha_30x30, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, &_phone_alpha_30x30, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_phone_alpha_30x30, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_phone_alpha_30x30, NULL);
	ui->screen_imgbtn_3_label = lv_label_create(ui->screen_imgbtn_3);
	lv_label_set_text(ui->screen_imgbtn_3_label, "");
	lv_label_set_long_mode(ui->screen_imgbtn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_imgbtn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_imgbtn_3, 621, 14);
	lv_obj_set_size(ui->screen_imgbtn_3, 30, 30);

	//Write style for screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_imgbtn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->screen_imgbtn_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(ui->screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_recolor_opa(ui->screen_imgbtn_3, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
	lv_obj_set_style_img_opa(ui->screen_imgbtn_3, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//The custom code of screen.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	//Init events for screen.
	events_init_screen(ui);
}
