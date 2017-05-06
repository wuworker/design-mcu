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
//定时状态
int time_pwm;

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
			doTimeJob();
		}
		//服务器数据到达
		while(total)
		{
			len = Get_Cmd(cmd,&queue);
			//这是服务器发的心跳包
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
		//开和关
		case ON:
			PWM_Out(packet->data[0]);
			break;
		case OFF:
			PWM_Out(0);
			break;
		//定时开和关
		case TIME_ON:
			time_out=0;
			time_pwm = packet->data[0]; 
			Time_Begin((packet->data[1]<<8 & 0xff00)|(packet->data[2]));
			break;
		case TIME_OFF:
			time_out=0;
			time_pwm = 0;
			Time_Begin((packet->data[1]<<8 & 0xff00)|(packet->data[2]));
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

