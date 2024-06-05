/******************************************************************************/
#include <semaphore.h>
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
#include <stdio.h>  
#include <fcntl.h> 
#include <stdlib.h>
/******************************************************************************/
#define     ASCII      256
#define  WORD_LENGTH    26
#define  DICT_PATH    "/home/karam/Desktop/infintylab/git/system_programming/src/counting_sort.txt"
/******************************************************************************/
enum{INDEX_RANGE = 2, NUM_OF_THREADS = 5, NUM_OF_CHUNKS = 4, ARRAY_SIZE = 20};
enum{INIT = 0, RANGE_BEGIN = 0, RANGE_END = 1};

/******************************************************************************/
typedef struct chunk
{
    char* input_arr;
    int* counting_arr;
    int range_of_ele[INDEX_RANGE];

}chunk_ty;

/******************************************************************************/
void CountingSort(char* input, size_t size);
static void DoSort(char* input, size_t size, int* counting_arr);
static void CpyArray(char* dest, char* src, size_t size);
static void SumCountingArr(int *counting_arr, int counting_arr_size);
static void* CountingIMP(void* single_range);
static void InitStuff(char* input, int* counting_arr, chunk_ty* ranges);
static void CheckIfWork(char* input, size_t size);
/******************************************************************************/
int main()
{
    char array[ARRAY_SIZE] = {"bclsdadsgfdsgfasasd"};
    
    CountingSort(array, ARRAY_SIZE);

    return 0;
}
/******************************************************************************/
void CountingSort(char* input, size_t size)
{
    size_t i = 0;
    int count_arr_size = ASCII;
    int *counting_arr = NULL;
    chunk_ty ranges[NUM_OF_THREADS];
    pthread_t thread[NUM_OF_THREADS] = {INIT};
    
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

    for(i=0; i < size; ++i)
    {
        printf("%c ", input[i]);
    }
    puts(" ");
    free(counting_arr);
}
/******************************************************************************/
static void CheckIfWork(char* input, size_t size)
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
static void DoSort(char* input, size_t size, int* counting_arr)
{
    size_t i = 0;
    char *tmp_arr = (char*)malloc(sizeof(char) * size);

    for(i = 0; i < size; ++i)
	{
		/* set the value in the sorted arr */ 
		tmp_arr[counting_arr[(int)input[i]] - 1] = input[i];
		/* decrement the value in the LUT */  
		counting_arr[(int)input[i]] -= 1;	
	}
    CpyArray(input, tmp_arr, size);
}
/******************************************************************************/
static void CpyArray(char* dest, char* src, size_t size)
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
    char* arr_to_sort = range->input_arr;
    int* counting_arr = range->counting_arr;
   
    for(i = range_begin; i <= range_end; ++i)
    {
        ++(counting_arr[(int)arr_to_sort[i]]);   
    }
    return NULL;
}
/******************************************************************************/
static void InitStuff(char* input, int* counting_arr, chunk_ty* ranges)
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



