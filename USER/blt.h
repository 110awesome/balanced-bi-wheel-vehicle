#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"
#include "timer.h"
/***************************************************************
Copyright (C), 2013-2023, YFRobot.
www.yfrobot.com
File������2��������(PA2/U2_TX;PA3/U2_RX)
Author��aosini    Version:1.0     Data:2014/05/28
Description:�˺�����ԭ�ӵĴ�����������������޸ģ��ڴ˸�л����ԭ��@ALIENTEK����
            Ӳ����BC04�Ľ��߷�ʽ��PA2������RXD��PA3��TXD��
***************************************************************/        
 
#define USART2_MAX_RECV_LEN		200					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		200					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.
#define true                  1
#define false                 0

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern u16 USART2_RX_STA;   						//��������״̬
extern int s;
extern int num;
void USART2_Init(u32 bound);				//����2��ʼ�� 
//void TIM1_Set(u8 sta);
//void TIM1_Init(u16 arr,u16 psc);
//void UART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar);
//void UART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u8 len);
void u2_printf(char* fmt, ...);
float myatof(const char *sptr);
#endif













