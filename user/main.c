#include<stm32f10x.h>
#include "common.h"
#include "led.h"
#include "usart.h"
#include "queue.h"
#include "pwm.h"
#include "wifi.h"

//获取命令
int Get_Cmd(char* cmd, Queue *q);

//执行任务
void doJob(DataPacket *packet,int dataLen);

//数据队列
Queue queue;

//是否为1
int total;

int main()
{
	DataPacket packet;
	char cmd[100];
	int len = 0;
	int result = 0;
	total = 0;
	Queue_Init(&queue);
	
	//PWM_Init();
	//LED_Init();

	Delay_MS(2000);
	WIFI_USART_Init();
	PC_USART_Init();
	WIFI_NVIC_Init();
	
	Send_ToPC(" wifi start init\n");
	
	WIFI_Init(&packet);
	
	Send_ToPC("wifi init success\n");
	
//	LED(ON);
	while(1)
	{
//		PWM_Out(10000);
		while(total)
		{
			len = Get_Cmd(cmd,&queue);
			if(len == 2)
			{
				Send_ToPC("heartbeat\n");
				total = Empty(&queue)?0:1;
				continue;
			}
			result = Get_Receive(&packet,cmd,len);
			if(result >=0)
			{
				Send_ToPC("start do job");
				doJob(&packet,result);
			}
			else
			{
				Send_ToPC("unkown cmd");
				break;
			}
//			switch(result)
//			{
//				case -1:
//					Send_ToPC("length is small:");
//					break;
//				case -2:
//					Send_ToPC("target is error:");
//					break;
//				default:
//					Send_ToPC("is ok\n");
//					Send_Response(&packet,result);
//					break;
//			}
			Send_ToPC(cmd);
			total = Empty(&queue)?0:1;
		}
	}
}

/*
* 执行任务
*/
void doJob(DataPacket *packet,int dataLen)
{
	switch(packet->cmd)
	{
		//app发出的确认是否在线
		case ONLINE:
			packet->cmd = OK;
			Send_Response(packet,0);
			break;
		
		default:break;
	}
}


/*
* 获得一条命令
* 返回命令长度
*/
int Get_Cmd(char* cmd, Queue *q)
{
	int receive_len = 0;
	while(!Empty(q))
	{
		*cmd = Poll(q);
		receive_len++;
		if(*cmd == END)
		{
			break;
		}
		cmd++;
	}
	return receive_len;
}

