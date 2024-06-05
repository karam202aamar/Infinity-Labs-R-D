/*******************************************************************************
 * Project: Data Structures - priority queue test
 * Date: 24/08/22
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#include "p_queue.h"
#include <stdio.h>/*puts*/
/*****************************************************************************/
static void ImplementFunc();

static void PQCreateDestroyTest();
static void PQEnqueueDequeuePeekTest();
static void PQSizeIsEmptyTest();
static void PQClearTest();
static void PQEraseTest();

static int FindBigger(const void *list_data,const void *new_data);
static int CompareData(void *data, void *param);
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
	
	pq_ty *list = PQCreate(sorting_type);
	
	if(!list)
	{
		puts("Creation failed");
	}
	
	PQDestroy(list);

}
/****************************Enqueue Dequeue peek test*************************/
static void PQEnqueueDequeuePeekTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQEnqueue(new_queue, &element1);
	PQEnqueue(new_queue, &element2);
	PQEnqueue(new_queue, &element3);
	
	if(10 != *(int *)PQPeek(new_queue))
	{
		puts("Enqueue and peek failed");
	}
	
	PQDequeue(new_queue);
	
	if(20 != *(int *)PQPeek(new_queue))
	{
		puts("Dequeue and peek failed");
	}
	
	PQDequeue(new_queue);
	
	if(30 != *(int *)PQPeek(new_queue))
	{
		puts("Dequeue and peek failed");
	}
	

	PQDestroy(new_queue);

}
/*******************************Size IsEmpty test*****************************/
static void PQSizeIsEmptyTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQEnqueue(new_queue, &element1);
	PQEnqueue(new_queue, &element2);
	PQEnqueue(new_queue, &element3);
	
	if(3 != PQSize(new_queue))
	{
		puts("Size failed");
	}
	
	PQDequeue(new_queue);
	PQDequeue(new_queue);
	PQDequeue(new_queue);
	
	if(!PQIsEmpty(new_queue))
	{
		puts("IsEmpty failed");
	}

	PQDestroy(new_queue);

}
/************************************clear test********************************/
static void PQClearTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQEnqueue(new_queue, &element1);
	PQEnqueue(new_queue, &element2);
	PQEnqueue(new_queue, &element3);
	
	PQClear(new_queue);
	
	if(!PQIsEmpty(new_queue))
	{
		puts("clear failed");
	}
	
	PQDestroy(new_queue);
}
/************************************erase test********************************/
static void PQEraseTest()
{
	pq_cmp_ty sorting_type = FindBigger;
	
	pq_ty *new_queue = PQCreate(sorting_type);
	
	int element1 = 10;
	int element2 = 20; 
	int element3 = 30;
	
	PQEnqueue(new_queue, &element1);
	PQEnqueue(new_queue, &element2);
	PQEnqueue(new_queue, &element3);
	
	if(20 != *(int *)PQErase(new_queue, CompareData,&element2))
	{
		puts("erase failed");
	}
	
	PQDestroy(new_queue);

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
static int CompareData(void *data, void *param)
{
	
	return *(int *)data == *(int *)param;
}
