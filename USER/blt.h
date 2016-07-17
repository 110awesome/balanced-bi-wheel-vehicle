#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"
#include "timer.h"
/***************************************************************
Copyright (C), 2013-2023, YFRobot.
www.yfrobot.com
File：串口2驱动代码(PA2/U2_TX;PA3/U2_RX)
Author：aosini    Version:1.0     Data:2014/05/28
Description:此函数对原子的串口驱动代买进行了修改，在此感谢正点原子@ALIENTEK分享
            硬件与BC04的接线方式，PA2接蓝牙RXD；PA3接TXD。
***************************************************************/        
 
#define USART2_MAX_RECV_LEN		200					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		200					//最大发送缓存字节数
#define USART2_RX_EN 			1					//0,不接收;1,接收.
#define true                  1
#define false                 0

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern u16 USART2_RX_STA;   						//接收数据状态
extern int s;
extern int num;
void USART2_Init(u32 bound);				//串口2初始化 
//void TIM1_Set(u8 sta);
//void TIM1_Init(u16 arr,u16 psc);
//void UART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar);
//void UART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u8 len);
void u2_printf(char* fmt, ...);
float myatof(const char *sptr);
#endif













