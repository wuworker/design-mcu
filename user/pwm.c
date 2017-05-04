#include "pwm.h"

//pwm百分比
u8 pwm=50;

/*
* pwm初始化
*/
void PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_PWM;
	TIM_TimeBaseInitTypeDef TIM_BasePwm;
	TIM_OCInitTypeDef TIM_OCPwm;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_PWM.GPIO_Pin=PWM_PORT;
	GPIO_PWM.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_PWM.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIO,&GPIO_PWM);

	TIM_BasePwm.TIM_Period=PWM_PERIOD;
	TIM_BasePwm.TIM_Prescaler=PWM_PRES;
	TIM_BasePwm.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_BasePwm.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_BasePwm);

	TIM_OCPwm.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCPwm.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCPwm.TIM_Pulse=PWM_PERIOD / 100 * pwm;
	TIM_OCPwm.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM3,&TIM_OCPwm);

	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

/*
* pwm输出
* 参数为百分比
*/
void PWM_Out(u8 val)
{
	if(val > 100)
	{
		val = 100;
	}
	pwm = val;
	TIM3->CCR1 = PWM_PERIOD / 100 * pwm;
}

/*
* 得到当前pwm百分比
*/
u8 PWM_Level()
{
	return pwm;
}
