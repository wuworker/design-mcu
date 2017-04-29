#ifndef __USART_HH
#define __USART_HH

#include"stm32f10x.h"
#include"stdio.h"

//PC USART
#define PC_USART  USART1
#define PC_GPIO   GPIOA
#define PC_TX     GPIO_Pin_9
#define PC_RX     GPIO_Pin_10
#define PC_IRQ    USART1_IRQn

//WIFI USART
#define WIFI_USART  USART2
#define WIFI_GPIO   GPIOA
#define WIFI_TX     GPIO_Pin_2
#define WIFI_RX     GPIO_Pin_3
#define WIFI_IRQ    USART2_IRQn

void WIFI_USART_Init(void);
void PC_USART_Init(void);

void WIFI_NVIC_Init(void);
void PC_NVIC_Init(void);

void Send_ToWIFI(char *s);
void Send_ToPC(char *s);


#endif

