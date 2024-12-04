/*
 * Copyright 2024 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl/lvgl.h"

	typedef struct
	{

		lv_obj_t *screen;
		bool screen_del;
		lv_obj_t *g_kb_screen;
		lv_obj_t *screen_Function_Set;
		lv_obj_t *screen_Function_Set_tab_1;
		lv_obj_t *screen_Function_Set_tab_2;
		lv_obj_t *screen_Function_Set_tab_3;
		lv_obj_t *screen_Function_Set_tab_4;
		lv_obj_t *screen_Function_Set_tab_5;
		lv_obj_t *screen_FG_SIN_IMG;
		lv_obj_t *screen_Sin_Channel_2_btn;
		lv_obj_t *screen_Sin_Channel_2_btn_label;
		lv_obj_t *screen_Sin_Channel_1_btn;
		lv_obj_t *screen_Sin_Channel_1_btn_label;
		lv_obj_t *screen_Sin_Pword_Slider;
		lv_obj_t *screen_Sin_Fword_Slider;
		lv_obj_t *screen_Sin_Aword_Slider;
		lv_obj_t *screen_Sin_Aword_Label;
		lv_obj_t *screen_Sin_Fword_Label;
		lv_obj_t *screen_Sin_Pword_Label;
		lv_obj_t *screen_Sin_MV_unit;
		lv_obj_t *screen_Sin_Degree_unit;
		lv_obj_t *screen_Sin_Hz_btn;
		lv_obj_t *screen_Sin_Hz_btn_label;
		lv_obj_t *screen_FG_SQU_IMG;
		lv_obj_t *screen_Squ_Channel_2_btn;
		lv_obj_t *screen_Squ_Channel_2_btn_label;
		lv_obj_t *screen_Squ_Channel_1_btn;
		lv_obj_t *screen_Squ_Channel_1_btn_label;
		lv_obj_t *screen_Squ_Pword_Slider;
		lv_obj_t *screen_Squ_Fword_Slider;
		lv_obj_t *screen_Squ_Aword_Slider;
		lv_obj_t *screen_Squ_Pword_Label;
		lv_obj_t *screen_Squ_Fword_Label;
		lv_obj_t *screen_Squ_Aword_Label;
		lv_obj_t *screen_Squ_Degree_unit;
		lv_obj_t *screen_Squ_MV_unit;
		lv_obj_t *screen_Squ_Hz_btn;
		lv_obj_t *screen_Squ_Hz_btn_label;
		lv_obj_t *screen_FG_TRI_IMG;
		lv_obj_t *screen_Tri_Channel_2_btn;
		lv_obj_t *screen_Tri_Channel_2_btn_label;
		lv_obj_t *screen_Tri_Channel_1_btn;
		lv_obj_t *screen_Tri_Channel_1_btn_label;
		lv_obj_t *screen_Tri_Pword_Slider;
		lv_obj_t *screen_Tri_Fword_Slider;
		lv_obj_t *screen_Tri_Aword_Slider;
		lv_obj_t *screen_Tri_Fword_Label;
		lv_obj_t *screen_Tri_Pword_Label;
		lv_obj_t *screen_Tri_Aword_Label;
		lv_obj_t *screen_Tri_MV_unit;
		lv_obj_t *screen_Tri_Degree_unit;
		lv_obj_t *screen_Tri_Hz_btn;
		lv_obj_t *screen_Tri_Hz_btn_label;
		lv_obj_t *screen_FG_CUS_IMG;
		lv_obj_t *screen_Cus_Channel_1_btn;
		lv_obj_t *screen_Cus_Channel_1_btn_label;
		lv_obj_t *screen_Cus_Channel_2_btn;
		lv_obj_t *screen_Cus_Channel_2_btn_label;
		lv_obj_t *screen_Cus_Pword_Slider;
		lv_obj_t *screen_Cus_Fword_Slider;
		lv_obj_t *screen_Cus_Aword_Slider;
		lv_obj_t *screen_Cus_Fword_Label;
		lv_obj_t *screen_Cus_Pword_Label;
		lv_obj_t *screen_Cus_Aword_Label;
		lv_obj_t *screen_Cus_MV_unit;
		lv_obj_t *screen_Cus_Degree_unit;
		lv_obj_t *screen_Cus_Hz_btn;
		lv_obj_t *screen_Cus_Hz_btn_label;
		lv_obj_t *screen_Cus_Line;
		lv_obj_t *screen_Cus_Label;
		lv_obj_t *screen_Coordinate_RetrievalX;
		lv_obj_t *screen_Coordinate_RetrievalY;
	} lv_ui;

	void init_scr_del_flag(lv_ui *ui);
	void setup_ui(lv_ui *ui);
	extern lv_ui guider_ui;

	void setup_scr_screen(lv_ui *ui);
	LV_IMG_DECLARE(_FG_SIN_alpha_102x119);
	LV_IMG_DECLARE(_FG_SQU_alpha_110x139);
	LV_IMG_DECLARE(_FG_TRI_alpha_108x149);
	LV_IMG_DECLARE(_FG_CUS_alpha_108x149);

	LV_FONT_DECLARE(lv_font_montserratMedium_15)
	LV_FONT_DECLARE(lv_font_montserratMedium_24)
	LV_FONT_DECLARE(lv_font_montserratMedium_12)

#ifdef __cplusplus
}
#endif
#endif
