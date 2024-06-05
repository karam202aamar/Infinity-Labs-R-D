#include <stdio.h>

int main()
{
	int num,fact,i;
	do{
		printf("enter a number:");
		scanf("%d",&num);
	}while(num<0);
	
	for(i=1 ; i <= num ; i++)
	{
		fact=fact*i;
	}
	
	printf("%d != %d \n",num,fact);
	
return 0 ;
}
