
#include "init.h"
#include <math.h>
/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 * ����  ����
 */
int main(void)
{	
	int i=0;
	int j=0;
	int k=0;
	u8 reclen=0;//���ݳ���
	Stm32_Clock_Init(6);//ϵͳʱ������Ϊ�ⲿ����9��Ƶ                                                                 
	delay_init(72);//ϵͳSysTick��ʼ�� �о���̫׼������delayms()������Ϊ1864

	
  GPIO_Configuration();//������led��
	USART1_Config();
   USART2_Init(9600);//����2��ʼ��	
		delay_ms(200);
	I2C_config(); 
  InitSensor();/*��������ʼ��*/

	SPI1_Init();
	PWM_Init(7199,0);//10kHZ
	TIM3_Init(29,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  30Ϊ3ms

	/***********************************************************************/

	for(;;)
	{
	switch(num)
		{
			case 0:
	Led_RollShow(data);
		break;
		case 1 :
			for(i=0;i<20;i++)
			{
				for(j=0;j<20;j++)
			Led_StaticShow1(d[0],i);}
			break;
		
		case 2 :
			for(i=0;i<20;i++)
			{
				for(j=20;j>0;j--)
			Led_StaticShow1(d[1],i);}
		break;
		case 3 :
	for(i=0;i<4;i++)
		{
			for(j=0;j<30;j++)
			Led_StaticShow(d[2+i]);
		}
			
		break;
	}}
//   
//		
//		
//	 default:
//		 Led_StaticShow(data);
//	  break;}
//		s=1;
//		delayms(1000);
//		s=0;
//		delayms(4000);
//		s=1;
//		delayms(1000);
//		s=0;
//		delayms(4000);
		s=2;
	delayms(4000);
	s=0;
	delayms(4000);
		


//		
//		if(KEY0==0)//�����档ǿ�Ʒ�ʽҲ����������
//			{		
//				delayms(5);
//				pwm_set_high(TIM8, TIM_Channel_3);
//				pwm_set_on(TIM1, TIM_Channel_1);
//				TIM_SetCompare1(TIM1, 450);
//				
//				pwm_set_high(TIM8, TIM_Channel_1);
//				pwm_set_on(TIM8, TIM_Channel_2);
//				TIM_SetCompare2(TIM8, 450);
//				
//				while(KEY0==0)
//				{					

//				}
//				pwm_set_off(TIM1, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_3);
//				pwm_set_off(TIM8, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_2);
//				
//			}	
//		 if(KEY1==0)
//			{
//				delayms(5);
//				pwm_set_on(TIM8, TIM_Channel_3);
//				pwm_set_high(TIM1, TIM_Channel_1);
//				TIM_SetCompare3(TIM8, 450);
//				
//				pwm_set_on(TIM8, TIM_Channel_1);
//				pwm_set_high(TIM8, TIM_Channel_2);
//				TIM_SetCompare1(TIM8, 450);
//				while(KEY1==0)
//				{					

//				}
//				pwm_set_off(TIM1, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_3);
//				pwm_set_off(TIM8, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_2);
//			}	

//	{		Angle_Calculate();
//			Angle_Control();
//			Set_Motor_Pwm();

			//Angle�ںϽǶ�
	
			//Gyro_y;//�������ٶ�
			//Angle_gy;//���ֽǶ�
			//0������û�����
			//showwave(Angle,Gyro_y,Angle_gy,0);
 
	//while����		
		

}

