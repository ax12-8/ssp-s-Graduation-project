//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸����
#include "esp8266.h"

//Ӳ������
#include "delay.h"
#include "usart.h"

//C��
#include <string.h>
#include <stdio.h>

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"727\",\"ssp7274568\"\r\n"

#define ESP8266_ONENET_INFO		"AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1\r\n"

#define ESP8266_USERCFG_INFO  "AT+MQTTUSERCFG=0,1,\"mqtt1\",\"u5vKy5kJhl\",\"version=2018-10-31&res=products%2Fu5vKy5kJhl%2Fdevices%2Fmqtt1&et=2817448486&method=md5&sign=Ee%2Bs2mZpZr332SQg29xhpw%3D%3D\",0,0,\"\"\r\n"

unsigned char esp8266_buf[256];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;

const char* pubtopic="$sys/u5vKy5kJhl/mqtt1/thing/property/post";

extern u8 humidityH;	  //ʪ����������

//==========================================================
//	�������ƣ�	ESP8266_Clear
//
//	�������ܣ�	��ջ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	�������ƣ�	ESP8266_WaitRecive
//
//	�������ܣ�	�ȴ��������
//
//	��ڲ�����	��
//
//	���ز�����	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
//
//	˵����		ѭ�����ü���Ƿ�������
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

	if(esp8266_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;
		
	if(esp8266_cnt == esp8266_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
	{
		esp8266_cnt = 0;							//��0���ռ���
			
		return REV_OK;								//���ؽ�����ɱ�־
	}
		
	esp8266_cntPre = esp8266_cnt;					//��Ϊ��ͬ
	
	return REV_WAIT;								//���ؽ���δ��ɱ�־

}

//==========================================================
//	�������ƣ�	ESP8266_SendCmd
//
//	�������ܣ�	��������
//
//	��ڲ�����	cmd������
//				res����Ҫ���ķ���ָ��
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{
	
	unsigned char timeOut = 200;

	Usart_SendString(USART3, (unsigned char *)cmd, strlen((const char *)cmd));

	while(timeOut--)
	{
		if(ESP8266_WaitRecive() == REV_OK)							//����յ�����
		{
			if(strstr((const char *)esp8266_buf, res) != NULL)		//����������ؼ���
			{
				ESP8266_Clear();									//��ջ���
				
				return 0;
			}
		}
		
		delay_ms(10);
	}
	
	return 1;

}

//==========================================================
//	�������ƣ�	ESP8266_SendData
//
//	�������ܣ�	��������
//
//	��ڲ�����	temp���¶�ֵ
//				      humi��ʪ��ֵ
//				      adcx�����ն�
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_SendData(double temp,double humi,int adcx,int COpmm,int PMpmm)
{
	char cmdBuf[512];
	
	ESP8266_Clear();								//��ս��ջ���
	
	//�ȷ���Ҫ�������ݵ�ָ����׼��
	
	sprintf(cmdBuf, "AT+MQTTPUB=0,\"%s\",\"{\\\"id\\\":\\\"123\\\"\\,\\"
                "\"params\\\":{\\\"temp\\\":{\\\"value\\\":%lf\\}\\,\\"
                "\"humi\\\":{\\\"value\\\":%lf\\}\\,\\\"adcx\\\":{\\\""
                "value\\\":%d\\}\\,\\\"COpmm\\\":{\\\"value\\\":%d\\}"
                "\\,\\\"PMpmm\\\":{\\\"value\\\":%d\\}}}\",0,0\r\n", 
                pubtopic, temp, humi, adcx, COpmm, PMpmm); //��������

	while(ESP8266_SendCmd(cmdBuf, "OK"))
		delay_ms(500);
	memset(cmdBuf,0,sizeof(cmdBuf));
	delay_ms(100);
}



//==========================================================
//	�������ƣ�	ESP8266_Init
//
//	�������ܣ�	��ʼ��ESP8266
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
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
//	�������ƣ�	USART3_IRQHandler
//
//	�������ܣ�	����3�շ��ж�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART3_IRQHandler(void)
{

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�����ж�
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	esp8266_cnt = 0; //��ֹ���ڱ�ˢ��
		esp8266_buf[esp8266_cnt++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}

}
