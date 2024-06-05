/*******************************************************************************

*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>/*perror*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include <string.h>/*strerro*/
#include <errno.h>/*errno*/
/******************************************************************************/
#include "sorted_list.h"
#include "dlinked_list.h"
/******************************************************************************/
#define DLIST_TO_SORT(dlist) (sort_list_iter_ty)dlist
#define SORT_TO_DLIST(sort_list) (dlist_iter_ty)sort_list
/******************************************************************************/
enum compare {LIST2_BIGGER_THAN_LIST1_ELEM = -1, EQUAL_ELEMS, 
									              LIST1_BIGGER_THAN_LIST2_ELEM};
typedef enum compare compare_elems_ty;
/******************************************************************************/
struct sort_list
{
	dlist_ty *dlist;
	compare_ty cmp_ptr;
};

struct param_str
{
	compare_ty compare_func;
	void *data;
};

typedef struct param_str param_ty;

static int BuiltInCompare(void *list_data, void *param);
/******************************************************************************/
sort_list_ty *SortListCreate(compare_ty compare_func)
{
	sort_list_ty *list = NULL;

	assert(compare_func);

	list = (sort_list_ty*)malloc(sizeof(sort_list_ty));
	if(NULL == list)
	{
		perror(strerror(errno));
		return NULL;
	}
	/*Allocate memory for the dlist.*/
	list->dlist = DListCreate();
	list->cmp_ptr = compare_func;
	/*Return the create list.*/
	return list;
}
/******************************************************************************/
void SortListDestroy(sort_list_ty *list)
{	
	assert(list);
	/*USe the Dlist Destroy*/
	DListDestroy(list->dlist);
	free(list);
}
/******************************************************************************/
sort_list_iter_ty SortListInsert(sort_list_ty *list, void *data)
{
	/*Point to the first iter of the created dlist.*/
	sort_list_iter_ty iter = SortListBegin(list);
	sort_list_iter_ty end_dummy = SortListEnd(list);
	/*Set a function pointer to the compare function.*/
	compare_ty cmp_ptr = list->cmp_ptr;

	
	assert(list);
	
	/*while node's data is smaller than iter's data*/
	while(!SortListIsSameIter(iter, end_dummy))
	{
	
		if(EQUAL_ELEMS < cmp_ptr(SortListGetData(iter), data))
		{
			return DLIST_TO_SORT(DListInsert(SORT_TO_DLIST(iter), data));
		}
		
		iter = SortListNext(iter);
	}
	/*Insert the node and return it's node.*/
	
	return DLIST_TO_SORT(DListInsert(SORT_TO_DLIST(iter), data));
	
}
/******************************************************************************/
sort_list_iter_ty SortListRemove(sort_list_iter_ty iter)
{
	/*Remove by using DList remove.*/
	return DLIST_TO_SORT(DListRemove(SORT_TO_DLIST(iter)));
}
/******************************************************************************/
size_t SortListSize(const sort_list_ty *list)
{
	/*Get size by using DLsize.*/
	return DListSize(list->dlist);
}
/******************************************************************************/
int SortListIsEmpty(const sort_list_ty *list)
{
	/*Check if empty by DList is empty function.*/
	return	DListIsEmpty(list->dlist);
}
/******************************************************************************/
void *SortListPopFront(sort_list_ty *list)
{
	/*pop front by using DList Pop front*/
	return DListPopFront(list->dlist);	
}
/******************************************************************************/
void *SortListPopBack(sort_list_ty *list)
{
	/*pop back by using DList Pop front*/
	return DListPopBack(list->dlist);
}
/******************************************************************************/
sort_list_iter_ty SortListBegin(const sort_list_ty *list)
{
	/*Return Begin of dlist*/
	return DLIST_TO_SORT(DListBegin(list->dlist));
}
/******************************************************************************/
sort_list_iter_ty SortListEnd(const sort_list_ty *list)
{
	/*Return End of dlist*/
	return DLIST_TO_SORT(DListEnd(list->dlist));
}
/******************************************************************************/
sort_list_iter_ty SortListNext(sort_list_iter_ty curr)
{
	/*Return next of curr iter*/
	return DLIST_TO_SORT(DListNext(SORT_TO_DLIST(curr)));
}
/******************************************************************************/
sort_list_iter_ty SortListPrev(sort_list_iter_ty curr)
{
	/*Return prev of curr iter*/
	return DLIST_TO_SORT(DListPrev(SORT_TO_DLIST(curr)));
}
/******************************************************************************/
int SortListIsSameIter(sort_list_iter_ty iter_1, sort_list_iter_ty iter_2)
{
	/*Check if two iters points to the same iter (by using DList's func)*/
	return DListIsSameIter(SORT_TO_DLIST(iter_1), SORT_TO_DLIST(iter_2));
}
/******************************************************************************/
void *SortListGetData(sort_list_iter_ty iter)
{
	/*Get data by using DList get data.*/
	return DListGetData(SORT_TO_DLIST(iter));
}
/******************************************************************************/
int SortListForEach(sort_list_iter_ty from, sort_list_iter_ty to, 
									    action_func_ty action_func, void *param)
{
	/*Perform DListForEach by using DList's ForEach function.*/
	return DListForeach(SORT_TO_DLIST(from), SORT_TO_DLIST(to), 
												 (action_ty)action_func, param);
}
/******************************************************************************/
sort_list_ty *SortListMerge(sort_list_ty *list_1, sort_list_ty *list_2)
{
	/*Set runners to point on the lists.*/
	sort_list_iter_ty dest = SortListBegin(list_1);
	sort_list_iter_ty src_from = SortListBegin(list_2);
	sort_list_iter_ty src_to = SortListBegin(list_2);
	/*Set function pointer.*/
	compare_ty cmp_func = list_1->cmp_ptr;

	/*Run over the lists until the end of both lists has been reached.*/
	while(SortListNext(src_from) && SortListNext(dest))
	{
		/*Compare between nodes and copy by splicing if it's possible.*/
		if(LIST2_BIGGER_THAN_LIST1_ELEM >= cmp_func(SortListGetData(dest)
											       , SortListGetData(src_from)))
		{
			dest = SortListNext(dest);		
		}
		
		else
		{
			while(SortListNext(src_to) &&
			 (EQUAL_ELEMS <= cmp_func(SortListGetData(dest), 
			                                          SortListGetData(src_to))))
			{	

				src_to = SortListNext(src_to);
			}
			DListSplice(SORT_TO_DLIST(src_from), SORT_TO_DLIST(src_to)
														  , SortListPrev(dest));
										             
		}
		src_from = src_to;
	}
	/*If list 2 is not empty and dest runner has reached the end.*/
	if(!SortListIsEmpty(list_2))
	{
		DListSplice(SORT_TO_DLIST(src_from), SORT_TO_DLIST(SortListEnd(list_2)),
											 SORT_TO_DLIST(SortListPrev(dest)));
	}
	return list_1;
}
/******************************************************************************/
sort_list_iter_ty SortListFind(sort_list_ty *list, sort_list_iter_ty from, 
									   sort_list_iter_ty to, void *data_to_find)
{
	param_ty param_str;
	param_str.compare_func = list->cmp_ptr;
	param_str.data = data_to_find;
	
	return SortListFindIf(from, to, BuiltInCompare, &param_str);
}
/******************************************************************************/
sort_list_iter_ty SortListFindIf(sort_list_iter_ty from, 
				   sort_list_iter_ty to, is_match_func_ty is_match, void *param)
{
	/*Use DListFind by using the is_match cmp function.*/
	match_ty is_match1 = (match_ty) is_match;
	return DLIST_TO_SORT(DListFind(SORT_TO_DLIST(from), SORT_TO_DLIST(to)
														   , is_match1, param));
}
/******************************************************************************/
static int BuiltInCompare(void *list_data, void *param)
{

	param_ty *param_str = (param_ty *)param; 
	
	return (param_str->compare_func(list_data, param_str->data) == 0) ? 1 : 0;	
}

