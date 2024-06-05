#include <stdlib.h>/*malloc, free*/
#include <string.h> /*strerro */
#include <errno.h> /*errno*/
#include <stdio.h> /*perror*/
#include <assert.h> /*assert*/

#include "linked_list.h"

#define UNACCESSABLE_ADDRESS 0xDEADBEEF00000000

struct slist_node
{	
	void *data;
	slist_iter_ty next_node;
};

struct slist
{
	slist_iter_ty head_node;
};

/******************************************************************************/
slist_ty *SListCreate()
{
	/*create dummy node and initialize it to NULL*/
	slist_iter_ty dummy_iter = NULL;
	/*create slist and allocate memory for it*/
	slist_ty *slist = (slist_ty*)malloc(sizeof(slist_ty));
	
	/*check if allocation failed*/
	if(NULL == slist)
	{
		/*print error per errno*/
		perror(strerror(errno));
		
		/*return NULL*/
		return NULL;
	}	
	
	dummy_iter = (slist_iter_ty)malloc(sizeof(slist_node_ty));
	
	if(NULL == dummy_iter)
	{
		/*print error per errno*/
		perror(strerror(errno));
		/*free the slist*/
		free(slist);
		/*set slist to NULL*/
		slist = NULL;
		
		/*return NULL*/
		return NULL;
	}
	
	/*init dummy node data to unaccessable address*/
	dummy_iter->data = (void*)UNACCESSABLE_ADDRESS;
	/*init dummy node next node to NULL*/
	dummy_iter->next_node = NULL;
	
	/*set slist head node to dummy_node*/
	slist->head_node = dummy_iter;

	/* slist - if allocation failed it will be NULL */
	return slist;
}

/******************************************************************************/
void SListDestroy(slist_ty *list)
{
	/*create new iter and set the head of list into it*/
	slist_iter_ty iter = list->head_node;
	/*craete temp iter and set it to NULL */
	slist_iter_ty iter_temp = NULL;
	
	/*loop while the data of iter is not unaccessable which means dummy*/
	while((void*)UNACCESSABLE_ADDRESS != iter->data)
	{
		/*set iter next node  address into iter temp before free*/
		iter_temp = iter->next_node;
		/*free the iter*/
		free(iter);
		/*update the iter next iter to iter temp*/
		iter = iter_temp; 
	}
	/*free iter and set it to NULL */
	free(iter);
	iter= NULL;
	/* free list and set it to NULL */
	free(list);
	list = NULL;
}

/******************************************************************************/
slist_iter_ty SListInsert(slist_iter_ty iterator, void *data)
{
	/*create a new iter and initilize it to NULL*/
	slist_iter_ty new_iter = NULL;

	/*allocate new node and set it into new iter */
	new_iter = (slist_iter_ty)malloc(sizeof(slist_node_ty));
	
	/*check if allocation failed*/
	if( NULL == new_iter)
	{
		/*print error per errno*/
		perror(strerror(errno));
		/*set new_iter to NULL*/
		new_iter = NULL;
		/*return 1 (failed)*/
		return NULL;
	}
	
	/* assign iterator data into new iter */
	new_iter->data = iterator->data;
	/* assign iterator next node into new iter next node */
	new_iter->next_node = iterator->next_node;
	/*assign into iterator the gived data as param*/
	iterator->data = data;
	/*assign new_iter into iterator next node*/
	iterator->next_node = new_iter;
	
	/*return the inserted iterator*/
	return iterator;
}

/******************************************************************************/
slist_iter_ty SListRemove(slist_iter_ty iterator)
{
	/*create iter and initilize it to NULL*/
	slist_iter_ty next_iter = NULL;
	
	/*check if the iterator is not dummy node*/
	if((void*)UNACCESSABLE_ADDRESS == iterator->data)
	{
		/*return NULL for fail - can;t remove dummy node*/
		return NULL;
	}
	
	/*set next_iter to be the next node of iterator*/
	next_iter = iterator->next_node;
	/*assign into iterator data the data of next_iter*/
	iterator->data = next_iter->data;
	/*assign into iterator next_node the next node of next_iter*/
	iterator->next_node = next_iter->next_node;
	/*update iterator to be the next node in list*/
	/*free next iter */
	free(next_iter);
	/*set next_iter to NULL*/
	next_iter = NULL;
	
	/*return iterator for success*/
	return iterator;	
}

