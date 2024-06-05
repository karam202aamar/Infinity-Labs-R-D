/*******************************************************************************
 * Project: Data Structures - priority queue heap test
 * Date: 29/10/22
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#include "pqueue_heap.h"
#include <stdio.h>/*puts*/
/*****************************************************************************/
static void ImplementFunc();

static void PQCreateDestroyTest();
static void PQEnqueueDequeuePeekTest();
static void PQSizeIsEmptyTest();
static void PQClearTest();
static void PQEraseTest();

static int FindBigger(const void *list_data,const void *new_data);
static int CompareData(const void *data,const void *param);
/*****************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0;
}
/***************************Implementation Function****************************/
static void ImplementFunc()
{
	PQCreateDestroyTest();
	PQEnqueueDequeuePeekTest();
	PQSizeIsEmptyTest();
	PQClearTest();
	PQEraseTest();
}
/*******************************create destroy test****************************/
static void PQCreateDestroyTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *list = PQHCreate(sorting_type);
	
	if(!list)
	{
		puts("Creation failed");
	}
	
	PQHDestroy(list);

}
/****************************Enqueue Dequeue peek test*************************/
static void PQEnqueueDequeuePeekTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQHCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQHEnqueue(new_queue, &element1);
	PQHEnqueue(new_queue, &element2);
	PQHEnqueue(new_queue, &element3);
	
	if(10 != *(int *)PQHPeek(new_queue))
	{
		puts("Enqueue and peek failed");
	}
	
	PQHDequeue(new_queue);
	
	if(20 != *(int *)PQHPeek(new_queue))
	{
		puts("Dequeue and peek failed");
	}
	
	PQHDequeue(new_queue);
	
	if(30 != *(int *)PQHPeek(new_queue))
	{
		puts("Dequeue and peek failed");
	}
	PQHDestroy(new_queue);
}
/*******************************Size IsEmpty test*****************************/
static void PQHSizeIsEmptyTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQHCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQHEnqueue(new_queue, &element1);
	PQHEnqueue(new_queue, &element2);
	PQHEnqueue(new_queue, &element3);
	
	if(3 != PQHSize(new_queue))
	{
		puts("Size failed");
	}
	
	PQHDequeue(new_queue);
	PQHDequeue(new_queue);
	PQHDequeue(new_queue);
	
	if(!PQHIsEmpty(new_queue))
	{
		puts("IsEmpty failed");
	}

	PQHDestroy(new_queue);

}
/************************************clear test********************************/
static void PQHClearTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQHEnqueue(new_queue, &element1);
	PQHEnqueue(new_queue, &element2);
	PQHEnqueue(new_queue, &element3);
	
	PQClear(new_queue);
	
	if(!PQHIsEmpty(new_queue))
	{
		puts("clear failed");
	}
	
	PQHDestroy(new_queue);
}
/************************************erase test********************************/
static void PQEraseTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQHCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQHEnqueue(new_queue, &element1);
	PQHEnqueue(new_queue, &element2);
	PQHEnqueue(new_queue, &element3);
	
	if(20 != *(int *)PQHErase(new_queue, CompareData,&element2))
	{
		puts("erase failed");
	}
	
	PQHDestroy(new_queue);

}
/***************************compare function***********************************/
static int FindBigger(const void *list_data,const void *new_data)
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
/********************************** MatchFunc *********************************/
static int CompareData(const void *data,const void *param)
{
	
	return *(int *)data == *(int *)param;
}
