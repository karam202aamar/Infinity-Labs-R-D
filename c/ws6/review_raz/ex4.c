/*
Project: Bitwise ex4
Date: 18/7/22
Reviewer: Karam
Version: 1.0 Befor review
*/
/*--------------------------------------------------*/

#include <stdio.h> /* printf */

#define MAX_BIT_COUNT 3
#define ARR_LEN 5

static void InputArr();

static void ThreeOnes(unsigned int *arr, size_t arr_len);
static int CountThreeOnes(unsigned int curr_num);

/*--------------------------------------------------*/
int main()
{
    InputArr();
    
    return 0;
}
static void InputArr()
{
	unsigned int arr[ARR_LEN] = {1,7,0,14,9};
	
	ThreeOnes(arr, ARR_LEN);
}
static void ThreeOnes(unsigned int *arr, size_t arr_len)
{
	size_t count_success = 0;
	size_t i = 0;
	
	while(i < arr_len)
	{
		if(CountThreeOnes(arr[i]) == 1)
		{
			++count_success;
		}
		++i;
	}
	printf("The total number of times it is shown in the array: %ld", 
	count_success);
}
static int CountThreeOnes(unsigned int curr_num)
{
	unsigned int temp_num = curr_num;
	unsigned int curr_count = 0;
	
	while((0 != curr_num) && (MAX_BIT_COUNT+1 > curr_count))
	{
		if(curr_num & 1)
		{
			++curr_count;
		}
		curr_num = curr_num>>1;		
	}
	if(MAX_BIT_COUNT == curr_count)
	{
		printf("The number %ld has 3 digits turn on\n",temp_num);
		return 1;
	}
	else
	{
		return 0;
	}
}
