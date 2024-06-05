/*
Project: ex9 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/

#include <stdio.h>

unsigned int countSetBits(unsigned int num);

/* Program to test function countSetBits */
int main()
{
	unsigned int number;
	printf("enter your number honey:");
	scanf("%u",&number);
	printf("%d\n", countSetBits(number));
    return 0;
}

unsigned int countSetBits(unsigned int num)
{
    unsigned int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}
 
