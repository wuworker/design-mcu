#include "wifi.h"


void WIFI_Init()
{
	int i=0;
	for(i=0;i<6;i++)
	{
		sendData[i] = WIFI_MAC[i];
	}
	
	Send_ToWIFI("++++");
	Delay_MS(500);
	Send_ToWIFI("a");
	Delay_MS(500);
	Send_ToWIFI("at+netp=TCP,CLIENT,9999,192.168.23.1\n");
	Delay_MS(500);
	Send_ToWIFI("at+entm\n");
}

/*
* 发送数据
*/
void Send_Data(s8* target,s8 cmd,s16 data)
{
	int i=0;
	for(i=0;i<6;i++)
	{
		sendData[6+i] = target[i];
	}
	sendData[12] = cmd;
	sendData[13] = (data >> 2) & 0xff;
	sendData[14] = data & 0xff;
	sendData[15] = '\n';
	
	Send_ToWIFI(sendData);
}

