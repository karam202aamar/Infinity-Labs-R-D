#include <stdio.h>

#define ARRAY_SIZE 6

int IsSumFound(int sum , int * arr , int index_arr[])
{
  int start_index,end_index,sum_index;    
  int *ptr1;
  
  ptr1=arr;
  start_index=0;
  end_index= ARRAY_SIZE-1;
   
 while(end_index>start_index)
 {
	sum_index= ptr1[start_index]+ptr1[end_index];
	
	if(sum_index > sum )
	{
		end_index--;
	}else {
		if(sum_index < sum )
		{
		start_index++;
		}
	}
	
	if(sum_index ==sum )
	{
		index_arr[0]=start_index;
		index_arr[1]=end_index;
		return 1;
	}
  }
	return 0; 
}

int main()
{
int index[2];
int arr[ARRAY_SIZE]={4,5,6,7,14,16};
int sum=21;
int result=0;

result=IsSumFound(sum,arr,index);

if(result==1)
{
	printf("you did it the index are %d %d\n ",index[0],index[1]);
}else
{
	printf("not found");
}


return 0;
}
