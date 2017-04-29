#include "led.h"

void LED_Init(void){

	GPIO_InitTypeDef GPIO_Initialize;

	RCC_APB2PeriphClockCmd(RCC_LED,ENABLE);

	GPIO_Initialize.GPIO_Pin = PIN_LED;
	GPIO_Initialize.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initialize.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIO_LED,&GPIO_Initialize);

	GPIO_SetBits(GPIO_LED,PIN_LED);

}
