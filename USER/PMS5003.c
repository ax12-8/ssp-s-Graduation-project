#include "PMS5003.h"
#include "delay.h"
#include "adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//LSENS(����������)��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////



////��ʼ���۳�������
//void PMS5003_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); // ʹ�� PORTF ʱ��
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ģ����������
//    GPIO_Init(GPIOF, &GPIO_InitStructure); // ʹ�� GPIOF ��ʼ��
//    Adc3_Init();
//}
////��ȡ�۳�Ũ�ȵ�ֵ
//int PMS5003_Get_Val(void)
//{
//	int PMppm_val=0;
////	u8 t;
////	for(t=0;t<PMS5003_READ_TIMES;t++)
////	{
//		PMppm_val =Get_Adc3(PMS5003_ADC_CHX);	//��ȡADCֵ
////		delay_ms(5);
////	}
////	PMppm_val/=PMS5003_READ_TIMES;//�õ�ƽ��ֵ 
////	if(PMppm_val>4000)PMppm_val=4000;
//	return PMppm_val;
//}

