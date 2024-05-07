#include "PMS5003.h"
#include "delay.h"
#include "adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//LSENS(光敏传感器)驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////



////初始化粉尘传感器
//void PMS5003_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); // 使能 PORTF 时钟
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入引脚
//    GPIO_Init(GPIOF, &GPIO_InitStructure); // 使用 GPIOF 初始化
//    Adc3_Init();
//}
////读取粉尘浓度的值
//int PMS5003_Get_Val(void)
//{
//	int PMppm_val=0;
////	u8 t;
////	for(t=0;t<PMS5003_READ_TIMES;t++)
////	{
//		PMppm_val =Get_Adc3(PMS5003_ADC_CHX);	//读取ADC值
////		delay_ms(5);
////	}
////	PMppm_val/=PMS5003_READ_TIMES;//得到平均值 
////	if(PMppm_val>4000)PMppm_val=4000;
//	return PMppm_val;
//}

