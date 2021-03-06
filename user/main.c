#include<stm32f10x.h>
#include "common.h"
#include "usart.h"
#include "queue.h"
#include "pwm.h"
#include "wifi.h"
#include "tim.h"
#include "nvic.h"

//获取命令
int Get_Cmd(char* cmd, Queue *q);

//执行任务
void doJob(DataPacket *packet,int dataLen);
void doTimeJob(void);

//数据队列
Queue queue;

//是否为1
int total;

//定时是否到达
int time_out;
//定时的pwm
int time_pwm;

//是否需要发送心跳
int heart;

int main()
{
	DataPacket packet;
	char cmd[DATA_MAX_LEN];
	//命令长度
	int len = 0;
	int result = 0;
	total = 0;
	time_out = 0;
	time_pwm=0;
	Queue_Init(&queue);
	
	Delay_MS(1000);
	
	PWM_Init();
	WIFI_USART_Init();
	PC_USART_Init();
	TIME_Init();
	
	//配置优先级
	NVIC_Config();
	
	Send_ToPC(" wifi start init\n");
	WIFI_Init(&packet);
	Send_ToPC("wifi init success\n");
	
//	Set_Time(1);
//	time_pwm = 0;
	
	while(1)
	{
		//定时时间到达
		if(time_out)
		{
			Send_ToPC("time over\n");
			doTimeJob();
			packet.cmd = TIME_OVER;
			packet.data[0] = time_pwm;
			Send_Response(&packet,1);
		}
		//发送心跳
		if(heart)
		{
			heart = 0;
			Send_ToPC("send heart");
			packet.cmd = ONLINE;
			Send_Response(&packet,0);
		}
		//服务器数据到达
		while(total)
		{
			len = Get_Cmd(cmd,&queue);
			Send_ToPC(cmd);
			result = Get_Receive(&packet,cmd,len);
			if(result >=0)
			{
				doJob(&packet,result);
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
		case STATUS:
			packet->cmd = OK;
			packet->data[0]=PWM_Level();
			Send_Response(packet,1);
			break;
		//开和关
		case ON:
			PWM_Out(packet->data[0]);
			break;
		case OFF:
			PWM_Out(0);
			break;
		//定时开和关
		//data[]
		case TIME_ON:
			time_out=0;
			time_pwm = packet->data[0];
			Time_BeginOfDay(packet->data[1],packet->data[2],packet->data[3],packet->data[4]);
			printf("limit:%d,%d\n",limit_minute,limit_second);
			break;
		case TIME_OFF:
			time_out=0;
			time_pwm = 0;
			Time_BeginOfDay(packet->data[0],packet->data[1],packet->data[2],packet->data[3]);
			printf("limit:%d,%d\n",limit_minute,limit_second);
			break;
		case TIME_CLR:
			time_out=0;
			Time_Clear();
			break;
		default:break;
	}
}

//定时任务
void doTimeJob()
{
	time_out=0;
	PWM_Out(time_pwm);
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

