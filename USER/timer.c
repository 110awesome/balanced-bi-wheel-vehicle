#include "timer.h"
#include "init.h"
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
float a=0;
void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}
u8 interrupt_flag=0;  //�����жϺ�����Ϊ�ĸ��׶�
u8 speed_control_flag=0;//
void TIM3_IRQHandler(void)   //TIM3�ж�
{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���־λ
		interrupt_flag++;
	
		if(interrupt_flag==1)
		{
 			
			Accel_x = GetData_GYRO(ACCEL_XOUT_H);
			Gyro_y =  GetData_GYRO(GYRO_YOUT_H);	
			Angle_Calculate();
			Angle_Control();
			
			
		}
		else if(interrupt_flag==2)
		{//�ٶȿ���,��ʱ�ò���������������С�ƿ���
			speed_control_flag++;
			if(speed_control_flag>=33)
			{		speed_control_flag = 0;
				
//					Accel_x = GetData_GYRO(ACCEL_XOUT_H);					
//					Gyro_y =  GetData_GYRO(GYRO_YOUT_H);	
//					printf("\r\n%f\t   %f\t  \r\n",Accel_x, Gyro_y);
					if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==Bit_RESET)  
					{  
						GPIO_SetBits(GPIOC,GPIO_Pin_0);  
					}else
					{  
						GPIO_ResetBits(GPIOC,GPIO_Pin_0);  
					} 
			}
		}
		else if(interrupt_flag==3)
		{
			interrupt_flag = 0;
		
		}
		switch(s)
		{
			case 0:
	Set_Motor_Pwm();
		break;
		case 1 :
			Set_control_Pwm(250,0.0);

		num=2;
//		testleft(30);
//		Set_Motor_Pwm();
//		 read();
//		s=9;
			break;
		
		case 2 :
	
		Set_control_Pwm(0.0,900);
		
		num=2;
		break;
		case 3 :
		testright(30);
		Set_Motor_Pwm();
		s=9;
	
		break;
	  case 4 :
    testright(-30);
		Set_Motor_Pwm();
		s=9;

		break;
		 case 5 :
			 	a-=10;
Set_control_Pwm(a,0.0);
			s=11;
     read();
		 USART2_SendString("a:%f\n",a);
		Set_Motor_Pwm();

		 break;
		 case 6 :
		testsetp(10);
		Set_Motor_Pwm();
		s=9;
	
			break;
		
		case 7 :
		testsetp(-10);
		Set_Motor_Pwm();
		s=9;
		break;
		case 8 :
		testsetd(0.05);
		Set_Motor_Pwm();
		s=9;
		
		break;
	  case 10 :
    testsetd(-0.05);
		Set_Motor_Pwm();
		s=9;
		
		break;
		case 11 :
   
		Set_control_Pwm(a,0.0);

		break;
	default:
		Set_Motor_Pwm();
	num=3;
	//Led_RollShow(data);
		break;
		
		
		
		}
}












