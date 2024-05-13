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

//网络设备
#include "esp8266.h"
//c库
#include "string.h"


//dht11添加变量
double humidityH;	  //湿度整数部分
double humidityL;	  //湿度小数部分
double temperatureH;   //温度整数部分
double temperatureL;   //温度小数部分

double humi,temp;
double adcx = 0;
double mq7 = 0;
double pm = 0;

int count=0;

DHT11_Data_TypeDef DHT11_Data;

int main(void)
{	
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 
	uart_init(115200);//串口1初始化
    uart2_init(9600);//串口2初始化
	uart3_init(115200);//串口3初始化
	 
	ESP8266_Init();	//初始化ESP8266
	DHT11_Init();//初始化温湿度传感器
	Lsens_Init();//初始化光敏传感器
    MQ7_Init();//初始化气敏传感器
    led_init();//初始化LED
    beep_init();//初始化蜂鸣器 
    delay_ms(1000);

	while(1)
	{
			if( Read_DHT11(&DHT11_Data)==SUCCESS)										 //“\”表示转向一下行
			{
				//主要用于数据上传使用
                temperatureH=DHT11_Data.temp_int;   //温度整数部分
				temperatureL=DHT11_Data.temp_deci;   //温度小数部分
				temp = temperatureH+temperatureL/10.0;
				
                humidityH=DHT11_Data.humi_int;	  //湿度整数部分
				humidityL=DHT11_Data.humi_deci;	  //湿度小数部分
				humi = humidityH+humidityL/10.0;
				
				adcx = Lsens_Get_Val();//光照强度
                
                mq7 = (0.0001*(MQ7_Get_Val())*(MQ7_Get_Val())+0.1*(MQ7_Get_Val())+10)/100;//CO浓度
                
                if(USART2_RX_BUF[12]<1)
                    pm = USART2_RX_BUF[12]*256+USART2_RX_BUF[13];//PM2.5浓度
                
                if(temp>30)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("温度过高\r\n");
                }
                if(humi>80)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("湿度过高\r\n");
                }
                if(adcx>80)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("光照强度过高\r\n");
                }
                if(mq7>10)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("CO浓度过高\r\n");
                }
                if(pm>100)
                {
                    BEEP(1);
                    LED0(0);
                    delay_ms(300);
                    LED0(1);
                    BEEP(0);
                    printf("PM2.5浓度过高\r\n");
                }
				printf("temp=%.2f°C,hum=%.2f%%RH, light value=%.2fLux,MQ7=%.2fppm,PM2.5=%.2fμg/m3\r\n",temp,humi,adcx,mq7,pm);//串口工具显示
                count++;
                if(count==100)printf("已输出100条数据\r\n");
				ESP8266_SendData(temp,humi,adcx,mq7,pm);//发送数据
				
				delay_ms(10000);
			}
				ESP8266_Clear();
	}
}
