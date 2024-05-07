#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x_tim.h" // 假设你使用的是STM32F10x系列芯片，需要包含相应的定时器头文件

// 定义定时器初始化函数
void TIM4_Int_Init(uint16_t arr, uint16_t psc);

// 定时器中断处理函数声明
void TIM4_IRQHandler(void);

#endif /* TIMER_H */
