//单片机头文件
#include "stm32f10x.h"

//网络设备驱动
#include "esp8266.h"

//硬件驱动
#include "delay.h"
#include "usart.h"

//C库
#include <string.h>
#include <stdio.h>

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"727\",\"ssp7274568\"\r\n"

#define ESP8266_ONENET_INFO		"AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1\r\n"

#define ESP8266_USERCFG_INFO  "AT+MQTTUSERCFG=0,1,\"mqtt1\",\"u5vKy5kJhl\",\"version=2018-10-31&res=products%2Fu5vKy5kJhl%2Fdevices%2Fmqtt1&et=2817448486&method=md5&sign=Ee%2Bs2mZpZr332SQg29xhpw%3D%3D\",0,0,\"\"\r\n"

unsigned char esp8266_buf[256];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;

const char* pubtopic="$sys/u5vKy5kJhl/mqtt1/thing/property/post";

extern u8 humidityH;	  //湿度整数部分

//==========================================================
//	函数名称：	ESP8266_Clear
//
//	函数功能：	清空缓存
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	函数名称：	ESP8266_WaitRecive
//
//	函数功能：	等待接收完成
//
//	入口参数：	无
//
//	返回参数：	REV_OK-接收完成		REV_WAIT-接收超时未完成
//
//	说明：		循环调用检测是否接收完成
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

	if(esp8266_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return REV_WAIT;
		
	if(esp8266_cnt == esp8266_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
	{
		esp8266_cnt = 0;							//清0接收计数
			
		return REV_OK;								//返回接收完成标志
	}
		
	esp8266_cntPre = esp8266_cnt;					//置为相同
	
	return REV_WAIT;								//返回接收未完成标志

}

//==========================================================
//	函数名称：	ESP8266_SendCmd
//
//	函数功能：	发送命令
//
//	入口参数：	cmd：命令
//				res：需要检查的返回指令
//
//	返回参数：	0-成功	1-失败
//
//	说明：		
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{
	
	unsigned char timeOut = 200;

	Usart_SendString(USART3, (unsigned char *)cmd, strlen((const char *)cmd));

	while(timeOut--)
	{
		if(ESP8266_WaitRecive() == REV_OK)							//如果收到数据
		{
			if(strstr((const char *)esp8266_buf, res) != NULL)		//如果检索到关键词
			{
				ESP8266_Clear();									//清空缓存
				
				return 0;
			}
		}
		
		delay_ms(10);
	}
	
	return 1;

}

//==========================================================
//	函数名称：	ESP8266_SendData
//
//	函数功能：	发送数据
//
//	入口参数：	temp：温度值
//				      humi：湿度值
//				      adcx：光照度
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_SendData(double temp,double humi,double adcx,double COpmm,double PMpmm)
{
	char cmdBuf[512];
	
	ESP8266_Clear();								//清空接收缓存
	
	//先发送要发送数据的指令做准备
	
	sprintf(cmdBuf, "AT+MQTTPUB=0,\"%s\",\"{\\\"id\\\":\\\"123\\\"\\,\\"
                "\"params\\\":{\\\"temp\\\":{\\\"value\\\":%.2f\\}\\,\\"
                "\"humi\\\":{\\\"value\\\":%.2f\\}\\,\\\"adcx\\\":{\\\""
                "value\\\":%.2f\\}\\,\\\"COpmm\\\":{\\\"value\\\":%.2f\\}"
                "\\,\\\"PMpmm\\\":{\\\"value\\\":%.2f\\}}}\",0,0\r\n", 
                pubtopic, temp, humi, adcx, COpmm, PMpmm); //发送命令

	while(ESP8266_SendCmd(cmdBuf, "OK"))
		delay_ms(500);
	memset(cmdBuf,0,sizeof(cmdBuf));
	delay_ms(100);
}



//==========================================================
//	函数名称：	ESP8266_Init
//
//	函数功能：	初始化ESP8266
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_Init(void)
{
	
	ESP8266_Clear();
	
	printf("0. AT\r\n");
	while(ESP8266_SendCmd("AT\r\n", "OK"))
		delay_ms(500);
	
	printf("1. AT+RST\r\n");
	while(ESP8266_SendCmd("AT+RST\r\n", ""))
		delay_ms(500);
	
	
	printf("2. CWMODE\r\n");
	while(ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK"))
		delay_ms(500);
	
	printf( "3. AT+CWDHCP\r\n");
	while(ESP8266_SendCmd("AT+CWDHCP=1,1\r\n", "OK"))
		delay_ms(500);
	
	printf("4. CWJAP\r\n");
	while(ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP"))
		delay_ms(500);
	
	printf( "5. MQTTUSERCFG\r\n");
	while(ESP8266_SendCmd(ESP8266_USERCFG_INFO, "OK"))
		delay_ms(500);

	
	printf( "6. MQTTCONN\r\n");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "OK"))
		delay_ms(500);
	
	printf("7. ESP8266 Init OK\r\n");

}

//==========================================================
//	函数名称：	USART3_IRQHandler
//
//	函数功能：	串口3收发中断
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART3_IRQHandler(void)
{

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收中断
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	esp8266_cnt = 0; //防止串口被刷爆
		esp8266_buf[esp8266_cnt++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}

}
