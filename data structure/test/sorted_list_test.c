/*******************************************************************************
 * Project: Data Structures - sorted list
 * Date: 18/08/22
 * Name: karam aamar
 * Reviewer: idan
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>/*puts*/
/*****************************************************************************/
#include "sorted_list.h"
/*****************************************************************************/
static void ImPlementFunc();
static void CreateSListDestroyTest();
static void SortListInsertTest();
static void SLRemoveSizeTest();/* test of : remove - list size */
static void SLEmptyPopTest(); /* test of : empty - pop back - pop front */
static void SortListForEachTest();
static void SortListMergeTest();
static void SortListFindTest();
int FindBigger(const void *list_data,const void *new_data);
int AddValue(void *data , void *param);
static int CompareData(void *data, void *param);
/*****************************************************************************/
int main()
{
	ImPlementFunc();
	return 0;
}
/*****************************************************************************/
static void ImPlementFunc()
{
	CreateSListDestroyTest();
	SortListInsertTest();
	SLRemoveSizeTest();
	SortListForEachTest();
	SortListMergeTest();
	SortListFindTest();
	SLEmptyPopTest();
}
/*****************************************************************************/
static void CreateSListDestroyTest()
{
	sort_list_ty *new_list = SortListCreate(FindBigger);
	
	if(NULL == new_list)
	{
		puts("Creation Failed");
	}
	
	SortListDestroy(new_list);
	
	new_list = NULL;
}
/*****************************************************************************/
static void SortListInsertTest()
{
	sort_list_ty *new_list = SortListCreate(FindBigger);
	dlist_iter_ty curr_iter = NULL;
	
	int a = 10;
	int b = 20;
	int c = 30; 
	
	int d = 15;
	
	curr_iter = SortListInsert(new_list,&a);
	
	curr_iter = SortListInsert(new_list,&b);
	
	curr_iter = SortListInsert(new_list,&c);
	
	curr_iter = SortListInsert(new_list,&d);
	
	/* 10 -> 20 ->30 */
	
	if(10 != *(int*)DListGetData(DListPrev(curr_iter)) && 20 !=
				    *(int*)DListGetData(DListNext(curr_iter)))
	{
		printf("insert function failed");
	}
}

/*****************************************************************************/
static void SLRemoveSizeTest()
{
	sort_list_ty *new_list = SortListCreate(FindBigger);
	dlist_iter_ty curr_iter = NULL;
	
	int a = 10;
	int b = 20;
	int c = 30; 
	
	curr_iter = SortListInsert(new_list,&a);
	curr_iter = SortListInsert(new_list,&b);
	curr_iter = SortListInsert(new_list,&c);
	


	curr_iter = SortListRemove(SortListPrev(curr_iter));
	
	if(2 != SortListSize(new_list))
	{
		puts("remove and size failed");
	}
}
/*****************************************************************************/
static void SLEmptyPopTest()
{
	sort_list_ty *new_list = SortListCreate(FindBigger);
	
	int value;
	
	int a = 10;
	int b = 20;
	int c = 30; 
	
	if(0 == SortListIsEmpty(new_list))
	{
		puts("Empty failed\n");
	}
	
	 SortListInsert(new_list,&a);
	 SortListInsert(new_list,&b);
	 SortListInsert(new_list,&c);
	
	value = *(int *)SortListPopFront(new_list);
	
	if(10 != value)
	{
		puts("pop front failed");
	}
}
/*****************************************************************************/
static void SortListMergeTest()
{
	sort_list_ty *new_list1 = SortListCreate(FindBigger);
	sort_list_ty *new_list2 = SortListCreate(FindBigger);
	
	
	int a = 10;
	int b = 20;
	int c = 30; 
	
	int d = 15;
	int e = 17;
	
	 SortListInsert(new_list1,&a);
	 SortListInsert(new_list1,&b);
	 SortListInsert(new_list1,&c);
	
	 SortListInsert(new_list2,&d);
	 SortListInsert(new_list2,&e);
	
	 SortListMerge(new_list1,new_list2);
	
	if(5 != SortListSize(new_list1))
	{
		puts("merge failed");
	}
}
/*****************************************************************************/
static void SortListForEachTest()
{
	sort_list_ty * new_list = SortListCreate(FindBigger);
	
	int a = 10;
	int b = 20;
	int c = 30;
	
	sort_list_iter_ty from = NULL;
	sort_list_iter_ty to = NULL;
	sort_list_iter_ty check_iter = NULL;
	
	SortListInsert(new_list, &a);
	SortListInsert(new_list, &b);
	SortListInsert(new_list, &c);
	
	from = SortListBegin(new_list);
	to = SortListEnd(new_list);
	
	if( SortListForEach(from , to , AddValue , &b))
	{
		puts("foreach failed");
	}
	
	SortListDestroy(new_list);
	
	new_list = NULL;
}

/*****************************************************************************/
static void SortListFindTest()
{
	sort_list_ty * new_list = SortListCreate(FindBigger);

	int a = 10;
	int b = 20;
	int c = 30;
	
	sort_list_iter_ty from = NULL;
	sort_list_iter_ty to = NULL;
	sort_list_iter_ty check_iter = NULL;
	
	SortListInsert(new_list, &a);
	SortListInsert(new_list, &b);
	SortListInsert(new_list, &c);
	
	from = SortListBegin(new_list);
	to = SortListEnd(new_list);
	
	check_iter = SortListFind(new_list , from , to , &b);
	
	if(20 != *(int *)SortListGetData(check_iter))
	{
		puts("Find Failed");
	}
	

	SortListDestroy(new_list);
	
	new_list = NULL;
}
/***************************compare function***********************************/
int FindBigger(const void *list_data,const void *new_data)
{
	if(*(int *)list_data > *(int *)new_data)
	{
		return 1;
	}else
	{
		if(*(int *)list_data < *(int *)new_data)
		{
			return -1;
		}else
		{
			return 0;
		}
	}
}
/*************************action_func_ty -> Addvalue***************************/
int AddValue(void *data,void *param)
{

	*(int *)data += *(int *)param ;	
	return 0;
}

/*********************is_match_func_ty -> MatchFunc****************************/
static int CompareData(void *data, void *param)
{
	
	return *(int *)data == *(int *)param;
}