/******************************************************************************/
slist_iter_ty SListFind(const slist_iter_ty from, const slist_iter_ty to,
				 					  is_match_func_ty match_func, void *param)
{
	/*create iter and initilize it to NULL*/
	slist_iter_ty iter = from;
	
	/*loop while iter is not equal to to*/
	while(iter != to)
	{
		/*check if is there is a macth with current iter*/
		if (match_func(iter->data, param))
		{
			/*return iter in case of success*/
			return iter;
		}
		
		/*update iter to point to the next node*/
		iter = iter->next_node;
	}
	
	/*return iter in case of failure to find a match */
	return iter;
}
				   
/******************************************************************************/
int SListForEach(const slist_iter_ty from, const slist_iter_ty to,
					   						 action_func_ty func, void *param)
{
	/*create iter and initilize it to NULL*/
	slist_iter_ty iter = from;
	/*create a res var of action_func_ty and initilize it to zero*/
	int action_res_counter = 0;

	/*loop while iter is not equal to to*/
	while(iter != to)
	{
		/*update action_res val by invoking func*/
		action_res_counter += (func(iter->data, param));
		/*update iter to point to the next node*/
		iter = iter->next_node;
	}
	
	/*check if at least one action has failed*/
	if(0 != action_res_counter)
	{
		/*return 1 for fail*/
		return 1;
	}
	
	/*return zero for success */
	return 0;
}

/******************************************************************************/
slist_iter_ty SListBegin(const slist_ty *list)
{	
	/*assert for null list */
	assert(list);
	
	/*return head_node*/
	return list->head_node;
}

/******************************************************************************/
slist_iter_ty SListEnd(const slist_ty *list)
{
	/*create new iter and set the head into it*/
	slist_iter_ty iter = list->head_node;
	
	/*assert for null list */
	assert(list);
	
	/*loop while the data of iter is not unaccessable which means dummy*/
	while((void*)UNACCESSABLE_ADDRESS != iter->data)
	{
		/*update the iter next iter to iter temp*/
		iter = iter->next_node; 
	}
	
	return iter;
}

/******************************************************************************/
slist_iter_ty SListNext(const slist_iter_ty iterator)
{
	/*assert for dummy node*/
	assert((void*)UNACCESSABLE_ADDRESS != iterator->data);
	
	/*return the next iter*/
	return iterator->next_node;
}

/******************************************************************************/
int SListIterIsEqual(const slist_iter_ty iterator1,
												const slist_iter_ty iterator2)
{
	/*assert for iterator1*/
	assert(iterator1);
	/*assert for iterator2*/
	assert(iterator2);	
	
	/*check if both iterators are pointing to the same node*/
	if( iterator1 == iterator2)
	{
		/*return 1 for success*/
		return 1;
	}
		
	/*return 0 for failure*/
	return 0;
}

/******************************************************************************/
void *SListGetData(const slist_iter_ty iterator)
{
	/*assert for dummy node*/
	assert((void*)UNACCESSABLE_ADDRESS != iterator->data);
	
	/*return the data of the iterator*/
	return iterator->data;
}

/******************************************************************************/
void SListSetData(slist_iter_ty iterator, void *data)
{
	/*assert for dummy node*/
	assert((void*)UNACCESSABLE_ADDRESS != iterator->data);
	
	/*set the given data into data of iter*/
	iterator->data = data;
}

/******************************************************************************/
size_t SListCount(const slist_ty *list)
{
	/*create new iter and set the head into it*/
	slist_iter_ty iter = list->head_node;
	/*create new counter and initilize it to zero */
	size_t counter = 0;
	
	/*assert for null list */
	assert(list);
	
	/*loop while the data of iter is not unaccessable which means dummy*/
	while((void*)UNACCESSABLE_ADDRESS != iter->data)
	{
		/*incremement counter by one*/
		++counter;
		/*update the iter next iter to iter temp*/
		iter = iter->next_node; 
	}
	
	return counter;
}

/******************************************************************************/
slist_ty *SListAppend(slist_ty *list_1, slist_ty *list_2)
{
	/*create end_list1_iter and set it to dummy node using helper function*/
	slist_iter_ty end_list1_iter = SListEnd(list_1);
	/*set head node data of list2 into dummy data of list1*/
	end_list1_iter->data = list_2->head_node->data;
	/*set head node next node of list2 into dummy next node of list1*/
	end_list1_iter->next_node = list_2->head_node->next_node;
	/*set into head node data of list2 unaccessable pointer*/
	list_2->head_node->data = (void*)UNACCESSABLE_ADDRESS;
	/*set into head node next node of list2 NULL*/
	list_2->head_node->next_node = NULL;
	
	/*return list_1*/
	return list_1;
}
#if 0
/*******************************************************************************
 * Project: Data Structures - Linked List
 * Date: 11/08/22
 * Name: karam Aamar
 * Reviewer: dana shapso
 * Version: 2.0 -SListInsert implemntation was updated as return value changed
 	        -SListRemove implemntation was updated as return value changed
 		-SlistAppend function added 				
*******************************************************************************/
#include <stdio.h>  /* print */
#include <assert.h> /* NULL pointers check */
#include <stdlib.h> /* allocation */
#include <string.h> /* memcpy strerror */
#include <errno.h>  /* errno perror */
/*****************************************************************************/
#include "linked_list.h"
/*****************************************************************************/
struct slist
{
	/* (slist_iter_ty) the type is ptr to slist_node_ty */
	slist_iter_ty head_node; 
	/* ptr to struct node - typedef "slist_node_ty*" slist_iter_ty; */ 
};

