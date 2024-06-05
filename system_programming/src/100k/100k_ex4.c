/*******************************************************************************
 * Project: multi-threads ex4
 * Date: 16/11/2022
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>	
#include <unistd.h>
#include <pthread.h> 
#include <stdlib.h> 
#include <time.h>
/******************************************************************************/
enum{NUM_OF_THREADS = 32000};
enum{INIT = 0};
/******************************************************************************/
/*define 100k arr*/
int arr[NUM_OF_THREADS] = {INIT};
/******************************************************************************/
void* DivisorsIMP(void* index_ptr);
/******************************************************************************/
const size_t input = 400000000;
size_t num_of_ranges = input / NUM_OF_THREADS;

int main()
{   
    size_t i = INIT;
    size_t sum_of_divisors = INIT;
    size_t *ret_val = NULL;
    size_t *index = NULL;
    time_t start_time = time(NULL);

    /*creat 100k thread hanlder*/
    pthread_t thread_handler[NUM_OF_THREADS];
    
    /*loop to create threads*/
    for(i = INIT; i < NUM_OF_THREADS; ++i)
    {
        index = (size_t*)malloc(sizeof(size_t));
        *index = i * num_of_ranges;
        pthread_create(thread_handler + i, NULL, &DivisorsIMP, index);
    }
    /*loop to join the the threads*/
    for(i = INIT; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_join(thread_handler[i], (void**)&ret_val))
        {
            perror("failed to join thread");
            return 1;
        }
        sum_of_divisors += *ret_val;
        free(ret_val);
    }

    printf("sum of divisors: %ld \n", sum_of_divisors);
    printf("the time token = %lds \n", (time(NULL) - start_time));

    return 0;
}
/******************************************************************************/
void* DivisorsIMP(void* arg)
{
    size_t i = 0;
    size_t sum_of_divisors = 0;
	size_t curr_i = *(size_t *)arg;

	for(i = curr_i + 1; i <= (curr_i + num_of_ranges) ; ++i)
	{
		if(0 == input % i)
		{
			sum_of_divisors += i;
		}
	}
    *(size_t *)arg = sum_of_divisors;
   
    return arg;
}
/******************************************************************************/

