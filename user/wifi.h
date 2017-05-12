#ifndef __WIFI_HH
#define __WIFI_HH

#include "usart.h"
#include "common.h"

//MAC   5ECF7FF1DC60
static char WIFI_MAC[]={94,207,127,241,220,96};

//结束符
#define END      0x0a

//最小长度
#define DATA_MIN_LEN   14
//最大长度
#define DATA_MAX_LEN   30

//数据偏移量
#define DATA_OFFEST    50

typedef enum
{
	OK        = 0x11,
	STATUS    = 0x12,
	
	IS_MCU    = 0x22,
	
	ONLINE    = 0x31,
	
	ON        = 0x61,
	OFF       = 0x62,
	TIME_ON   = 0x63,
	TIME_OFF  = 0x64,
	TIME_CLR  = 0x65,
	TIME_OVER = 0x66
}CMD;

//数据包
typedef struct
{
	char target[6];  //目标
	char origin[6];  //来源
    char cmd;		//命令
	char data[16];   //数据，不包括结束符
}DataPacket;


//发送的数据
static char sendData[DATA_MAX_LEN];

//wifi初始化
void WIFI_Init(DataPacket *packet);

//数据包初始化
void Packet_Init(DataPacket *packet);

//发送数据
void Send_Response(DataPacket *packet,int len);

//获取数据
int Get_Receive(DataPacket *packet,char* cmds,int len);
	
#endif
