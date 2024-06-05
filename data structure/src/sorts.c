/*******************************************************************************
 * Project: Comparision Sort
 * Date: 21/09/22
 * Name: karam
 * Reviewer: DANA 
 * Version: 1.0
*******************************************************************************/
#include <stdlib.h> /* malloc , free */
#include <string.h>/* memcpy */

#include "sorts.h"
/******************************************************************************/
typedef enum STATUS {NO_SWAP = 0 , SWAPPED } status_ty;
/******************************************************************************/
/* swap the values of two numbers*/
static void SwapFunc(int* num1 , int* num2);
/* helper function for the radix function */
static int CountSortRadix(unsigned int a[], size_t arr_size, int place);

static ssize_t BinarySearchHelper(const int *arr, size_t start, size_t end, int query);
static void QuickSortRecursive(int *arr,int start, int end);
static int PartitionFunc(int *arr,int start, int end);
static void Merge(int *arr, int *divided_arr, size_t arr_size);
/******************************************************************************/
void BubbleSort(int *arr_to_sort, size_t arr_size)
{
	/* define variable for the satus if swapped or not */
	size_t status = SWAPPED , i = 0;
	/* loop untill there is nothing to swap */
	while(status)
	{
		/* set status no_swap this way if there is no
				 need to swap the loop stops */
		status = NO_SWAP;
		/* loop & if cuurent value bigger than next swap*/ 
		for(i = 0; i < (arr_size - 1); ++i)
		{
			if(arr_to_sort[i] > arr_to_sort[i+1])
			{
				SwapFunc(arr_to_sort + i, arr_to_sort + i + 1);
				status = SWAPPED;
			}
		}
	}
}
/******************************************************************************/
void InsertionSort(int *arr_to_sort, size_t arr_size)
{
	size_t main_i = 1 , i;

	/* loop - on the array */
	for (main_i = 1; main_i < arr_size; ++main_i)
	{
		i = main_i;
		  /* Move the elements of the array one position 
		  			     ahead of their current position */
		while (i > 0 && (arr_to_sort[i] < arr_to_sort[i-1]))
		{
			/* swap the values */
			SwapFunc(&arr_to_sort[i], &arr_to_sort[i-1]);
			/* decrement i */
			--i;
		}
	}
}
/******************************************************************************/
void SelectionSort(int *arr_to_sort, size_t arr_size)
{
	/* set indexes*/
	size_t i, base_i, j;
 
	/* loop untill we find unsorted */
	for (i = 0; i < arr_size ; ++i)
	{
		/* set base index (current) */
		base_i = i;
		/* loop to find the new min*/
		for (j = i+1 ; j < arr_size ; ++j)
		{
			if (arr_to_sort[j] < arr_to_sort[base_i])
			{
				base_i = j;
			}
		}
		/* Swap between the minimum we found and current index */
		if(base_i != i)
		{
			SwapFunc(&arr_to_sort[base_i], &arr_to_sort[i]);
		}
	}
}
/******************************************************************************/
int CountSort(unsigned int *arr_to_sort, size_t arr_size)
{
	size_t i = 0 , max_num = 0;
	unsigned int * ptr_lut = NULL;
	
	unsigned int * ptr_tmp_sorted = NULL;
	
	/* find the range of the numbers */
	for(i = 0; i < arr_size; ++i)
	{
		if(arr_to_sort[i] > max_num)
		{
			max_num = arr_to_sort[i];
		}
	}
	/* allocate LUT table */
	ptr_lut = (unsigned int *)malloc((max_num + 1) * sizeof(unsigned int));
	
	if(NULL == ptr_lut)
	{
		return 1;
	}
	
	/* set zero's at LUT */
	for(i = 0; i <= max_num; ++i)
	{
		ptr_lut[i] = 0;
	}
	
	/* fill the LUT table */
	for(i = 0; i < arr_size; ++i)
	{
		/* increment the value in the LUT table */
		ptr_lut[arr_to_sort[i]] += 1;
	}

	/* combine each two values */
	for(i = 1; i <= max_num; ++i)
	{
		ptr_lut[i] = ptr_lut[i] + ptr_lut[i - 1];
	}

	ptr_tmp_sorted = (unsigned int *)malloc(arr_size * sizeof(unsigned int));
	
	if(NULL == ptr_tmp_sorted)
	{
		return 1;
	}
	
	for(i = 0; i < max_num; ++i)
	{
		ptr_tmp_sorted[i] = 0;
	}
	
	/* set the values int the tmp sorted - I HAVE TO FIX */
	for(i = 0; i < arr_size; ++i)
	{
		/* set the value in the sorted arr */ 
		ptr_tmp_sorted[ptr_lut[arr_to_sort[i]]-1] = arr_to_sort[i];
		/* decrement the value in the LUT */  
		ptr_lut[arr_to_sort[i]] -= 1;	
	}
	
	/* copy the sorted values */	
	for(i = 0; i < arr_size; ++i)
	{
		arr_to_sort[i] = ptr_tmp_sorted[i];	
	}
	
	free(ptr_lut);
	free(ptr_tmp_sorted);
	
	ptr_lut = NULL;
	ptr_tmp_sorted = NULL;
	return 0;
}
/******************************************************************************/
int RadixSort(unsigned int *arr_to_sort, size_t arr_size)
{
	size_t i = 0 , num_of_digits = 0;
	unsigned int place = 1 , max_num = 0 ;

	/* find the biggest number */
	for(i = 0; i < arr_size; ++i)
	{
		if(arr_to_sort[i] > max_num)
		{
			max_num = arr_to_sort[i];
		}
	}
	/* calculate number of digits for the max number */
	while(max_num)
	{
		++num_of_digits;
		max_num = max_num / 10;	
	}
	/* loop by number of digits */
	while(num_of_digits)
	{ 
		if(1 == CountSortRadix(arr_to_sort, arr_size, place))
		{
			return 1;
		}
		
		--num_of_digits;
		place = place*10;
	}

	return 0;
}
/******************************************************************************/
static int CountSortRadix(unsigned int a[], size_t arr_size, int place)
{
	int i;
	int count[10] = {0}; 
	unsigned int * output_arr = NULL;
	
	/* allocate LUT table */
	output_arr = (unsigned int *)malloc((arr_size + 1) * sizeof(unsigned int));
	
	if(NULL == output_arr)
	{
		return 1;
	}
	
	/* fill up current lut(count) */
	for (i = 0; i < (int)arr_size; ++i) 
	{ 
		count[(a[i] / place) % 10]++;  
    	}
    	
	/* increment the value in the LUT(count) table */
	for (i = 1; i < 10; i++) 
	{ 
		count[i] += count[i - 1];  
  	}
  	
  	/* Place the elements in sorted order */  
	for (i = arr_size - 1; i >= 0; --i) 
	{  
		output_arr[count[(a[i] / place) % 10] - 1] = a[i];  
		count[(a[i] / place) % 10]--;  
	}  
	/* copy to original array */
  	for (i = 0; i < (int)arr_size; ++i) 
	{ 
		a[i] = output_arr[i];  
	}
	
	free(output_arr);
	output_arr = NULL;
	
	return 0;
}
/******************************************************************************/
ssize_t BinarySearchIterative(const int *arr, size_t arr_size, int query)
{
	size_t start = 0;
	size_t middle = 0;
	size_t end = arr_size - 1;
	
	while(end > start)
	{
		middle = (start + end) / 2;
		
		if(query == arr[middle])
		{
			return middle;
		}
		else if(query > arr[middle])
		{
			start = middle;
		}
		else if(query < arr[middle])
		{
			end = middle;
		}
	}
	return -1;
}
/******************************************************************************/
ssize_t BinarySearch(const int *arr, size_t arr_size, int query)
{
	size_t start = 0;
	size_t end = arr_size - 1;
	
	return BinarySearchHelper(arr, start, end, query);
}
/******************************************************************************/
static ssize_t BinarySearchHelper(const int *arr, size_t start, size_t end, int query)
{
	size_t middle = 0;
	
	if(start > end)
	{
		return -1;
	}
	else 
	{
		middle = (start + end) / 2;
		
		if(query == arr[middle])
		{
			return middle;
		}
		else if(query > arr[middle])
		{
			return BinarySearchHelper(arr, middle + 1, end, query);
		}
		else if(query < arr[middle])
		{
			return BinarySearchHelper(arr, start, middle - 1, query);
		}
	}
	return 0;
}
/******************************************************************************/
void QuickSort(int *arr, size_t arr_size)
{
	int start = 0;
	int end = arr_size - 1;
	
	QuickSortRecursive(arr, start, end);
}
/******************************************************************************/
static void QuickSortRecursive(int *arr,int start, int end)
{
	int partition = 0;
	
	if (start < end) 
	{
		partition = PartitionFunc(arr, start, end);
		
       	 	QuickSortRecursive(arr, start, partition - 1);
        	QuickSortRecursive(arr, partition + 1, end);
	}
}
/******************************************************************************/
static int PartitionFunc(int *arr,int start, int end)
{
	int j = 0;
	int pivot = arr[end];
	int i = start - 1;
	
	/* loop from start to end */
	for(j = start; j < arr[end]; j++)
	{
		/* check if the value is smaller than pivot */
		if(arr[j] < pivot)
		{	
			/* increment I */
			++i;
			/* swap values */
			SwapFunc(&arr[i], &arr[j]);
		}
	} 
	SwapFunc(&arr[i + 1], &arr[end]);
	/* return the partition place */
	return i + 1;
}
/******************************************************************************/
int MergeSort(int* arr, size_t arr_size)
{
	int* divided_arr = (int*)malloc(sizeof(int) * arr_size);
	
	if(NULL == divided_arr)
	{
		return 1;
	}
	/* copy the values */
	memcpy(arr, divided_arr, sizeof(int)*arr_size);
	
	/* call recursive function */
	Merge(arr, divided_arr, arr_size);
	
	/* copy the values after sort */
	memcpy(divided_arr, arr, sizeof(int)*arr_size);
	
	free(divided_arr);
	divided_arr = NULL;
	
	return 0;
}
/******************************************************************************/
static void Merge(int *arr, int *divided_arr, size_t arr_size)
{
	size_t middle = (arr_size)/2;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	
	if(1 == arr_size)
	{
		return;
	}
	
	Merge(arr, divided_arr, middle);
	Merge(arr + middle, divided_arr + middle, arr_size - middle);
	
	while(i < middle && j < (arr_size - middle))
	{
		if(divided_arr[i] > (divided_arr+middle)[j])
		{
			/* assign the value of the second range */
			arr[k] = (divided_arr+middle)[j];
			/* increment the second one*/
			++j;
		}
		else
		{	
			/* assign the value of the first range */
			arr[k] = divided_arr[i];
			++i;
		}
		++k;
	}
	/* only one of i and i got to the end so we check which one didn't*/
	if(j < (arr_size - middle))
	{
		/* then j didnt get to the end */
		memcpy(arr + k, divided_arr + middle + j, sizeof(int)*(arr_size
								 - middle - j));
	}
	else
	{
		/* then i didnt get to the end */
		memcpy(arr + k, divided_arr + i, sizeof(int)*(middle - i));
	}
	
	/* copy the values of the arr[k] to divided */
	memcpy(divided_arr, arr, sizeof(int)*arr_size);
}
/******************************************************************************/
static void SwapFunc(int* num1 , int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2= temp;
}
/******************************************************************************/
