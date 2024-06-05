/*******************************************************************************
 * Project: Data Structures - Linked List
 * Date: 12/08/22
 * Name: 	
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>/*puts*/

#include "linked_list.h"
/******************************************************************************/

static void RunTests();
static void CreateLlistTest();
static void InsertTest();
static void RemoveTest();
static void FindTest();
static void ForEachTest();
static void ListBeginTest();
static void ListEndTest();
static void ListNextTest();
static void IsEqualTest();
static void GetDataTest();
static void SetDataTest();
static void CountTest();
static void TestAppend();
static int IntComp(const void *data, void *param);
static int AddTwoForEachTest(void *data, void *param); 
/******************************************************************************/
int main()
{
	RunTests();
	return 0;
}
/******************************************************************************/
static void RunTests()
{
	CreateLlistTest();
	InsertTest();
	RemoveTest();
	FindTest();
	ForEachTest();
	ListBeginTest();
	ListEndTest();
	ListNextTest();
	IsEqualTest();
	GetDataTest();
	SetDataTest();
	CountTest();
	TestAppend();
}
/******************************************************************************/
static void CreateLlistTest()
{
	/*Creation test.*/
	slist_ty *list = SListCreate();
	if(!list)
	{
		puts("Creation test has been failed");
	}
	
	SListDestroy(list);

}
/******************************************************************************/
static void InsertTest()
{
	slist_ty *list = SListCreate();
	
	/*set test*/
	int a = 4;
	int b = 5;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	
	if(5 != *(int *)SListGetData(SListBegin(list)))
	{
		puts("Insert list has been failed");
	}
	
	SListDestroy(list); 
}
/******************************************************************************/
static void RemoveTest()
{
	slist_ty *list = SListCreate();
	int a = 4;
	int b = 5;
	/*Remove test*/
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListRemove(SListBegin(list));
	
	if(4 != *(int *)SListGetData(SListBegin(list)))
	{
		puts("Destroy list has been failed");
	}
	
	SListDestroy(list); 
}
/******************************************************************************/
static void FindTest()
{
	/*Is find test.*/
	slist_ty *list = SListCreate();
	slist_iter_ty start = NULL;
	slist_iter_ty temp = NULL;
	slist_iter_ty end = NULL;

	int a = 3;
	int b = 4;
	int c = 5;
	int d = 10;
	
	/*Point to the function*/
	is_match_func_ty ptr = IntComp;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);
	SListInsert(SListBegin(list), &d);
	
	/*Set pointers to nodes.*/
	start = SListBegin(list);
	temp = SListNext(start);
	end = SListNext(temp);
	
	if(SListNext(start) != SListFind(start, end, ptr, &c))
	{
		puts("Find failed");
	}
	
	SListDestroy(list);
}
/******************************************************************************/
static void ForEachTest()
{
	slist_ty *list = SListCreate();
	slist_iter_ty start = NULL;
	slist_iter_ty temp = NULL;
	slist_iter_ty temp_next = NULL;
	slist_iter_ty end = NULL;
	slist_iter_ty iterator = NULL;

	int a = 3;
	int b = 4;
	int c = 5;
	int d = 10;
	
	/*The param for addition action*/
	int addition_param = 13;
	
	/*An array for testing*/
	int checking_arr[3] = {10,5,4};
	
	int i = 0;
	action_func_ty ptr = AddTwoForEachTest;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);
	SListInsert(SListBegin(list), &d);
	
	/*Setting pointer to the nodes of the linked_list.*/
	start = SListBegin(list);
	temp = SListNext(start);
	temp_next = SListNext(temp);
	end = SListNext(temp_next);
	
	if(SListForEach(start, end, ptr, &addition_param))
	{
		puts("For each test has been failed");
	}
	
	iterator = start;
	/*Check if the action function has done the desired action on each of
	  the elements within the specified range.*/
	while(iterator != end)
	{
		if(*(int *)SListGetData(iterator) != checking_arr[i] + addition_param)
		{
			puts("For each test has been failed");	
		}
		++i;
		iterator = SListNext(iterator);
	}
	
	SListDestroy(list);
}
/******************************************************************************/
static void ListBeginTest()
{
	slist_ty *list = SListCreate();
	/*List begin test.*/
	int a = 3;
	int b = 4;
	int c = 5;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);
	
	if(5 != *(int *)SListGetData(SListBegin(list)))
	{
		puts("Begin test has been failed");
	}
	SListDestroy(list);
}
/******************************************************************************/
static void ListEndTest()
{
	slist_ty *list = SListCreate();
	/*List end test.*/
	int a = 10;
	int b = 11;
	int c = 12;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);
	
	if(10 != *(int *)SListGetData(SListEnd(list)))
	{
		puts("End test has failed");
	}
	SListDestroy(list);
}
/******************************************************************************/
static void ListNextTest()
{
	slist_ty *list = SListCreate();
	slist_iter_ty iter = NULL;

	/*List next test.*/
	int a = 3;
	int b = 4;
	int c = 5;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);
	
	iter = SListBegin(list);
	
	if(4 != *(int *)SListGetData(SListNext(iter)))
	{
		puts("Next test has been failed");
	}
	SListDestroy(list);	
}
/******************************************************************************/
static void IsEqualTest()
{
	slist_ty *list = SListCreate();
	slist_iter_ty head = SListBegin(list);
	slist_iter_ty head_copy = head;
	/*List equal test (check if two nodes are the same).*/
	if(!SListIterIsEqual(head,head_copy))
	{
		puts("IsEqual test has been failed");
	}
	
	SListDestroy(list);
}
/******************************************************************************/
static void GetDataTest()
{
	slist_ty *list = SListCreate();
	slist_iter_ty temp = NULL;

	int a = 1;
	int b = 2;
	int c = 3;
	
	/*Get data test (check if two nodes are the same).*/
	temp = SListBegin(list);
	
	SListInsert(temp , &a);
	temp = SListNext(temp);
	
	SListInsert(temp, &b);
	temp = SListNext(temp);
	SListInsert(temp, &c);
	
	if(3 != *(int *)SListGetData(SListEnd(list)))
	{
		puts("Get test has been failed");
	}
	
	SListDestroy(list);
}
/******************************************************************************/
static void SetDataTest()
{
	slist_ty *list = SListCreate();

	int a = 3;
	int b = 4;
	int c = 5;
	int d = 101;
	
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);
	
	SListSetData(SListBegin(list), &d);
	if(101 != *(int *)SListGetData(SListBegin(list)))
	{
		puts("Set data test has been failed");
	}
	SListDestroy(list);
}
/******************************************************************************/
static void CountTest()
{
	slist_ty *list = SListCreate();

	int a = 3;
	int b = 4;
	int c = 5;
	/*Count nodes test.*/
	SListInsert(SListBegin(list), &a);
	SListInsert(SListBegin(list), &b);
	SListInsert(SListBegin(list), &c);

	if(3 != SListCount(list))
	{
		puts("Count test has been failed");	
	}
	
	SListDestroy(list);
}
/*****************************Helper functions*********************************/
static int IntComp(const void *data, void *param)
{
	/*Compration between two values*/
	return *(int *)data == *(int *)param; 	
}
/******************************************************************************/
static int AddTwoForEachTest(void *data, void *param)
{
	/*add the value param to node data */
	*(int *)data += *(int *)param;
	
	if(NULL == data)
	{
		return 1;
	}
	
	return 0;	
}
/******************************************************************************/
static void TestAppend()
{
	slist_ty *list1 = SListCreate();
	slist_ty *list2 = SListCreate();
	
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	
	int element4 = 4;
	int element5 = 5;
	int element6 = 6;
	
	SListInsert(SListBegin(list1), &element1);
	SListInsert(SListBegin(list1), &element2);
	SListInsert(SListBegin(list1), &element3);
	
	SListInsert(SListBegin(list2), &element4);
	SListInsert(SListBegin(list2), &element5);
	SListInsert(SListBegin(list2), &element6);
	
	list1 = SListAppend(list1, list2);
	
	if(6 != SListCount(list1))
	{
		puts("Append test Failed");
	}
}

