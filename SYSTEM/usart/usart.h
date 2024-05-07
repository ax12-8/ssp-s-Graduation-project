#ifndef __USART_H
#define __USART_H
#include "stdio.h"  
#include "sys.h" 

#define USART_REC_LEN       200     //�����������ֽ��� 200
#define EN_USART1_RX        1       //ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX        1       //ʹ�ܣ�1��/��ֹ��0������2����
#define EN_USART3_RX        1       //ʹ�ܣ�1��/��ֹ��0������3����
       
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;                 //����״̬���  

extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;                //����״̬��� 

extern u8  USART3_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;                //����״̬���  

void uart_init(u32 bound);
void uart2_init(u32 bound); // ��Ӵ���2��ʼ����������

void uart3_init(u32 bound);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
#endif
