/*******************************************************************************
 * Project: Data Structures - Priority Queue heap
 * Date: 29/10/22
 * Name: 
 * Reviewer: 
 * Version: 1.1
*******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "heap.h"
#include "pqueue_heap.h"
/******************************************************************************/
struct priority_q 
{
    heap_ty* pq_heap;
}; /*pq_ty*/
/******************************************************************************/
pq_ty *PQHCreate(pq_cmp_ty cmp_func)
{
    pq_ty* pqueue = NULL;

    pqueue = (pq_ty*)malloc(sizeof(pq_ty));

     if(NULL == pqueue)
    {
        perror(strerror(errno));
		return NULL;
    }
    pqueue->pq_heap = HeapCreate(cmp_func);

    return pqueue;
}
/******************************************************************************/
void PQHDestroy(pq_ty *queue)
{
    assert(queue);

    HeapDestroy(queue->pq_heap);
    free(queue);
    queue = NULL;
}
/******************************************************************************/
int PQHEnqueue(pq_ty *queue, void *data)
{
    int status = 0;

    assert(queue);
    assert(data);

    status = HeapPush(queue->pq_heap, data);

    return status;
}
/******************************************************************************/
void *PQHDequeue(pq_ty *queue)
{
    assert(queue);
	
	return HeapPop(queue->pq_heap);
}
/******************************************************************************/
void *PQHPeek(const pq_ty *queue)
{
    void *return_data = NULL;

    assert(queue);

    return_data = HeapPeek(queue->pq_heap);

    return return_data;
}
/******************************************************************************/
size_t PQHSize(const pq_ty *queue)
{
    assert(queue);
    return HeapSize(queue->pq_heap);
}
/******************************************************************************/
int PQHIsEmpty(const pq_ty *queue)
{
    assert(queue);

    return HeapIsEmpty(queue->pq_heap);
}
/******************************************************************************/
void PQHClear(pq_ty *queue)
{
    assert(queue);

    while(1 != PQHIsEmpty(queue))
    {
        PQHDequeue(queue);
    }
}
/******************************************************************************/
void *PQHErase(pq_ty *queue, pq_is_match_ty is_match, void *param)
{
    assert(queue);

	return HeapRemove(queue->pq_heap, is_match, param);
}
/******************************************************************************/