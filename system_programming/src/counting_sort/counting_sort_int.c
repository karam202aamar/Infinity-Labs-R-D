/******************************************************************************/
#include <semaphore.h>
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
#include <stdio.h>  
#include <fcntl.h> 
#include <stdlib.h>
/******************************************************************************/

/******************************************************************************/
enum{INDEX_RANGE = 2, NUM_OF_THREADS = 5, NUM_OF_CHUNKS = 4, ARRAY_SIZE = 20};
enum{INIT = 0, RANGE_BEGIN = 0, RANGE_END = 1};

/******************************************************************************/
typedef struct chunk
{
    int* input_arr;
    int* counting_arr;
    int range_of_ele[INDEX_RANGE];

}chunk_ty;

/******************************************************************************/
void CountingSort(int* input, size_t size);
static void DoSort(int* input, size_t size, int* counting_arr);
static void CpyArray(int* dest, int* src, size_t size);
static void SumCountingArr(int *counting_arr, int counting_arr_size);
static void* CountingIMP(void* single_range);
static void InitStuff(int* input, int* counting_arr, chunk_ty* ranges);
static int FindMaxIMP(int* input, size_t size);
static void CheckIfWork(int* input, size_t size);
/******************************************************************************/
int main()
{
    int array[ARRAY_SIZE] = {3,2,5,4,1,12,14,15,11,13,24,23,21,25,27
                                                            ,33,31,30,32,39};
    
    CountingSort(array, ARRAY_SIZE);

    return 0;
}
/******************************************************************************/
void CountingSort(int* input, size_t size)
{
    size_t i = 0;
    int max_ele = 0;
    int count_arr_size = 0;
    int *counting_arr = NULL;
    chunk_ty ranges[NUM_OF_THREADS];
    pthread_t thread[NUM_OF_THREADS] = {INIT};

    max_ele = FindMaxIMP(input, size);
    count_arr_size = max_ele + 1;
    /*test*/
    
    counting_arr = (int*)calloc(count_arr_size, sizeof(int));

    if(NULL == counting_arr)
    {
        /*error message*/
        fputs("failed\n", stderr);
    }

    InitStuff(input, counting_arr, ranges);
    
    /*threads creation*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(thread + i, NULL, &CountingIMP, &ranges[i]))
        {
            fputs("failed to create producer threads\n", stderr);
        }
    }
    
    /*threads join*/
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(thread[i], NULL);
    }

    /*sum counting array*/
    SumCountingArr(counting_arr, count_arr_size);
    
    
    /*do the sort*/
    DoSort(input, size, counting_arr);
    
    CheckIfWork(input, size);

    free(counting_arr);
}
/******************************************************************************/
static void CheckIfWork(int* input, size_t size)
{
    size_t i = 0;

    /*check if it's work*/
    for(i = 0; i < (size - 1); ++i)
	{
		if(input[i] > input[i + 1])
        {
             fputs("failed\n", stderr);
        }	
	}
}
/******************************************************************************/
static void DoSort(int* input, size_t size, int* counting_arr)
{
    size_t i = 0;
    int *tmp_arr = (int*)malloc(sizeof(int) * size);

    for(i = 0; i < size; ++i)
	{
		/* set the value in the sorted arr */ 
		tmp_arr[counting_arr[input[i]] - 1] = input[i];
		/* decrement the value in the LUT */  
		counting_arr[input[i]] -= 1;	
	}
    CpyArray(input, tmp_arr, size);
}
/******************************************************************************/
static void CpyArray(int* dest, int* src, size_t size)
{
    size_t i =0;

    for(i = 0; i < size; ++i)
	{
		dest[i] = src[i];
	}
}
/******************************************************************************/
static void SumCountingArr(int *counting_arr, int counting_arr_size)
{
    int i = 0;

    for(i = 1; i < counting_arr_size; ++i)
    {
        counting_arr[i] += counting_arr[i - 1];
    }
}
/******************************************************************************/
static void* CountingIMP(void* single_range)
{
    /*single range*/
    chunk_ty* range = (chunk_ty*)single_range;
    /*define variable for the range*/
    int i = 0;
    int range_begin = range->range_of_ele[RANGE_BEGIN];
    int range_end = range->range_of_ele[RANGE_END];
    int* arr_to_sort = range->input_arr;
    int* counting_arr = range->counting_arr;
   
    for(i = range_begin; i <= range_end; ++i)
    {
        ++(counting_arr[arr_to_sort[i]]);   
    }
    return NULL;
}
/******************************************************************************/
static void InitStuff(int* input, int* counting_arr, chunk_ty* ranges)
{
    size_t i = 0;
    
    /*init the ranges struct*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        
        ranges[i].input_arr = input;
        ranges[i].counting_arr = counting_arr;
        ranges[i].range_of_ele[RANGE_BEGIN] = i * NUM_OF_CHUNKS;
        ranges[i].range_of_ele[RANGE_END] = (i * NUM_OF_CHUNKS) + (NUM_OF_CHUNKS - 1);
        /*
        printf("%d ",ranges[i].range_of_ele[RANGE_BEGIN]);
        printf("%d \n",ranges[i].range_of_ele[RANGE_END]);
        */
    }
    
    /*
    for(i = 0; i < count_arr_size; ++i)
    {
        printf("%d ",counting_arr[i]);
    }
    */
}
/******************************************************************************/
static int FindMaxIMP(int* input, size_t size)
{
    size_t i = 0;
    int max_value = 0;

    for(i = 0; i < size; ++i)
    {
        if(input[i] > max_value)
        {
            max_value = input[i];
        }
    }
    return max_value;
}
/******************************************************************************/


