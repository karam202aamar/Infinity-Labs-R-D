#include <stdio.h>

#define ARRAY_SIZE 8

int FindMax(int arr[] , int index_arr[])
{
  int max,min,max_profit=0,i,sum,index_s,index_e;    

min=arr[0];
max=arr[0];

for(i=0;i<ARRAY_SIZE;i++)
{
	if(arr[i]<min)
	{
		min=arr[i];
		max=arr[i];
		index_s=i;
	}
	if(arr[i]>max)
	{
		
		max=arr[i];
		index_e=i;
	}
	
	sum=max-min;
	if(sum>max_profit)
	{
		max_profit=max-min;
		index_e=i;
		index_arr[0]=index_s;
		index_arr[1]=index_e;
		index_arr[2]=max_profit ;
	}
}
 		
 
	return 0; 
}

int main()
{
int index[3];
int arr[ARRAY_SIZE]={3,2,1,5,6,12,0,7};

FindMax(arr,index);

	printf("the maximum profit is %d the indexes are %d %d \n ",index[2],index[0],index[1]);

return 0;

}
