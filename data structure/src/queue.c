#include <stdio.h>  /* print */
#include <assert.h> /* NULL pointers check */
#include <stdlib.h> /* allocation */
#include <string.h> /* memcpy strerror */
#include <errno.h>  /* errno perror */

/*****************************************************************************/
#include "queue.h"
#include "linked_list.h"
/*****************************************************************************/
struct queue
{
	slist_ty * list;
}; /* queue_ty */
/*****************************************************************************/
queue_ty *QCreate()
{
	/* dynamically allocate queue */
	queue_ty* queue = (queue_ty*)malloc(sizeof(queue_ty));
	
	/* set queue list - call function from linked_list that's creates list*/
	queue -> list = SListCreate();
	
	return queue;
}
/*****************************************************************************/
void QDestroy(queue_ty *queue)
{
	SListDestroy(queue -> list);
	free(queue);
}
/*****************************************************************************/
int QEnqueue(queue_ty *queue, void *data)
{
	/* count how much nodes we have */
	size_t size = SListCount(queue->list);
	
	if(size > 0)
	{
		
		SListInsert(SListNext(SListBegin(queue->list)), data);	
	}
	else
	{
	
		SListInsert(SListBegin(queue->list), data);	
	}
	
	return 0;
}
/*****************************************************************************/
void QDequeue(queue_ty *queue)
{
	SListRemove(SListBegin(queue -> list));
}
/*****************************************************************************/
void *QPeek(const queue_ty *queue)
{
	return SListGetData(SListBegin(queue->list));
	
}
/*****************************************************************************/
int QIsEmpty(const queue_ty *queue)
{

	if(NULL == SListGetData(SListBegin(queue->list)))
	{
		return 1;
	}
	return 0;
}
/*****************************************************************************/
size_t QSize(const queue_ty *queue)
{
	size_t count = 0;
	
	count = SListCount(queue -> list);
	
	return count;
}
/*****************************************************************************/
queue_ty *QAppend(queue_ty *queue_1, queue_ty *queue_2)
{	
	SListAppend(queue_1->list, queue_2->list);
	return queue_1;
}


