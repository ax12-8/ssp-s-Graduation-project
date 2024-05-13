#include "lsens.h"
#include "delay.h"
#include "adc.h"

//��ʼ������������
void Lsens_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTFʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PF8 anolog����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	Adc3_Init();
}
//��ȡLight Sens��ֵ
//0~100:0,�;100,���� 

float Lsens_Get_Val(void)
{
    u32 light_val = 0;
    u8 t;
    float average_light_val;
    for(t = 0; t < LSENS_READ_TIMES; t++)
    {
        light_val += Get_Adc3(LSENS_ADC_CHX);    // ��ȡADCֵ
        delay_ms(5);
    }
    average_light_val = (float)light_val / LSENS_READ_TIMES;
    if(average_light_val > 4000.00) average_light_val = 4000.00;
    return 100.00 - (average_light_val / 40.00);
}

