/*******************************************************************************
 * Project: Data Structures - DList
 * Date: 18/08/22
 * Name: karam
 * Reviewer: shirley
 * Version: 1.0 
 * Version: 1.1 - Fixed minor typos
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>/*perror*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include <string.h>/*strerro*/
#include <errno.h>/*errno*/

#include "dlist.h"
/******************************************************************************/
static dlist_iter_ty DListFindTail(dlist_iter_ty iter);
/******************************************************************************/
enum STATUS {SUCCESS = 0, FAIL};
typedef enum STATUS status_ty;
/******************************************************************************/
/*The pointer to linked list head and tail.*/
struct dlist 
{
	dlist_iter_ty head;
	dlist_iter_ty tail;
};
/*A struct which represents a node of a linked-list.*/
struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
};
/******************************************************************************/
dlist_ty *DListCreate(void)
{
	/*Allocate memory for dlist allocate memory for the linked list "head"*/
	dlist_ty *list = NULL;
	dlist_iter_ty head_dummy = NULL;
	dlist_iter_ty tail_dummy = NULL;
	/*Create a new linked list.*/
	list = (dlist_ty*)malloc(sizeof(dlist_ty));
	if(NULL == list)
	{
		perror(strerror(errno));
		list = NULL;
		return NULL;
	}
	/*Allocate memory for the head dummy node*/
	head_dummy = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	
	if(NULL == head_dummy)
	{
		free(list);
		perror(strerror(errno));
		list = NULL;
		return NULL;
	}
	
	/*Allocate memory for the tail dummy node*/
	tail_dummy = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	
	if(NULL == tail_dummy)
	{
		free(list);
		free(head_dummy);
		perror(strerror(errno));
		list = NULL;
		head_dummy = NULL;
		return NULL;
	}
	/*Set dummy nodes..*/
	head_dummy->data = (void *)0xDEADBEEF;
	head_dummy->next = tail_dummy;
	head_dummy->prev = NULL;
	tail_dummy->data = (void *)0xDEADBEEF;
	tail_dummy->prev = head_dummy;
	tail_dummy->next = NULL;
	list->head = head_dummy;
	list->tail = tail_dummy;
	/*Return a pointer of the head*/
	return list; 
}
/******************************************************************************/
void DListDestroy(dlist_ty *list)
{
	/*Set pointer to the head.*/
	dlist_iter_ty iter = list->head; 
	dlist_iter_ty temp = NULL;
	
	assert(list);
	/*Destory sequence of all link list's nodes.*/
	while(iter)
	{
		temp = iter;
		iter = iter->next;
		free(temp);
	}
	/*Free the pointer to the linked list*/
	free(list);	
}
/******************************************************************************/
size_t DListSize(const dlist_ty *list)
{
	dlist_iter_ty head = DListNext(list->head);
	size_t count = 0;
	
	assert(list);
	/*Count nodes within the link list.*/
	while(head->next)
	{
		head = head->next;
		++count;
	}	
	return count;
}
/******************************************************************************/
int DListIsEmpty(const dlist_ty *list)
{
	assert(list);
	return NULL == DListNext(DListNext(list->head));	
}
/******************************************************************************/
dlist_iter_ty DListBegin(const dlist_ty *list)
{
	assert(list);
	/*Return the head pointer.*/
	return DListNext(list->head);
}
/******************************************************************************/
dlist_iter_ty DListEnd(const dlist_ty *list)
{
	assert(list);
	/*Return the last node.*/
	return list->tail;
}
/******************************************************************************/
dlist_iter_ty DListNext(dlist_iter_ty curr)
{
	assert(curr);
	/*Return the next pointed node.*/
	return curr->next;
}
/******************************************************************************/
dlist_iter_ty DListPrev(dlist_iter_ty curr)
{
	assert(curr);
	/*Return the prev pointed node.*/
	return curr->prev;
	
}
/******************************************************************************/
int DListIsSameIter(dlist_iter_ty iter_1, dlist_iter_ty iter_2)
{
	assert(iter_1);
	assert(iter_2);
	/*Check if iters are the same.*/
	return iter_1 == iter_2;
}
/******************************************************************************/
void *DListGetData(const dlist_iter_ty iter)
{
	/*Return the iters data.*/
	assert(iter);
	return iter->data;
}
/******************************************************************************/
void DListSetData(dlist_iter_ty iter, void *data)
{
	/*Set iter's data.*/
	assert(iter);
	iter->data = data;
}
/******************************************************************************/
dlist_iter_ty DListInsert(dlist_iter_ty iterator, void *data)
{
	/*Allocate memory for a new node*/	
	dlist_iter_ty node = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	assert(data);
	/*If node allocation has failed*/
	if(NULL == node)
	{
		perror(strerror(errno));
		node = NULL;
		return DListFindTail(iterator);
	}
	/*Set the iterator node and it's next node to point on the new inserted node
	.*/
	node->next = iterator;
	(iterator->prev)->next = node;
	node->prev = iterator->prev;
	iterator->prev = node;

	node->data = data;

	return node;
}
/******************************************************************************/
dlist_iter_ty DListRemove(dlist_iter_ty iter)
{
	/*Remove the desired iter.*/
	dlist_iter_ty ret_iter = iter->next;
	(iter->prev)->next = iter->next;
	(iter->next)->prev = iter->prev;
	free(iter);
	
	return ret_iter;
}
/******************************************************************************/
dlist_iter_ty DListPushFront(dlist_ty *list, void *data)
{		
	dlist_iter_ty new_node = DListInsert(DListBegin(list), data);
	
	assert(list);
	
	return new_node;
}
/******************************************************************************/
dlist_iter_ty DListPushBack(dlist_ty *list, void *data)
{
	if (DListIsEmpty(list))
	{
		return DListInsert(DListBegin(list), data);
	}
	
	else
	{
		return DListInsert(DListEnd(list), data);
	}
}
/******************************************************************************/
void *DListPopFront(dlist_ty *list)
{
	void *data = DListGetData(DListBegin(list));
	DListRemove(DListBegin(list));
	
	assert(list);
	
	return data;
}
/******************************************************************************/
void *DListPopBack(dlist_ty *list)
{
	void *data = DListGetData(DListPrev(DListEnd(list)));
	DListRemove(DListPrev(DListEnd(list)));
	
	assert(list);
	
	return data;
}
/******************************************************************************/
int DListForeach(const dlist_iter_ty from, const dlist_iter_ty to,
					    					action_ty action_func, void *param)
{
	dlist_iter_ty iterator = from;
	int status = 0;
	
	assert(from);
	assert(to);
	/*assert(param);*/
	
	/*Iterate through the linked list until "to" is reached.
	  Perform the the set action on each node's data.*/
	while(iterator != to)
	{
		status = action_func(iterator->data, param);
		if (status)
		{
			return status;
		}

		iterator = iterator->next;
	}
	return status;
}
/******************************************************************************/
dlist_iter_ty DListSplice(dlist_iter_ty from, dlist_iter_ty to,
							    							 dlist_iter_ty dest)
{
	dlist_iter_ty splised_head = from;
	dlist_iter_ty temp_iter = NULL;
	dlist_iter_ty node_before_to = DListPrev(to);

	/*Splise the sub linked list between from and to and link dest iter to
	  point on it (and link the last node the splised list to point on
	  the node which comes after dest.*/
	to->prev = DListPrev(splised_head);
	(splised_head->prev)->next = to;
	
	splised_head->prev = dest;

	temp_iter = dest->next;

	dest->next = splised_head;

	temp_iter->prev = node_before_to;
	node_before_to->next = temp_iter;

	return from;
	
}
/******************************************************************************/
dlist_iter_ty DListFind(const dlist_iter_ty from, const dlist_iter_ty to,
					      					   match_ty match_func, void *param)
{
	/*Set a runner*/
	dlist_iter_ty iterator = from;
	assert(from);
	
	assert(to);
	
	assert(match_func);
	
	/*Iterate through the linked list until there is a match.
	  If there is no match, return "to" node.*/
	while(iterator != to)
	{
		if(match_func(iterator->data, param))
		{
			return iterator;
		}
		iterator = iterator->next;
	}
	
	return to;
}
/******************************************************************************/
int DListMultiFind(const dlist_iter_ty from, const dlist_iter_ty to,
			 			  match_ty match_func, void *param, dlist_ty *dest_list)
{
	/*Set a runner*/
	dlist_iter_ty iterator = from;
	status_ty status = FAIL;
	assert(from);
	
	assert(to);
	
	assert(match_func);
	
	/*Iterate through the linked list, if there is a match - add the matched
	node to the new linked list. if there haven't bee even one match - return 
	FAIL, otherwise- return success.*/

	while(iterator != to)
	{
		if(match_func(iterator->data, param))
		{

			DListPushBack(dest_list, iterator->data);	
			
			status = SUCCESS;
		}
		
		iterator = DListNext(iterator);
	}
	
	return status;	
}
/******************************************************************************/
static dlist_iter_ty DListFindTail(dlist_iter_ty iter)
{
	while(iter->next)
	{
		iter = DListNext(iter);
	}
	
	return iter;
}


