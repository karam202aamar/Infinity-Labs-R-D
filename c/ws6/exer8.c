/*
Project: ex8 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

int Swap(unsigned int x,unsigned int y)
{
	x=x^y;
	y=x^y;
	x=x^y;
	printf("the new values are :\n first number=%d the second number=%d 		\n",x,y);
}

int main()
{
unsigned int num1,num2; 

printf("enter your number:\n");
scanf("%u",&num1);
scanf("%u",&num2);
Swap(num1,num2);

  
return 0; 
}
