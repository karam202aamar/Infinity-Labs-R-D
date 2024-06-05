/*
Project: ex4 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

#define SIZE 6

void ThreeBitsNum(int arr[])
{
	int count,i,temp;
	
	for(i=0;i<SIZE;i++)
	{	
		temp=arr[i];
		count=0;
		
		while(arr[i]>0)
		{
			if(arr[i]&1)
			{
				count++;
			}
			arr[i]>>=1;
		}
		if(count==3)
		{
			printf("good job we found one %d it's 3 bits number \n",temp);
		}else{
			printf("unfortunately this number %d is not 3 bits\n",temp);
		}
	}
	
}
int main()
{
int array[SIZE]={1,2,3,4,5,7};
ThreeBitsNum(array);

return 0; 
}
