#include <stdlib.h>
#include "lvgl.h"
#include <math.h>
#include "customUSART.h"

/*********************
 *      DEFINES
 *********************/

static struct
{
    bool Sin_Channel1;
    bool Sin_Channel2;
    bool Squ_Channel1;
    bool Squ_Channel2;
    bool Tri_Channel1;
    bool Tri_Channel2;
    bool Cus_Channel1;
    bool Cus_Channel2;
    uint32_t Channel1_Freq;
    uint32_t Channel1_Phas;
    uint16_t Channel1_Ampl;
    uint32_t Channel1_Freq_Unit;
    uint32_t Channel2_Freq;
    uint32_t Channel2_Phas;
    uint16_t Channel2_Ampl;
    uint32_t Channel2_Freq_Unit;
    uint16_t Cus_LineX[8];
    uint16_t Cus_LineY[8];
} Wave_Data_Buffer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0};

// struct init
lv_user_pointer_t guider_user = {
    .pointer_Function_Set_tab_1 = &user_data_Function_Set_tab_1,
    .pointer_Function_Set_tab_2 = &user_data_Function_Set_tab_2,
    .pointer_Function_Set_tab_3 = &user_data_Function_Set_tab_3,
    .pointer_Function_Set_tab_4 = &user_data_Function_Set_tab_4,
    .pointer_Function_Set_tab_5 = &user_data_Function_Set_tab_5,
    .pointer_Sin_Channel_2_btn = &user_data_Sin_Channel_2_btn,
    .pointer_Sin_Channel_1_btn = &user_data_Sin_Channel_1_btn,
    .pointer_Sin_Pword_Slider = &user_data_Sin_Pword_Slider,
    .pointer_Sin_Fword_Slider = &user_data_Sin_Fword_Slider,
    .pointer_Sin_Aword_Slider = &user_data_Sin_Aword_Slider,
    .pointer_Sin_Hz_btn = &user_data_Sin_Hz_btn,
    .pointer_Squ_Channel_2_btn = &user_data_Squ_Channel_2_btn,
    .pointer_Squ_Channel_1_btn = &user_data_Squ_Channel_1_btn,
    .pointer_Squ_Pword_Slider = &user_data_Squ_Pword_Slider,
    .pointer_Squ_Fword_Slider = &user_data_Squ_Fword_Slider,
    .pointer_Squ_Aword_Slider = &user_data_Squ_Aword_Slider,
    .pointer_Squ_Hz_btn = &user_data_Squ_Hz_btn,
    .pointer_Tri_Channel_2_btn = &user_data_Tri_Channel_2_btn,
    .pointer_Tri_Channel_1_btn = &user_data_Tri_Channel_1_btn,
    .pointer_Tri_Pword_Slider = &user_data_Tri_Pword_Slider,
    .pointer_Tri_Fword_Slider = &user_data_Tri_Fword_Slider,
    .pointer_Tri_Aword_Slider = &user_data_Tri_Aword_Slider,
    .pointer_Tri_Hz_btn = &user_data_Tri_Hz_btn,
    .pointer_Cus_Channel_2_btn = &user_data_Cus_Channel_2_btn,
    .pointer_Cus_Channel_1_btn = &user_data_Cus_Channel_1_btn,
    .pointer_Cus_Pword_Slider = &user_data_Cus_Pword_Slider,
    .pointer_Cus_Fword_Slider = &user_data_Cus_Fword_Slider,
    .pointer_Cus_Aword_Slider = &user_data_Cus_Aword_Slider,
    .pointer_Cus_Hz_btn = &user_data_Cus_Hz_btn,
    .pointer_Cus_Line = &user_data_Cus_Line,
};

