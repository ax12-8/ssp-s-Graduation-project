#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"
#include "dht11.h"
#include "esp8266.h"
#include "adc.h"
#include "lsens.h"
#include "MQ7.h"
#include "beep.h"

//�����豸
#include "esp8266.h"
//c��
#include "string.h"


//dht11��ӱ���
double humidityH;	  //ʪ����������
double humidityL;	  //ʪ��С������
double temperatureH;   //�¶���������
double temperatureL;   //�¶�С������

double humi,temp;
double adcx = 0;
double mq7 = 0;
double pm = 0;

int count=0;

DHT11_Data_TypeDef DHT11_Data;

int main(void)
{	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 
	uart_init(115200);//����1��ʼ��
    uart2_init(9600);//����2��ʼ��
	uart3_init(115200);//����3��ʼ��
	 
	ESP8266_Init();	//��ʼ��ESP8266
	DHT11_Init();//��ʼ����ʪ�ȴ�����
	Lsens_Init();//��ʼ������������
    MQ7_Init();//��ʼ������������
    led_init();//��ʼ��LED
    beep_init();//��ʼ�������� 
    delay_ms(1000);

	while(1)
	{
			if( Read_DHT11(&DHT11_Data)==SUCCESS)										 //��\����ʾת��һ����
			{
				//��Ҫ���������ϴ�ʹ��
                temperatureH=DHT11_Data.temp_int;   //�¶���������
				temperatureL=DHT11_Data.temp_deci;   //�¶�С������
				temp = temperatureH+temperatureL/10.0;
				
                humidityH=DHT11_Data.humi_int;	  //ʪ����������
				humidityL=DHT11_Data.humi_deci;	  //ʪ��С������
				humi = humidityH+humidityL/10.0;
				
				adcx = Lsens_Get_Val();//����ǿ��
                
                mq7 = (0.0001*(MQ7_Get_Val())*(MQ7_Get_Val())+0.1*(MQ7_Get_Val())+10)/100;//COŨ��
                
                if(USART2_RX_BUF[12]<1)
                    pm = USART2_RX_BUF[12]*256+USART2_RX_BUF[13];//PM2.5Ũ��
                
                if(temp>30)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("�¶ȹ���\r\n");
                }
                if(humi>80)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("ʪ�ȹ���\r\n");
                }
                if(adcx>80)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("����ǿ�ȹ���\r\n");
                }
                if(mq7>10)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("COŨ�ȹ���\r\n");
                }
                if(pm>100)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("PM2.5Ũ�ȹ���\r\n");
                }
				printf("temp=%.2f��C,hum=%.2f%%RH, light value=%.2fLux,MQ7=%.2fppm,PM2.5=%.2f��g/m3\r\n",temp,humi,adcx,mq7,pm);//���ڹ�����ʾ
                count++;
                if(count==100)printf("�����100������\r\n");
				ESP8266_SendData(temp,humi,adcx,mq7,pm);//��������
				
				delay_ms(10000);
			}
				ESP8266_Clear();
	}
}