struct slist_node
{
	void * data;
	slist_node_ty * next_node;
};
/*****************************************************************************/
slist_ty *SListCreate()
{
	/*create dummy node and initialize it to NULL*/
	slist_iter_ty dummy_node = NULL;
	
	/*Allocate memory for linked list (struct slist/slist_ty)*/
	slist_ty *list = (slist_ty*)malloc(sizeof(slist_ty));
	
	/*check if allocation failed*/
	if(NULL == list)
	{
		/*print error per errno*/
		perror(strerror(errno));
		
		/*return NULL*/
		return NULL;
	}	

	/*Allocate memory for dummy node - last node in the list*/
        dummy_node = (slist_iter_ty)malloc(sizeof(slist_node_ty));
	
	if(NULL == dummy_node)
	{
		/*print error per errno*/
		perror(strerror(errno));
		/*free the slist*/
		free(list);
		/*set slist to NULL*/
		list = NULL;
		
		/*return NULL*/
		return NULL;
	}
	
	/*init dummy node data to unaccessable address*/
	dummy_node->data = (void*)0xDEADBEEF;
	/* *(unsigned int *)&dummy_node -> data = 0xDEADBEEF;*/
	
	/*Set dummy - point to NULL*/
	dummy_node -> next_node = NULL;
	
	/*Initialize the header to point to the dummy node.*/
	list -> head_node = dummy_node;
	
	/*Return a pointer of the head*/
	return list; 
}
/*****************************************************************************/
void SListDestroy(slist_ty *list)
{
	/*point to the head*/
	slist_iter_ty iter_curr_node = list->head_node; 
	
	/*temp iter to hold the node to be free*/
	slist_iter_ty temp = NULL;
	
	/*loop & free the list*/
	while((void*)0xDEADBEEF != iter_curr_node->data)
	{
		temp = iter_curr_node->next_node;
		free(iter_curr_node);
		iter_curr_node = temp;
		
	}
	/*Free dummy node*/
	free(iter_curr_node);
	
	/*Free the pointer to the linked list*/
	free(list);
	
	/* free list and set it to NULL */
	list = NULL;
}
/*****************************************************************************/
slist_iter_ty SListInsert(slist_iter_ty iterator, void *data)
{
	/*create new node and initialize it to NULL*/
	slist_iter_ty new_node = NULL;
	
	/*dynamic allocation for the new node*/
	new_node = (slist_iter_ty)malloc(sizeof(slist_node_ty));

	/*check if the malloc worked*/
	if (NULL == new_node)
	{
		perror(strerror(errno));
		
		return NULL;
	}
	
	/*copy the old iterator in the new place*/
	new_node->data = iterator->data;
	new_node->next_node = iterator->next_node;
	
	/*set the new iterator in the old space*/
	iterator->data = data;
	iterator->next_node = new_node;
	
	/*return the inserted iterator*/
	return iterator;

}
/*****************************************************************************/
slist_iter_ty SListRemove(slist_iter_ty iterator)
{
	/*create temp node and initilize to next node */
 	slist_iter_ty temp_node_remove = iterator->next_node;

	/*check if it's a dummy node*/
	if((void*)0xDEADBEEF == iterator->data)
	{
		
		return NULL;
	}
	
	/*copy next to current*/
	iterator->data = iterator->next_node->data;
	
	/*point to the next node of the next one*/
	iterator->next_node = iterator->next_node->next_node;
	
	/*free next*/
	free(temp_node_remove);
	
	/* free temp node and set it to NULL */
	temp_node_remove = NULL; 
	
	/*return the iterator*/
	return iterator;
}
/*****************************************************************************/
slist_iter_ty SListFind(const slist_iter_ty from, const slist_iter_ty to,
				   is_match_func_ty match_func, void *param)
{	
	/*Set a runner*/
	slist_iter_ty iterator = from;
	
	/*loop while iter is not equal to to*/
	while(iterator != to)
	{
		/*check if is there is a macth with current iter*/
		if(match_func(iterator->data, param))
		{
			/*return iter in case of success*/
			return iterator;
		}
		/*update iter to point to the next node*/
		iterator = iterator->next_node;
	}
	/* return iter in case of failure to find a match */
	return to;
}
/*****************************************************************************/
int SListForEach(const slist_iter_ty from, const slist_iter_ty to,action_func_ty
                                                             func, void *param)
{	/*Set a runner & initialize it with from*/
	slist_iter_ty iterator = from;
	
	/* status if works or not*/
	int status = 0;
	
	/*loop while iter is not equal to to*/
	while(iterator != to)
	{
		/*check return value from the function*/
		status = func(iterator->data,param);
		
		/*check if workeded*/
		if (status)
		{
			/*retrun success*/
			return status;
		}
		/*move to next node*/
		iterator = iterator->next_node;
	}
	/*return status*/
	return status;
}				  					 			   
/*****************************************************************************/
		
