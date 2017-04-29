#ifndef __WIFI_HH
#define __WIFI_HH

#include "usart.h"
#include "common.h"

//MAC
#define WIFI_MAC  "5ECF7FF1DC60"

//CMD
#define OK       0x11
#define IS_MCU   0x32

//发送长度
#define SEND_LENGTH     16
//接收长度
#define RECEIVE_LENGTH  10

//接收的数据包
typedef struct{
	s8 success;
	s8 origin[6];
    s8 cmd;
	s16 data;
	s8 end;
}DataPacket;


//发送的数据
static char sendData[SEND_LENGTH];

//wifi初始化
void WIFI_Init(void);

//发送数据
void Send_Data(s8* target,s8 cmd,s16 data);


#endif
