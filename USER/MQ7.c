#include "MQ7.h"
#include "delay.h"
#include "adc.h"

//初始化烟雾传感器
void MQ7_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	Adc3_Init();
}
//读取烟雾浓度的值
int MQ7_Get_Val(void)
{
	int COppm_val=0;
		COppm_val =Get_Adc3(MQ7_ADC_CHX);	//读取ADC值
	return COppm_val;
}



