/*******************************************************************************
 * Project: multi-threads ex1
 * Date: 16/11/2022
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>	
#include <unistd.h>
#include <pthread.h> 
#include <time.h>
/******************************************************************************/
enum{NUM_OF_THREADS = 100000};
enum{INIT = 0};
/******************************************************************************/
/*define 100k arr*/
int arr[NUM_OF_THREADS] = {INIT};
/******************************************************************************/
void* SetIndexIMP(void* index_ptr);
/******************************************************************************/
int main()
{
    int count = INIT;
    int i = INIT;
    /*creat 100k thread hanlder*/
    pthread_t thread_handler[NUM_OF_THREADS];
    /*define time*/
    time_t start_time = time(NULL);

    /*loop to create threads*/
    for(i = INIT; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(thread_handler + i, NULL, &SetIndexIMP, ((void*)&i));
    }
    /*check if we got the correct result*/
    for(i = INIT; i < NUM_OF_THREADS; ++i)
    {
        if(arr[i] != i)
        {
            ++count;
            puts("failed to set value");
        }
    }
    printf("time token = %lds , num of successful threads allocations = %d \n",
                           (time(NULL) - start_time), (NUM_OF_THREADS - count));
    return 0;
}
/******************************************************************************/
void* SetIndexIMP(void* index_ptr)
{
    arr[*(int*)index_ptr] = *(int*)index_ptr;
    return NULL;
}
/******************************************************************************/
