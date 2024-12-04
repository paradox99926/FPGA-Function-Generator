#ifndef __CUSTOMUSART_H_
#define __CUSTOMUSART_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "../generated/gui_guider.h"
#include "../../SYSTEM/usart/usart.h"
#include "../../SYSTEM/delay/delay.h"
#include "custom.h"
#include "SEGGER_RTT.h"

    typedef enum
    {
        tag_Function_Set_tab_1,
        tag_Function_Set_tab_2,
        tag_Function_Set_tab_3,
        tag_Function_Set_tab_4,
        tag_Function_Set_tab_5,
        tag_Sin_Channel_2_btn,
        tag_Sin_Channel_1_btn,
        tag_Sin_Pword_Slider,
        tag_Sin_Fword_Slider,
        tag_Sin_Aword_Slider,
        tag_Sin_Hz_btn,
        tag_Squ_Channel_2_btn,
        tag_Squ_Channel_1_btn,
        tag_Squ_Pword_Slider,
        tag_Squ_Fword_Slider,
        tag_Squ_Aword_Slider,
        tag_Squ_Hz_btn,
        tag_Tri_Channel_2_btn,
        tag_Tri_Channel_1_btn,
        tag_Tri_Pword_Slider,
        tag_Tri_Fword_Slider,
        tag_Tri_Aword_Slider,
        tag_Tri_Hz_btn,
        tag_Cus_Channel_2_btn,
        tag_Cus_Channel_1_btn,
        tag_Cus_Pword_Slider,
        tag_Cus_Fword_Slider,
        tag_Cus_Aword_Slider,
        tag_Cus_Hz_btn,
        tag_Cus_Line,
    } lv_user_tag_t;

    typedef enum
    {
        HZ = 1,
        KHZ = 1000,
        MHZ = 1000000,

        OFF = 0,
        ON = 2,

        DEFAULT = 3,
        CHANGE = 4,

    } lv_user_state_t;

    typedef struct
    {
        lv_user_state_t State;
        lv_user_tag_t tag;
        int16_t value;
        lv_point_t point[8];
    } lv_user_data_t;

    typedef struct
    {
        lv_user_data_t *pointer_Function_Set_tab_1;
        lv_user_data_t *pointer_Function_Set_tab_2;
        lv_user_data_t *pointer_Function_Set_tab_3;
        lv_user_data_t *pointer_Function_Set_tab_4;
        lv_user_data_t *pointer_Function_Set_tab_5;
        lv_user_data_t *pointer_Sin_Channel_2_btn;
        lv_user_data_t *pointer_Sin_Channel_1_btn;
        lv_user_data_t *pointer_Sin_Pword_Slider;
        lv_user_data_t *pointer_Sin_Fword_Slider;
        lv_user_data_t *pointer_Sin_Aword_Slider;
        lv_user_data_t *pointer_Sin_Hz_btn;
        lv_user_data_t *pointer_Squ_Channel_2_btn;
        lv_user_data_t *pointer_Squ_Channel_1_btn;
        lv_user_data_t *pointer_Squ_Pword_Slider;
        lv_user_data_t *pointer_Squ_Fword_Slider;
        lv_user_data_t *pointer_Squ_Aword_Slider;
        lv_user_data_t *pointer_Squ_Hz_btn;
        lv_user_data_t *pointer_Tri_Channel_2_btn;
        lv_user_data_t *pointer_Tri_Channel_1_btn;
        lv_user_data_t *pointer_Tri_Pword_Slider;
        lv_user_data_t *pointer_Tri_Fword_Slider;
        lv_user_data_t *pointer_Tri_Aword_Slider;
        lv_user_data_t *pointer_Tri_Hz_btn;
        lv_user_data_t *pointer_Cus_Channel_2_btn;
        lv_user_data_t *pointer_Cus_Channel_1_btn;
        lv_user_data_t *pointer_Cus_Pword_Slider;
        lv_user_data_t *pointer_Cus_Fword_Slider;
        lv_user_data_t *pointer_Cus_Aword_Slider;
        lv_user_data_t *pointer_Cus_Hz_btn;
        lv_user_data_t *pointer_Cus_Line;
    } lv_user_pointer_t;

    typedef struct
    {
        uint8_t Channel0_Freq[8];
        uint8_t Channel0_Phas[8];
        uint8_t Channel0_Ampl[8];
        uint8_t Channel1_Freq[8];
        uint8_t Channel1_Phas[8];
        uint8_t Channel1_Ampl[8];

        uint8_t Channel_line1[8];
        uint8_t Channel_line2[8];
        uint8_t Channel_line3[8];
        uint8_t Channel_line4[8];
        uint8_t Channel_line5[8];
        uint8_t Channel_line6[8];
        uint8_t Channel_line7[8];
        uint8_t Channel_line8[8];

        uint8_t Channel_Sel[8];
        uint8_t Renew[8];
    } lv_wave_data_t;

    // struct init
    static lv_user_data_t user_data_Function_Set_tab_1 = {.State = DEFAULT, .tag = tag_Function_Set_tab_1, .value = 0};
    static lv_user_data_t user_data_Function_Set_tab_2 = {.State = DEFAULT, .tag = tag_Function_Set_tab_2, .value = 0};
    static lv_user_data_t user_data_Function_Set_tab_3 = {.State = DEFAULT, .tag = tag_Function_Set_tab_3, .value = 0};
    static lv_user_data_t user_data_Function_Set_tab_4 = {.State = DEFAULT, .tag = tag_Function_Set_tab_4, .value = 0};
    static lv_user_data_t user_data_Function_Set_tab_5 = {.State = DEFAULT, .tag = tag_Function_Set_tab_5, .value = 0};
    static lv_user_data_t user_data_Sin_Channel_2_btn = {.State = DEFAULT, .tag = tag_Sin_Channel_2_btn, .value = 0};
    static lv_user_data_t user_data_Sin_Channel_1_btn = {.State = DEFAULT, .tag = tag_Sin_Channel_1_btn, .value = 0};
    static lv_user_data_t user_data_Sin_Pword_Slider = {.State = DEFAULT, .tag = tag_Sin_Pword_Slider, .value = 0};
    static lv_user_data_t user_data_Sin_Fword_Slider = {.State = DEFAULT, .tag = tag_Sin_Fword_Slider, .value = 0};
    static lv_user_data_t user_data_Sin_Aword_Slider = {.State = DEFAULT, .tag = tag_Sin_Aword_Slider, .value = 0};
    static lv_user_data_t user_data_Sin_Hz_btn = {.State = DEFAULT, .tag = tag_Sin_Hz_btn, .value = 0};
    static lv_user_data_t user_data_Squ_Channel_2_btn = {.State = DEFAULT, .tag = tag_Squ_Channel_2_btn, .value = 0};
    static lv_user_data_t user_data_Squ_Channel_1_btn = {.State = DEFAULT, .tag = tag_Squ_Channel_1_btn, .value = 0};
    static lv_user_data_t user_data_Squ_Pword_Slider = {.State = DEFAULT, .tag = tag_Squ_Pword_Slider, .value = 0};
    static lv_user_data_t user_data_Squ_Fword_Slider = {.State = DEFAULT, .tag = tag_Squ_Fword_Slider, .value = 0};
    static lv_user_data_t user_data_Squ_Aword_Slider = {.State = DEFAULT, .tag = tag_Squ_Aword_Slider, .value = 0};
    static lv_user_data_t user_data_Squ_Hz_btn = {.State = DEFAULT, .tag = tag_Squ_Hz_btn, .value = 0};
    static lv_user_data_t user_data_Tri_Channel_2_btn = {.State = DEFAULT, .tag = tag_Tri_Channel_2_btn, .value = 0};
    static lv_user_data_t user_data_Tri_Channel_1_btn = {.State = DEFAULT, .tag = tag_Tri_Channel_1_btn, .value = 0};
    static lv_user_data_t user_data_Tri_Pword_Slider = {.State = DEFAULT, .tag = tag_Tri_Pword_Slider, .value = 0};
    static lv_user_data_t user_data_Tri_Fword_Slider = {.State = DEFAULT, .tag = tag_Tri_Fword_Slider, .value = 0};
    static lv_user_data_t user_data_Tri_Aword_Slider = {.State = DEFAULT, .tag = tag_Tri_Aword_Slider, .value = 0};
    static lv_user_data_t user_data_Tri_Hz_btn = {.State = DEFAULT, .tag = tag_Tri_Hz_btn, .value = 0};
    static lv_user_data_t user_data_Cus_Channel_2_btn = {.State = DEFAULT, .tag = tag_Cus_Channel_2_btn, .value = 0};
    static lv_user_data_t user_data_Cus_Channel_1_btn = {.State = DEFAULT, .tag = tag_Cus_Channel_1_btn, .value = 0};
    static lv_user_data_t user_data_Cus_Pword_Slider = {.State = DEFAULT, .tag = tag_Cus_Pword_Slider, .value = 0};
    static lv_user_data_t user_data_Cus_Fword_Slider = {.State = DEFAULT, .tag = tag_Cus_Fword_Slider, .value = 0};
    static lv_user_data_t user_data_Cus_Aword_Slider = {.State = DEFAULT, .tag = tag_Cus_Aword_Slider, .value = 0};
    static lv_user_data_t user_data_Cus_Hz_btn = {.State = DEFAULT, .tag = tag_Cus_Hz_btn, .value = 0};
    static lv_user_data_t user_data_Cus_Line = {.State = DEFAULT, .tag = tag_Cus_Line, .value = 0, .point = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // function declaration
    void
    customUSART_init(lv_ui *ui, lv_user_pointer_t guider_user);
    void customUSART_write(lv_obj_t *obj);
    void customUSART_coding(void);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
