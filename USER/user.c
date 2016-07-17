#include "init.h"

u8 data[20] = {0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 d[6][20]= {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x99,0xDB,
0x7E,0x3C,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x3C,0x7E,0xDB,0x99,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x11,0x11,0x73,0x00,0x0E,0x11,0x11,0x7F,0x00,
0x00,0x00,0x00,0x00,
0x00,0x0C,0x10,0x7F,0x10,0x0C,0x00,0x3E,0x41,0x1C,0x00,0x00,
0x0E,0x15,0x15,0x55,0x35,0x0E,0x00,
0x00,0x00,0x00,0x01,0x3E,0x46,0x42,0x42,0x3C,0x00,0x00,0x00,0x00,0x0E,0x79,0x4A,
0x5A,0x42,0x00,0x00,
0x00,0x02,0x7E,0x22,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x3C,0x00,0x7E,0x08,0x10,
0x20,0x7E,0x00,0x00
};
u8 empty = 0x00,j=0,k=0;

void Led_RollShow(u8 data[])
{
	 u8 i=0;
	
		

		for(i = 0; i < 20; i++)
		{
			SPI1_WriteByte(0xFF);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			delayus(100);
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(120000);
		}
	}

								
void Led_StaticShow(u8 data[])
{
		u8 i=0;
		for(i = 0; i < 20; i++)
		{
			SPI1_WriteByte(data[i]);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(600);
		}
}


void Led_StaticShow1(u8 data[],int j)
{
		u8 i=0;
		for(i = 0; i < 20; i++)
		{
			SPI1_WriteByte(data[(i+j)%20]);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(600);
		}
}
//		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==Bit_RESET)  
//				{  
//					GPIO_SetBits(GPIOC,GPIO_Pin_0);  
//				}else{  
//				GPIO_ResetBits(GPIOC,GPIO_Pin_0);  
//				} 



//if(KEY0==0)//经仿真。强制方式也存在死区的
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


//		printf("\r\n---------加速度X轴原始数据---------%d \r\n",GetData_GYRO(ACCEL_XOUT_H));
//		printf("\r\n---------加速度Y轴原始数据---------%d \r\n",GetData_GYRO(ACCEL_YOUT_H));	
//		printf("\r\n---------加速度Z轴原始数据---------%d \r\n",GetData_GYRO(ACCEL_ZOUT_H));	
//		printf("\r\n---------陀螺仪X轴原始数据---------%d \r\n",GetData_GYRO(GYRO_XOUT_H));	
//		printf("\r\n---------陀螺仪Y轴原始数据---------%d \r\n",GetData_GYRO(GYRO_YOUT_H));	
//		printf("\r\n---------陀螺仪Z轴原始数据---------%d \r\n",GetData_GYRO(GYRO_ZOUT_H));	
//		printf("\r\n---------罗盘Z轴原始数据---------%d \r\n",GetData_MAG(MAG_XOUT_L));
//		printf("\r\n---------罗盘Z轴原始数据---------%d \r\n",GetData_MAG(MAG_YOUT_L));
//		printf("\r\n---------罗盘Z轴原始数据---------%d \r\n",GetData_MAG(MAG_ZOUT_L));
		
//		printf("\r\n%d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t\r\n",
//							GetData_GYRO(ACCEL_XOUT_H),GetData_GYRO(ACCEL_YOUT_H),GetData_GYRO(ACCEL_ZOUT_H)
//							,GetData_GYRO(GYRO_XOUT_H),GetData_GYRO(GYRO_YOUT_H),GetData_GYRO(GYRO_ZOUT_H)
//							,GetData_MAG(MAG_XOUT_L),GetData_MAG(MAG_YOUT_L),GetData_MAG(MAG_ZOUT_L)
//							,GetData_BMP280(BMP280_TEMPERATURE_MSB_REG),GetData_BMP280(BMP280_PRESSURE_MSB_REG));



//Temp+=0.1;
//		OutData[0] = 100*sin(Temp)+100;
//    OutData[1] = 100*sin(Temp+2.09)+100;
//    OutData[2] = 100*sin(Temp+4.18)+100;
//    OutData[3] = sin(Temp);
//    if(Temp >= 3.1*2) Temp = 0;
//	   OutPut_Data();


