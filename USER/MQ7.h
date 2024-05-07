#ifndef __MQ7_H
#define __MQ7_H	
#include "sys.h" 
#include "adc.h" 

#define MQ7_READ_TIMES	10		//定义烟雾传感器读取次数,读这么多次,然后取平均值
#define MQ7_ADC_CHX		ADC_Channel_1	//定义烟雾传感器所在的ADC通道编号
    
void MQ7_Init(void); 				//初始化烟雾传感器
int MQ7_Get_Val(void);				//读取烟雾传感器的值
#endif 
