#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"
#include "stm32f10x_adc.h"

short Get_Temprate(void);			//获取内部温度传感器温度值
void T_Adc_Init(void); //ADC通道初始化
u16  T_Get_Adc(u8 ch); //获得某个通道值  
u16  T_Get_Adc_Average(u8 ch,u8 times);//得到某个通道10次采样的平均值 

void Adc3_Init(void); 				//ADC3初始化
u16  Get_Adc3(u8 ch); 				//获得ADC3某个通道值  
#endif 
