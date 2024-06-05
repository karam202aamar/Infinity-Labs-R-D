/*******************************************************************************
 * Project: multi-threads ex5
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
size_t DivisorsIMP();
/******************************************************************************/
const size_t input = 400000000;

int main()
{   
    size_t i = INIT;
    size_t sum_of_divisors = INIT;
    time_t start_time = time(NULL);

    sum_of_divisors = DivisorsIMP();

    printf("sum of divisors: %ld \n", sum_of_divisors);
    printf("the time token = %lds \n", (time(NULL) - start_time));

    return 0;
}
/******************************************************************************/
size_t DivisorsIMP()
{
    size_t i = 0;
    size_t sum_of_divisors = 0;

	for(i = 1; i <= input; ++i)
    {
        if(0 == input % i)
        {
            sum_of_divisors += i;
        }
    }
    return sum_of_divisors;
}
/******************************************************************************/

