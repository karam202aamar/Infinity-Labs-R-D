/******************************************************************************/
#include <semaphore.h>
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
#include <stdio.h>  
#include <fcntl.h> 
#include <stdlib.h>
#include <assert.h>
/******************************************************************************/
#define     ASCII      256
#define  WORD_LENGTH    26
#define  DICT_PATH    "/home/karam/Desktop/infintylab/git/system_programming/src/counting_sort/words_mt"
/******************************************************************************/
enum{INDEX_RANGE = 2, NUM_OF_THREADS = 8, NUM_OF_CHUNKS = 4, ARRAY_SIZE = 20};
enum{INIT = 0, RANGE_BEGIN = 0, RANGE_END = 1};

/******************************************************************************/
typedef struct chunk
{
    unsigned char* input_arr;
    size_t* counting_arr;
    int range_of_ele[INDEX_RANGE];

}chunk_ty;
/******************************************************************************/
void Administor();
void CountingSort(unsigned char* input, size_t size);
static void DoSort(unsigned char* input, size_t size, size_t* counting_arr);
static void CpyArray(unsigned char* dest, unsigned char* src, size_t size);
static void SumCountingArr(size_t *counting_arr, size_t counting_arr_size);
static void* CountingIMP(void* single_range);
static void InitStuff(unsigned char* input, size_t* counting_arr,
                                                 chunk_ty* ranges, size_t size);
static void CheckIfWork(unsigned char* input, size_t size);
/******************************************************************************/
int main()
{
    Administor();

    return 0;
}
/******************************************************************************/
void Administor()
{
    size_t i = 0;
    size_t num_of_ch = INIT;
    FILE *file = NULL;
    char char_runner = '\0';
    unsigned char *arr_of_chars = NULL;

    file = fopen(DICT_PATH,"r");

    assert(file);	
	/* while we didnt get to the end */
	while(EOF != (char_runner = fgetc(file)))
	{
		++num_of_ch;
	}
	/* close the file */
	fclose(file);
    printf("num of chars is: %ld \n", num_of_ch);

    /*dynamically allocate array of all chars*/
    arr_of_chars = (unsigned char*)calloc(num_of_ch, sizeof(char));

    if(NULL == arr_of_chars)
    {
        /*error message*/
        fputs("failed to allocate\n", stderr);
    }
    
    /*open file again*/
    file = fopen(DICT_PATH,"r");
    
    /* while we didnt get to the end */
	while(EOF != (char_runner = fgetc(file)))
	{
		arr_of_chars[i] = char_runner;
        ++i; 
	}
	/* close the file */
	fclose(file);

    CountingSort(arr_of_chars, num_of_ch);
}
/******************************************************************************/
void CountingSort(unsigned char* input, size_t size)
{
    size_t k = 0;
    size_t i = 0;
    size_t count_arr_size = ASCII;
    size_t *counting_arr = NULL;
    chunk_ty ranges[NUM_OF_THREADS];
    pthread_t thread[NUM_OF_THREADS] = {INIT};
    
    counting_arr = (size_t*)calloc(count_arr_size, sizeof(size_t));
    
    if(NULL == counting_arr)
    {
        /*error message*/
        fputs("failed\n", stderr);
    }
    
    InitStuff(input, counting_arr, ranges, size);
    
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
static void CheckIfWork(unsigned char* input, size_t size)
{
    size_t i = 0;

    /*check if it's work*/
    for(i = 0; i < (size - 1); ++i)
	{
		if(input[i] > input[i + 1])
        {
            printf("i failure %ld %d %d\n", i , input[i],input[i+1]);
        }	
	}
}
/******************************************************************************/
static void DoSort(unsigned char* input, size_t size, size_t* counting_arr)
{
    size_t i = 0;
    size_t starting_i = 0;
    unsigned char *tmp_arr = (unsigned char*)calloc(sizeof(unsigned char), size);
    
    while(counting_arr[starting_i] == 0)
    {
        ++starting_i;
    }
    printf("starting index %ld \n", starting_i);
    
    for(i = starting_i; i < size; ++i)
	{      
        tmp_arr[counting_arr[(size_t)input[i]]] = input[i];

        /* decrement the value in the LUT */  
        --counting_arr[(size_t)input[i]];
	}
    CpyArray(input, tmp_arr, size);

    free(tmp_arr);
}
/******************************************************************************/
static void CpyArray(unsigned char* dest, unsigned char* src, size_t size)
{
    size_t i = 0;

    for(i = 0; i < size; ++i)
	{
		dest[i] = src[i];
	}
}
/******************************************************************************/
static void SumCountingArr(size_t *counting_arr, size_t counting_arr_size)
{
    size_t i = 0;
    size_t ctr = 0;

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
    size_t i = 0;
    size_t range_begin = range->range_of_ele[RANGE_BEGIN];
    size_t range_end = range->range_of_ele[RANGE_END];

    unsigned char* arr_to_sort = range->input_arr;
    size_t* counting_arr = range->counting_arr;
   
    for(i = range_begin; i <= range_end; ++i)
    {
        /*atomic fetch and add*/  
        __sync_add_and_fetch(&counting_arr[(size_t)arr_to_sort[i]], 1);
    }
    return NULL;
}
/******************************************************************************/
static void InitStuff(unsigned char* input, size_t* counting_arr,
                                                 chunk_ty* ranges, size_t size)
{
    size_t i = 0;
    size_t num_of_chunks = (size / NUM_OF_THREADS);
    /*init the ranges struct*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        
        ranges[i].input_arr = input;
        ranges[i].counting_arr = counting_arr;
        ranges[i].range_of_ele[RANGE_BEGIN] = i * num_of_chunks;
        ranges[i].range_of_ele[RANGE_END] = (i * num_of_chunks) + (num_of_chunks - 1);
        
        if(NUM_OF_THREADS == (i + 1))
        {
            ranges[i].range_of_ele[RANGE_END] = size;
        }

        printf("thread range begin : %d ",ranges[i].range_of_ele[RANGE_BEGIN]);
        printf("thread range end : %d \n",ranges[i].range_of_ele[RANGE_END]);
    } 
}
/******************************************************************************/


