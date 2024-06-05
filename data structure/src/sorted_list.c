/*******************************************************************************
 * Project: Data Structures - sorted list
 * Date: 18/08/22
 * Name: karam aamar
 * Reviewer: idan
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>  /* prints , perror */
#include <assert.h> /* aseert */
#include <stdlib.h> /* malloc , free */
#include <string.h> /* strerror */
#include <errno.h>  /* errno */
/******************************************************************************/
#include "sorted_list.h"
#include "dlist.h"
/******************************************************************************/
#define DLIST_TO_SORT(dlist) (sort_list_iter_ty)dlist
#define SORT_TO_DLIST(sort_dlist) (dlist_iter_ty)sort_dlist /* phizit its work without it because same itter for now */
/******************************************************************************/
struct sort_list 
{
	dlist_ty *d_list;
	compare_ty compare; 
};
/******************************************************************************/
sort_list_ty *SortListCreate(compare_ty compare_func)
{
	/* define new sorted list */
	sort_list_ty *sorted_list = NULL;
	
	/* dynamically allocate sorted list*/
	sorted_list = (sort_list_ty *)malloc(sizeof(sort_list_ty));
	
	assert(compare_func);
	
	/* init sorted list */
	sorted_list -> d_list = DListCreate();
	sorted_list -> compare = compare_func;
	
	return sorted_list;
}
/******************************************************************************/
void SortListDestroy(sort_list_ty *list)
{
	assert(list);
	
	DListDestroy(list->d_list);
	
	free(list);
}
/******************************************************************************/
sort_list_iter_ty SortListInsert(sort_list_ty *list, void *data)
{
	/* define iter for dlist */
	dlist_iter_ty curr_iter = NULL;
	
	/* define return ptr */
	sort_list_iter_ty return_sorted_iter = NULL;
	
	assert(list);
	
	/* set to first iter in dlist */
	curr_iter = DListBegin(list->d_list);
	
	
	/* loop untill last dummy or untill success */
	while(curr_iter != DListEnd(list->d_list))
	{
		/* if we have 1 or zero which means success for insert */
		if(-1 != list->compare(DListGetData((curr_iter)),data))
		{	
			/* insert the value */
			return_sorted_iter = DLIST_TO_SORT(SORT_TO_DLIST(DListInsert(curr_iter,data)));
			
			return return_sorted_iter;
				
		}
		/* move to next node */
		curr_iter = DListNext(curr_iter);	
	}
	/* insert before dummy */
	return_sorted_iter = DLIST_TO_SORT(DListInsert(SORT_TO_DLIST(curr_iter),data));
	
	return return_sorted_iter;
}
/******************************************************************************/
sort_list_iter_ty SortListRemove(sort_list_iter_ty iter)
{
	assert(iter);
	
	iter = DLIST_TO_SORT(DListRemove(SORT_TO_DLIST(iter)));
	return iter;
}
/******************************************************************************/
size_t SortListSize(const sort_list_ty *list)
{
	assert(list);
	
	return DListSize(list->d_list);
}
/******************************************************************************/
int SortListIsEmpty(const sort_list_ty *list)
{
	assert(list);
	
	return DListIsEmpty(list->d_list);
}
/******************************************************************************/
void *SortListPopFront(sort_list_ty *list)
{
	assert(list);
	
	return DListPopFront(list->d_list);
}
/******************************************************************************/
void *SortListPopBack(sort_list_ty *list)
{
	assert(list);
	
	return DListPopBack(list->d_list);
}
/******************************************************************************/
sort_list_iter_ty SortListBegin(const sort_list_ty *list)
{
	assert(list);
	
	return DLIST_TO_SORT(DListBegin(list->d_list));
}

/******************************************************************************/
sort_list_iter_ty SortListEnd(const sort_list_ty *list)
{
	assert(list);
	
	return DLIST_TO_SORT(DListEnd(list->d_list));
}
/******************************************************************************/
sort_list_iter_ty SortListNext(sort_list_iter_ty curr)
{
	return DLIST_TO_SORT(DListNext(SORT_TO_DLIST(curr)));
}
/******************************************************************************/
sort_list_iter_ty SortListPrev(sort_list_iter_ty curr)
{
	return DLIST_TO_SORT(SORT_TO_DLIST(DListPrev(curr)));
}
/******************************************************************************/
int SortListIsSameIter(sort_list_iter_ty iter_1, sort_list_iter_ty iter_2)
{
	return DListIsSameIter(SORT_TO_DLIST(iter_1), SORT_TO_DLIST(iter_2));
}

