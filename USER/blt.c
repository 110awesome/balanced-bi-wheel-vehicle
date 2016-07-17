#include "delay.h"
#include "blt.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
/***************************************************************
Copyright (C), 2013-2023, YFRobot.
www.yfrobot.com
File������2��������(PA2/U2_TX;PA3/U2_RX)
Author��aosini    Version:1.0     Data:2014/05/28
Description:�˺�����ԭ�ӵĴ�����������������޸ģ��ڴ˸�л����ԭ��@ALIENTEK����
            Ӳ����BC04�Ľ��߷�ʽ��PA2������RXD��PA3��TXD��
***************************************************************/  

//���ڷ��ͻ����� 	
__align(8) u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
#ifdef USART2_RX_EN   								//���ʹ���˽���   	  
//���ڽ��ջ����� 	
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
int s=9;
int num=0;
//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
u16 USART2_RX_STA=0;  
u8 reclen=0;
void USART2_IRQHandler(void)
{
	u8 res;	int i;    
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	
		res=USART_ReceiveData(USART2);
		USART2_RX_BUF[USART2_RX_STA++]=res;
 		reclen = USART2_RX_STA&0X7FFF;	//�õ����ݳ���	 	//���������
	  USART_SendData(USART2,USART2_RX_BUF[reclen-1]);
	  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 

		//�жϽ��յ����ݣ���������Ӧ����
			if(USART2_RX_BUF[0] == '0')       {s=0;}	
			else if(USART2_RX_BUF[0] == '1')  {s=1;}
			else if(USART2_RX_BUF[0] == '2')  {s=2;}
			else if(USART2_RX_BUF[0] == '3')  {s=3;}
			else if(USART2_RX_BUF[0] == '4')  {s=4;}
			else if(USART2_RX_BUF[0] =='5')   {s=5;}
			else if(USART2_RX_BUF[0] == '6')  {s=6;}
			else if(USART2_RX_BUF[0] == '7')  {s=7;}
			else if(USART2_RX_BUF[0] == '8')  {s=8;}
			else if(USART2_RX_BUF[0] == '9')  {s=10;}
			//else if(USART2_RX_BUF[0] == '10')  {s=12;}
 			USART2_RX_STA=0;	 	
		}	
		//res=USART2->DR; 			 
//		//if(USART2_RX_STA<USART2_MAX_RECV_LEN)		//�����Խ�������
//		{
//			//TIM1->CNT=0;         					//���������
//			//if(USART2_RX_STA==0)TIM1_Set(1);	 	//ʹ�ܶ�ʱ��4���ж� 
//			USART2_RX_BUF[USART2_RX_STA++]=res;		//��¼���յ���ֵ	 
//		}else 
//		{
//			USART2_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
//		} 
	}  											 
//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void USART2_Init(u32 bound)
{  	 		 
//	RCC->APB2ENR|=1<<8;   	//ʹ��PORTG��ʱ��  
// 	GPIOG->CRH&=0XFFFFFF0F;	//IO״̬����
//	GPIOG->CRH|=0X00000030;	//IO״̬����
//	RCC->APB2ENR|=1<<2;   	//ʹ��PORTA��ʱ��  
//	GPIOA->CRL&=0XFFFF00FF;	//IO״̬����
//	GPIOA->CRL|=0X00008B00;	//IO״̬����	 
//	RCC->APB1ENR|=1<<17;  	//ʹ�ܴ���ʱ�� 	 
//	RCC->APB1RSTR|=1<<17;   //��λ����2
//	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
//	//����������
// 	USART2->BRR=(pclk1*1000000)/(bound);// ����������	 
//	USART2->CR1|=0X200C;  	//1λֹͣ,��У��λ.
//	USART2->CR3=1<<7;   	//ʹ�ܴ���2��DMA����
//	UART_DMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)USART2_TX_BUF);//DMA1ͨ��7,����Ϊ����2,�洢��ΪUSART2_TX_BUF 
	
	//pa2 pa3
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
#ifdef USART2_RX_EN
		NVIC_InitTypeDef NVIC_InitStructure;
#endif
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//TX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);     	
	//RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure); 
  USART_Cmd(USART2, ENABLE);
	
#ifdef USART2_RX_EN		  	//���ʹ���˽���
//	//ʹ�ܽ����ж�
//	USART2->CR1|=1<<8;    	//PE�ж�ʹ��
//	USART2->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
//	MY_NVIC_Init(2,3,USART2_IRQn,2);//��2��������ȼ� 
//	//TIM1_Init(99,7199);		//10ms�ж�
//	USART2_RX_STA=0;		//����
//	//TIM1_Set(0);			//�رն�ʱ��4
USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

#endif										  	
}
//����2,printf ����
//ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
//void u2_printf(char* fmt,...)  
//{  
//	va_list ap;
//	va_start(ap,fmt);
//	vsprintf((char*)USART2_TX_BUF,fmt,ap);
//	va_end(ap);
//	while(DMA1_Channel7->CNDTR!=0);	//�ȴ�ͨ��7�������   
//	UART_DMA_Enable(DMA1_Channel7,strlen((const char*)USART2_TX_BUF)); 	//ͨ��dma���ͳ�ȥ
//}
void USART2_SendString(char *fmt, ...)
 {
	char buffer[USART2_MAX_SEND_LEN+1];  // 
	u8 i = 0;
	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART2_MAX_SEND_LEN+1, fmt, arg_ptr);
	USART_ClearFlag(USART2,USART_FLAG_TXE);
	while ((i < USART2_MAX_SEND_LEN) && buffer[i])
	{
		if(buffer[i] == '\n'){
        USART_SendData(USART2,(u8)'\r');
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
        USART_SendData(USART2,(u8)buffer[i++]);
        }else{
	    USART_SendData(USART2, (u8) buffer[i++]);
        }
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
	}
	va_end(arg_ptr);
 }