slist_iter_ty SListBegin(const slist_ty *list)
{
	/*assert for null list */
	assert(list);
	
	/*return head_node*/
	return list->head_node;
}
/*****************************************************************************/
slist_iter_ty SListEnd(const slist_ty *list)
{
	/*Point to the head of the list.*/
	slist_iter_ty node = list->head_node;
	
	/*create new iter point to node */
	slist_iter_ty tmp_node = node;
	
	/*assert for null list */
	assert(list);
	
	/*Iterate until dummy node has been reached.*/
	while(node->next_node->next_node)
	{	
		/*move to next node */
		node = node->next_node;
		tmp_node = node;
	}
	/*return the last node.*/
	return tmp_node;
}
/*****************************************************************************/
slist_iter_ty SListNext(const slist_iter_ty iterator)
{
	/*assert*/
	assert((void*)0xDEADBEEF != iterator->data);
	
	/*return the next iter*/
	return iterator -> next_node; 
}
/*****************************************************************************/
int SListIterIsEqual(const slist_iter_ty iterator1,
						const slist_iter_ty iterator2)
{
	/*assert for iterator1*/
	assert(iterator1);
	
	/*assert for iterator2*/
	assert(iterator2);
	
	/*return if equals iterators*/   
	return (iterator1 == iterator2);
}
/*****************************************************************************/
void *SListGetData(const slist_iter_ty iterator)
{
	/*return the data of the iterator*/
	return iterator->data;
}
/*****************************************************************************/
void SListSetData(slist_iter_ty iterator, void *data)
{
	assert((void*)0xDEADBEEF != iterator->data);
	
	/*set the data of the sent iterator*/
	iterator->data = data;
}
/*****************************************************************************/
size_t SListCount(const slist_ty *list)
{
	slist_iter_ty head_list = list->head_node;
	
	size_t count = 0;
	
	assert(list);
	
	while(head_list->next_node)
	{
		head_list = head_list->next_node;
		++count;
	}	
	return count;

}
/*****************************************************************************/	
slist_ty *SListAppend(slist_ty *list_1, slist_ty *list_2)
{
	/*runner for list*/
	slist_iter_ty runner = list_1->head_node;

	assert(list_1);
	assert(list_2);
	
	/*Loop till end of list_1*/
	while(NULL != runner->next_node->next_node)
	{
		runner = runner->next_node;
	}
	
	/*Append list_2 to end of list_1*/
	runner->next_node = list_2->head_node;
	
	return list_1;
}
/*****************************************************************************/	
        /*
	printf("%d\n",*(int*)SListEnd(list_1)->data);
	printf("k%d\n",*(int*)SListGetData(list_2->head_node));
        ===================
   
	dlist_iter_ty current_iter = from;
	
	
	dlist_iter_ty return_iter = dest;
	
	
	
	dlist_iter_ty dest_iter_prev = NULL;
	dlist_iter_ty dest_iter_next = NULL;
	
	assert(from);
	assert(to);
	assert(dest);
	
	
	while(current_iter != to)
	{
		
		
		dest_iter_prev = current_iter->prev_node;
		dest_iter_next = current_iter->next_node;
		dest_iter_prev->next_node = dest_iter_next;
		dest_iter_next->prev_node=dest_iter_prev;
		
		DListInsert(dest, DListGetData(current_iter));
		
		(dest->next_node)->prev_node = current_iter;
		dest->next_node = current_iter;
		
		
		current_iter = current_iter->next_node;	
			
	}
	return return_iter; */
	
	


#endif