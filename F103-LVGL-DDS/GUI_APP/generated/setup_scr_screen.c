/*
 * Copyright 2023 NXP
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
#include "../custom/custom.h"

static lv_obj_t *kb;
static void kb_event_cb(lv_obj_t *event_kb, lv_event_t event)
{
	lv_keyboard_def_event_cb(event_kb, event);
	if (event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL)
	{
		lv_obj_set_hidden(event_kb, true);
	}
}

static void text_area_event_cb(lv_obj_t *ta, lv_event_t event)
{
	if (event == LV_EVENT_FOCUSED || event == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_move_foreground(kb);
		lv_obj_set_hidden(kb, false);
	}
	if (event == LV_EVENT_CANCEL || event == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_move_background(kb);
		lv_obj_set_hidden(kb, true);
	}
}

void setup_scr_screen(lv_ui *ui)
{
	// Widget: screen
	ui->screen = lv_obj_create(NULL, NULL);
	kb = lv_keyboard_create(ui->screen, NULL);
	lv_obj_set_event_cb(kb, kb_event_cb);
	lv_obj_set_hidden(kb, true);
	lv_obj_set_size(ui->screen, 320, 240);

	// Set style for screen. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_main_default;
	lv_style_reset(&style_screen_main_default);
	lv_style_set_bg_opa(&style_screen_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen, LV_OBJ_PART_MAIN, &style_screen_main_default);

	// Widget: screen_Function_Set
	ui->screen_Function_Set = lv_tabview_create(ui->screen, NULL);
	lv_obj_set_pos(ui->screen_Function_Set, -2, -1);
	lv_obj_set_size(ui->screen_Function_Set, 324, 243);

	// Set style for screen_Function_Set. Part: LV_TABVIEW_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Function_Set_bg_default;
	lv_style_reset(&style_screen_Function_Set_bg_default);
	lv_style_set_bg_opa(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xeaeff3));
	lv_style_set_text_color(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x4d4d4d));
	lv_style_set_text_font(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_15);
	lv_style_set_text_letter_space(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, 16);
	lv_style_set_border_width(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xc0c0c0));
	lv_style_set_shadow_width(&style_screen_Function_Set_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Function_Set, LV_TABVIEW_PART_BG, &style_screen_Function_Set_bg_default);

	// Set style for screen_Function_Set. Part: LV_TABVIEW_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Function_Set_indic_default;
	lv_style_reset(&style_screen_Function_Set_indic_default);
	lv_style_set_bg_opa(&style_screen_Function_Set_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Function_Set_indic_default, LV_STATE_DEFAULT, lv_color_hex(0xb9001c));
	lv_obj_add_style(ui->screen_Function_Set, LV_TABVIEW_PART_INDIC, &style_screen_Function_Set_indic_default);

	// Set style for screen_Function_Set. Part: LV_TABVIEW_PART_TAB_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Function_Set_tab_bg_default;
	lv_style_reset(&style_screen_Function_Set_tab_bg_default);
	lv_style_set_bg_opa(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xa5a5a5));
	lv_style_set_pad_top(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Function_Set_tab_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Function_Set, LV_TABVIEW_PART_TAB_BG, &style_screen_Function_Set_tab_bg_default);

	// Set style for screen_Function_Set. Part: LV_TABVIEW_PART_TAB_BTN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Function_Set_tab_btn_default;
	lv_style_reset(&style_screen_Function_Set_tab_btn_default);
	lv_style_set_text_color(&style_screen_Function_Set_tab_btn_default, LV_STATE_DEFAULT, lv_color_hex(0x4d4d4d));
	lv_style_set_text_font(&style_screen_Function_Set_tab_btn_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_24);
	lv_style_set_text_letter_space(&style_screen_Function_Set_tab_btn_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Function_Set, LV_TABVIEW_PART_TAB_BTN, &style_screen_Function_Set_tab_btn_default);

	// Set style for screen_Function_Set. Part: LV_TABVIEW_PART_TAB_BTN, State: LV_STATE_CHECKED
	static lv_style_t style_screen_Function_Set_tab_btn_checked;
	lv_style_reset(&style_screen_Function_Set_tab_btn_checked);
	lv_style_set_text_color(&style_screen_Function_Set_tab_btn_checked, LV_STATE_CHECKED, lv_color_hex(0x4d4d4d));
	lv_style_set_text_font(&style_screen_Function_Set_tab_btn_checked, LV_STATE_CHECKED, &lv_font_montserratMedium_24);
	lv_style_set_text_letter_space(&style_screen_Function_Set_tab_btn_checked, LV_STATE_CHECKED, 0);
	lv_obj_add_style(ui->screen_Function_Set, LV_TABVIEW_PART_TAB_BTN, &style_screen_Function_Set_tab_btn_checked);

	// Tab: screen_Function_Set_tab_1 with title "Sin"
	ui->screen_Function_Set_tab_1 = lv_tabview_add_tab(ui->screen_Function_Set, "Sin");
	lv_obj_t *screen_Function_Set_tab_1_label = lv_label_create(ui->screen_Function_Set_tab_1, NULL);
	lv_label_set_text(screen_Function_Set_tab_1_label, "");

	// Widget: screen_FG_SIN_IMG
	ui->screen_FG_SIN_IMG = lv_img_create(ui->screen_Function_Set_tab_1, NULL);
	lv_obj_set_click(ui->screen_FG_SIN_IMG, true);
	lv_img_set_src(ui->screen_FG_SIN_IMG, &_FG_SIN_alpha_102x119);
	lv_img_set_pivot(ui->screen_FG_SIN_IMG, 50, 50);
	lv_img_set_angle(ui->screen_FG_SIN_IMG, 0);
	lv_obj_set_pos(ui->screen_FG_SIN_IMG, 9, -10);
	lv_obj_set_size(ui->screen_FG_SIN_IMG, 102, 119);

	// Set style for screen_FG_SIN_IMG. Part: LV_IMG_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_FG_SIN_IMG_main_default;
	lv_style_reset(&style_screen_FG_SIN_IMG_main_default);
	lv_style_set_image_opa(&style_screen_FG_SIN_IMG_main_default, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_FG_SIN_IMG, LV_IMG_PART_MAIN, &style_screen_FG_SIN_IMG_main_default);

	// Widget: screen_Sin_Channel_2_btn
	ui->screen_Sin_Channel_2_btn = lv_btn_create(ui->screen_Function_Set_tab_1, NULL);
	lv_btn_set_checkable(ui->screen_Sin_Channel_2_btn, true);
	ui->screen_Sin_Channel_2_btn_label = lv_label_create(ui->screen_Sin_Channel_2_btn, NULL);
	lv_label_set_text(ui->screen_Sin_Channel_2_btn_label, "Channel 2");
	lv_label_set_align(ui->screen_Sin_Channel_2_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Channel_2_btn, 15, 131);
	lv_obj_set_size(ui->screen_Sin_Channel_2_btn, 89, 23);

	// Set style for screen_Sin_Channel_2_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Channel_2_btn_main_default;
	lv_style_reset(&style_screen_Sin_Channel_2_btn_main_default);
	lv_style_set_text_color(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xbf001d));
	lv_style_set_radius(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, 4);
	lv_style_set_shadow_width(&style_screen_Sin_Channel_2_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Channel_2_btn, LV_BTN_PART_MAIN, &style_screen_Sin_Channel_2_btn_main_default);

	// Set style for screen_Sin_Channel_2_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_PRESSED
	if (Btn_Sel.Sin_Channel_2)
	{
		static lv_style_t style_screen_Sin_Channel_2_btn_main_pressed;
		lv_style_reset(&style_screen_Sin_Channel_2_btn_main_pressed);
		lv_style_set_text_color(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x000000));
		lv_style_set_text_font(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, &lv_font_montserratMedium_12);
		lv_style_set_bg_opa(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_bg_color(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0xD0F6FF));
		lv_style_set_border_width(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 2);
		lv_style_set_border_opa(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_border_color(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x01a2b1));
		lv_style_set_radius(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 4);
		lv_style_set_shadow_width(&style_screen_Sin_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 0);
		lv_obj_add_style(ui->screen_Sin_Channel_2_btn, LV_BTN_PART_MAIN, &style_screen_Sin_Channel_2_btn_main_pressed);
	}
	// Widget: screen_Sin_Channel_1_btn
	ui->screen_Sin_Channel_1_btn = lv_btn_create(ui->screen_Function_Set_tab_1, NULL);
	lv_btn_set_checkable(ui->screen_Sin_Channel_1_btn, true);
	ui->screen_Sin_Channel_1_btn_label = lv_label_create(ui->screen_Sin_Channel_1_btn, NULL);
	lv_label_set_text(ui->screen_Sin_Channel_1_btn_label, "Channel 1");
	lv_label_set_align(ui->screen_Sin_Channel_1_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Channel_1_btn, 15, 99);
	lv_obj_set_size(ui->screen_Sin_Channel_1_btn, 89, 23);

	// Set style for screen_Sin_Channel_1_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Channel_1_btn_main_default;
	lv_style_reset(&style_screen_Sin_Channel_1_btn_main_default);
	lv_style_set_text_color(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xbf001d));
	lv_style_set_radius(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, 4);
	lv_style_set_shadow_width(&style_screen_Sin_Channel_1_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Channel_1_btn, LV_BTN_PART_MAIN, &style_screen_Sin_Channel_1_btn_main_default);

	// Set style for screen_Sin_Channel_1_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_PRESSED
	if (Btn_Sel.Sin_Channel_1)
	{
		static lv_style_t style_screen_Sin_Channel_1_btn_main_pressed;
		lv_style_reset(&style_screen_Sin_Channel_1_btn_main_pressed);
		lv_style_set_text_color(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x000000));
		lv_style_set_text_font(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, &lv_font_montserratMedium_12);
		lv_style_set_bg_opa(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_bg_color(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0xd0f6ff));
		lv_style_set_border_width(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 2);
		lv_style_set_border_opa(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_border_color(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x01a2b1));
		lv_style_set_radius(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 4);
		lv_style_set_shadow_width(&style_screen_Sin_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 0);
		lv_obj_add_style(ui->screen_Sin_Channel_1_btn, LV_BTN_PART_MAIN, &style_screen_Sin_Channel_1_btn_main_pressed);
	}
	// Widget: screen_Sin_Pword_Slider
	ui->screen_Sin_Pword_Slider = lv_slider_create(ui->screen_Function_Set_tab_1, NULL);
	lv_slider_set_range(ui->screen_Sin_Pword_Slider, 0, 360);
	lv_slider_set_value(ui->screen_Sin_Pword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Sin_Pword_Slider, 151, 151);
	lv_obj_set_size(ui->screen_Sin_Pword_Slider, 168, 5);

	// Set style for screen_Sin_Pword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Pword_Slider_bg_default;
	lv_style_reset(&style_screen_Sin_Pword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Sin_Pword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Pword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Sin_Pword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Sin_Pword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Pword_Slider, LV_SLIDER_PART_BG, &style_screen_Sin_Pword_Slider_bg_default);

	// Set style for screen_Sin_Pword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Pword_Slider_indic_default;
	lv_style_reset(&style_screen_Sin_Pword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Sin_Pword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Pword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Sin_Pword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Sin_Pword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Sin_Pword_Slider_indic_default);

	// Set style for screen_Sin_Pword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Pword_Slider_knob_default;
	lv_style_reset(&style_screen_Sin_Pword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Sin_Pword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Pword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Sin_Pword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Sin_Pword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Sin_Pword_Slider_knob_default);

	// Widget: screen_Sin_Fword_Slider
	ui->screen_Sin_Fword_Slider = lv_slider_create(ui->screen_Function_Set_tab_1, NULL);
	lv_slider_set_range(ui->screen_Sin_Fword_Slider, 0, 1000);
	lv_slider_set_value(ui->screen_Sin_Fword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Sin_Fword_Slider, 151, 91);
	lv_obj_set_size(ui->screen_Sin_Fword_Slider, 168, 5);

	// Set style for screen_Sin_Fword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Fword_Slider_bg_default;
	lv_style_reset(&style_screen_Sin_Fword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Sin_Fword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Fword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Sin_Fword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Sin_Fword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Fword_Slider, LV_SLIDER_PART_BG, &style_screen_Sin_Fword_Slider_bg_default);

	// Set style for screen_Sin_Fword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Fword_Slider_indic_default;
	lv_style_reset(&style_screen_Sin_Fword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Sin_Fword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Fword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Sin_Fword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Sin_Fword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Sin_Fword_Slider_indic_default);

	// Set style for screen_Sin_Fword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Fword_Slider_knob_default;
	lv_style_reset(&style_screen_Sin_Fword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Sin_Fword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Fword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Sin_Fword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Sin_Fword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Sin_Fword_Slider_knob_default);

	// Widget: screen_Sin_Aword_Slider
	ui->screen_Sin_Aword_Slider = lv_slider_create(ui->screen_Function_Set_tab_1, NULL);
	lv_slider_set_range(ui->screen_Sin_Aword_Slider, 0, 10000);
	lv_slider_set_value(ui->screen_Sin_Aword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Sin_Aword_Slider, 151, 31);
	lv_obj_set_size(ui->screen_Sin_Aword_Slider, 168, 5);

	// Set style for screen_Sin_Aword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Aword_Slider_bg_default;
	lv_style_reset(&style_screen_Sin_Aword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Sin_Aword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Aword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Sin_Aword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Sin_Aword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Aword_Slider, LV_SLIDER_PART_BG, &style_screen_Sin_Aword_Slider_bg_default);

	// Set style for screen_Sin_Aword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Aword_Slider_indic_default;
	lv_style_reset(&style_screen_Sin_Aword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Sin_Aword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Aword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Sin_Aword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Sin_Aword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Sin_Aword_Slider_indic_default);

	// Set style for screen_Sin_Aword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Aword_Slider_knob_default;
	lv_style_reset(&style_screen_Sin_Aword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Sin_Aword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Sin_Aword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Sin_Aword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Sin_Aword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Sin_Aword_Slider_knob_default);

	// Widget: screen_Sin_Aword_Label
	ui->screen_Sin_Aword_Label = lv_label_create(ui->screen_Function_Set_tab_1, NULL);
	lv_label_set_text(ui->screen_Sin_Aword_Label, "Ampl :");
	lv_label_set_align(ui->screen_Sin_Aword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Aword_Label, 150, 10);
	lv_obj_set_width(ui->screen_Sin_Aword_Label, 100);

	// Set style for screen_Sin_Aword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Aword_Label_main_default;
	lv_style_reset(&style_screen_Sin_Aword_Label_main_default);
	lv_style_set_radius(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Sin_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Aword_Label, LV_LABEL_PART_MAIN, &style_screen_Sin_Aword_Label_main_default);

	// Widget: screen_Sin_Fword_Label
	ui->screen_Sin_Fword_Label = lv_label_create(ui->screen_Function_Set_tab_1, NULL);
	lv_label_set_text(ui->screen_Sin_Fword_Label, "Freq :");
	lv_label_set_align(ui->screen_Sin_Fword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Fword_Label, 150, 70);
	lv_obj_set_width(ui->screen_Sin_Fword_Label, 100);

	// Set style for screen_Sin_Fword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Fword_Label_main_default;
	lv_style_reset(&style_screen_Sin_Fword_Label_main_default);
	lv_style_set_radius(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Sin_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Fword_Label, LV_LABEL_PART_MAIN, &style_screen_Sin_Fword_Label_main_default);

	// Widget: screen_Sin_Pword_Label
	ui->screen_Sin_Pword_Label = lv_label_create(ui->screen_Function_Set_tab_1, NULL);
	lv_label_set_text(ui->screen_Sin_Pword_Label, "Phas :");
	lv_label_set_align(ui->screen_Sin_Pword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Pword_Label, 150, 130);
	lv_obj_set_width(ui->screen_Sin_Pword_Label, 100);

	// Set style for screen_Sin_Pword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Pword_Label_main_default;
	lv_style_reset(&style_screen_Sin_Pword_Label_main_default);
	lv_style_set_radius(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Sin_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Pword_Label, LV_LABEL_PART_MAIN, &style_screen_Sin_Pword_Label_main_default);

	// Widget: screen_Sin_MV_unit
	ui->screen_Sin_MV_unit = lv_label_create(ui->screen_Function_Set_tab_1, NULL);
	lv_label_set_text(ui->screen_Sin_MV_unit, "mV");
	lv_label_set_align(ui->screen_Sin_MV_unit, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_MV_unit, 267, 10);
	lv_obj_set_width(ui->screen_Sin_MV_unit, 32);

	// Set style for screen_Sin_MV_unit. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_MV_unit_main_default;
	lv_style_reset(&style_screen_Sin_MV_unit_main_default);
	lv_style_set_radius(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Sin_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_MV_unit, LV_LABEL_PART_MAIN, &style_screen_Sin_MV_unit_main_default);

	// Widget: screen_Sin_Degree_unit
	ui->screen_Sin_Degree_unit = lv_label_create(ui->screen_Function_Set_tab_1, NULL);
	lv_label_set_text(ui->screen_Sin_Degree_unit, "degree");
	lv_label_set_align(ui->screen_Sin_Degree_unit, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Degree_unit, 261, 130);
	lv_obj_set_width(ui->screen_Sin_Degree_unit, 56);

	// Set style for screen_Sin_Degree_unit. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Degree_unit_main_default;
	lv_style_reset(&style_screen_Sin_Degree_unit_main_default);
	lv_style_set_radius(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Sin_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Degree_unit, LV_LABEL_PART_MAIN, &style_screen_Sin_Degree_unit_main_default);

	// Widget: screen_Sin_Hz_btn
	ui->screen_Sin_Hz_btn = lv_btn_create(ui->screen_Function_Set_tab_1, NULL);
	ui->screen_Sin_Hz_btn_label = lv_label_create(ui->screen_Sin_Hz_btn, NULL);
	lv_label_set_text(ui->screen_Sin_Hz_btn_label, "Hz");
	lv_label_set_align(ui->screen_Sin_Hz_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Sin_Hz_btn, 260, 65);
	lv_obj_set_size(ui->screen_Sin_Hz_btn, 49, 23);

	// Set style for screen_Sin_Hz_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Sin_Hz_btn_main_default;
	lv_style_reset(&style_screen_Sin_Hz_btn_main_default);
	lv_style_set_text_color(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_shadow_width(&style_screen_Sin_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Sin_Hz_btn, LV_BTN_PART_MAIN, &style_screen_Sin_Hz_btn_main_default);

	// Tab: screen_Function_Set_tab_2 with title "Squ"
	ui->screen_Function_Set_tab_2 = lv_tabview_add_tab(ui->screen_Function_Set, "Squ");
	lv_obj_t *screen_Function_Set_tab_2_label = lv_label_create(ui->screen_Function_Set_tab_2, NULL);
	lv_label_set_text(screen_Function_Set_tab_2_label, "");

	// Widget: screen_FG_SQU_IMG
	ui->screen_FG_SQU_IMG = lv_img_create(ui->screen_Function_Set_tab_2, NULL);
	lv_obj_set_click(ui->screen_FG_SQU_IMG, true);
	lv_img_set_src(ui->screen_FG_SQU_IMG, &_FG_SQU_alpha_110x139);
	lv_img_set_pivot(ui->screen_FG_SQU_IMG, 50, 50);
	lv_img_set_angle(ui->screen_FG_SQU_IMG, 0);
	lv_obj_set_pos(ui->screen_FG_SQU_IMG, 9, -15);
	lv_obj_set_size(ui->screen_FG_SQU_IMG, 110, 139);

	// Set style for screen_FG_SQU_IMG. Part: LV_IMG_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_FG_SQU_IMG_main_default;
	lv_style_reset(&style_screen_FG_SQU_IMG_main_default);
	lv_style_set_image_opa(&style_screen_FG_SQU_IMG_main_default, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_FG_SQU_IMG, LV_IMG_PART_MAIN, &style_screen_FG_SQU_IMG_main_default);

	// Widget: screen_Squ_Channel_2_btn
	ui->screen_Squ_Channel_2_btn = lv_btn_create(ui->screen_Function_Set_tab_2, NULL);
	lv_btn_set_checkable(ui->screen_Squ_Channel_2_btn, true);
	ui->screen_Squ_Channel_2_btn_label = lv_label_create(ui->screen_Squ_Channel_2_btn, NULL);
	lv_label_set_text(ui->screen_Squ_Channel_2_btn_label, "Channel 2");
	lv_label_set_align(ui->screen_Squ_Channel_2_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Channel_2_btn, 15, 131);
	lv_obj_set_size(ui->screen_Squ_Channel_2_btn, 89, 23);

	// Set style for screen_Squ_Channel_2_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Channel_2_btn_main_default;
	lv_style_reset(&style_screen_Squ_Channel_2_btn_main_default);
	lv_style_set_text_color(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xbf001d));
	lv_style_set_radius(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, 4);
	lv_style_set_shadow_width(&style_screen_Squ_Channel_2_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Channel_2_btn, LV_BTN_PART_MAIN, &style_screen_Squ_Channel_2_btn_main_default);

	// Set style for screen_Squ_Channel_2_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_PRESSED
	if (Btn_Sel.Squ_Channel_2)
	{
		static lv_style_t style_screen_Squ_Channel_2_btn_main_pressed;
		lv_style_reset(&style_screen_Squ_Channel_2_btn_main_pressed);
		lv_style_set_text_color(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x000000));
		lv_style_set_text_font(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, &lv_font_montserratMedium_12);
		lv_style_set_bg_opa(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_bg_color(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0xD0F6FF));
		lv_style_set_border_width(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 2);
		lv_style_set_border_opa(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_border_color(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x01a2b1));
		lv_style_set_radius(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 4);
		lv_style_set_shadow_width(&style_screen_Squ_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 0);
		lv_obj_add_style(ui->screen_Squ_Channel_2_btn, LV_BTN_PART_MAIN, &style_screen_Squ_Channel_2_btn_main_pressed);
	}
	// Widget: screen_Squ_Channel_1_btn
	ui->screen_Squ_Channel_1_btn = lv_btn_create(ui->screen_Function_Set_tab_2, NULL);
	lv_btn_set_checkable(ui->screen_Squ_Channel_1_btn, true);
	ui->screen_Squ_Channel_1_btn_label = lv_label_create(ui->screen_Squ_Channel_1_btn, NULL);
	lv_label_set_text(ui->screen_Squ_Channel_1_btn_label, "Channel 1");
	lv_label_set_align(ui->screen_Squ_Channel_1_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Channel_1_btn, 15, 99);
	lv_obj_set_size(ui->screen_Squ_Channel_1_btn, 89, 23);

	// Set style for screen_Squ_Channel_1_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Channel_1_btn_main_default;
	lv_style_reset(&style_screen_Squ_Channel_1_btn_main_default);
	lv_style_set_text_color(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xbf001d));
	lv_style_set_radius(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, 4);
	lv_style_set_shadow_width(&style_screen_Squ_Channel_1_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Channel_1_btn, LV_BTN_PART_MAIN, &style_screen_Squ_Channel_1_btn_main_default);

	// Set style for screen_Squ_Channel_1_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_PRESSED
	if (Btn_Sel.Squ_Channel_1)
	{
		static lv_style_t style_screen_Squ_Channel_1_btn_main_pressed;
		lv_style_reset(&style_screen_Squ_Channel_1_btn_main_pressed);
		lv_style_set_text_color(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x000000));
		lv_style_set_text_font(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, &lv_font_montserratMedium_12);
		lv_style_set_bg_opa(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_bg_color(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0xD0F6FF));
		lv_style_set_border_width(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 2);
		lv_style_set_border_opa(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_border_color(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x01a2b1));
		lv_style_set_radius(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 4);
		lv_style_set_shadow_width(&style_screen_Squ_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 0);
		lv_obj_add_style(ui->screen_Squ_Channel_1_btn, LV_BTN_PART_MAIN, &style_screen_Squ_Channel_1_btn_main_pressed);
	}
	// Widget: screen_Squ_Pword_Slider
	ui->screen_Squ_Pword_Slider = lv_slider_create(ui->screen_Function_Set_tab_2, NULL);
	lv_slider_set_range(ui->screen_Squ_Pword_Slider, 0, 360);
	lv_slider_set_value(ui->screen_Squ_Pword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Squ_Pword_Slider, 151, 151);
	lv_obj_set_size(ui->screen_Squ_Pword_Slider, 168, 5);

	// Set style for screen_Squ_Pword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Pword_Slider_bg_default;
	lv_style_reset(&style_screen_Squ_Pword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Squ_Pword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Pword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Squ_Pword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Squ_Pword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Pword_Slider, LV_SLIDER_PART_BG, &style_screen_Squ_Pword_Slider_bg_default);

	// Set style for screen_Squ_Pword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Pword_Slider_indic_default;
	lv_style_reset(&style_screen_Squ_Pword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Squ_Pword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Pword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Squ_Pword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Squ_Pword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Squ_Pword_Slider_indic_default);

	// Set style for screen_Squ_Pword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Pword_Slider_knob_default;
	lv_style_reset(&style_screen_Squ_Pword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Squ_Pword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Pword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Squ_Pword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Squ_Pword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Squ_Pword_Slider_knob_default);

	// Widget: screen_Squ_Fword_Slider
	ui->screen_Squ_Fword_Slider = lv_slider_create(ui->screen_Function_Set_tab_2, NULL);
	lv_slider_set_range(ui->screen_Squ_Fword_Slider, 0, 1000);
	lv_slider_set_value(ui->screen_Squ_Fword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Squ_Fword_Slider, 151, 91);
	lv_obj_set_size(ui->screen_Squ_Fword_Slider, 168, 5);

	// Set style for screen_Squ_Fword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Fword_Slider_bg_default;
	lv_style_reset(&style_screen_Squ_Fword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Squ_Fword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Fword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Squ_Fword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Squ_Fword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Fword_Slider, LV_SLIDER_PART_BG, &style_screen_Squ_Fword_Slider_bg_default);

	// Set style for screen_Squ_Fword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Fword_Slider_indic_default;
	lv_style_reset(&style_screen_Squ_Fword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Squ_Fword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Fword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Squ_Fword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Squ_Fword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Squ_Fword_Slider_indic_default);

	// Set style for screen_Squ_Fword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Fword_Slider_knob_default;
	lv_style_reset(&style_screen_Squ_Fword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Squ_Fword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Fword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Squ_Fword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Squ_Fword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Squ_Fword_Slider_knob_default);

	// Widget: screen_Squ_Aword_Slider
	ui->screen_Squ_Aword_Slider = lv_slider_create(ui->screen_Function_Set_tab_2, NULL);
	lv_slider_set_range(ui->screen_Squ_Aword_Slider, 0, 10000);
	lv_slider_set_value(ui->screen_Squ_Aword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Squ_Aword_Slider, 151, 31);
	lv_obj_set_size(ui->screen_Squ_Aword_Slider, 168, 5);

	// Set style for screen_Squ_Aword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Aword_Slider_bg_default;
	lv_style_reset(&style_screen_Squ_Aword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Squ_Aword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Aword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Squ_Aword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Squ_Aword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Aword_Slider, LV_SLIDER_PART_BG, &style_screen_Squ_Aword_Slider_bg_default);

	// Set style for screen_Squ_Aword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Aword_Slider_indic_default;
	lv_style_reset(&style_screen_Squ_Aword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Squ_Aword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Aword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Squ_Aword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Squ_Aword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Squ_Aword_Slider_indic_default);

	// Set style for screen_Squ_Aword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Aword_Slider_knob_default;
	lv_style_reset(&style_screen_Squ_Aword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Squ_Aword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Squ_Aword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Squ_Aword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Squ_Aword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Squ_Aword_Slider_knob_default);

	// Widget: screen_Squ_Pword_Label
	ui->screen_Squ_Pword_Label = lv_label_create(ui->screen_Function_Set_tab_2, NULL);
	lv_label_set_text(ui->screen_Squ_Pword_Label, "Phas :");
	lv_label_set_align(ui->screen_Squ_Pword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Pword_Label, 150, 130);
	lv_obj_set_width(ui->screen_Squ_Pword_Label, 100);

	// Set style for screen_Squ_Pword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Pword_Label_main_default;
	lv_style_reset(&style_screen_Squ_Pword_Label_main_default);
	lv_style_set_radius(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Squ_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Pword_Label, LV_LABEL_PART_MAIN, &style_screen_Squ_Pword_Label_main_default);

	// Widget: screen_Squ_Fword_Label
	ui->screen_Squ_Fword_Label = lv_label_create(ui->screen_Function_Set_tab_2, NULL);
	lv_label_set_text(ui->screen_Squ_Fword_Label, "Freq :");
	lv_label_set_align(ui->screen_Squ_Fword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Fword_Label, 150, 70);
	lv_obj_set_width(ui->screen_Squ_Fword_Label, 100);

	// Set style for screen_Squ_Fword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Fword_Label_main_default;
	lv_style_reset(&style_screen_Squ_Fword_Label_main_default);
	lv_style_set_radius(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Squ_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Fword_Label, LV_LABEL_PART_MAIN, &style_screen_Squ_Fword_Label_main_default);

	// Widget: screen_Squ_Aword_Label
	ui->screen_Squ_Aword_Label = lv_label_create(ui->screen_Function_Set_tab_2, NULL);
	lv_label_set_text(ui->screen_Squ_Aword_Label, "Ampl :");
	lv_label_set_align(ui->screen_Squ_Aword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Aword_Label, 150, 10);
	lv_obj_set_width(ui->screen_Squ_Aword_Label, 100);

	// Set style for screen_Squ_Aword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Aword_Label_main_default;
	lv_style_reset(&style_screen_Squ_Aword_Label_main_default);
	lv_style_set_radius(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Squ_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Aword_Label, LV_LABEL_PART_MAIN, &style_screen_Squ_Aword_Label_main_default);

	// Widget: screen_Squ_Degree_unit
	ui->screen_Squ_Degree_unit = lv_label_create(ui->screen_Function_Set_tab_2, NULL);
	lv_label_set_text(ui->screen_Squ_Degree_unit, "degree");
	lv_label_set_align(ui->screen_Squ_Degree_unit, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Degree_unit, 261, 130);
	lv_obj_set_width(ui->screen_Squ_Degree_unit, 56);

	// Set style for screen_Squ_Degree_unit. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Degree_unit_main_default;
	lv_style_reset(&style_screen_Squ_Degree_unit_main_default);
	lv_style_set_radius(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Squ_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Degree_unit, LV_LABEL_PART_MAIN, &style_screen_Squ_Degree_unit_main_default);

	// Widget: screen_Squ_MV_unit
	ui->screen_Squ_MV_unit = lv_label_create(ui->screen_Function_Set_tab_2, NULL);
	lv_label_set_text(ui->screen_Squ_MV_unit, "mV");
	lv_label_set_align(ui->screen_Squ_MV_unit, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_MV_unit, 267, 10);
	lv_obj_set_width(ui->screen_Squ_MV_unit, 32);

	// Set style for screen_Squ_MV_unit. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_MV_unit_main_default;
	lv_style_reset(&style_screen_Squ_MV_unit_main_default);
	lv_style_set_radius(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Squ_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_MV_unit, LV_LABEL_PART_MAIN, &style_screen_Squ_MV_unit_main_default);

	// Widget: screen_Squ_Hz_btn
	ui->screen_Squ_Hz_btn = lv_btn_create(ui->screen_Function_Set_tab_2, NULL);
	ui->screen_Squ_Hz_btn_label = lv_label_create(ui->screen_Squ_Hz_btn, NULL);
	lv_label_set_text(ui->screen_Squ_Hz_btn_label, "Hz");
	lv_label_set_align(ui->screen_Squ_Hz_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Squ_Hz_btn, 260, 65);
	lv_obj_set_size(ui->screen_Squ_Hz_btn, 49, 23);

	// Set style for screen_Squ_Hz_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Squ_Hz_btn_main_default;
	lv_style_reset(&style_screen_Squ_Hz_btn_main_default);
	lv_style_set_text_color(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_shadow_width(&style_screen_Squ_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Squ_Hz_btn, LV_BTN_PART_MAIN, &style_screen_Squ_Hz_btn_main_default);

	// Tab: screen_Function_Set_tab_3 with title "Tri"
	ui->screen_Function_Set_tab_3 = lv_tabview_add_tab(ui->screen_Function_Set, "Tri");
	lv_obj_t *screen_Function_Set_tab_3_label = lv_label_create(ui->screen_Function_Set_tab_3, NULL);
	lv_label_set_text(screen_Function_Set_tab_3_label, "");

	// Widget: screen_FG_TRI_IMG
	ui->screen_FG_TRI_IMG = lv_img_create(ui->screen_Function_Set_tab_3, NULL);
	lv_obj_set_click(ui->screen_FG_TRI_IMG, true);
	lv_img_set_src(ui->screen_FG_TRI_IMG, &_FG_TRI_alpha_108x149);
	lv_img_set_pivot(ui->screen_FG_TRI_IMG, 50, 50);
	lv_img_set_angle(ui->screen_FG_TRI_IMG, 0);
	lv_obj_set_pos(ui->screen_FG_TRI_IMG, 10, -17);
	lv_obj_set_size(ui->screen_FG_TRI_IMG, 108, 149);

	// Set style for screen_FG_TRI_IMG. Part: LV_IMG_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_FG_TRI_IMG_main_default;
	lv_style_reset(&style_screen_FG_TRI_IMG_main_default);
	lv_style_set_image_opa(&style_screen_FG_TRI_IMG_main_default, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_FG_TRI_IMG, LV_IMG_PART_MAIN, &style_screen_FG_TRI_IMG_main_default);

	// Widget: screen_Tri_Channel_2_btn
	ui->screen_Tri_Channel_2_btn = lv_btn_create(ui->screen_Function_Set_tab_3, NULL);
	lv_btn_set_checkable(ui->screen_Tri_Channel_2_btn, true);
	ui->screen_Tri_Channel_2_btn_label = lv_label_create(ui->screen_Tri_Channel_2_btn, NULL);
	lv_label_set_text(ui->screen_Tri_Channel_2_btn_label, "Channel 2");
	lv_label_set_align(ui->screen_Tri_Channel_2_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Channel_2_btn, 15, 131);
	lv_obj_set_size(ui->screen_Tri_Channel_2_btn, 89, 23);

	// Set style for screen_Tri_Channel_2_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Channel_2_btn_main_default;
	lv_style_reset(&style_screen_Tri_Channel_2_btn_main_default);
	lv_style_set_text_color(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xbf001d));
	lv_style_set_radius(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, 4);
	lv_style_set_shadow_width(&style_screen_Tri_Channel_2_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Channel_2_btn, LV_BTN_PART_MAIN, &style_screen_Tri_Channel_2_btn_main_default);

	// Set style for screen_Tri_Channel_2_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_PRESSED
	if (Btn_Sel.Tri_Channel_2)
	{
		static lv_style_t style_screen_Tri_Channel_2_btn_main_pressed;
		lv_style_reset(&style_screen_Tri_Channel_2_btn_main_pressed);
		lv_style_set_text_color(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x000000));
		lv_style_set_text_font(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, &lv_font_montserratMedium_12);
		lv_style_set_bg_opa(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_bg_color(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0xD0F6FF));
		lv_style_set_border_width(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 2);
		lv_style_set_border_opa(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_border_color(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x01a2b1));
		lv_style_set_radius(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 4);
		lv_style_set_shadow_width(&style_screen_Tri_Channel_2_btn_main_pressed, LV_STATE_PRESSED, 0);
		lv_obj_add_style(ui->screen_Tri_Channel_2_btn, LV_BTN_PART_MAIN, &style_screen_Tri_Channel_2_btn_main_pressed);
	}

	// Widget: screen_Tri_Channel_1_btn
	ui->screen_Tri_Channel_1_btn = lv_btn_create(ui->screen_Function_Set_tab_3, NULL);
	lv_btn_set_checkable(ui->screen_Tri_Channel_1_btn, true);
	ui->screen_Tri_Channel_1_btn_label = lv_label_create(ui->screen_Tri_Channel_1_btn, NULL);
	lv_label_set_text(ui->screen_Tri_Channel_1_btn_label, "Channel 1");
	lv_label_set_align(ui->screen_Tri_Channel_1_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Channel_1_btn, 15, 99);
	lv_obj_set_size(ui->screen_Tri_Channel_1_btn, 89, 23);

	// Set style for screen_Tri_Channel_1_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Channel_1_btn_main_default;
	lv_style_reset(&style_screen_Tri_Channel_1_btn_main_default);
	lv_style_set_text_color(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0xbf001d));
	lv_style_set_radius(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, 4);
	lv_style_set_shadow_width(&style_screen_Tri_Channel_1_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Channel_1_btn, LV_BTN_PART_MAIN, &style_screen_Tri_Channel_1_btn_main_default);

	// Set style for screen_Tri_Channel_1_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_PRESSED
	if (Btn_Sel.Tri_Channel_1)
	{
		static lv_style_t style_screen_Tri_Channel_1_btn_main_pressed;
		lv_style_reset(&style_screen_Tri_Channel_1_btn_main_pressed);
		lv_style_set_text_color(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x000000));
		lv_style_set_text_font(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, &lv_font_montserratMedium_12);
		lv_style_set_bg_opa(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_bg_color(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0xD0F6FF));
		lv_style_set_border_width(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 2);
		lv_style_set_border_opa(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 255);
		lv_style_set_border_color(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, lv_color_hex(0x01a2b1));
		lv_style_set_radius(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 4);
		lv_style_set_shadow_width(&style_screen_Tri_Channel_1_btn_main_pressed, LV_STATE_PRESSED, 0);
		lv_obj_add_style(ui->screen_Tri_Channel_1_btn, LV_BTN_PART_MAIN, &style_screen_Tri_Channel_1_btn_main_pressed);
	}
	// Widget: screen_Tri_Pword_Slider
	ui->screen_Tri_Pword_Slider = lv_slider_create(ui->screen_Function_Set_tab_3, NULL);
	lv_slider_set_range(ui->screen_Tri_Pword_Slider, 0, 360);
	lv_slider_set_value(ui->screen_Tri_Pword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Tri_Pword_Slider, 151, 151);
	lv_obj_set_size(ui->screen_Tri_Pword_Slider, 168, 5);

	// Set style for screen_Tri_Pword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Pword_Slider_bg_default;
	lv_style_reset(&style_screen_Tri_Pword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Tri_Pword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Pword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Tri_Pword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Tri_Pword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Pword_Slider, LV_SLIDER_PART_BG, &style_screen_Tri_Pword_Slider_bg_default);

	// Set style for screen_Tri_Pword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Pword_Slider_indic_default;
	lv_style_reset(&style_screen_Tri_Pword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Tri_Pword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Pword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Tri_Pword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Tri_Pword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Tri_Pword_Slider_indic_default);

	// Set style for screen_Tri_Pword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Pword_Slider_knob_default;
	lv_style_reset(&style_screen_Tri_Pword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Tri_Pword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Pword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Tri_Pword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Tri_Pword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Tri_Pword_Slider_knob_default);

	// Widget: screen_Tri_Fword_Slider
	ui->screen_Tri_Fword_Slider = lv_slider_create(ui->screen_Function_Set_tab_3, NULL);
	lv_slider_set_range(ui->screen_Tri_Fword_Slider, 0, 1000);
	lv_slider_set_value(ui->screen_Tri_Fword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Tri_Fword_Slider, 151, 91);
	lv_obj_set_size(ui->screen_Tri_Fword_Slider, 168, 5);

	// Set style for screen_Tri_Fword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Fword_Slider_bg_default;
	lv_style_reset(&style_screen_Tri_Fword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Tri_Fword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Fword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Tri_Fword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Tri_Fword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Fword_Slider, LV_SLIDER_PART_BG, &style_screen_Tri_Fword_Slider_bg_default);

	// Set style for screen_Tri_Fword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Fword_Slider_indic_default;
	lv_style_reset(&style_screen_Tri_Fword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Tri_Fword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Fword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Tri_Fword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Tri_Fword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Tri_Fword_Slider_indic_default);

	// Set style for screen_Tri_Fword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Fword_Slider_knob_default;
	lv_style_reset(&style_screen_Tri_Fword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Tri_Fword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Fword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Tri_Fword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Tri_Fword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Tri_Fword_Slider_knob_default);

	// Widget: screen_Tri_Aword_Slider
	ui->screen_Tri_Aword_Slider = lv_slider_create(ui->screen_Function_Set_tab_3, NULL);
	lv_slider_set_range(ui->screen_Tri_Aword_Slider, 0, 10000);
	lv_slider_set_value(ui->screen_Tri_Aword_Slider, 50, false);
	lv_obj_set_pos(ui->screen_Tri_Aword_Slider, 151, 31);
	lv_obj_set_size(ui->screen_Tri_Aword_Slider, 168, 5);

	// Set style for screen_Tri_Aword_Slider. Part: LV_SLIDER_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Aword_Slider_bg_default;
	lv_style_reset(&style_screen_Tri_Aword_Slider_bg_default);
	lv_style_set_bg_opa(&style_screen_Tri_Aword_Slider_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Aword_Slider_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_Tri_Aword_Slider_bg_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_Tri_Aword_Slider_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Aword_Slider, LV_SLIDER_PART_BG, &style_screen_Tri_Aword_Slider_bg_default);

	// Set style for screen_Tri_Aword_Slider. Part: LV_SLIDER_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Aword_Slider_indic_default;
	lv_style_reset(&style_screen_Tri_Aword_Slider_indic_default);
	lv_style_set_bg_opa(&style_screen_Tri_Aword_Slider_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Aword_Slider_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x49000b));
	lv_style_set_radius(&style_screen_Tri_Aword_Slider_indic_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Tri_Aword_Slider, LV_SLIDER_PART_INDIC, &style_screen_Tri_Aword_Slider_indic_default);

	// Set style for screen_Tri_Aword_Slider. Part: LV_SLIDER_PART_KNOB, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Aword_Slider_knob_default;
	lv_style_reset(&style_screen_Tri_Aword_Slider_knob_default);
	lv_style_set_bg_opa(&style_screen_Tri_Aword_Slider_knob_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_Tri_Aword_Slider_knob_default, LV_STATE_DEFAULT, lv_color_hex(0xd30020));
	lv_style_set_radius(&style_screen_Tri_Aword_Slider_knob_default, LV_STATE_DEFAULT, 50);
	lv_obj_add_style(ui->screen_Tri_Aword_Slider, LV_SLIDER_PART_KNOB, &style_screen_Tri_Aword_Slider_knob_default);

	// Widget: screen_Tri_Fword_Label
	ui->screen_Tri_Fword_Label = lv_label_create(ui->screen_Function_Set_tab_3, NULL);
	lv_label_set_text(ui->screen_Tri_Fword_Label, "Freq :");
	lv_label_set_align(ui->screen_Tri_Fword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Fword_Label, 150, 70);
	lv_obj_set_width(ui->screen_Tri_Fword_Label, 100);

	// Set style for screen_Tri_Fword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Fword_Label_main_default;
	lv_style_reset(&style_screen_Tri_Fword_Label_main_default);
	lv_style_set_radius(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Tri_Fword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Fword_Label, LV_LABEL_PART_MAIN, &style_screen_Tri_Fword_Label_main_default);

	// Widget: screen_Tri_Pword_Label
	ui->screen_Tri_Pword_Label = lv_label_create(ui->screen_Function_Set_tab_3, NULL);
	lv_label_set_text(ui->screen_Tri_Pword_Label, "Phas :");
	lv_label_set_align(ui->screen_Tri_Pword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Pword_Label, 150, 130);
	lv_obj_set_width(ui->screen_Tri_Pword_Label, 100);

	// Set style for screen_Tri_Pword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Pword_Label_main_default;
	lv_style_reset(&style_screen_Tri_Pword_Label_main_default);
	lv_style_set_radius(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Tri_Pword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Pword_Label, LV_LABEL_PART_MAIN, &style_screen_Tri_Pword_Label_main_default);

	// Widget: screen_Tri_Aword_Label
	ui->screen_Tri_Aword_Label = lv_label_create(ui->screen_Function_Set_tab_3, NULL);
	lv_label_set_text(ui->screen_Tri_Aword_Label, "Ampl :");
	lv_label_set_align(ui->screen_Tri_Aword_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Aword_Label, 150, 10);
	lv_obj_set_width(ui->screen_Tri_Aword_Label, 100);

	// Set style for screen_Tri_Aword_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Aword_Label_main_default;
	lv_style_reset(&style_screen_Tri_Aword_Label_main_default);
	lv_style_set_radius(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Tri_Aword_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Aword_Label, LV_LABEL_PART_MAIN, &style_screen_Tri_Aword_Label_main_default);

	// Widget: screen_Tri_MV_unit
	ui->screen_Tri_MV_unit = lv_label_create(ui->screen_Function_Set_tab_3, NULL);
	lv_label_set_text(ui->screen_Tri_MV_unit, "mV");
	lv_label_set_align(ui->screen_Tri_MV_unit, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_MV_unit, 267, 10);
	lv_obj_set_width(ui->screen_Tri_MV_unit, 32);

	// Set style for screen_Tri_MV_unit. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_MV_unit_main_default;
	lv_style_reset(&style_screen_Tri_MV_unit_main_default);
	lv_style_set_radius(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Tri_MV_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_MV_unit, LV_LABEL_PART_MAIN, &style_screen_Tri_MV_unit_main_default);

	// Widget: screen_Tri_Degree_unit
	ui->screen_Tri_Degree_unit = lv_label_create(ui->screen_Function_Set_tab_3, NULL);
	lv_label_set_text(ui->screen_Tri_Degree_unit, "degree");
	lv_label_set_align(ui->screen_Tri_Degree_unit, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Degree_unit, 261, 130);
	lv_obj_set_width(ui->screen_Tri_Degree_unit, 56);

	// Set style for screen_Tri_Degree_unit. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Degree_unit_main_default;
	lv_style_reset(&style_screen_Tri_Degree_unit_main_default);
	lv_style_set_radius(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Tri_Degree_unit_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Degree_unit, LV_LABEL_PART_MAIN, &style_screen_Tri_Degree_unit_main_default);

	// Widget: screen_Tri_Hz_btn
	ui->screen_Tri_Hz_btn = lv_btn_create(ui->screen_Function_Set_tab_3, NULL);
	ui->screen_Tri_Hz_btn_label = lv_label_create(ui->screen_Tri_Hz_btn, NULL);
	lv_label_set_text(ui->screen_Tri_Hz_btn_label, "Hz");
	lv_label_set_align(ui->screen_Tri_Hz_btn_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Tri_Hz_btn, 260, 65);
	lv_obj_set_size(ui->screen_Tri_Hz_btn, 49, 23);

	// Set style for screen_Tri_Hz_btn. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Tri_Hz_btn_main_default;
	lv_style_reset(&style_screen_Tri_Hz_btn_main_default);
	lv_style_set_text_color(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_width(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_shadow_width(&style_screen_Tri_Hz_btn_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Tri_Hz_btn, LV_BTN_PART_MAIN, &style_screen_Tri_Hz_btn_main_default);

	// Tab: screen_Function_Set_tab_4 with title "Cus"
	ui->screen_Function_Set_tab_4 = lv_tabview_add_tab(ui->screen_Function_Set, "Cus");
	lv_obj_t *screen_Function_Set_tab_4_label = lv_label_create(ui->screen_Function_Set_tab_4, NULL);
	lv_label_set_text(screen_Function_Set_tab_4_label, "");

	// Widget: screen_Cus_Line
	ui->screen_Cus_Line = lv_line_create(ui->screen_Function_Set_tab_4, NULL);
	static lv_point_t screen_Cus_Line[] = {
		{0, 100},
		{10, 100},
		{70, 100},
		{130, 100},
		{190, 100},
		{250, 100},
		{310, 100},
		{320, 100},
	};
	lv_line_set_points(ui->screen_Cus_Line, screen_Cus_Line, 8);
	lv_obj_set_pos(ui->screen_Cus_Line, 0, 0);
	lv_obj_set_size(ui->screen_Cus_Line, 320, 180);

	// Set style for screen_Cus_Line. Part: LV_LINE_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Cus_Line_main_default;
	lv_style_reset(&style_screen_Cus_Line_main_default);
	lv_style_set_line_color(&style_screen_Cus_Line_main_default, LV_STATE_DEFAULT, lv_color_hex(0xd20020));
	lv_style_set_line_rounded(&style_screen_Cus_Line_main_default, LV_STATE_DEFAULT, true);
	lv_style_set_line_width(&style_screen_Cus_Line_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_screen_Cus_Line_main_default, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_Cus_Line, LV_LINE_PART_MAIN, &style_screen_Cus_Line_main_default);

	// Widget: screen_Cus_Label
	ui->screen_Cus_Label = lv_label_create(ui->screen_Function_Set_tab_4, NULL);
	lv_label_set_text(ui->screen_Cus_Label, "please draw the line here");
	lv_label_set_align(ui->screen_Cus_Label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Cus_Label, 24, 1);
	lv_obj_set_width(ui->screen_Cus_Label, 300);

	// Set style for screen_Cus_Label. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Cus_Label_main_default;
	lv_style_reset(&style_screen_Cus_Label_main_default);
	lv_style_set_radius(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Cus_Label_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Cus_Label, LV_LABEL_PART_MAIN, &style_screen_Cus_Label_main_default);

	// Widget: screen_Coordinate_RetrievalX
	ui->screen_Coordinate_RetrievalX = lv_label_create(ui->screen_Function_Set_tab_4, NULL);
	lv_label_set_text(ui->screen_Coordinate_RetrievalX, "T/1000 :");
	lv_label_set_align(ui->screen_Coordinate_RetrievalX, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Coordinate_RetrievalX, 10, 20);
	lv_obj_set_width(ui->screen_Coordinate_RetrievalX, 100);

	// Set style for screen_Coordinate_RetrievalX. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Coordinate_RetrievalX_main_default;
	lv_style_reset(&style_screen_Coordinate_RetrievalX_main_default);
	lv_style_set_radius(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Coordinate_RetrievalX_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Coordinate_RetrievalX, LV_LABEL_PART_MAIN, &style_screen_Coordinate_RetrievalX_main_default);

	// Widget: screen_Coordinate_RetrievalY
	ui->screen_Coordinate_RetrievalY = lv_label_create(ui->screen_Function_Set_tab_4, NULL);
	lv_label_set_text(ui->screen_Coordinate_RetrievalY, "mV :");
	lv_label_set_align(ui->screen_Coordinate_RetrievalY, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_Coordinate_RetrievalY, 10, 40);
	lv_obj_set_width(ui->screen_Coordinate_RetrievalY, 100);

	// Set style for screen_Coordinate_RetrievalY. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_Coordinate_RetrievalY_main_default;
	lv_style_reset(&style_screen_Coordinate_RetrievalY_main_default);
	lv_style_set_radius(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_Coordinate_RetrievalY_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_Coordinate_RetrievalY, LV_LABEL_PART_MAIN, &style_screen_Coordinate_RetrievalY_main_default);

	// Init events for screen.
	events_init_screen(ui);
}
