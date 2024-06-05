/*
Project: ex2 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

int PowOfTwo_a(unsigned int num);
int PowOfTwo_b(unsigned int num);

int main()
{
printf("the result of function a %d \n",PowOfTwo_a(10));
printf("the result of function b %d \n",PowOfTwo_b(10));

return 0 ; 
}

int PowOfTwo_a(unsigned int num)
{
	int count=0;
	
	while(num>0)
	{
		if(num&1)
		{
			count++;
		}
		num>>=1;
	}
	if(count==1)
		return 1; 
	else 
		return 0; 	
}
int PowOfTwo_b(unsigned int num)
{
	if(!(num&(num-1)))
	{
		return 1; 
	}else return 0;
}