/******************************************************************************/
void *SortListGetData(sort_list_iter_ty iter)
{
	return DListGetData(SORT_TO_DLIST(iter));
}
/******************************************************************************/
int SortListForEach(sort_list_iter_ty from, sort_list_iter_ty to, 
					action_func_ty action_func, void *param)
{
	assert(action_func);
	
	return DListForeach(SORT_TO_DLIST(from) , SORT_TO_DLIST(to) , (action_ty)action_func, param);
}
/******************************************************************************/
sort_list_ty *SortListMerge(sort_list_ty *list_1, sort_list_ty *list_2)
{
	sort_list_iter_ty curr_iter_list1 = NULL;	
		
	sort_list_iter_ty from_list2 = NULL;
	sort_list_iter_ty to_list2 = NULL;
	
	assert(list_1);
	assert(list_2);
	
	/* set iters to first nodes */ 
	curr_iter_list1 = SortListBegin(list_1);
	
	from_list2 = SortListBegin(list_2);
	to_list2 = SortListNext(SortListBegin(list_2));
	
	/* loop untill the end of one of the lists */ 
	while(!SortListIsSameIter(curr_iter_list1,SortListEnd(list_1)) && !      
	                SortListIsSameIter(from_list2,SortListEnd(list_2)))
	{
		/* if the value of dest(list1) bigger then check more values
						 in the range of list 2*/ 
		if(1 == list_1->compare(SortListGetData(curr_iter_list1),
					           SortListGetData(from_list2)))
                {
                   /* enter while the value in dest bigger than value in src */ 
                  while(!SortListIsSameIter(curr_iter_list1,SortListEnd(list_1)) 
                             && list_1->compare(SortListGetData(curr_iter_list1)
                             			    ,SortListGetData(to_list2)))
                                  {
                                  	to_list2 = SortListNext(to_list2);
                                  	
                                  	/* check if we got to the end */
                                  	if(SortListIsSameIter(to_list2,
                                  			  SortListEnd(list_2)))
                                  	{
                                  		break;
                                  	}
                                  }
                                  /* send to splice from to to */
                		  DListSplice(SORT_TO_DLIST(from_list2),
                		  			SORT_TO_DLIST(to_list2),
                		  		 SortListPrev(curr_iter_list1));
                  		  /* update from */
                 		  from_list2 = to_list2;
                }
                /* next node of from */
		to_list2 = SortListNext(from_list2);
		curr_iter_list1 = SortListNext(curr_iter_list1);
	}
	
	if( 1 != SortListIsSameIter(from_list2,SortListEnd(list_2)))
	{
		DListSplice(SORT_TO_DLIST(from_list2),SORT_TO_DLIST(to_list2),SortListPrev(curr_iter_list1));
        }
        return list_1;
}
/******************************************************************************/
sort_list_iter_ty SortListFind(sort_list_ty *list, 
                sort_list_iter_ty from,sort_list_iter_ty to, void *data_to_find)
{
	/* set iter to from (the range we have) */
	sort_list_iter_ty iter_runner = from;
	
	/* assert-check we are not in the end */
	assert(from != SortListEnd(list));
	
	/*loop from "from" to "to" */
	while(iter_runner != to)
	{
		/* check if equals by the cretira-returns zero if equals */
	      if(0 == list->compare(SortListGetData(iter_runner), data_to_find))
	      {
			
			return iter_runner;
	      }
		/* move to next node */ 
		iter_runner = SortListNext(iter_runner);
	}
	return to;
}		
/******************************************************************************/
sort_list_iter_ty SortListFindIf(sort_list_iter_ty from, 
		 sort_list_iter_ty to, is_match_func_ty is_match, void *param)
{
	sort_list_iter_ty runner = from;

	assert(is_match);

	while(runner != to)
	{
		if(is_match(SortListGetData(runner), param))
		{
			return runner;
		}

		runner = SortListNext(runner);
	}
	return to;
}
/******************************************************************************/
