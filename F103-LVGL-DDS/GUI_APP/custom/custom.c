// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include "lvgl.h"
#include "custom.h"
// #include "customUSART.h"

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    UNIT_HZ,
    UNIT_KHZ,
    UNIT_MHZ,
} unit_hz_t;
/*********************
 *      DEFINES
 *********************/

static unit_hz_t current_Sin = UNIT_HZ;
static unit_hz_t current_Squ = UNIT_HZ;
static unit_hz_t current_Tri = UNIT_HZ;

static lv_point_t screen_Cus_Line_buf[] = {
    {0, 100},
    {10, 100},
    {70, 100},
    {130, 100},
    {190, 100},
    {250, 100},
    {310, 100},
    {320, 100},
};

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

// Create a demo application
void Set_State()
{
    if (Btn_Sel.Sin_Channel_1 == 0)
        lv_btn_set_state(guider_ui.screen_Sin_Channel_1_btn, LV_STATE_DEFAULT);
    if (Btn_Sel.Sin_Channel_2 == 0)
        lv_btn_set_state(guider_ui.screen_Sin_Channel_2_btn, LV_STATE_DEFAULT);
    if (Btn_Sel.Squ_Channel_1 == 0)
        lv_btn_set_state(guider_ui.screen_Squ_Channel_1_btn, LV_STATE_DEFAULT);
    if (Btn_Sel.Squ_Channel_2 == 0)
        lv_btn_set_state(guider_ui.screen_Squ_Channel_2_btn, LV_STATE_DEFAULT);
    if (Btn_Sel.Tri_Channel_1 == 0)
        lv_btn_set_state(guider_ui.screen_Tri_Channel_1_btn, LV_STATE_DEFAULT);
    if (Btn_Sel.Tri_Channel_2 == 0)
        lv_btn_set_state(guider_ui.screen_Tri_Channel_2_btn, LV_STATE_DEFAULT);
}

static void Sin_Channel_1_btn_event_handler(lv_obj_t *channel, lv_event_t event)
{
    if (event == LV_STATE_PRESSED)
    {
        Btn_Sel.Sin_Channel_1 = ~Btn_Sel.Sin_Channel_1;
        if (Btn_Sel.Sin_Channel_1)
        {
            Btn_Sel.Squ_Channel_1 = 0;
            Btn_Sel.Tri_Channel_1 = 0;
        }
        Set_State();
    }
}
static void Sin_Channel_2_btn_event_handler(lv_obj_t *channel, lv_event_t event)
{
    if (event == LV_STATE_PRESSED)
    {
        Btn_Sel.Sin_Channel_2 = ~Btn_Sel.Sin_Channel_2;
        if (Btn_Sel.Sin_Channel_2)
        {
            Btn_Sel.Squ_Channel_2 = 0;
            Btn_Sel.Tri_Channel_2 = 0;
        }
        Set_State();
    }
}
static void Squ_Channel_1_btn_event_handler(lv_obj_t *channel, lv_event_t event)
{
    if (event == LV_STATE_PRESSED)
    {
        Btn_Sel.Squ_Channel_1 = ~Btn_Sel.Squ_Channel_1;
        if (Btn_Sel.Squ_Channel_1)
        {
            Btn_Sel.Sin_Channel_1 = 0;
            Btn_Sel.Tri_Channel_1 = 0;
        }
        Set_State();
    }
}
static void Squ_Channel_2_btn_event_handler(lv_obj_t *channel, lv_event_t event)
{
    if (event == LV_STATE_PRESSED)
    {
        Btn_Sel.Squ_Channel_2 = ~Btn_Sel.Squ_Channel_2;
        if (Btn_Sel.Squ_Channel_2)
        {
            Btn_Sel.Sin_Channel_2 = 0;
            Btn_Sel.Tri_Channel_2 = 0;
        }
        Set_State();
    }
}
static void Tri_Channel_1_btn_event_handler(lv_obj_t *channel, lv_event_t event)
{
    if (event == LV_STATE_PRESSED)
    {
        Btn_Sel.Tri_Channel_1 = ~Btn_Sel.Tri_Channel_1;
        if (Btn_Sel.Tri_Channel_1)
        {
            Btn_Sel.Sin_Channel_1 = 0;
            Btn_Sel.Squ_Channel_1 = 0;
        }
        Set_State();
    }
}
static void Tri_Channel_2_btn_event_handler(lv_obj_t *channel, lv_event_t event)
{
    if (event == LV_STATE_PRESSED)
    {
        Btn_Sel.Tri_Channel_2 = ~Btn_Sel.Tri_Channel_2;
        if (Btn_Sel.Tri_Channel_2)
        {
            Btn_Sel.Sin_Channel_2 = 0;
            Btn_Sel.Squ_Channel_2 = 0;
        }
        Set_State();
    }
}

