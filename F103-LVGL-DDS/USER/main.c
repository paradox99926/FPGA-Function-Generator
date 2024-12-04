#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "touch.h"
#include "timer.h"
#include "sram.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_examples.h"
#include "lv_mainstart.h"

// #include "lv_qrcode.h"
// #include "../GUI/lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"

int main(void)
{
	delay_init();									// 延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);								// 串口初始化为9600 [115200]
	LED_Init();										// LED端口初始化
	KEY_Init();										// 按键初始化
	TIM3_Int_Init(999, 71);							// 定时器初始化(1ms中断),用于给lvgl提供1ms的心跳节拍
	FSMC_SRAM_Init();								// 外部1MB的sram初始化
	LCD_Init();										// LCD初始化
	LCD_Display_Dir(1);
	tp_dev.init(); // 触摸屏初始化

	lv_init();			  // lvgl系统初始化
	lv_port_disp_init();  // lvgl显示接口初始化
	lv_port_indev_init(); // lvgl输入接口初始化

	// const char *data = "坛友们好！\n这是一个LVGL二维码例程测试";

	// /*Create a 100x100 QR code*/
	// lv_obj_t *qr = lv_qrcode_create(lv_scr_act(), 100, lv_color_hex3(0x33f), lv_color_hex3(0xeef));

	// /*Set data*/
	// lv_qrcode_update(qr, data, strlen(data));
	// lv_demo_widgets();

	lv_mainstart();

	while (1)
	{
		/* 电阻屏坐标矫正 */
		if (KEY_Scan(0) == KEY0_PRES) /* KEY0按下,则执行校准程序 */
		{
			LCD_Clear(WHITE); /* 清屏 */
			TP_Adjust();	  /* 屏幕校准 */
			TP_Save_Adjdata();
			lv_mainstart();
		}

		tp_dev.scan(0);

		lv_task_handler();
	}
}
