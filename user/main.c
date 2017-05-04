#include<stm32f10x.h>
#include "common.h"
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
	char cmd[DATA_MAX_LEN];
	//命令长度
	int len = 0;
	int result = 0;
	total = 0;
	Queue_Init(&queue);
	
	Delay_MS(1000);
	
	PWM_Init();
	WIFI_USART_Init();
	PC_USART_Init();
	WIFI_NVIC_Init();
	
	Send_ToPC(" wifi start init\n");
	
	WIFI_Init(&packet);
	
	Send_ToPC("wifi init success\n");
	
	while(1)
	{
		//为1说明有数据
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
				doJob(&packet,result);
			}
			else
			{
				Send_ToPC("unkown cmd");
			}
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
			packet->data[0]=PWM_Level();
			Send_Response(packet,1);
			break;
		case ON:
			PWM_Out(packet->data[0]);
			break;
		case OFF:
			PWM_Out(0);
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