static void Sin_Aword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{
    int16_t value = lv_slider_get_value(guider_ui.screen_Sin_Aword_Slider);

    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Sin_Aword_Label, "Ampl : %d", (value - 5000));
        // guider_user.pointer_Sin_Aword_Slider->value = value - 5000;
        // guider_user.pointer_Sin_Aword_Slider->State = CHANGE;
    }
}

static void Sin_Fword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Sin_Fword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Sin_Fword_Label, "Freq : %d", value);
    }
}

static void Sin_Pword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Sin_Pword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Sin_Pword_Label, "Phas : %d", value);
    }
}

static void Squ_Aword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Squ_Aword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Squ_Aword_Label, "Ampl : %d", (value - 5000));
    }
}

static void Squ_Fword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Squ_Fword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Squ_Fword_Label, "Freq : %d", value);
    }
}

static void Squ_Pword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Squ_Pword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Squ_Pword_Label, "Phas : %d", value);
    }
}

static void Tri_Aword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Tri_Aword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Tri_Aword_Label, "Ampl : %d", (value - 5000));
    }
}

static void Tri_Fword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Tri_Fword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Tri_Fword_Label, "Freq : %d", value);
    }
}

static void Tri_Pword_Slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    int16_t value = lv_slider_get_value(guider_ui.screen_Tri_Pword_Slider);
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(guider_ui.screen_Tri_Pword_Label, "Phas : %d", value);
    }
}

static void Sin_Hz_btn_event_handler(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED)
    {
        switch (current_Sin)
        {
        case UNIT_HZ:
            current_Sin = UNIT_KHZ;
            lv_label_set_text(guider_ui.screen_Sin_Hz_btn_label, "KHz");
            break;
        case UNIT_KHZ:
            current_Sin = UNIT_MHZ;
            lv_label_set_text(guider_ui.screen_Sin_Hz_btn_label, "MHz");
            break;
        case UNIT_MHZ:
            current_Sin = UNIT_HZ;
            lv_label_set_text(guider_ui.screen_Sin_Hz_btn_label, "Hz");
            break;
        }
    }
}
static void Squ_Hz_btn_event_handler(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED)
    {
        switch (current_Squ)
        {
        case UNIT_HZ:
            current_Squ = UNIT_KHZ;
            lv_label_set_text(guider_ui.screen_Squ_Hz_btn_label, "KHz");
            break;
        case UNIT_KHZ:
            current_Squ = UNIT_MHZ;
            lv_label_set_text(guider_ui.screen_Squ_Hz_btn_label, "MHz");
            break;
        case UNIT_MHZ:
            current_Squ = UNIT_HZ;
            lv_label_set_text(guider_ui.screen_Squ_Hz_btn_label, "Hz");
            break;
        }
    }
}

static void Tri_Hz_btn_event_handler(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED)
    {
        switch (current_Tri)
        {
        case UNIT_HZ:
            current_Tri = UNIT_KHZ;
            lv_label_set_text(guider_ui.screen_Tri_Hz_btn_label, "KHz");
            break;
        case UNIT_KHZ:
            current_Tri = UNIT_MHZ;
            lv_label_set_text(guider_ui.screen_Tri_Hz_btn_label, "MHz");
            break;
        case UNIT_MHZ:
            current_Tri = UNIT_HZ;
            lv_label_set_text(guider_ui.screen_Tri_Hz_btn_label, "Hz");
            break;
        }
    }
}

/* -------------------------------------------------------------------------- */
int16_t find_min_index(int16_t numbers[8])
{
    // Initialize min value and index
    int16_t min_value = numbers[0];
    int16_t min_index = 0;
    // Find the smallest number and its index
    for (uint8_t i = 1; i < 8; ++i)
    {
        if (numbers[i] < min_value)
        {
            min_value = numbers[i];
            min_index = i;
        }
    }

    return min_index;
}

