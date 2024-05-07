#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"

/******************************************************************************************/
/* ���� ���� */

#define BEEP_GPIO_PORT                  GPIOB
#define BEEP_GPIO_PIN                   SYS_GPIO_PIN8
#define BEEP_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 3; }while(0)   /* PB��ʱ��ʹ�� */

/******************************************************************************************/

/* ���������� */
#define BEEP(x)         sys_gpio_pin_set(BEEP_GPIO_PORT, BEEP_GPIO_PIN, x)

/* BEEPȡ������ */
#define BEEP_TOGGLE()   do{ BEEP_GPIO_PORT->ODR ^= BEEP_GPIO_PIN; }while(0)     /* BEEP = !BEEP */

void beep_init(void);   /* ��ʼ�������� */

#endif

















