#include<stm32f10x.h>
#include "common.h"
#include "led.h"
#include "usart.h"
#include "queue.h"
#include "pwm.h"
#include "wifi.h"

//获取命令
void Get_Cmd(char* cmd, Queue *q);
//获得数据
void Get_Receive(DataPacket *packet,Queue *q);

//数据队列
Queue queue;

//数据包
DataPacket packet;


//是否为1
int total;

int main()
{
	total = 0;
	Queue_Init(&queue);
	//PWM_Init();
	//LED_Init();
	
	Delay_MS(2000);
	WIFI_USART_Init();
	PC_USART_Init();
	
	Send_ToPC(" uart start init\n");
	WIFI_NVIC_Init();
	
	Delay_MS(500);
	Send_ToPC("wifi start init\n");
	
	WIFI_Init();
	
//	LED(ON);
	while(1)
	{
		
		//Send_String("hello\n");
//		PWM_Out(10000);
//		Delay_MS(1000);
		
//		LED(OFF);
		
//		PWM_Out(30000);
//		Delay_MS(1000);
		
		while(total)
		{
			//Get_Cmd(cmd,&queue);
			Get_Receive(&packet,&queue);
			if(packet.success)
			{
				Send_Data(packet.origin,packet.cmd,packet.data);
			}
			
			total = Empty(&queue)?0:1;
		}
	}
}

//获得命令
void Get_Cmd(char* cmd, Queue *q)
{
	while(!Empty(q))
	{
		*cmd = Poll(q);
		if(*cmd == '\n')
		{
			break;
		}
		cmd++;
	}
}

/**
* 拿到接收的数据
*/
void Get_Receive(DataPacket *packet,Queue *q)
{
	packet->success=0;
	if(Size(q)>=10)
	{
		int i=0;
		for(i=0;i<6;i++)
		{
			packet->origin[i] = Poll(q);
		}
		packet->cmd = Poll(q);
		packet->data = ((Poll(q) << 2) & 0xff00) | Poll(q);
		packet->end = Poll(q);
		//数据正确
		if(packet->end == '\n')
		{
			packet->success=1;
		}
		else
		{
			Send_ToPC("receive error\n");
		}
	}
	else
	{
		Send_ToPC("receive other:\n");
		while(!Empty(q))
		{
			USART_SendData(PC_USART,Poll(q));
			while(USART_GetFlagStatus(PC_USART,USART_FLAG_TC)!=SET);
		}
	}
}
