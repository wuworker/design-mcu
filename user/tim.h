#ifndef __HH_TIM_H
#define __HH_TIM_H

#include "stm32f10x.h"

#define LED_TIM       TIM4
#define LED_TIM_IRQ   TIM4_IRQn

#define LED_PERIOD    2000
#define LED_PRES      35999

//定时中断一秒钟一次
// LED_PERIOD * LED_PRES/72000000 = 1
#define LED_SS        1

//限制多长时间
extern u16 limit_minute;
extern u16 limit_second;

//现在时间
extern u16 second;
extern u16 minute;

//初始化
void TIME_Init(void);

//增加时间，返回是否定时已到
u8 Time_Up(void);

//设置定时时间
//单位分钟
//最大限制30天
void Time_Begin(u16 minutes,u16 second);
void Time_BeginOfDay(u8 day,u8 hour,u8 minute,u8 second);

//清除定时任务
void Time_Clear(void);

#endif
