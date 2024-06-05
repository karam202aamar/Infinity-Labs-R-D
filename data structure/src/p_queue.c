/*******************************************************************************
 * Project: Data Structures - priority queue 
 * Date: 24/08/22
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>  /* prints , perror */
#include <assert.h> /* aseert */
#include <stdlib.h> /* malloc , free */
#include <string.h> /* strerror */
#include <errno.h>  /* errno */
/*****************************************************************************/
#include "p_queue.h"
#include "sorted_list.h"
/*****************************************************************************/
struct priority_q
{
	sort_list_ty *list; 
}; /* pq_ty */
/*****************************************************************************/
pq_ty *PQCreate(pq_cmp_ty compare_func)
{
	/* define new priority queue (pointer to struct)*/
	pq_ty *new_queue = NULL;
	
	/* assert compare func */
	assert(compare_func);
	
	/* dynamically allocate queue list*/
	new_queue = (pq_ty*)malloc(sizeof(pq_ty));
	
	/* init p-queue call create func of sorted list */
	new_queue -> list = SortListCreate(compare_func);
	
	/* return p-queue */
	return new_queue;
}
/*****************************************************************************/
void PQDestroy(pq_ty *queue)
{
	/* assert p-queue */
	assert(queue);
	
	/* send queue to sorted-list-destroy */
	SortListDestroy(queue->list);
	
	/* free p-queue */	
	free(queue);
	queue = NULL;
}
/*****************************************************************************/
int PQEnqueue(pq_ty *queue, void *data)
{
	/* assert queue */
	assert(queue);
		
	/* call SortListInsert - if not null then success*/
	if(!SortListInsert(queue->list,data))
	{
		return 1;
	}
	
	return 0;
	
}
/*****************************************************************************/
void *PQDequeue(pq_ty *queue)
{
	void* return_val = NULL;
	
	/* assert queue */	
	assert(queue);
	
	
	/* call popfrontsortedlist */
	return_val = SortListPopFront(queue->list);
	
	/* return void* */
	return return_val;
}
/*****************************************************************************/
void *PQPeek(const pq_ty *queue)
{
	void* return_val = NULL;
	
	/* assert queue */
	assert(queue);
	
	/* call  SortListGetData -> SortListBegin */
	return_val = SortListGetData(SortListBegin(queue->list));
	
	return return_val;
}
/*****************************************************************************/
size_t PQSize(const pq_ty *queue)
{
	size_t queue_size = 0;
	
	/* assert queue */
	assert(queue);
	
	/* call SortListSize */
	queue_size = SortListSize(queue->list);
	
	return queue_size;
}
/*****************************************************************************/
int PQIsEmpty(const pq_ty *queue)
{
	/* assert queue */
	assert(queue);
	
	/* call SortListIsEmpty */
	return SortListIsEmpty(queue->list);
	
}
/*****************************************************************************/
void PQClear(pq_ty *queue)
{
	
	/* assert queue */
	assert(queue);
	
	/* loop untill we have empty queue */
	while(1 != PQIsEmpty(queue))
	{
		PQDequeue(queue);
	}	
}
/*****************************************************************************/
void *PQErase(pq_ty *queue, pq_is_match_ty is_match, void *param)
{
	void* return_val = NULL;
	
	assert(queue);
	assert(is_match);
	
	/* 
	SortListFindIf - returns the ither if found
	the send it to SortListRemove , SortListRemove return the iter 
	then get value of the removed
	*/
	if(SortListEnd(queue->list) == ((SortListFindIf(SortListBegin
			(queue->list),SortListEnd(queue->list),is_match,param))))
	{
				return NULL;
	}else
	{
	
		return_val = SortListGetData((SortListFindIf(SortListBegin
			(queue->list),SortListEnd(queue->list),is_match,param)));
	
		SortListRemove((SortListFindIf(SortListBegin
			(queue->list),SortListEnd(queue->list),is_match,param)));
	
		return return_val;
	}	
}
/*****************************************************************************/
