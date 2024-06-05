/******************************************************************************/
#include <stdio.h>
/******************************************************************************/
enum {INIT = 0, FIRST_ELE = 0, RESULT_PARA = 3, ARRAY_SIZE = 8};
/******************************************************************************/
int BursaIMP(int arr[] , int result[], int arraysize);
/******************************************************************************/
int main()
{
    int result[RESULT_PARA] = {INIT};
    int arr[ARRAY_SIZE] = {6,12,3,5,1,4,9,2};

    BursaIMP(arr, result, ARRAY_SIZE);

	printf("the maximum profit is %d the indexes are %d %d \n ", result[2],
                                                          result[0], result[1]);
    return 0;
}
/******************************************************************************/
int BursaIMP(int arr[] , int result[], int arraysize)
{
    /*define variables*/
    int current_max = INIT;
    int curret_min = INIT;
    int current_sum = INIT;
    int i = INIT;
    int max_profit = INIT, starting_index = INIT, finish_index = INIT;   

    /*starting position*/
    curret_min = arr[FIRST_ELE];
    current_max = arr[FIRST_ELE];

    /*loop*/
    for(i = INIT; i < arraysize; i++)
    {
        /*if we find new minimum - then start from this point */
	    if(arr[i] < curret_min)
	    {
		    curret_min = arr[i];
		    current_max = arr[i];
		    starting_index = i;
	    }
        /*if we found a bigger value the update current max */
	    if(arr[i] > current_max)
	    {
		    current_max = arr[i];
		    finish_index = i;
	    }
        /*check current profit*/
        current_sum = current_max - curret_min;

        /*if it's bigger then update max profit*/
	    if(current_sum > max_profit)
	    {
		    max_profit = current_max - curret_min;
		    finish_index = i;
		    result[0] = starting_index;
		    result[1] = finish_index;
		    result[2] = max_profit ;
	    }
    }
 	return 0; 
}
/******************************************************************************/