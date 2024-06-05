#include <stdio.h>  /* print */
/*****************************************************************************/
#define ARRAY_SIZE 5
/*****************************************************************************/
int RemoveDuplicates(int *array,int length);
/*****************************************************************************/
int main()
{
	int count= 0;
	int i = 0;
	int array[ARRAY_SIZE] = {1,1,1,5,4};
	
        count = RemoveDuplicates(array , ARRAY_SIZE);
        
	printf("number of non duplicated is : %d\n",count);
	
	for(i = 0 ; i< count ; i++)
	{
		printf("%d\n",array[i]);
	}
	
	return 0;
}
/*****************************************************************************/
int RemoveDuplicates(int *array,int length)
{
	/* set i runner and temp */
	int i = 0 , allowed = 0;
	
	/* check if the length is one or zerp then retun from the function */
	if(length == 0 || length == 1)
	{
		return length;
	}
	
	/* loop on the array */
	for(i ; i < length ; i++)
	{
		/* if we dont have the same value then set next*/
		if(array[i] != array[i+1])
		{
			array[allowed] = array[i];
			allowed++;
		}
	}
	
	return allowed;
}
