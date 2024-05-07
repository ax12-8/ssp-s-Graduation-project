#ifndef _ESP8266_H_
#define _ESP8266_H_


#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־


void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(double temp,double humi,int acdx,int COpmm,int PMpmm);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);


#endif
