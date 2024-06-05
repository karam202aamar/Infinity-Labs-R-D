/*
Project: ex1 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

long Pow(unsigned int x,unsigned int y);

int main()
{
	unsigned x = 0;
	unsigned y = 0;
    
	puts("Enter x:");
	scanf("%u", &x);
	puts("Enter y:");
	scanf("%u", &y);
    
	printf("Result: %ld",Pow2(x,y));
    
return 0 ; 
}

long Pow(unsigned int x,unsigned int y)
{
	return x<<y;
}
