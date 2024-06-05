#include <stdio.h> /*puts*/
/*****************************************************************************/
#include "queue.h"
#include "linked_list.h"
/*****************************************************************************/
static void ImplementFunc();
static void CreateDestroyQueueTest();
static void QEnqueueTest();
static void QDequeueTest();
static void QIsEmptyTest();
static void QSizeTest();
static void QueueAppendTest();
/*****************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0;
}
/*****************************************************************************/
static void ImplementFunc()
{
	CreateDestroyQueueTest();
	/*
	QEnqueueTest();
	QDequeueTest();
	QIsEmptyTest();
	QSizeTest();      */
	QueueAppendTest();
}
/*****************************************************************************/
static void CreateDestroyQueueTest()
{
	queue_ty *queue = QCreate();
	
	if(!queue)
	{
		puts("Creation test has been failed");
	}
	
	QDestroy(queue);

}
/*****************************************************************************/
static void QEnqueueTest()
{
	queue_ty *queue = QCreate();
	
	int a = 3;
	int b = 4;
	int c = 5;
	int d = 6;
	
	QEnqueue(queue , &a);
	QEnqueue(queue , &b);
	QEnqueue(queue , &c);
	QEnqueue(queue , &d);
	
	if(4 != QSize(queue))
	{
		printf("QEnqueue test failed");
		printf("Qpeek test failed");
	}
	
	QDestroy(queue);	
}
/*****************************************************************************/
static void QDequeueTest()
{

	queue_ty *new_queue = QCreate();
	int node_a = 3;
	int node_b = 4;
	
	QEnqueue(new_queue,&node_a);
	QEnqueue(new_queue,&node_b);
	
	QDequeue(new_queue);
	
	if(4 != *(int *)QPeek(new_queue))
	{
		puts("Dequeue test has been failed");
	}
	
	QDestroy(new_queue);

}
/*****************************************************************************/
static void QIsEmptyTest()
{
	queue_ty *new_queue = QCreate();
	if(1 == QIsEmpty(new_queue))
	{
		puts("Queue is empty test failed");
	}
	QDestroy(new_queue);
}
/*****************************************************************************/
static void QSizeTest()
{
	queue_ty *new_queue = QCreate();
	int node_a = 3;
	int node_b = 4;
	int node_c = 5;
	
	QEnqueue(new_queue,&node_a);
	QEnqueue(new_queue,&node_b);
	QEnqueue(new_queue,&node_c);
	
	if(3 != QSize(new_queue))
	{
		puts("Queue size test failed");
	}
	QDestroy(new_queue);
	
}
/*****************************************************************************/
static void QueueAppendTest()
{
	queue_ty *new_queue1 = QCreate();
	queue_ty *new_queue2 = QCreate();
	int node_a = 3;
	int node_b = 4;
	int node_c = 5;
	
	int node_d = 6;
	
	QEnqueue(new_queue1,&node_a);
	QEnqueue(new_queue1,&node_b);
	QEnqueue(new_queue1,&node_c);
	
	QEnqueue(new_queue2,&node_d);
	
	new_queue1 = QAppend(new_queue1, new_queue2);
	
	if(5 != QSize(new_queue1))
	{
		puts("Queue append test has been failed");
	}
	
	QDestroy(new_queue1);	
	QDestroy(new_queue2);	
}


