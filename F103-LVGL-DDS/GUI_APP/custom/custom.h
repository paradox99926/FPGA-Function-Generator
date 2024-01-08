// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "../generated/gui_guider.h"

    static struct
    {
        bool Sin_Channel_1;
        bool Sin_Channel_2;
        bool Squ_Channel_1;
        bool Squ_Channel_2;
        bool Tri_Channel_1;
        bool Tri_Channel_2;
    } Btn_Sel = {0, 0, 0, 0, 0, 0};

    void Set_State();
    void custom_init(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