#if 0
#include <stddef.h> /* size_t */
#include <stdio.h>/*perror*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include <string.h>/*strerro*/
#include <errno.h>/*errno*/

#include "dlist.h"
/******************************************************************************/
static dlist_iter_ty DListFindTail(dlist_iter_ty iter);
/******************************************************************************/
enum STATUS {SUCCESS = 0, FAIL};
typedef enum STATUS status_ty;
/******************************************************************************/
/*The pointer to linked list head and tail.*/
struct dlist 
{
	dlist_iter_ty head;
	dlist_iter_ty tail;
};
/*A struct which represents a node of a linked-list.*/
struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
};
/******************************************************************************/
dlist_ty *DListCreate(void)
{
	/*Allocate memory for dlist allocate memory for the linked list "head"*/
	dlist_ty *list = NULL;
	dlist_iter_ty head_dummy = NULL;
	dlist_iter_ty tail_dummy = NULL;
	/*Create a new linked list.*/
	list = (dlist_ty*)malloc(sizeof(dlist_ty));
	if(NULL == list)
	{
		perror(strerror(errno));
		list = NULL;
		return NULL;
	}
	/*Allocate memory for the head dummy node*/
	head_dummy = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	
	if(NULL == head_dummy)
	{
		free(list);
		perror(strerror(errno));
		list = NULL;
		return NULL;
	}
	
	/*Allocate memory for the tail dummy node*/
	tail_dummy = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	
	if(NULL == tail_dummy)
	{
		free(list);
		free(head_dummy);
		perror(strerror(errno));
		list = NULL;
		head_dummy = NULL;
		return NULL;
	}
	/*Set dummy nodes..*/
	head_dummy->data = (void *)0xDEADBEEF;
	head_dummy->next = tail_dummy;
	head_dummy->prev = NULL;
	tail_dummy->data = (void *)0xDEADBEEF;
	tail_dummy->prev = head_dummy;
	tail_dummy->next = NULL;
	list->head = head_dummy;
	list->tail = tail_dummy;
	/*Return a pointer of the head*/
	return list; 
}
/******************************************************************************/
void DListDestroy(dlist_ty *list)
{
	/*Set pointer to the head.*/
	dlist_iter_ty iter = list->head; 
	dlist_iter_ty temp = NULL;
	
	assert(list);
	/*Destory sequence of all link list's nodes.*/
	while(iter)
	{
		temp = iter;
		iter = iter->next;
		free(temp);
	}
	/*Free the pointer to the linked list*/
	free(list);	
}
/******************************************************************************/
size_t DListSize(const dlist_ty *list)
{
	dlist_iter_ty head = DListNext(list->head);
	size_t count = 0;
	
	assert(list);
	/*Count nodes within the link list.*/
	while(head->next)
	{
		head = head->next;
		++count;
	}	
	return count;
}
/******************************************************************************/
int DListIsEmpty(const dlist_ty *list)
{
	assert(list);
	return NULL == DListNext(DListNext(list->head));	
}
/******************************************************************************/
dlist_iter_ty DListBegin(const dlist_ty *list)
{
	assert(list);
	/*Return the head pointer.*/

	return DListNext(list->head);
	
}
/******************************************************************************/
dlist_iter_ty DListEnd(const dlist_ty *list)
{
	assert(list);
	/*Return the last node.*/
	return list->tail;
}
/******************************************************************************/
dlist_iter_ty DListNext(dlist_iter_ty curr)
{
	assert(curr);
	/*Return the next pointed node.*/
	return curr->next;
}
/***********************************************************************8******/
dlist_iter_ty DListPrev(dlist_iter_ty curr)
{
	assert(curr);
	/*Return the prev pointed node.*/
	return curr->prev;
	
}
/******************************************************************************/
int DListIsSameIter(dlist_iter_ty iter_1, dlist_iter_ty iter_2)
{
	assert(iter_1);
	assert(iter_2);
	/*Check if iters are the same.*/
	return iter_1 == iter_2;
}
/******************************************************************************/
void *DListGetData(const dlist_iter_ty iter)
{
	/*Return the iters data.*/
	assert(iter);
	return iter->data;
}
/******************************************************************************/
void DListSetData(dlist_iter_ty iter, void *data)
{
	/*Set iter's data.*/
	assert(iter);
	iter->data = data;
}
/******************************************************************************/
dlist_iter_ty DListInsert(dlist_iter_ty iterator, void *data)
{
	/*Allocate memory for a new node*/	
	dlist_iter_ty node = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	assert(data);
	/*If node allocation has failed*/
	if(NULL == node)
	{
		perror(strerror(errno));
		node = NULL;
		return DListFindTail(iterator);
	}
	/*Set the iterator node and it's next node to point on the new inserted node
	.*/
	node->next = iterator;
	(iterator->prev)->next = node;
	node->prev = iterator->prev;
	iterator->prev = node;

	node->data = data;

	return node;
}
/******************************************************************************/
dlist_iter_ty DListRemove(dlist_iter_ty iter)
{
	/*Remove the desired iter.*/
	dlist_iter_ty ret_iter = iter->next;
	(iter->prev)->next = iter->next;
	(iter->next)->prev = iter->prev;
	free(iter);
	
	return ret_iter;
}
/******************************************************************************/
dlist_iter_ty DListPushFront(dlist_ty *list, void *data)
{		
	dlist_iter_ty new_node = DListInsert(DListBegin(list), data);
	
	assert(list);
	
	return new_node;
}
/******************************************************************************/
dlist_iter_ty DListPushBack(dlist_ty *list, void *data)
{
	if (DListIsEmpty(list))
	{
		return DListInsert(DListBegin(list), data);
	}
	
	else
	{
		return DListInsert(DListEnd(list), data);
	}
}
/******************************************************************************/
void *DListPopFront(dlist_ty *list)
{
	void *data = DListGetData(DListBegin(list));
	DListRemove(DListBegin(list));
	
	assert(list);
	
	return data;
}
/******************************************************************************/
void *DListPopBack(dlist_ty *list)
{
	void *data = DListGetData(DListPrev(DListEnd(list)));
	DListRemove(DListPrev(DListEnd(list)));
	
	assert(list);
	
	return data;
}
/******************************************************************************/
int DListForeach(const dlist_iter_ty from, const dlist_iter_ty to,
					    					action_ty action_func, void *param)
{
	dlist_iter_ty iterator = from;
	int status = 0;
	
	assert(from);
	assert(to);
	assert(param);
	
	/*Iterate through the linked list until "to" is reached.
	  Perform the the set action on each node's data.*/
	while(iterator != to)
	{
		status = action_func(iterator->data, param);
		if (status)
		{
			return status;
		}

		iterator = iterator->next;
	}
	return status;
}
/******************************************************************************/
dlist_iter_ty DListSplice(dlist_iter_ty from, dlist_iter_ty to,
							    							 dlist_iter_ty dest)
{
	dlist_iter_ty splised_head = from;
	dlist_iter_ty temp_iter = NULL;
	dlist_iter_ty node_before_to = DListPrev(to);

	/*Splise the sub linked list between from and to and link dest iter to
	  point on it (and link the last node the splised list to point on
	  the node which comes after dest.*/
	to->prev = DListPrev(splised_head);
	(splised_head->prev)->next = to;
	
	splised_head->prev = dest;

	temp_iter = dest->next;

	dest->next = splised_head;

	temp_iter->prev = node_before_to;
	node_before_to->next = temp_iter;

	return from;
	
}
/******************************************************************************/
dlist_iter_ty DListFind(const dlist_iter_ty from, const dlist_iter_ty to,
					      					   match_ty match_func, void *param)
{
	/*Set a runner*/
	dlist_iter_ty iterator = from;
	
	assert(from);
	
	assert(to);
	
	assert(match_func);
	
	/*Iterate through the linked list until there is a match.
	  If there is no match, return "to" node.*/
	while(iterator != to)
	{
		if(match_func(iterator->data, param))
		{
			return iterator;
		}
		iterator = iterator->next;
	}
	
	return to;
}
/******************************************************************************/
int DListMultiFind(const dlist_iter_ty from, const dlist_iter_ty to,
			  match_ty match_func, void *param, dlist_ty *dest_list)
{
	/*Set a runner*/
	dlist_iter_ty iterator = from;
	status_ty status = FAIL;
	assert(from);
	
	assert(to);
	
	assert(match_func);
	
	/*Iterate through the linked list, if there is a match - add the matched
	node to the new linked list. if there haven't bee even one match - return 
	FAIL, otherwise- return success.*/

	while(iterator != to)
	{
		if(match_func(iterator->data, param))
		{

			DListPushBack(dest_list, iterator->data);	
			
			status = SUCCESS;
		}
		
		iterator = DListNext(iterator);
	}
	
	return status;	
}
/******************************************************************************/
static dlist_iter_ty DListFindTail(dlist_iter_ty iter)
{
	while(iter->next)
	{
		iter = DListNext(iter);
	}
	
	return iter;
}
#endif	
	

