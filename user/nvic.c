#include "nvic.h"


void NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	//优先级组为1，抢占1位，响应3位
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	//wifi优先级最高
	NVIC_InitStructure.NVIC_IRQChannel = WIFI_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//led定时器
	NVIC_InitStructure.NVIC_IRQChannel = LED_TIM_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//PC的串口中断
	NVIC_InitStructure.NVIC_IRQChannel = PC_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}






