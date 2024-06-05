/*
Project: Bitwise ex2
Date: 18/7/22
Reviewer: Karam
Version: 1.0 Befor review
*/
/*--------------------------------------------------*/

#include <stdio.h> /*pust printf scanf*/

size_t PowOfTwoNoLoop(unsigned int x);
size_t PowOfTwoWithLoop(unsigned int x);
/*--------------------------------------------------*/
int main()
{
    unsigned x = 0;
    
    puts("Enter x:");
    scanf("%u", &x);
    
    printf(" No Loop:%ld",PowOfTwoNoLoop(x));
	printf(" With Loop %ld",PowOfTwoWithLoop(x));    
    return 0;
}
size_t PowOfTwoNoLoop(unsigned int x)
{
	if((x > 0) && (x&(x-1)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
size_t PowOfTwoWithLoop(unsigned int x)
{
	size_t and_count = 0;
	
	while(0 != x)
	{
		if((x & 1) == 1)
		{
			++and_count;
		}
		x = x>>1;
	}
	if(and_count == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