extern lv_wave_data_t Wave_Data = {
    .Channel0_Freq = {0xaa, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel0_Phas = {0xaa, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel0_Ampl = {0xaa, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel1_Freq = {0xaa, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel1_Phas = {0xaa, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel1_Ampl = {0xaa, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x88},

    .Channel_line1 = {0xaa, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line2 = {0xaa, 0x03, 0x09, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line3 = {0xaa, 0x03, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line4 = {0xaa, 0x03, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line5 = {0xaa, 0x03, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line6 = {0xaa, 0x03, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line7 = {0xaa, 0x03, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x88},
    .Channel_line8 = {0xaa, 0x03, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x88},

    .Channel_Sel = {0xaa, 0x03, 0x06, 0x36, 0x00, 0x00, 0x00, 0x88},
    .Renew = {0xaa, 0x03, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x88},
};

void customUSART_init(lv_ui *ui, lv_user_pointer_t guider_user)
{
    // set user data
    lv_obj_set_user_data(ui->screen_Function_Set_tab_1, guider_user.pointer_Function_Set_tab_1);
    lv_obj_set_user_data(ui->screen_Function_Set_tab_2, guider_user.pointer_Function_Set_tab_2);
    lv_obj_set_user_data(ui->screen_Function_Set_tab_3, guider_user.pointer_Function_Set_tab_3);
    lv_obj_set_user_data(ui->screen_Function_Set_tab_4, guider_user.pointer_Function_Set_tab_4);
    lv_obj_set_user_data(ui->screen_Function_Set_tab_5, guider_user.pointer_Function_Set_tab_5);
    lv_obj_set_user_data(ui->screen_Sin_Channel_2_btn, guider_user.pointer_Sin_Channel_2_btn);
    lv_obj_set_user_data(ui->screen_Sin_Channel_1_btn, guider_user.pointer_Sin_Channel_1_btn);
    lv_obj_set_user_data(ui->screen_Sin_Pword_Slider, guider_user.pointer_Sin_Pword_Slider);
    lv_obj_set_user_data(ui->screen_Sin_Fword_Slider, guider_user.pointer_Sin_Fword_Slider);
    lv_obj_set_user_data(ui->screen_Sin_Aword_Slider, guider_user.pointer_Sin_Aword_Slider);
    lv_obj_set_user_data(ui->screen_Sin_Hz_btn, guider_user.pointer_Sin_Hz_btn);
    lv_obj_set_user_data(ui->screen_Squ_Channel_2_btn, guider_user.pointer_Squ_Channel_2_btn);
    lv_obj_set_user_data(ui->screen_Squ_Channel_1_btn, guider_user.pointer_Squ_Channel_1_btn);
    lv_obj_set_user_data(ui->screen_Squ_Fword_Slider, guider_user.pointer_Squ_Fword_Slider);
    lv_obj_set_user_data(ui->screen_Squ_Aword_Slider, guider_user.pointer_Squ_Aword_Slider);
    lv_obj_set_user_data(ui->screen_Squ_Pword_Slider, guider_user.pointer_Squ_Pword_Slider);
    lv_obj_set_user_data(ui->screen_Squ_Hz_btn, guider_user.pointer_Squ_Hz_btn);
    lv_obj_set_user_data(ui->screen_Tri_Channel_2_btn, guider_user.pointer_Tri_Channel_2_btn);
    lv_obj_set_user_data(ui->screen_Tri_Channel_1_btn, guider_user.pointer_Tri_Channel_1_btn);
    lv_obj_set_user_data(ui->screen_Tri_Pword_Slider, guider_user.pointer_Tri_Pword_Slider);
    lv_obj_set_user_data(ui->screen_Tri_Fword_Slider, guider_user.pointer_Tri_Fword_Slider);
    lv_obj_set_user_data(ui->screen_Tri_Aword_Slider, guider_user.pointer_Tri_Aword_Slider);
    lv_obj_set_user_data(ui->screen_Tri_Hz_btn, guider_user.pointer_Tri_Hz_btn);
    lv_obj_set_user_data(ui->screen_Cus_Channel_2_btn, guider_user.pointer_Cus_Channel_2_btn);
    lv_obj_set_user_data(ui->screen_Cus_Channel_1_btn, guider_user.pointer_Cus_Channel_1_btn);
    lv_obj_set_user_data(ui->screen_Cus_Pword_Slider, guider_user.pointer_Cus_Pword_Slider);
    lv_obj_set_user_data(ui->screen_Cus_Fword_Slider, guider_user.pointer_Cus_Fword_Slider);
    lv_obj_set_user_data(ui->screen_Cus_Aword_Slider, guider_user.pointer_Cus_Aword_Slider);
    lv_obj_set_user_data(ui->screen_Cus_Hz_btn, guider_user.pointer_Cus_Hz_btn);
    lv_obj_set_user_data(ui->screen_Cus_Line, guider_user.pointer_Cus_Line);
}

void customUSART_write(lv_obj_t *obj)
{
    lv_obj_user_data_t data0 = lv_obj_get_user_data(obj);
    lv_user_data_t *data = data0;

    switch (data->tag)
    {

    case tag_Sin_Channel_2_btn:
        Wave_Data_Buffer.Sin_Channel2 = ((data->State) == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Sin_Channel2)
        {
            Wave_Data_Buffer.Squ_Channel2 = 0;
            Wave_Data_Buffer.Tri_Channel2 = 0;
            Wave_Data_Buffer.Cus_Channel2 = 0;
        }
        break;

    case tag_Sin_Channel_1_btn:
        Wave_Data_Buffer.Sin_Channel1 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Sin_Channel1)
        {
            Wave_Data_Buffer.Squ_Channel1 = 0;
            Wave_Data_Buffer.Tri_Channel1 = 0;
            Wave_Data_Buffer.Cus_Channel2 = 0;
        }
        break;

    case tag_Squ_Channel_2_btn:
        Wave_Data_Buffer.Squ_Channel2 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Squ_Channel2)
        {
            Wave_Data_Buffer.Sin_Channel2 = 0;
            Wave_Data_Buffer.Tri_Channel2 = 0;
            Wave_Data_Buffer.Cus_Channel2 = 0;
        }
        break;

    case tag_Squ_Channel_1_btn:
        Wave_Data_Buffer.Squ_Channel1 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Squ_Channel1)
        {
            Wave_Data_Buffer.Sin_Channel1 = 0;
            Wave_Data_Buffer.Tri_Channel1 = 0;
            Wave_Data_Buffer.Cus_Channel2 = 0;
        }
        break;

    case tag_Tri_Channel_2_btn:
        Wave_Data_Buffer.Tri_Channel2 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Tri_Channel2)
        {
            Wave_Data_Buffer.Sin_Channel2 = 0;
            Wave_Data_Buffer.Squ_Channel2 = 0;
            Wave_Data_Buffer.Cus_Channel2 = 0;
        }
        break;
    case tag_Tri_Channel_1_btn:
        Wave_Data_Buffer.Tri_Channel1 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Tri_Channel1)
        {
            Wave_Data_Buffer.Sin_Channel1 = 0;
            Wave_Data_Buffer.Squ_Channel1 = 0;
            Wave_Data_Buffer.Cus_Channel2 = 0;
        }
        break;

    case tag_Cus_Channel_2_btn:
        Wave_Data_Buffer.Cus_Channel2 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Cus_Channel2)
        {
            Wave_Data_Buffer.Sin_Channel2 = 0;
            Wave_Data_Buffer.Squ_Channel2 = 0;
            Wave_Data_Buffer.Tri_Channel2 = 0;
        }
        break;
    case tag_Cus_Channel_1_btn:
        Wave_Data_Buffer.Cus_Channel1 = (data->State == ON) ? 1 : 0;
        if (Wave_Data_Buffer.Cus_Channel1)
        {
            Wave_Data_Buffer.Sin_Channel1 = 0;
            Wave_Data_Buffer.Squ_Channel1 = 0;
            Wave_Data_Buffer.Tri_Channel2 = 0;
        }
        break;

    case tag_Sin_Pword_Slider:
        if (Wave_Data_Buffer.Sin_Channel1)
            Wave_Data_Buffer.Channel1_Phas = data->value;
        if (Wave_Data_Buffer.Sin_Channel2)
            Wave_Data_Buffer.Channel2_Phas = data->value;
        break;

    case tag_Sin_Fword_Slider:
        if (Wave_Data_Buffer.Sin_Channel1)
            Wave_Data_Buffer.Channel1_Freq = data->value;
        if (Wave_Data_Buffer.Sin_Channel2)
            Wave_Data_Buffer.Channel2_Freq = data->value;
        break;

    case tag_Sin_Aword_Slider:
        if (Wave_Data_Buffer.Sin_Channel1)
            Wave_Data_Buffer.Channel1_Ampl = (data->value);
        if (Wave_Data_Buffer.Sin_Channel2)
            Wave_Data_Buffer.Channel2_Ampl = (data->value);
        break;

    case tag_Sin_Hz_btn:
        if (Wave_Data_Buffer.Sin_Channel1)
            Wave_Data_Buffer.Channel1_Freq_Unit = data->State;
        if (Wave_Data_Buffer.Sin_Channel2)
            Wave_Data_Buffer.Channel2_Freq_Unit = data->State;
        break;

    case tag_Squ_Pword_Slider:
        if (Wave_Data_Buffer.Squ_Channel1)
            Wave_Data_Buffer.Channel1_Phas = data->value;
        if (Wave_Data_Buffer.Squ_Channel2)
            Wave_Data_Buffer.Channel2_Phas = data->value;
        break;

    case tag_Squ_Fword_Slider:
        if (Wave_Data_Buffer.Squ_Channel1)
            Wave_Data_Buffer.Channel1_Freq = data->value;
        if (Wave_Data_Buffer.Squ_Channel2)
            Wave_Data_Buffer.Channel2_Freq = data->value;
        break;

    case tag_Squ_Aword_Slider:
        if (Wave_Data_Buffer.Squ_Channel1)
            Wave_Data_Buffer.Channel1_Ampl = (data->value);
        if (Wave_Data_Buffer.Squ_Channel2)
            Wave_Data_Buffer.Channel2_Ampl = (data->value);
        break;

    case tag_Squ_Hz_btn:
        if (Wave_Data_Buffer.Squ_Channel1)
            Wave_Data_Buffer.Channel1_Freq_Unit = (data->State);
        if (Wave_Data_Buffer.Squ_Channel2)
            Wave_Data_Buffer.Channel2_Freq_Unit = (data->State);
        break;

    case tag_Tri_Pword_Slider:
        if (Wave_Data_Buffer.Tri_Channel1)
            Wave_Data_Buffer.Channel1_Phas = (data->value);
        if (Wave_Data_Buffer.Tri_Channel2)
            Wave_Data_Buffer.Channel2_Phas = (data->value);
        break;

    case tag_Tri_Fword_Slider:
        if (Wave_Data_Buffer.Tri_Channel1)
            Wave_Data_Buffer.Channel1_Freq = (data->value);
        if (Wave_Data_Buffer.Tri_Channel2)
            Wave_Data_Buffer.Channel2_Freq = (data->value);
        break;

    case tag_Tri_Aword_Slider:
        if (Wave_Data_Buffer.Tri_Channel1)
            Wave_Data_Buffer.Channel1_Ampl = (data->value);
        if (Wave_Data_Buffer.Tri_Channel2)
            Wave_Data_Buffer.Channel2_Ampl = (data->value);
        break;

    case tag_Tri_Hz_btn:
        if (Wave_Data_Buffer.Tri_Channel1)
            Wave_Data_Buffer.Channel1_Freq_Unit = (data->State);
        if (Wave_Data_Buffer.Tri_Channel2)
            Wave_Data_Buffer.Channel2_Freq_Unit = (data->State);
        break;

    case tag_Cus_Pword_Slider:
        if (Wave_Data_Buffer.Cus_Channel1)
            Wave_Data_Buffer.Channel1_Phas = (data->value);
        if (Wave_Data_Buffer.Cus_Channel2)
            Wave_Data_Buffer.Channel2_Phas = (data->value);
        break;

    case tag_Cus_Fword_Slider:
        if (Wave_Data_Buffer.Cus_Channel1)
            Wave_Data_Buffer.Channel1_Freq = (data->value);
        if (Wave_Data_Buffer.Cus_Channel2)
            Wave_Data_Buffer.Channel2_Freq = (data->value);
        break;

    case tag_Cus_Aword_Slider:
        if (Wave_Data_Buffer.Cus_Channel1)
            Wave_Data_Buffer.Channel1_Ampl = (data->value);
        if (Wave_Data_Buffer.Cus_Channel2)
            Wave_Data_Buffer.Channel2_Ampl = (data->value);
        break;

    case tag_Cus_Hz_btn:
        if (Wave_Data_Buffer.Cus_Channel1)
            Wave_Data_Buffer.Channel1_Freq_Unit = (data->State);
        if (Wave_Data_Buffer.Cus_Channel2)
            Wave_Data_Buffer.Channel2_Freq_Unit = (data->State);
        break;

    case tag_Cus_Line:
        Wave_Data_Buffer.Cus_LineX[0] = data->point[0].x;
        Wave_Data_Buffer.Cus_LineY[0] = data->point[0].y;
        Wave_Data_Buffer.Cus_LineX[1] = data->point[1].x;
        Wave_Data_Buffer.Cus_LineY[1] = data->point[1].y;
        Wave_Data_Buffer.Cus_LineX[2] = data->point[2].x;
        Wave_Data_Buffer.Cus_LineY[2] = data->point[2].y;
        Wave_Data_Buffer.Cus_LineX[3] = data->point[3].x;
        Wave_Data_Buffer.Cus_LineY[3] = data->point[3].y;
        Wave_Data_Buffer.Cus_LineX[4] = data->point[4].x;
        Wave_Data_Buffer.Cus_LineY[4] = data->point[4].y;
        Wave_Data_Buffer.Cus_LineX[5] = data->point[5].x;
        Wave_Data_Buffer.Cus_LineY[5] = data->point[5].y;
        Wave_Data_Buffer.Cus_LineX[6] = data->point[6].x;
        Wave_Data_Buffer.Cus_LineY[6] = data->point[6].y;
        Wave_Data_Buffer.Cus_LineX[7] = data->point[7].x;
        Wave_Data_Buffer.Cus_LineY[7] = data->point[7].y;
        SEGGER_RTT_printf(0, "tag_Cus_Line_ACT\n");
        SEGGER_RTT_printf(0, "datapoint7X=%d\n", data->point[6].x);
        SEGGER_RTT_printf(0, "datapoint7y=%d\n", data->point[6].y);
    default:
        break;
    }
    // Debug

    SEGGER_RTT_printf(0, "State=%d\n", data->State);
    SEGGER_RTT_printf(0, "value=%d\n", data->value);
    SEGGER_RTT_printf(0, "tag=%d\n", data->tag);

    SEGGER_RTT_printf(0, "Sin_Channel1=%d\n", Wave_Data_Buffer.Sin_Channel1);
    SEGGER_RTT_printf(0, "Sin_Channel2=%d\n", Wave_Data_Buffer.Sin_Channel2);
    SEGGER_RTT_printf(0, "Squ_Channel1=%d\n", Wave_Data_Buffer.Squ_Channel1);
    SEGGER_RTT_printf(0, "Squ_Channel2=%d\n", Wave_Data_Buffer.Squ_Channel2);
    SEGGER_RTT_printf(0, "Tri_Channel1=%d\n", Wave_Data_Buffer.Tri_Channel1);
    SEGGER_RTT_printf(0, "Tri_Channel2=%d\n", Wave_Data_Buffer.Tri_Channel2);
    SEGGER_RTT_printf(0, "Cus_Channel1=%d\n", Wave_Data_Buffer.Cus_Channel1);
    SEGGER_RTT_printf(0, "Cus_Channel2=%d\n", Wave_Data_Buffer.Cus_Channel2);

    SEGGER_RTT_printf(0, "Channel1_Freq=%d\n", Wave_Data_Buffer.Channel1_Freq);
    SEGGER_RTT_printf(0, "Channel1_Phas=%d\n", Wave_Data_Buffer.Channel1_Phas);
    SEGGER_RTT_printf(0, "Channel1_Ampl=%d\n", Wave_Data_Buffer.Channel1_Ampl);
    SEGGER_RTT_printf(0, "Channel1_Freq_Unit=%d\n", Wave_Data_Buffer.Channel1_Freq_Unit);
    SEGGER_RTT_printf(0, "Channel2_Freq=%d\n", Wave_Data_Buffer.Channel2_Freq);
    SEGGER_RTT_printf(0, "Channel2_Phas=%d\n", Wave_Data_Buffer.Channel2_Phas);
    SEGGER_RTT_printf(0, "Channel2_Ampl=%d\n", Wave_Data_Buffer.Channel2_Ampl);
    SEGGER_RTT_printf(0, "Channel2_Freq_Unit=%d\n", Wave_Data_Buffer.Channel2_Freq_Unit);
}

uint32_t HLconverter(uint32_t HtoL, uint8_t bit)
{
    uint32_t LtoH = 0;
    for (int i = 0; i < bit; i++)
    {
        LtoH <<= 1;         // 将LtoH左移一位，为下一个位反转做准备
        LtoH |= (HtoL & 1); // 将HtoL的最低位加到LtoH上
        HtoL >>= 1;         // 将HtoL右移一位，准备下一次操作
    }
    return LtoH;
    SEGGER_RTT_printf(0, "HLconverter\n");
}

#define Fclk 125000000
// 要先乘后除，因为keil不支持小数和浮点数
uint16_t mulX = 1000 * 4096 / 240 / 1400;
uint16_t mulY = 50 * 16384 / 8000;

void customUSART_coding(void)
{
    uint8_t Channel0_Sel_buf;
    uint8_t Channel1_Sel_buf;
    if (Wave_Data_Buffer.Sin_Channel1)
        Channel0_Sel_buf = 0;
    else if (Wave_Data_Buffer.Squ_Channel1)
        Channel0_Sel_buf = 1;
    else if (Wave_Data_Buffer.Tri_Channel1)
        Channel0_Sel_buf = 2;
    else if (Wave_Data_Buffer.Cus_Channel1)
        Channel0_Sel_buf = 4;
    else
        Channel0_Sel_buf = 3;

    if (Wave_Data_Buffer.Sin_Channel2)
        Channel1_Sel_buf = 0;
    else if (Wave_Data_Buffer.Squ_Channel2)
        Channel1_Sel_buf = 1;
    else if (Wave_Data_Buffer.Tri_Channel2)
        Channel1_Sel_buf = 2;
    else if (Wave_Data_Buffer.Cus_Channel2)
        Channel1_Sel_buf = 4;
    else
        Channel1_Sel_buf = 3;

    uint32_t Channel0_Freq_buf = 4294967296 * Wave_Data_Buffer.Channel1_Freq * Wave_Data_Buffer.Channel1_Freq_Unit / Fclk;
    uint32_t Channel0_Phas_buf = Wave_Data_Buffer.Channel1_Phas * 4096 / 360;
    uint32_t Channel1_Freq_buf = 4294967296 * Wave_Data_Buffer.Channel2_Freq * Wave_Data_Buffer.Channel2_Freq_Unit / Fclk;
    uint32_t Channel1_Phas_buf = Wave_Data_Buffer.Channel2_Phas * 4096 / 360;

    uint32_t Channel0_Ampl_buf = Wave_Data_Buffer.Channel1_Ampl * 4096 / 5000;
    uint32_t Channel1_Ampl_buf = Wave_Data_Buffer.Channel2_Ampl * 4096 / 5000;
    // 自定义波形编码

    uint32_t Channel_Line1_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[0] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[0]) * mulY);
    uint32_t Channel_Line2_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[1] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[1]) * mulY);
    uint32_t Channel_Line3_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[2] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[2]) * mulY);
    uint32_t Channel_Line4_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[3] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[3]) * mulY);
    uint32_t Channel_Line5_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[4] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[4]) * mulY);
    uint32_t Channel_Line6_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[5] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[5]) * mulY);
    uint32_t Channel_Line7_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[6] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[6]) * mulY);
    uint32_t Channel_Line8_buf = ((uint32_t)(Wave_Data_Buffer.Cus_LineX[7] * mulX) << 16) | (3600 + (153 - Wave_Data_Buffer.Cus_LineY[7]) * mulY);

    SEGGER_RTT_printf(0, "Channel0_Sel_buf=%d\n", Channel0_Sel_buf);
    SEGGER_RTT_printf(0, "Channel1_Sel_buf=%d\n", Channel1_Sel_buf);
    SEGGER_RTT_printf(0, "Channel0_Freq_buf=%d\n", Channel0_Freq_buf);
    SEGGER_RTT_printf(0, "Channel0_Phas_buf=%d\n", Channel0_Phas_buf);
    SEGGER_RTT_printf(0, "Channel1_Freq_buf=%d\n", Channel1_Freq_buf);
    SEGGER_RTT_printf(0, "Channel1_Phas_buf=%d\n", Channel1_Phas_buf);
    SEGGER_RTT_printf(0, "Channel0_Ampl_buf=%d\n", Channel0_Ampl_buf);
    SEGGER_RTT_printf(0, "Channel1_Ampl_buf=%d\n", Channel1_Ampl_buf);

    SEGGER_RTT_printf(0, "Channel_Line7X=%d\n", Wave_Data_Buffer.Cus_LineX[6]);
    SEGGER_RTT_printf(0, "Channel_Line7Y=%d\n", Wave_Data_Buffer.Cus_LineY[6]);

    SEGGER_RTT_printf(0, "Channel_Line7X_buf=%d\n", Channel_Line7_buf >> 16);

    SEGGER_RTT_printf(0, "Channel_Line7Y_buf=%d\n", (uint16_t)(Channel_Line7_buf));

    // Channel_Sel
    Wave_Data.Channel_Sel[3] = HLconverter((Channel1_Sel_buf << 2) | (Channel0_Sel_buf << 5), 8) << 2;
    // Channel0_Freq
    Wave_Data.Channel0_Freq[3] = (uint8_t)(HLconverter(Channel0_Freq_buf, 32) >> 24);
    Wave_Data.Channel0_Freq[4] = (uint8_t)(HLconverter(Channel0_Freq_buf, 32) >> 16);
    Wave_Data.Channel0_Freq[5] = (uint8_t)(HLconverter(Channel0_Freq_buf, 32) >> 8);
    Wave_Data.Channel0_Freq[6] = (uint8_t)(HLconverter(Channel0_Freq_buf, 32));
    // Channel1_Freq
    Wave_Data.Channel1_Freq[3] = (uint8_t)(HLconverter(Channel1_Freq_buf, 32) >> 24);
    Wave_Data.Channel1_Freq[4] = (uint8_t)(HLconverter(Channel1_Freq_buf, 32) >> 16);
    Wave_Data.Channel1_Freq[5] = (uint8_t)(HLconverter(Channel1_Freq_buf, 32) >> 8);
    Wave_Data.Channel1_Freq[6] = (uint8_t)(HLconverter(Channel1_Freq_buf, 32));
    // Channel0_Phas
    Wave_Data.Channel0_Phas[3] = (uint8_t)(HLconverter(Channel0_Phas_buf, 32) >> 24);
    Wave_Data.Channel0_Phas[4] = (uint8_t)(HLconverter(Channel0_Phas_buf, 32) >> 16);
    Wave_Data.Channel0_Phas[5] = (uint8_t)(HLconverter(Channel0_Phas_buf, 32) >> 8);
    Wave_Data.Channel0_Phas[6] = (uint8_t)(HLconverter(Channel0_Phas_buf, 32));
    // Channel1_Phas
    Wave_Data.Channel1_Phas[3] = (uint8_t)(HLconverter(Channel1_Phas_buf, 32) >> 24);
    Wave_Data.Channel1_Phas[4] = (uint8_t)(HLconverter(Channel1_Phas_buf, 32) >> 16);
    Wave_Data.Channel1_Phas[5] = (uint8_t)(HLconverter(Channel1_Phas_buf, 32) >> 8);
    Wave_Data.Channel1_Phas[6] = (uint8_t)(HLconverter(Channel1_Phas_buf, 32));
    // Channel0_Ampl
    Wave_Data.Channel0_Ampl[3] = (uint8_t)(HLconverter(Channel0_Ampl_buf, 32) >> 24);
    Wave_Data.Channel0_Ampl[4] = (uint8_t)(HLconverter(Channel0_Ampl_buf, 32) >> 16);
    Wave_Data.Channel0_Ampl[5] = (uint8_t)(HLconverter(Channel0_Ampl_buf, 32) >> 8);
    Wave_Data.Channel0_Ampl[6] = (uint8_t)(HLconverter(Channel0_Ampl_buf, 32));
    // Channel1_Ampl
    Wave_Data.Channel1_Ampl[3] = (uint8_t)(HLconverter(Channel1_Ampl_buf, 32) >> 24);
    Wave_Data.Channel1_Ampl[4] = (uint8_t)(HLconverter(Channel1_Ampl_buf, 32) >> 16);
    Wave_Data.Channel1_Ampl[5] = (uint8_t)(HLconverter(Channel1_Ampl_buf, 32) >> 8);
    Wave_Data.Channel1_Ampl[6] = (uint8_t)(HLconverter(Channel1_Ampl_buf, 32));
    // Channel_Line
    Wave_Data.Channel_line1[3] = (uint8_t)(HLconverter(Channel_Line1_buf, 32) >> 24);
    Wave_Data.Channel_line1[4] = (uint8_t)(HLconverter(Channel_Line1_buf, 32) >> 16);
    Wave_Data.Channel_line1[5] = (uint8_t)(HLconverter(Channel_Line1_buf, 32) >> 8);
    Wave_Data.Channel_line1[6] = (uint8_t)(HLconverter(Channel_Line1_buf, 32));
    Wave_Data.Channel_line2[3] = (uint8_t)(HLconverter(Channel_Line2_buf, 32) >> 24);
    Wave_Data.Channel_line2[4] = (uint8_t)(HLconverter(Channel_Line2_buf, 32) >> 16);
    Wave_Data.Channel_line2[5] = (uint8_t)(HLconverter(Channel_Line2_buf, 32) >> 8);
    Wave_Data.Channel_line2[6] = (uint8_t)(HLconverter(Channel_Line2_buf, 32));
    Wave_Data.Channel_line3[3] = (uint8_t)(HLconverter(Channel_Line3_buf, 32) >> 24);
    Wave_Data.Channel_line3[4] = (uint8_t)(HLconverter(Channel_Line3_buf, 32) >> 16);
    Wave_Data.Channel_line3[5] = (uint8_t)(HLconverter(Channel_Line3_buf, 32) >> 8);
    Wave_Data.Channel_line3[6] = (uint8_t)(HLconverter(Channel_Line3_buf, 32));
    Wave_Data.Channel_line4[3] = (uint8_t)(HLconverter(Channel_Line4_buf, 32) >> 24);
    Wave_Data.Channel_line4[4] = (uint8_t)(HLconverter(Channel_Line4_buf, 32) >> 16);
    Wave_Data.Channel_line4[5] = (uint8_t)(HLconverter(Channel_Line4_buf, 32) >> 8);
    Wave_Data.Channel_line4[6] = (uint8_t)(HLconverter(Channel_Line4_buf, 32));
    Wave_Data.Channel_line5[3] = (uint8_t)(HLconverter(Channel_Line5_buf, 32) >> 24);
    Wave_Data.Channel_line5[4] = (uint8_t)(HLconverter(Channel_Line5_buf, 32) >> 16);
    Wave_Data.Channel_line5[5] = (uint8_t)(HLconverter(Channel_Line5_buf, 32) >> 8);
    Wave_Data.Channel_line5[6] = (uint8_t)(HLconverter(Channel_Line5_buf, 32));
    Wave_Data.Channel_line6[3] = (uint8_t)(HLconverter(Channel_Line6_buf, 32) >> 24);
    Wave_Data.Channel_line6[4] = (uint8_t)(HLconverter(Channel_Line6_buf, 32) >> 16);
    Wave_Data.Channel_line6[5] = (uint8_t)(HLconverter(Channel_Line6_buf, 32) >> 8);
    Wave_Data.Channel_line6[6] = (uint8_t)(HLconverter(Channel_Line6_buf, 32));
    Wave_Data.Channel_line7[3] = (uint8_t)(HLconverter(Channel_Line7_buf, 32) >> 24);
    Wave_Data.Channel_line7[4] = (uint8_t)(HLconverter(Channel_Line7_buf, 32) >> 16);
    Wave_Data.Channel_line7[5] = (uint8_t)(HLconverter(Channel_Line7_buf, 32) >> 8);
    Wave_Data.Channel_line7[6] = (uint8_t)(HLconverter(Channel_Line7_buf, 32));
    Wave_Data.Channel_line8[3] = (uint8_t)(HLconverter(Channel_Line8_buf, 32) >> 24);
    Wave_Data.Channel_line8[4] = (uint8_t)(HLconverter(Channel_Line8_buf, 32) >> 16);
    Wave_Data.Channel_line8[5] = (uint8_t)(HLconverter(Channel_Line8_buf, 32) >> 8);
    Wave_Data.Channel_line8[6] = (uint8_t)(HLconverter(Channel_Line8_buf, 32));

    // Debug
    SEGGER_RTT_printf(0, "customUSART_coding\n");
}
