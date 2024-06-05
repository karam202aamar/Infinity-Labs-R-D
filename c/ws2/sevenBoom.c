#include <stdio.h>  /* prints*/

#define MAX_NUM 50 

void Sevens(size_t arr[],int start,int end);

int main()
{	
	int i,number_digits,startm,endm;
	size_t array[MAX_NUM];
	
	printf("enter how much numbers you want to enter :");
	scanf("%d",&number_digits);
	
	for(i=0 ; i<number_digits ; i++)
	{
		scanf("%d",&array[i]);
	}
	printf("enter the index of the the range: ");
	scanf("%d",&startm);
	scanf("%d",&endm);
	
	Sevens(array,startm,endm);
	
	
	return 0;
}

void Sevens(size_t arr[],int start,int end)
{ 
	int i;
	
	for(i=start;i<end;i++)
	{
		if((arr[i])%7==0)
		{
			printf("\n BOOM \n");
		}else 
		{
			printf("\n %ld \n",arr[i]);
		}
	
	
	}
}


