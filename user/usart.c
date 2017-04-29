#include "usart.h"

/*
	wifi的UART初始化
*/
void WIFI_USART_Init()
{
	GPIO_InitTypeDef GPIO_US;
	USART_InitTypeDef USART_US;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	GPIO_US.GPIO_Pin = WIFI_TX;
	GPIO_US.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_US.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(WIFI_GPIO,&GPIO_US);

	GPIO_US.GPIO_Pin=WIFI_RX;
	GPIO_US.GPIO_Mode=GPIO_Mode_IN_FLOATING;

	GPIO_Init(WIFI_GPIO,&GPIO_US);

	USART_US.USART_BaudRate=115200;
	USART_US.USART_WordLength=USART_WordLength_8b;
	USART_US.USART_StopBits=USART_StopBits_1;
	USART_US.USART_Parity=USART_Parity_No;
	USART_US.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_US.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(WIFI_USART,&USART_US);
	
	USART_ITConfig(WIFI_USART, USART_IT_RXNE, ENABLE);
	USART_Cmd(WIFI_USART,ENABLE);
}

/*
 PC的UART初始化
**/
void PC_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_US;
	USART_InitTypeDef USART_US;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_US.GPIO_Pin = PC_TX;
	GPIO_US.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_US.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(PC_GPIO,&GPIO_US);

	GPIO_US.GPIO_Pin=PC_RX;
	GPIO_US.GPIO_Mode=GPIO_Mode_IN_FLOATING;

	GPIO_Init(PC_GPIO,&GPIO_US);

	USART_US.USART_BaudRate=115200;
	USART_US.USART_WordLength=USART_WordLength_8b;
	USART_US.USART_StopBits=USART_StopBits_1;
	USART_US.USART_Parity=USART_Parity_No;
	USART_US.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_US.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(PC_USART,&USART_US);
	
	USART_ITConfig(PC_USART, USART_IT_RXNE, ENABLE);
	USART_Cmd(PC_USART,ENABLE);
}

/* 
	WIFI接收中断
*/
void WIFI_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = WIFI_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/* 
*	PC接收中断
*/
void PC_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = PC_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
	pringf重定向到PC
*/
int fputc(int ch,FILE *f)
{
	USART_SendData(PC_USART,(unsigned char)ch);
	while(USART_GetFlagStatus(PC_USART,USART_FLAG_TC)!=SET);
	return (ch);
}
/*
	发送到PC
*/
void Send_ToPC(char *s){
	
	while(*s!=0){
		USART_SendData(PC_USART,*s);
		while(USART_GetFlagStatus(PC_USART,USART_FLAG_TC)!=SET);
		//把\n后的数据忽略
		if(*s++ == '\n')
			break;
	}
}
/**
* 发送到WIFI
*/
void Send_ToWIFI(char *s){
	
	while(*s!=0){
		USART_SendData(WIFI_USART,*s);
		while(USART_GetFlagStatus(WIFI_USART,USART_FLAG_TC)!=SET);
		//把\n后的数据忽略
		if(*s++ == '\n')
			break;
	}
}





