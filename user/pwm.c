#include "pwm.h"

void PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_PWM;
	TIM_TimeBaseInitTypeDef TIM_BasePwm;
	TIM_OCInitTypeDef TIM_OCPwm;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_PWM.GPIO_Pin=GPIO_Pin_6;
	GPIO_PWM.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_PWM.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_PWM);

	TIM_BasePwm.TIM_Period=40000;
	TIM_BasePwm.TIM_Prescaler=17;
	TIM_BasePwm.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_BasePwm.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_BasePwm);

	TIM_OCPwm.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCPwm.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCPwm.TIM_Pulse=20000;
	TIM_OCPwm.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM3,&TIM_OCPwm);

	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void PWM_Out(u16 val)
{
	TIM3->CCR1 = val;

}
