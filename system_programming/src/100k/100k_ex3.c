/*******************************************************************************
 * Project: multi-threads ex2
 * Date: 16/11/2022
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>	
#include <unistd.h>
#include <pthread.h> 
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
    int i = INIT;
    int status = INIT;

    /*creat 100k thread hanlder*/
    pthread_t thread_handler[NUM_OF_THREADS];
    /*define indexes array*/
    int indexes_arr[NUM_OF_THREADS] = {0};

    /*loop to create threads*/
    for(i = INIT; i < NUM_OF_THREADS; ++i)
    {
        indexes_arr[i] = i;
        status = pthread_create(thread_handler + i, NULL, &SetIndexIMP, &indexes_arr[i]);
        /*detach threads*/
        pthread_detach(thread_handler[i]);

        /*check if the thread creation success*/
        if(status)
        {
            /*loop untill it success*/
            while(status)
            {   
                /* create again */
                status = pthread_create(thread_handler + i, NULL, &SetIndexIMP, &indexes_arr[i]);
                puts("infinity");           
            }
        }
    }
    for(i = 0; i < NUM_OF_THREADS ; ++i)
    {
        if(arr[i] != i)
        {
            printf("failed \n");
        }
    }
    pthread_exit(0);
}
/******************************************************************************/
void* SetIndexIMP(void* index_ptr)
{
    int index = *(int*)index_ptr;
    arr[index] = index;
    
    return NULL;
}
/******************************************************************************/

