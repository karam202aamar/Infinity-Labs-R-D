/******************************************************************************
 * Project: Data Structures - Heap Test
 * Date: 26/10/22
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
 * ****************************************************************************/
/******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "heap.h"
/******************************************************************************/
static void ImplementFunc();

static void HeapCreateDestroyTest();
static void HeapPushTest();
static void HeapPopTest();
static void HeapPeekTest();
static void HeapSizeTest();
static void HeapIsEmptyTest();
static void HeapRemoveTest();

int CmpFunc(const void *data1, const void *data2);
int IsMatch(const void *data1, const void *data2);
/******************************************************************************/
 int main()
 {
	ImplementFunc();

 	return 0;
 }
 /******************************************************************************/
static void ImplementFunc()
{
	HeapCreateDestroyTest();
	HeapPushTest();
	HeapPeekTest();
	HeapPopTest();
	HeapSizeTest();
	HeapIsEmptyTest();
	HeapRemoveTest();
}
/******************************************************************************/
static void HeapCreateDestroyTest()
{
	heap_ty* heap = HeapCreate(CmpFunc);

	if(NULL == heap)
	{
		puts("FAILED TO CREATE");
	}

	HeapDestroy(heap);
}
/******************************************************************************/
static void HeapPushTest()
{
	int a = 80;
	int b = 90;
	int c = 100;
	int d = 200;
	

	heap_ty* heap = HeapCreate(CmpFunc);

	if(NULL == heap)
	{
		puts("FAILED TO CREATE");
	}
	if(HeapPush(heap, &a))
	{
		puts("FAILED TO INSERT");
	}

	if(HeapPush(heap, &b))
	{
		puts("FAILED TO INSERT");
	}
		
	if(HeapPush(heap, &c))
	{
		puts("FAILED TO INSERT");
	}

	if(HeapPush(heap, &d))
	{
		puts("FAILED TO INSERT");
	}
	
	HeapDestroy(heap);
}
/******************************************************************************/
static void HeapPopTest()
{
	int a = 80;
	int b = 90;
	int c = 100;
	int d = 200;

	heap_ty* heap = HeapCreate(CmpFunc);

	HeapPush(heap, &a);
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	HeapPush(heap, &d);

	if(200 != **(int**)(HeapPeek(heap)))
	{
		HeapPop(heap);

		if(100 != **(int**)(HeapPeek(heap)))
		{
			puts("FAILED TO POP");
		}
	}
	HeapDestroy(heap);
}
/******************************************************************************/
static void HeapPeekTest()
{
	int a = 80;

	heap_ty* heap = HeapCreate(CmpFunc);

	if(NULL == heap)
	{
		puts("FAILED TO CREATE");
	}
	if(HeapPush(heap, &a))
	{
		puts("FAILED TO INSERT");
	}
	if(80 != **(int**)(HeapPeek(heap)))
	{
		puts("PEEK FAILED");
	}
	
	HeapDestroy(heap);
}
/******************************************************************************/
static void HeapSizeTest()
{
	int a = 80;
	int b = 90;
	int c = 100;
	int d = 200;

	heap_ty* heap = HeapCreate(CmpFunc);

	HeapPush(heap, &a);
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	HeapPush(heap, &d);

	if(4 != HeapSize(heap))
	{
		puts("HEAP SIZE FAILED");
	}
	HeapDestroy(heap);
}
/******************************************************************************/
static void HeapIsEmptyTest()
{
	int a = 80;
	int b = 90;
	int c = 100;
	int d = 200;

	heap_ty* heap = HeapCreate(CmpFunc);

	if(1 != HeapIsEmpty(heap))
	{
		puts("HEAP IS EMPTY FAILED");
	}

	HeapPush(heap, &a);
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	HeapPush(heap, &d);

	if(0 != HeapIsEmpty(heap))
	{
		puts("HEAP IS EMPTY FAILED");
	}
	HeapDestroy(heap);
}
/******************************************************************************/
static void HeapRemoveTest()
{
	int a = 80;
	int b = 90;
	int c = 100;
	int d = 200;
	int e = 20;


	void *returned_value = NULL;

	heap_ty* heap = HeapCreate(CmpFunc);

	HeapPush(heap, &a);
	HeapPush(heap, &b);
	HeapPush(heap, &c);
	HeapPush(heap, &d);
	HeapPush(heap, &e);

	returned_value = HeapRemove(heap, IsMatch, &c);

	if(100 != *(int*)returned_value)
	{
		puts("REMOVE FAILED 1");
	}
	
	if(4 != HeapSize(heap))
	{
		puts("REMOVE FAILED");
	}
	
	HeapDestroy(heap);
}
/******************************************************************************/
int CmpFunc(const void *data1, const void *data2)
{
	if(*(int*)data1 > *(int*)data2)
	{
		return 1;
	}
	else if(*(int*)data1 < *(int*)data2)
	{
		return -1;
	}
	return 0;
}
/******************************************************************************/
int IsMatch(const void *data1, const void *data2)
{
	if(*(int*)data1 == *(int*)data2)
	{
		return 1;
	}
	return 0;
}