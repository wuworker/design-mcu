#ifndef __WIFI_HH
#define __WIFI_HH

#include "usart.h"
#include "common.h"

//MAC   5ECF7FF1DC60
static char WIFI_MAC[]={94,207,127,241,220,96};

//CMD
#define OK       0x11
#define IS_MCU   0x22

#define END      0x0a

//最小长度
#define DATA_MIN_LEN   14
//最大长度
#define DATA_MAX_LEN   30

//数据包
typedef struct{
	char target[6];  //目标
	char origin[6];  //来源
    char cmd;		//命令
	char data[16];   //数据，不包括结束符
}DataPacket;


//发送的数据
static char sendData[DATA_MAX_LEN];

//wifi初始化
void WIFI_Init(DataPacket *packet);

void Packet_Init(DataPacket *packet);

//发送数据
void Send_Response(DataPacket *packet,int len);

//获取数据
int Get_Receive(DataPacket *packet,char* cmds,int len);
	
#endif
