/*
Project: ex6 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

int FindOn(unsigned char num)
{

	if(((num>>1)&1) && ((num>>5)&1))
	{
		return 1;
	}else   return 0;
	
}

int main()
{
unsigned char ch; 

printf("enter your number:");
scanf("%c",&ch);

	if(FindOn(ch))
	{
		printf("true\n");
	}else 	{
  	printf("false\n");
     		 }

return 0; 
}
