#ifndef	__LED_H
#define	__LED_H

#include"stm32f10x.h"

#define GPIO_LED  GPIOA
#define PIN_LED   GPIO_Pin_3
#define RCC_LED   RCC_APB2Periph_GPIOA

#define ON 1
#define OFF 0

#define LED(a)	if(a)\
					GPIO_SetBits(GPIO_LED,PIN_LED);\
				else\
					GPIO_ResetBits(GPIO_LED,PIN_LED);

void LED_Init(void);


#endif