static void scroll_event_cb(lv_obj_t *obj, lv_event_t event)
{

    lv_indev_t *indev = lv_indev_get_act(); // 获取输入设备
    if (indev == NULL)
    {
        return;
    }
    lv_point_t lv_point;
    lv_indev_get_point(indev, &lv_point);
    // 显示X,Y坐标
    // printf("[%s]  lv_point.x = %d  lv_point.y = %d \n", __func__, lv_point.x, lv_point.y);
    uint16_t screen_height = lv_disp_get_ver_res(NULL);
    uint16_t screen_width = lv_disp_get_hor_res(NULL);

    int16_t diff[] = {0, 0, 0, 0, 0, 0, 0, 0};

    diff[0] = abs(lv_point.x - screen_Cus_Line_buf[0].x);
    diff[1] = abs(lv_point.x - screen_Cus_Line_buf[1].x);
    diff[2] = abs(lv_point.x - screen_Cus_Line_buf[2].x);
    diff[3] = abs(lv_point.x - screen_Cus_Line_buf[3].x);
    diff[4] = abs(lv_point.x - screen_Cus_Line_buf[4].x);
    diff[5] = abs(lv_point.x - screen_Cus_Line_buf[5].x);
    diff[6] = abs(lv_point.x - screen_Cus_Line_buf[6].x);
    diff[7] = abs(lv_point.x - screen_Cus_Line_buf[7].x);

    int16_t min_index = find_min_index(diff);

    if (min_index == 7)
        min_index = 6;
    else if (min_index == 0)
        min_index = 1;
    else
        min_index = min_index;

    _Bool flag = 1;
    if (lv_point.y < 60)
    {
        lv_point.y = 60;
        flag = 0;
    }
    else
        flag = 1;

    if (flag)
    {
        int16_t T = lv_point.x * 1000 / screen_height;
        int16_t mV = (screen_height / 2 - lv_point.y + 33) * 9000 / (screen_height - 60);

        lv_label_set_text_fmt(guider_ui.screen_Coordinate_RetrievalX, "T/1000 : %d", T);
        lv_label_set_text_fmt(guider_ui.screen_Coordinate_RetrievalY, "mV : %d", mV);

        screen_Cus_Line_buf[min_index].x = lv_point.x;
        screen_Cus_Line_buf[min_index].y = lv_point.y - (screen_height - lv_obj_get_height(obj));

        lv_line_set_points(guider_ui.screen_Cus_Line, screen_Cus_Line_buf, 8);
    }
}

/* -------------------------------------------------------------------------- */

void custom_init(lv_ui *ui)
{
    // customUSART_init(ui, guider_user);
    // /*tab handler*/
    // lv_obj_set_event_cb(ui->screen_Function_Set_tab_1, Sin_event_handler);
    // lv_obj_set_event_cb(ui->screen_Function_Set_tab_2, Squ_event_handler);
    // lv_obj_set_event_cb(ui->screen_Function_Set_tab_3, Tri_event_handler);
    // lv_obj_set_event_cb(ui->screen_Function_Set_tab_4, Tri_event_handler);
    /*channel handler*/
    lv_obj_set_event_cb(ui->screen_Sin_Channel_1_btn, Sin_Channel_1_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Sin_Channel_2_btn, Sin_Channel_2_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Squ_Channel_1_btn, Squ_Channel_1_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Squ_Channel_2_btn, Squ_Channel_2_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Tri_Channel_1_btn, Tri_Channel_1_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Tri_Channel_2_btn, Tri_Channel_2_btn_event_handler);
    /*btn handler*/
    lv_obj_set_event_cb(ui->screen_Sin_Hz_btn, Sin_Hz_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Squ_Hz_btn, Squ_Hz_btn_event_handler);
    lv_obj_set_event_cb(ui->screen_Tri_Hz_btn, Tri_Hz_btn_event_handler);
    /* slider handler */
    lv_obj_set_event_cb(ui->screen_Sin_Aword_Slider, Sin_Aword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Sin_Fword_Slider, Sin_Fword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Sin_Pword_Slider, Sin_Pword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Squ_Aword_Slider, Squ_Aword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Squ_Fword_Slider, Squ_Fword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Squ_Pword_Slider, Squ_Pword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Tri_Aword_Slider, Tri_Aword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Tri_Fword_Slider, Tri_Fword_Slider_event_handler);
    lv_obj_set_event_cb(ui->screen_Tri_Pword_Slider, Tri_Pword_Slider_event_handler);
    /* line handler */
    lv_obj_set_event_cb(ui->screen_Function_Set_tab_4, scroll_event_cb);
}
