#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x_tim.h" // ������ʹ�õ���STM32F10xϵ��оƬ����Ҫ������Ӧ�Ķ�ʱ��ͷ�ļ�

// ���嶨ʱ����ʼ������
void TIM4_Int_Init(uint16_t arr, uint16_t psc);

// ��ʱ���жϴ���������
void TIM4_IRQHandler(void);

#endif /* TIMER_H */
