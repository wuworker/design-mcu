#include "queue.h"

/*
* 简单的数据队列
*/

/*
* 队列初始化
*/
void Queue_Init(Queue *q)
{
    q->front = q->rear = 0;
	q->size = 0;
}
/*
* 队列是否满
*/
int Full(Queue *q)  
{
    return (q->rear+1)%QueueSize == q->front;  
}

/*
* 队列是否空
*/
int Empty(Queue *q)  
{  
    return q->front == q->rear;  
} 

/*
( 向队尾添加
*/
int Offer(Queue *q,char data)  
{
    if(Full(q)){
        return 0;
    }
    q->array[q->rear] = data;
    q->rear = (q->rear+1)%QueueSize;
	q->size = (q->size + 1);
	return 1;
}

/*
* 拿到队头数据
*/
char Poll(Queue *q)  
{
	char data = 0;
    if(Empty(q))  
    {
        return 0;
    }
  
    data = q->array[q->front];  
    q->front = (q->front+1)%QueueSize;  
	q->size = (q->size - 1);
    return data;
}
/*
* 队列大小
*/
int Size(Queue *q)
{
	return q->size;
}
