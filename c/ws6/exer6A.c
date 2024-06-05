/*
Project: ex6 A in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

int FindOn(unsigned char num)
{

	int two_mask,six_mask; 
	
	two_mask=1;
	six_mask=1;
	
	two_mask <<= 1;
	six_mask <<= 5;
		
	return (two_mask & num) && (six_mask & num);

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
