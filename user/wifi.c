#include "wifi.h"

/*
* wifi初始化
*/
void WIFI_Init(DataPacket *packet)
{
	int i=0;
	for(i=0;i<6;i++)
	{
		sendData[6+i] = WIFI_MAC[i];
	}
	
	Send_ToWIFI("++++");
	Delay_MS(500);
	Send_ToWIFI("a");
	Delay_MS(500);
//	Send_ToWIFI("at+netp=TCP,CLIENT,9999,192.168.23.1\n");
	Send_ToWIFI("at+netp=TCP,CLIENT,9999,120.24.96.239\n");
	Delay_MS(1000);
	Send_ToWIFI("at+entm\n");
	Delay_MS(1000);
	
	//进行注册
	Packet_Init(packet);
	Send_Response(packet,0);
}

/*
* 数据包初始化
*/
void Packet_Init(DataPacket *packet)
{
	int i=0;
	for(i=0;i<6;i++)
	{
		packet->target[i]=WIFI_MAC[i];
		packet->origin[i]=WIFI_MAC[i];
	}
	packet->cmd = IS_MCU;
	for(i=0;i<15;i++)
	{
		packet->data[i]=0;
	}
}

/*
* 发送数据，加个偏移量
* len 数据正文长度
*/
void Send_Response(DataPacket *packet,int len)
{
	int i=0;
	//来源作为自己的目标
	for(i=0;i<6;i++)
	{
		sendData[i] = packet->origin[i];
	}
	sendData[12] = packet->cmd;
	for(i=0;i<len;i++)
	{
		sendData[13+i]=packet->data[i] + DATA_OFFEST;
	}
	sendData[13+len] = END;
	Send_ToWIFI(sendData);
}

/**
* 拿到接收的数据
* 减个偏移量
* 返回数据正文长度
*/
int Get_Receive(DataPacket *packet,char* cmds,int len)
{
	int i=0;
	int result = 0;
	
	if(len < DATA_MIN_LEN)
		return -1;

	//拿到数据目的、来源、命令、数据
	for(i=0;i<6;i++,cmds++)
	{
		packet->target[i] = *cmds;
	}
	for(i=0;i<6;i++,cmds++)
	{
		packet->origin[i] = *cmds;
	}
	packet->cmd = *cmds++;
	i=0;
	while(*cmds!=END)
	{
		packet->data[i++] = *cmds++ - DATA_OFFEST;
	}
	result = i;
	
	//校验目标是否是自己
//	for(i=0;i<6;i++)
//		if(packet->target[i]!= WIFI_MAC[i])
//			return -2;
		
	return result;
}

