#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"
#include "stm32f10x_adc.h"

short Get_Temprate(void);			//��ȡ�ڲ��¶ȴ������¶�ֵ
void T_Adc_Init(void); //ADCͨ����ʼ��
u16  T_Get_Adc(u8 ch); //���ĳ��ͨ��ֵ  
u16  T_Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 

void Adc3_Init(void); 				//ADC3��ʼ��
u16  Get_Adc3(u8 ch); 				//���ADC3ĳ��ͨ��ֵ  
#endif 
