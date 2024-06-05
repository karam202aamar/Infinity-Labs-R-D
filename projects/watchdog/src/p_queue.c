/*******************************************************************************

*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>/* perror */
#include <stdlib.h>/* malloc, free */
#include <assert.h>/* assert */
#include <string.h>/* strerro */
#include <errno.h>/* errno */
/******************************************************************************/
#include "p_queue.h"
#include "sorted_list.h"
/******************************************************************************/
struct priority_q
{
	sort_list_ty *so_list;
};

typedef enum STATUS {SUCCESS = 0, FAIL = 1} status_ty;

/******************************************************************************/
pq_ty *PQCreate(pq_cmp_ty cmp_func)
{
	pq_ty *queue = NULL;

	assert(cmp_func);

	queue = (pq_ty*)malloc(sizeof(pq_ty));
	if(NULL == queue)
	{
		perror(strerror(errno));
		return NULL;
	}
	/*Allocate memory for the dlist.*/
	queue->so_list = SortListCreate((compare_ty)cmp_func);
	if(NULL == queue->so_list)
	{
		free(queue);
		queue = NULL;
	}
	
	/*Return the create list.*/
	return queue;
}
/******************************************************************************/
void PQDestroy(pq_ty *queue)
{
	assert(queue);
	/*USe the Dlist Destroy*/
	SortListDestroy(queue->so_list);
	free(queue);
	
	queue = NULL;
}
/******************************************************************************/
int PQEnqueue(pq_ty *queue, void *data)
{
	sort_list_iter_ty iter = NULL;
	iter = SortListInsert(queue->so_list, data);
	assert(queue);
	
	if(SortListIsSameIter(iter, SortListEnd(queue->so_list)))
	{
		return FAIL;
	}
	
	return SUCCESS;
}
/******************************************************************************/
void *PQDequeue(pq_ty *queue)
{
	assert(queue);
	
	return SortListPopFront(queue->so_list);
}
/******************************************************************************/
void *PQPeek(const pq_ty *queue)
{
	assert(queue);
	
	return SortListGetData(SortListBegin(queue->so_list));
}
/******************************************************************************/
size_t PQSize(const pq_ty *queue)
{
	assert(queue);
	
	return SortListSize(queue->so_list);
}
/******************************************************************************/
int PQIsEmpty(const pq_ty *queue)
{
	assert(queue);

	return SortListIsEmpty(queue->so_list);
}
/******************************************************************************/
void PQClear(pq_ty *queue)
{
	assert(queue);

	while(!PQIsEmpty(queue))
	{
		PQDequeue(queue);
	}
}
/******************************************************************************/
void *PQErase(pq_ty *queue, pq_is_match_ty is_match, void *param)
{
	/*Initialization*/
	sort_list_iter_ty begin_iter = SortListBegin(queue->so_list);
	sort_list_iter_ty end_iter = SortListEnd(queue->so_list);
	is_match_func_ty match_func = (is_match_func_ty)is_match;
	sort_list_iter_ty find_iter = NULL;
	/*Data which will be returned.*/
	void *ret_data = NULL;
	
	/*Find the suitable iter (if exists)*/
	find_iter = SortListFindIf(begin_iter, end_iter, match_func, param);
	/*Get iter's data*/
	ret_data = SortListGetData(find_iter);

	assert(is_match);
	assert(queue);
	/*Check if the found iter is not a dummy.*/
	if(!SortListIsSameIter(find_iter, end_iter))
	{
		SortListRemove(find_iter);
		return ret_data;
	}
	/*If the iter is dummy.*/
	return NULL;
}



