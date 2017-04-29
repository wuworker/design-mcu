#ifndef __QUEUE_HH
#define __QUEUE_HH

#define QueueSize 1024

typedef struct{
    char array[QueueSize];
    int front;
	int rear;
	int size;
}Queue;

//队列初始化
void Queue_Init(Queue *q);

//队列是否满
int Full(Queue *q);

//队列是否空
int Empty(Queue *q);

//队尾加数据
int Offer(Queue *q,char n);

//队头拿数据
char Poll(Queue *q);

//队列大小
int Size(Queue *q);



#endif
