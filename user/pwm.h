#ifndef __PWM_HH
#define __PWM_HH

#include "stm32f10x.h"

#define PWM_GPIO 	GPIOA
#define PWM_PORT 	GPIO_Pin_6
#define PWM_PERIOD  40000
#define PWM_PRES    17

//PWM_HZ = 72000000 / PWM_PERIOD / (PWM_PRES + 1)
#define PWM_HZ      100

//pwm初始化
void PWM_Init(void);

//pwm输出
void PWM_Out(u8 val);

//得到当前pwm百分比
u8 PWM_Level(void);

#endif