//��ʱ��1�жϷ������		    
//void TIM1_UP_IRQHandler(void)
//{ 	
//	if(TIM1->SR&0X01)//�Ǹ����ж�
//	{	 			   
//		USART2_RX_STA|=1<<15;	//��ǽ������
//		TIM1->SR&=~(1<<0);		//����жϱ�־λ		   
//		TIM1_Set(0);			//�ر�TIM1 
//	}	    
//}
//����TIM1�Ŀ���
//sta:0���ر�;1,����;
//void TIM1_Set(u8 sta)
//{
//	if(sta)
//	{
//    	TIM1->CNT=0;         //���������
//		TIM1->CR1|=1<<0;     //ʹ�ܶ�ʱ��1
//	}else TIM1->CR1&=~(1<<0);//�رն�ʱ��1	   
//}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʼ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��		 
//void TIM1_Init(u16 arr,u16 psc)
//{
//	RCC->APB2ENR|=1<<11;	//TIM1ʱ��ʹ��    
// 	TIM1->ARR=arr;  	//�趨�������Զ���װֵ   
//	TIM1->PSC=psc;  	//Ԥ��Ƶ��
// 	TIM1->DIER|=1<<0;   //��������ж�				
// 	TIM1->CR1|=0x01;  	//ʹ�ܶ�ʱ��1	  	   
//   	MY_NVIC_Init(1,3,TIM1_UP_IRQn,2);//��ռ2�������ȼ�3����2	��2�����ȼ����								 
//}
#endif		 
///////////////////////////////////////USART2 DMA�������ò���//////////////////////////////////	   		    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ    
//void UART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar)
//{
// 	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
//	delay_us(5);
//	DMA_CHx->CPAR=cpar; 		//DMA1 �����ַ 
//	DMA_CHx->CMAR=cmar; 		//DMA1,�洢����ַ	 
//	DMA_CHx->CCR=0X00000000;	//��λ
//	DMA_CHx->CCR|=1<<4;  		//�Ӵ洢����
//	DMA_CHx->CCR|=0<<5;  		//��ͨģʽ
//	DMA_CHx->CCR|=0<<6;  		//�����ַ������ģʽ
//	DMA_CHx->CCR|=1<<7;  		//�洢������ģʽ
//	DMA_CHx->CCR|=0<<8;  		//�������ݿ��Ϊ8λ
//	DMA_CHx->CCR|=0<<10; 		//�洢�����ݿ��8λ
//	DMA_CHx->CCR|=1<<12; 		//�е����ȼ�
//	DMA_CHx->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ		  	
//} 
////����һ��DMA����
//void UART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u8 len)
//{
//	DMA_CHx->CCR&=~(1<<0);       //�ر�DMA���� 
//	DMA_CHx->CNDTR=len;          //DMA1,���������� 
//	DMA_CHx->CCR|=1<<0;          //����DMA����
//}	   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 									 
//��������myatof
//���ܣ����ַ���ת��Ϊ double ������
//������Դ��my array to floating point number
//����˵��������һ���ַ����жϵ�һ���ַ��ã�û�з���Ĭ��Ϊ��ֵ��Ȼ���ʣ���ַ�����ת����
//����\0��������󷵻�һ��double
float myatof(const char *sptr)
{
    float temp = 10;
	char ispnum = true;
	float ans = 0;
	if(*sptr == '-')  //�ж��Ƿ��Ǹ���
	{
	    ispnum = false;
		sptr++;
	}
	else if(*sptr == '+') //�ж��Ƿ�Ϊ����
	{
	    sptr++;
	}
	while(*sptr != '\0')//Ѱ��С����֮ǰ����
	{
	    if(*sptr == '.') {sptr++; break;}//��⵽��0�� �����ѭ��
		ans = ans*10 + (*sptr - '0');
		sptr++;
	}
	while(*sptr != '\0')
	{
	    ans = ans + (*sptr - '0')/temp;
		temp *= 10;
		sptr++;
	}
	if(ispnum)return ans;
	else return ans*(-1); 

}























