/*******************************************************************************
 * Project: Comparision Sort
 * Date: 21/09/22
 * Name: karam
 * Reviewer: DANA 
 * Version: 1.0
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* puts */
#include <time.h>   /*  clock_t */
#include <stdlib.h> /* qsort */
/******************************************************************************/
#include "sorts.h"
/******************************************************************************/
#define ARRAY_SIZE 10 
#define MAX_ARRAY_SIZE 5000 
/******************************************************************************/
typedef enum {SUCCESS, FAIL} SORT_STATUS_ty;
/******************************************************************************/
static void ImplementFunc();

static void BubbleSortTest();
static void InsertionSortTest();
static void SelectionSortTest();

static void CountSortTest();
static void RadixSortTest();

static void RandomBubbleSortTest();
static void RandomInsertionSortTest();
static void RandomSelectionSortTest();

static void BinarySearchTest();
static void QuickSortTest();
static void MergeSortTest();

static SORT_STATUS_ty SortStatus(int *arr_to_check , size_t arr_size);
static int CompareFunc(const void *num1, const void *num2);
static void CopyArray(int *src, int *dest, size_t arr_size);
/******************************************************************************/
int main()
{
	ImplementFunc();
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	BubbleSortTest();
	InsertionSortTest();
	SelectionSortTest();
	CountSortTest();
	RadixSortTest();
	
	RandomBubbleSortTest();
	RandomInsertionSortTest();
	RandomSelectionSortTest();
	
	BinarySearchTest();
	QuickSortTest();
	MergeSortTest();
}
/**********************************BubbleSort**********************************/
static void BubbleSortTest()
{
	int array[ARRAY_SIZE] = {3,2,1,6,2,7,9,8,6,5};
	
	BubbleSort(array,ARRAY_SIZE);

	if(FAIL == SortStatus(array,ARRAY_SIZE))
	{
		puts("FAILED 1");
	}
}
/********************************InsertionSort*********************************/
static void InsertionSortTest()
{

	int array[ARRAY_SIZE] = {3,2,1,6,4,7,9,8,6,5};
	InsertionSort(array,ARRAY_SIZE);
	
	if(FAIL == SortStatus(array,ARRAY_SIZE))
	{
		puts("FAILED 2");
	}
}
/********************************SelectionSort*********************************/
static void SelectionSortTest()
{
	int array[ARRAY_SIZE] = {3,2,1,6,4,7,9,8,6,5};
	
	SelectionSort(array,ARRAY_SIZE);
	
	if(FAIL == SortStatus(array,ARRAY_SIZE))
	{
		puts("FAILED 3");
	}
}
/********************************CountingSort**********************************/
static void CountSortTest()
{
	int i = 0;
	unsigned int array[MAX_ARRAY_SIZE] = {0};
	
	for (i = 0; i < MAX_ARRAY_SIZE; ++i)
	{
		array[i] = (rand() % 100) + 1;
	}
	
	if(FAIL == CountSort(array , MAX_ARRAY_SIZE))
	{
		puts("FAILED 4");
	}
}
/********************************RadixSort**********************************/
static void RadixSortTest()
{
	int i = 0;
	unsigned int array[MAX_ARRAY_SIZE] = {0};
	
	for (i = 0; i < MAX_ARRAY_SIZE; ++i)
	{
		array[i] = rand() % 1000000;
	}
	
	if(FAIL == RadixSort(array , MAX_ARRAY_SIZE))
	{
		puts("FAILED 5");
	}
}
/*******************************RANDOM-BubbleSort******************************/
static void RandomBubbleSortTest()
{
	size_t i = 0;
	int array_to_test[MAX_ARRAY_SIZE] = {0};
	int array_to_test_qs[MAX_ARRAY_SIZE] = {0};
	
	clock_t mysort_start = 0;
	clock_t mysort_end = 0;
	
	clock_t qsort_start = 0;
	clock_t qsort_end = 0;
	
	for (i = 0; i < MAX_ARRAY_SIZE; ++i)
	{
		array_to_test[i] = rand();
	}
	
	CopyArray(array_to_test , array_to_test_qs , MAX_ARRAY_SIZE);
	
	mysort_start = clock();
	BubbleSort(array_to_test, MAX_ARRAY_SIZE);
	mysort_end = clock();
	
	qsort_start = clock();
	qsort(array_to_test, MAX_ARRAY_SIZE, sizeof(int), CompareFunc);
	qsort_end = clock();
	
	puts("\nBubbleSort output : ");
	printf("time taken to BubbleSort = %ld\n",(mysort_end - mysort_start));
	printf("time taken to qsort = %ld\n",(qsort_end - qsort_start));
}
/*******************************RANDOM-InsertionSort******************************/
static void RandomInsertionSortTest()
{
	size_t i = 0;
	int array_to_test[5000] = {0};
	int array_to_test_qs[MAX_ARRAY_SIZE] = {0};
	
	clock_t mysort_start = 0;
	clock_t mysort_end = 0;
	
	clock_t qsort_start = 0;
	clock_t qsort_end = 0;
	
	for (i = 0; i < 5000; ++i)
	{
		array_to_test[i] = rand();
	}
	
	CopyArray(array_to_test , array_to_test_qs , MAX_ARRAY_SIZE);
	
	mysort_start = clock();
	InsertionSort(array_to_test, 5000);
	mysort_end = clock();
	
	qsort_start = clock();
	qsort(array_to_test, 5000, sizeof(int), CompareFunc);
	qsort_end = clock();
	
	puts("\nInsertionSort output : ");
	printf("time taken to InsertionSort = %ld\n",(mysort_end - mysort_start));
	printf("time taken to qsort = %ld\n",(qsort_end - qsort_start));
}
/*******************************RANDOM-SelectionSort******************************/
static void RandomSelectionSortTest()
{
	size_t i = 0;
	int array_to_test[5000] = {0};
	int array_to_test_qs[MAX_ARRAY_SIZE] = {0};
	
	clock_t mysort_start = 0;
	clock_t mysort_end = 0;
	
	clock_t qsort_start = 0;
	clock_t qsort_end = 0;
	
	for (i = 0; i < 5000; ++i)
	{
		array_to_test[i] = rand();
	}
	
	CopyArray(array_to_test , array_to_test_qs , MAX_ARRAY_SIZE);
	
	mysort_start = clock();
	SelectionSort(array_to_test, 5000);
	mysort_end = clock();
	
	qsort_start = clock();
	qsort(array_to_test, 5000, sizeof(int), CompareFunc);
	qsort_end = clock();
	
	puts("\nSelectionSort output : ");
	printf("time taken to SelectionSort = %ld\n",(mysort_end - mysort_start));
	printf("time taken to qsort = %ld\n",(qsort_end - qsort_start));
}
/******************************Binary Search Test******************************/
static void BinarySearchTest()
{
	int arr[8] = {1,2,3,4,7,8,9,11};
	int num = 3;
	
	if(2 != BinarySearchIterative(arr, 8, num))
	{
		puts("iterative binary search failed\n");
		printf("%ld\n",BinarySearchIterative(arr, 8, num));
	}
	
	if(2 != BinarySearch(arr, 8, num))
	{
		puts("recursive binary search failed\n");
	}
}
/*******************************Quick sort Test********************************/
static void QuickSortTest()
{
	int array[ARRAY_SIZE] = {3,2,1,6,4,7,9,8,11,5};
	QuickSort(array,ARRAY_SIZE);
	
	if(FAIL == SortStatus(array,ARRAY_SIZE))
	{
		puts("quick sort failed\n");
	}
}
/*******************************merge sort Test********************************/
static void MergeSortTest()
{
	int array[ARRAY_SIZE] = {3,2,1,6,4,7,9,8,11,5};
	
	MergeSort(array, ARRAY_SIZE);
	
	if(FAIL == SortStatus(array,ARRAY_SIZE))
	{
		puts("merge sort failed\n");
	}
}
/***********************helper function - check if sorted**********************/
static SORT_STATUS_ty SortStatus(int *arr_to_check , size_t arr_size)
{
	size_t i = 0;
	
	for (i = 0; i < arr_size-1; ++i)
	{
		if (arr_to_check[i] > arr_to_check[i+1])
		{
			return FAIL;
		}
	}
	return SUCCESS;
}
/******************************************************************************/
static int CompareFunc(const void *num1, const void *num2)
{
	if (*(int *)num1 < *(int *)num2)
	{
		return -1;
	}
	if (*(int *)num1 > *(int *)num2)
	{
		return 1;
	}
	return 0;
}
/******************************************************************************/
static void CopyArray(int *src, int *dest, size_t arr_size)
{
	size_t i;
	
	for(i = 0; i < arr_size; i++)
	{
		dest[i] = src[i];
	}
}



