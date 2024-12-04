#include "timer.h"
#include "lvgl.h"

#include "../../GUI_APP/custom/customUSART.h"
//////////////////////////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// ALIENTEK战舰STM32开发板
// 定时器 驱动代码
// 正点原子@ALIENTEK
// 技术论坛:www.openedv.com
// 修改日期:2012/9/3
// 版本：V1.0
// 版权所有，盗版必究。
// Copyright(C) 广州市星翼电子科技有限公司 2009-2019
// All rights reserved
//////////////////////////////////////////////////////////////////////////////////

// 通用定时器3中断初始化
// 这里时钟选择为APB1的2倍，而APB1为36M
// arr：自动重装值。
// psc：时钟预分频数
// 这里使用的是定时器3!
void TIM3_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 时钟使能

	// 定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr;						// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					// 设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				// 根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能指定的TIM3中断,允许更新中断

	// 中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;			  // TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  // 从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);							  // 初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE); // 使能TIMx
}

static uint16_t NUM;
extern bool event_flag;
bool send_flag;
static uint8_t flag;
extern lv_wave_data_t Wave_Data;
// #define step 500

// 定时器3中断服务程序
void TIM3_IRQHandler(void)
{
	if (TIM3->SR & TIM_IT_Update) // 溢出中断
	{
		lv_tick_inc(1); // lvgl的1ms心跳

		////////////////////////////////////////////////////////////////////////

		if (event_flag)
			send_flag = 1;

		if (send_flag)
		{
			NUM++;
			event_flag = 0;

			switch (NUM)
			{
			case 2:
				customUSART_coding();
				break;

			case 10:
				USART_SendArray(Wave_Data.Channel0_Freq, 8, flag);
				SEGGER_RTT_printf(0, "Channel0_Freq_Send=%d\n", Wave_Data.Channel0_Freq[3]);
				break;

			case 22:
				USART_SendArray(Wave_Data.Channel0_Phas, 8, flag);
				SEGGER_RTT_printf(0, "Channel0_Phas_Send=%d\n", Wave_Data.Channel0_Phas[3]);
				break;

			case 34:
				USART_SendArray(Wave_Data.Channel1_Freq, 8, flag);
				SEGGER_RTT_printf(0, "Channel1_Freq_Send=%d\n", Wave_Data.Channel1_Freq[3]);
				break;

			case 46:
				USART_SendArray(Wave_Data.Channel1_Phas, 8, flag);
				SEGGER_RTT_printf(0, "Channel1_Phas_Send=%d\n", Wave_Data.Channel1_Phas[3]);
				break;

			case 58:
				USART_SendArray(Wave_Data.Channel0_Ampl, 8, flag);
				SEGGER_RTT_printf(0, "Channel0_Ampl_Send=%d\n", Wave_Data.Channel0_Ampl[3]);
				break;

			case 70:
				USART_SendArray(Wave_Data.Channel1_Ampl, 8, flag);
				SEGGER_RTT_printf(0, "Channel1_Ampl_Send=%d\n", Wave_Data.Channel1_Ampl[3]);
				break;

			case 82:
				USART_SendArray(Wave_Data.Channel_line1, 8, flag);
				break;

			case 94:
				USART_SendArray(Wave_Data.Channel_line2, 8, flag);
				break;

			case 106:
				USART_SendArray(Wave_Data.Channel_line3, 8, flag);
				SEGGER_RTT_printf(0, "Channel_line3_Send=%d\n", Wave_Data.Channel_line3[3]);
				break;

			case 118:
				USART_SendArray(Wave_Data.Channel_line4, 8, flag);
				break;

			case 130:
				USART_SendArray(Wave_Data.Channel_line5, 8, flag);
				break;

			case 142:
				USART_SendArray(Wave_Data.Channel_line6, 8, flag);
				break;

			case 154:
				USART_SendArray(Wave_Data.Channel_line7, 8, flag);
				break;

			case 166:
				USART_SendArray(Wave_Data.Channel_line8, 8, flag);
				break;

			case 178:
				USART_SendArray(Wave_Data.Channel_Sel, 8, flag);
				SEGGER_RTT_printf(0, "\n");
				break;

			case 190:
				USART_SendArray(Wave_Data.Renew, 8, flag);
				break;

			case 202:
				NUM = 0;
				send_flag = 0;
				break;

			default:
				break;
			}
		}
		////////////////////////////////////////////////////////////////////////
		// TEST

		// uint8_t Channel0_Freq[8] = {0xAA, 0x03, 0x00, 0x36, 0xB0, 0x00, 0x00, 0x88};
		// uint8_t Channel0_Phas[8] = {0xAA, 0x03, 0x02, 0x00, 0x20, 0x00, 0x00, 0x88};
		// uint8_t Channel1_Freq[8] = {0xAA, 0x03, 0x01, 0x1C, 0x61, 0x00, 0x00, 0x88};
		// uint8_t Channel1_Phas[8] = {0xAA, 0x03, 0x03, 0x00, 0x10, 0x00, 0x00, 0x88};
		// uint8_t Channel0_Ampl[8] = {0xAA, 0x03, 0x04, 0x58, 0x30, 0x00, 0x00, 0x88};
		// uint8_t Channel1_Ampl[8] = {0xAA, 0x03, 0x05, 0xFF, 0xF0, 0x00, 0x00, 0x88};
		// uint8_t Channel_line1[8] = {0xAA, 0x03, 0x08, 0x00, 0x04, 0x00, 0x00, 0x88};
		// uint8_t Channel_line2[8] = {0xAA, 0x03, 0x09, 0x2c, 0x10, 0x34, 0xc0, 0x88};
		// uint8_t Channel_line3[8] = {0xAA, 0x03, 0x0a, 0x13, 0x4c, 0x1a, 0x60, 0x88};
		// uint8_t Channel_line4[8] = {0xAA, 0x03, 0x0b, 0xdb, 0x38, 0x00, 0x10, 0x88};
		// uint8_t Channel_line5[8] = {0xAA, 0x03, 0x0c, 0x01, 0x7c, 0x2c, 0x50, 0x88};
		// uint8_t Channel_line6[8] = {0xAA, 0x03, 0x0d, 0xb5, 0x20, 0x67, 0xd0, 0x88};
		// uint8_t Channel_line7[8] = {0xAA, 0x03, 0x0e, 0x99, 0x20, 0x81, 0x70, 0x88};
		// uint8_t Channel_line8[8] = {0xAA, 0x03, 0x0f, 0xd8, 0x64, 0x00, 0x08, 0x88};
		// uint8_t Channel_Sel[8] = {0xAA, 0x03, 0x06, 0x44, 0x00, 0x00, 0x00, 0x88};
		// uint8_t Renew[8] = {0xAA, 0x03, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x88};

		// if (send_flag)
		// {
		// 	NUM++;
		// 	event_flag = 0;

		// 	switch (NUM)
		// 	{
		// 	case 2:
		// 		customUSART_coding();
		// 		break;

		// 	case 10:
		// 		USART_SendArray(Channel0_Freq, 8, flag);
		// 		break;

		// 	case (10 + step):
		// 		USART_SendArray(Channel0_Phas, 8, flag);
		// 		break;

		// 	case (10 + 2 * step):
		// 		USART_SendArray(Channel1_Freq, 8, flag);
		// 		break;

		// 	case (10 + 3 * step):
		// 		USART_SendArray(Channel1_Phas, 8, flag);
		// 		break;

		// 	case (10 + 4 * step):
		// 		USART_SendArray(Channel0_Ampl, 8, flag);
		// 		break;

		// 	case (10 + 5 * step):
		// 		USART_SendArray(Channel1_Ampl, 8, flag);
		// 		break;

		// 	case (10 + 6 * step):
		// 		USART_SendArray(Channel_line1, 8, flag);
		// 		break;

		// 	case (10 + 7 * step):
		// 		USART_SendArray(Channel_line2, 8, flag);
		// 		break;

		// 	case (10 + 8 * step):
		// 		USART_SendArray(Channel_line3, 8, flag);
		// 		break;

		// 	case (10 + 9 * step):
		// 		USART_SendArray(Channel_line4, 8, flag);
		// 		break;

		// 	case (10 + 10 * step):
		// 		USART_SendArray(Channel_line5, 8, flag);
		// 		break;

		// 	case (10 + 11 * step):
		// 		USART_SendArray(Channel_line6, 8, flag);
		// 		break;

		// 	case (10 + 12 * step):
		// 		USART_SendArray(Channel_line7, 8, flag);
		// 		break;

		// 	case (10 + 13 * step):
		// 		USART_SendArray(Channel_line8, 8, flag);
		// 		break;

		// 	case (10 + 14 * step):
		// 		USART_SendArray(Channel_Sel, 8, flag);
		// 		SEGGER_RTT_printf(0, "\n");
		// 		break;

		// 	case (10 + 15 * step):
		// 		USART_SendArray(Renew, 8, flag);
		// 		break;

		// 	case (10 + 16 * step):
		// 		NUM = 0;
		// 		send_flag = 0;
		// 		break;

		// 	default:
		// 		break;
		// 	}
		// }
	}
	TIM3->SR = (uint16_t)~TIM_IT_Update;
}
