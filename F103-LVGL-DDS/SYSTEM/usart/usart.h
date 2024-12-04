#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ALIENTEK STM32������
// ����1��ʼ��
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// �޸�����:2012/8/18
// �汾��V1.5
// ��Ȩ���У�����ؾ���
// Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
// All rights reserved
//********************************************************************************
// V1.3�޸�˵��
// ֧����Ӧ��ͬƵ���µĴ��ڲ���������.
// �����˶�printf��֧��
// �����˴��ڽ��������.
// ������printf��һ���ַ���ʧ��bug
// V1.4�޸�˵��
// 1,�޸Ĵ��ڳ�ʼ��IO��bug
// 2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
// 3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
// 4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
// V1.5�޸�˵��
// 1,�����˶�UCOSII��֧��
#define USART_REC_LEN 200 // �����������ֽ��� 200
#define EN_USART1_RX 1    // ʹ�ܣ�1��/��ֹ��0������1����

extern u8 USART_RX_BUF[USART_REC_LEN]; // ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;               // ����״̬���

// ����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
// ���ú�����
void USART_SendByte(uint8_t Byte);
void USART_SendArray(uint8_t *Array, uint16_t Length, uint8_t FLAG);
void USART_SendString(char *String, uint8_t FLAG);
uint32_t USART_Pow(uint32_t X, uint32_t Y);
void USART_SendNumber(uint32_t Number, uint8_t Length, uint8_t FLAG);
#endif
