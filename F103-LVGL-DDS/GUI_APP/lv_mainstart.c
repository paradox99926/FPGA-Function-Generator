#include "lv_mainstart.h"
#include "lvgl.h"
#include <stdio.h>
#include "./generated/gui_guider.h"
#include "./generated/events_init.h"
#include "./custom/custom.h"

lv_ui guider_ui;
void lv_mainstart(void)
{

    /*Create a GUI-Guider app */
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);
}
