/*******************************************************************************
 * Project: Data Structures - DList -test
 * Date: 18/08/22
 * Name: Karam Aamar
 * Reviewer:
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>/*puts*/
/******************************************************************************/
#include "dlist.h"
/******************************************************************************/
static void ImPlementFunc();
static void CreateLlistDestroyTest();
static void IsEmptyTest();
static void DListSizeTest();
static void DListBeginTest();
static void DListEndTest();
static void DListNextTest();
static void DListPrevTest();
static void DListIsEqualTest();
static void DListGetSetDataTest();
static void DListPushPopTest();
static void DListForeachTest();
static void DListFindTest();
static void DListMultiFindTest();
static void DListSpliceTest();
static int AddValueToNode(void *list,const void *param);
static int IsDataFound(const void *data, const void *param);
/******************************************************************************/
int main()
{
	ImPlementFunc();
	return 0;
}
/******************************************************************************/
static void ImPlementFunc()
{
	/*CreateLlistDestroyTest();
	IsEmptyTest();
	DListSizeTest();
	DListBeginTest();
	DListEndTest();
	DListNextTest();
	DListPrevTest();
	DListIsEqualTest();
	DListGetSetDataTest();
	DListPushPopTest();
	DListForeachTest();
	DListFindTest();
	DListMultiFindTest();*/
	DListSpliceTest();
}
/******************************************************************************/
static void CreateLlistDestroyTest()
{
	dlist_ty *new_list = DListCreate();
	
	if(NULL == new_list)
	{
		puts("Creation Failed");
	}
	
	DListDestroy(new_list);
	
	new_list = NULL;

}
/******************************************************************************/
static void IsEmptyTest()
{
	dlist_ty *new_list = DListCreate();
	
	if(0 == DListIsEmpty(new_list))
	{
		puts("IsEmpty Failed");
	}
	
	DListDestroy(new_list);
	
	new_list = NULL;

}
/******************************************************************************/
static void DListSizeTest()
{
	dlist_ty *new_list = DListCreate();
	dlist_iter_ty current = NULL;
	
	int a = 10;
	int b = 20;
	int c = 30;
	
	current = DListBegin(new_list);
	
	current = DListInsert((current),&a);
	current = DListInsert((current),&b);
	current = DListInsert((current),&c);
	
	if(NULL == new_list)
	{
		puts("insert node Failed");
	}else
	{
		if(3 != DListSize(new_list))
		{
			puts("list size function failed");
		}
	}
	
	DListDestroy(new_list);
	new_list = NULL;
}
/******************************************************************************/
static void DListBeginTest()
{
	dlist_ty *list = DListCreate();
	
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	DListPushFront(list, &a);
	DListInsert(DListBegin(list), &b);
	DListInsert(DListBegin(list), &c);
	
	if(3 != *(int *)DListGetData((DListBegin(list))))
	{
		puts("Begin test has been failed");
	}
	
	DListDestroy(list);
}
/******************************************************************************/
static void DListEndTest()
{
	dlist_ty *list = DListCreate();
	
	dlist_iter_ty dummy = NULL;
	
	int a = 3;
	int b = 4;
	int c = 5;
	
	DListPushFront(list, &a);
	DListInsert(DListBegin(list), &b);
	DListPushFront(list, &c);
	
	dummy = DListEnd(list);
	
	if( (void *)0xDEADBEEF != DListGetData(dummy))
	{
		puts("End list failed");
	}
	
	DListDestroy(list);
}
/******************************************************************************/
static void DListNextTest()
{
	dlist_ty *list = DListCreate();
	
	dlist_iter_ty check_node = NULL;
	
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	DListInsert(DListBegin(list), &a);
	DListInsert(DListBegin(list), &b);
	DListInsert(DListBegin(list), &c);
	
	check_node = DListNext((DListBegin(list)));
	
	if(2 != *(int *)DListGetData(check_node))
	{
		puts("Next test has been failed");
	}
	
	DListDestroy(list);	
}
/******************************************************************************/
static void DListPrevTest(void)
{
	dlist_ty *list = DListCreate();
	
	dlist_iter_ty check_node = NULL;
	
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	DListInsert(DListBegin(list), &a);
	DListInsert(DListBegin(list), &b);
	DListInsert(DListBegin(list), &c);
	
	check_node = DListPrev(DListNext((DListBegin(list))));
	
	if(3 != *(int *)DListGetData(check_node))
	{
		puts("Prev test has been failed");
	}
	
	DListDestroy(list);
}
/******************************************************************************/
static void DListIsEqualTest()
{
	dlist_ty *list = DListCreate();
	dlist_iter_ty head_one =(DListBegin(list));
	dlist_iter_ty head_two = head_one;
	
	if( 0 == DListIsSameIter(head_one,head_two))
	{
		puts("IsEqual test has been failed");
	}
	
	DListDestroy(list);
}
/******************************************************************************/
static void DListGetSetDataTest()
{
	dlist_ty *list = DListCreate();
	
	dlist_iter_ty check_node = NULL;
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	int d = 4;
	
	DListInsert(DListBegin(list), &a);
	DListInsert(DListBegin(list), &b);
	DListInsert(DListBegin(list), &c);
	
	check_node = DListNext(DListNext(DListBegin(list)));

	if(1 != *(int *)DListGetData(check_node))
	{
		puts("get data failed\n");
	}
	
	DListSetData(DListNext(DListBegin(list)),&d);
	
	check_node = DListNext(DListBegin(list));
	
	if(4 != *(int *)DListGetData(check_node))
	{
		puts("set data failed\n");
	}
	
	DListDestroy(list);
	
	list = NULL; 	
}
/******************************************************************************/
static void DListPushPopTest()
{
	dlist_ty *list = DListCreate();
	
	int a = 3;
	int b = 4;
	int c = 5;
	
	int d = 100;
	int e = 200;
	
	int compare_value = 0;
	
	DListPushFront(list, &a);
	DListPushFront(list, &b);
	DListPushFront(list, &c);
	DListPushFront(list, &d);
	
	if(100 != *(int *)DListGetData((DListBegin(list))))
	{
		puts("Push front failed\n");
	}
	
	DListPushBack(list, &e);
	
	if(200 != *(int *)DListGetData(DListPrev(DListEnd(list))))
	{
		puts("Push back failed\n");
	}
	
	compare_value = *(int*)DListPopFront(list);
	
	if(100 != compare_value)
	{
		printf("failed to pop front\n");
	}
	
	compare_value = *(int*)DListPopBack(list);
	
	if(200 != compare_value)
	{
		printf("failed to pop back\n");
	}
	DListDestroy(list);	
	
}
/******************************************************************************/
static void DListForeachTest()
{
	
	dlist_ty *new_list = DListCreate();

	int element1 = 1;
	int element2 = 55;
	int element3 = 25;
	
	dlist_iter_ty head = NULL;
	dlist_iter_ty curr = NULL;
	dlist_iter_ty tail = NULL;
	
	DListInsert(DListBegin(new_list), &element1);
	DListInsert(DListBegin(new_list), &element2);
	DListInsert(DListBegin(new_list), &element3);
	
	head = DListNext(DListBegin(new_list));
	curr = DListNext(head);
	tail = DListNext(curr);
	
	if(1 == DListForeach(head, tail, &AddValueToNode, &element1))
	{
		puts("ForEach Failed");
	}
	
	if(26 != *(int *)DListGetData(head))
	{
		puts("ForEach Failed");
	}
	
	if(56 != *(int *)DListGetData(curr))
	{
		puts("ForEach Failed");
	}
	
	DListDestroy(new_list);
	
	new_list = NULL;	

}
/******************************************************************************/
static int AddValueToNode(void *list,const void *param)
{
	*(int *)list += *(int *)param;
	
	if(NULL == list)
	{
		return 1;
	}
	
	return 0;	
}
/******************************************************************************/
static void DListFindTest()
{
	dlist_ty *new_list = DListCreate();

	int a = 10;
	int b = 20;
	int c = 30;
	
	dlist_iter_ty head = NULL;
	dlist_iter_ty curr = NULL;
	dlist_iter_ty tail = NULL;
	dlist_iter_ty iter_to_find = NULL;
	
	DListInsert(DListBegin(new_list), &a);
	DListInsert(DListBegin(new_list), &b);
	DListInsert(DListBegin(new_list), &c);
	
	head = DListNext(DListBegin(new_list));
	curr = DListNext(head);
	tail = DListNext(curr);
	
	iter_to_find = DListFind(head, tail, &IsDataFound, &a);

	if(10 != *(int *)DListGetData(iter_to_find))
	{
		puts("Find Failed");
	}
	
	iter_to_find = DListFind(head, tail, &IsDataFound, &b);
	
	if(20 != *(int *)DListGetData(iter_to_find))
	{
		puts("Find Failed");
	}
	
	iter_to_find = DListFind(head, tail, &IsDataFound, &c);

	if(30 != *(int *)DListGetData(iter_to_find))
	{
		puts("Find Failed");
	}
	
	DListDestroy(new_list);
	new_list = NULL;

}
/******************************************************************************/
static int IsDataFound(const void *data, const void *data2)
{

	return *(int *)data == *(int *)data2;
}
/******************************************************************************/
static void DListMultiFindTest()
{
	dlist_ty *list1 = DListCreate();
	dlist_ty *list2 = DListCreate();
	
	int data = 1;
	
	int array[5] = {0,2,1,1,2};
	
	size_t i = 0;
	
	for(i = 0; i<5; ++i)
	{
		DListInsert(DListBegin(list1), &array[i]);
	}
	
	if(!DListMultiFind(DListNext(DListBegin(list1)), 
		      DListPrev(DListEnd(list1)), &IsDataFound, &data, list2))
	{
		puts("MultiFind Failed");
	}
         
	if(2 != DListSize(list2))
	{
		puts("MultiFind Failed");	
	}
	
	DListDestroy(list1);
	list1 = NULL;	
	
	DListDestroy(list2);
	list2 = NULL;

}
/******************************************************************************/
static void DListSpliceTest()
{	
	dlist_iter_ty dest_iter = NULL;
	dlist_iter_ty from_iter = NULL;
	dlist_iter_ty to_iter = NULL;
	
	dlist_ty *list1 = DListCreate();
	dlist_ty *list2 = DListCreate();
	
	int a = 10;
	int b = 20;
	int c = 30;
	int e = 40;
	int f = 50;
	
	int g = 60;
	int h = 70;
	int k = 80;
	
	DListInsert(DListBegin(list1), &a);
	DListInsert(DListBegin(list1), &b);
	DListInsert(DListBegin(list1), &c);
	DListInsert(DListBegin(list1), &e);
	DListInsert(DListBegin(list1), &f);
	
	DListInsert(DListBegin(list2), &g);
	DListInsert(DListBegin(list2), &h);
	DListInsert(DListBegin(list2), &k);
	
	dest_iter = DListNext(DListBegin(list1));

	from_iter = DListNext(DListBegin(list2));

	to_iter = DListPrev(DListEnd(list2));

        DListSplice(from_iter,to_iter,dest_iter);
	
	if(6 != DListSize(list1) && 2 != DListSize(list2))
	{
		puts("splice list Failed");
	}
	
	DListDestroy(list1);
	list1 = NULL;	
	
	DListDestroy(list2);
	list2 = NULL;
}
