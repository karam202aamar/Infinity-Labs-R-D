/*
Project: Bitwise ex1
Date: 18/7/22
Reviewer: Karam
Version: 1.0 Befor review
*/
/*--------------------------------------------------*/

#include <stdio.h> /*pust printf scanf*/

long DupPowOfTwo(unsigned int x, unsigned int y);
/*--------------------------------------------------*/
int main()
{
    unsigned x = 0;
    unsigned y = 0;
    
    puts("Enter x:");
    scanf("%u", &x);
    puts("Enter y:");
    scanf("%u", &y);
    
    printf("Result: %ld",DupPowOfTwo(x,y));
    
    return 0;
}
long DupPowOfTwo(unsigned int x, unsigned int y)
{
	return x<<y;
}

