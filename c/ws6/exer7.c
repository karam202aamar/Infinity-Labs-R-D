/*
Project: ex7 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

int DivisibleNum(unsigned int num)
{
	num=num>>4;
	num=num<<4;
	return num;
}

int main()
{
unsigned int num; 

printf("enter your number:\n");
scanf("%u",&num);

printf("your divisible is : %d \n",DivisibleNum(num));
  
return 0; 
}
