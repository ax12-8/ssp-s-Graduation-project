#ifndef __MQ7_H
#define __MQ7_H	
#include "sys.h" 
#include "adc.h" 

#define MQ7_READ_TIMES	10		//��������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
#define MQ7_ADC_CHX		ADC_Channel_1	//���������������ڵ�ADCͨ�����
    
void MQ7_Init(void); 				//��ʼ����������
int MQ7_Get_Val(void);				//��ȡ����������ֵ
#endif 
