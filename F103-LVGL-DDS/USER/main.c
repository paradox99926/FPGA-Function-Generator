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
	delay_init();									// ��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);								// ���ڳ�ʼ��Ϊ9600 [115200]
	LED_Init();										// LED�˿ڳ�ʼ��
	KEY_Init();										// ������ʼ��
	TIM3_Int_Init(999, 71);							// ��ʱ����ʼ��(1ms�ж�),���ڸ�lvgl�ṩ1ms����������
	FSMC_SRAM_Init();								// �ⲿ1MB��sram��ʼ��
	LCD_Init();										// LCD��ʼ��
	LCD_Display_Dir(1);
	tp_dev.init(); // ��������ʼ��

	lv_init();			  // lvglϵͳ��ʼ��
	lv_port_disp_init();  // lvgl��ʾ�ӿڳ�ʼ��
	lv_port_indev_init(); // lvgl����ӿڳ�ʼ��

	// const char *data = "̳���Ǻã�\n����һ��LVGL��ά�����̲���";

	// /*Create a 100x100 QR code*/
	// lv_obj_t *qr = lv_qrcode_create(lv_scr_act(), 100, lv_color_hex3(0x33f), lv_color_hex3(0xeef));

	// /*Set data*/
	// lv_qrcode_update(qr, data, strlen(data));
	// lv_demo_widgets();

	lv_mainstart();

	while (1)
	{
		/* ������������� */
		if (KEY_Scan(0) == KEY0_PRES) /* KEY0����,��ִ��У׼���� */
		{
			LCD_Clear(WHITE); /* ���� */
			TP_Adjust();	  /* ��ĻУ׼ */
			TP_Save_Adjdata();
			lv_mainstart();
		}

		tp_dev.scan(0);

		lv_task_handler();
	}
}
