#include "MQ7.h"
#include "delay.h"
#include "adc.h"

//��ʼ����������
void MQ7_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	Adc3_Init();
}
//��ȡ����Ũ�ȵ�ֵ
int MQ7_Get_Val(void)
{
	int COppm_val=0;
		COppm_val =Get_Adc3(MQ7_ADC_CHX);	//��ȡADCֵ
	return COppm_val;
}



