#include "tim.h"

//限制多长时间
u16 limit_minute;
u16 limit_second;

//现在时间
u16 second;
u16 minute;

/*
* 定时器初始化
*/
void TIME_Init()    
{  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    TIM_ClearITPendingBit(LED_TIM, TIM_IT_Update);  
    
	TIM_TimeBaseStructure.TIM_Period = LED_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = LED_PRES;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(LED_TIM, &TIM_TimeBaseStructure);  
    
	TIM_ITConfig(LED_TIM, TIM_IT_Update, ENABLE ); 
	//开始禁止启动
	TIM_Cmd(LED_TIM,DISABLE);  
}

/*
* 增加时间
* 返回定时时间是否结束
*/
u8 Time_Up(void)
{
	if(++second == 60)
	{
		second = 0;
		if(++minute==limit_minute)
		{
			minute = 0;
			limit_minute = 0;
		}
	}
	//定时时间到
	if(second == limit_second && limit_minute == 0)
	{
		limit_second=0;
		second=0;
		TIM_Cmd(LED_TIM,DISABLE); 
		return 1;
	}
	return 0;
}

/*
* 设置定时时间
* 单位:分钟
* 最小1分钟，最大31天
*/
void Time_Begin(u16 min,u16 sec)
{
	if(min==0 && sec==0)
		return;
	
	second = 0;
	minute = 0;
	limit_minute = min;
	limit_second = sec;
	
	TIM_Cmd(LED_TIM,ENABLE);
}

void Time_BeginOfDay(u8 day,u8 hour,u8 minute,u8 second)
{
	int min = (day * 24 + hour)*60 + minute;
	Time_Begin(min,second);
}

/*
* 清除任务
*/
void Time_Clear()
{
	second = 0;
	minute = 0;
	limit_minute = 0;
	
	TIM_Cmd(LED_TIM,DISABLE);
}




