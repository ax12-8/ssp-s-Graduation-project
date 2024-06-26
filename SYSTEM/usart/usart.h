#ifndef __USART_H
#define __USART_H
#include "stdio.h"  
#include "sys.h" 

#define USART_REC_LEN       200     //定义最大接收字节数 200
#define EN_USART1_RX        1       //使能（1）/禁止（0）串口1接收
#define EN_USART2_RX        1       //使能（1）/禁止（0）串口2接收
#define EN_USART3_RX        1       //使能（1）/禁止（0）串口3接收
       
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;                 //接收状态标记  

extern u8  USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;                //接收状态标记 

extern u8  USART3_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;                //接收状态标记  

void uart_init(u32 bound);
void uart2_init(u32 bound); // 添加串口2初始化函数声明

void uart3_init(u32 bound);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
#endif
