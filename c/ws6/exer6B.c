/*
Project: ex6 B in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>


int FindOnB(unsigned char num)
{

	int two_mask,six_mask; 
	
	two_mask=1;
	six_mask=1;
	
	two_mask <<= 1;
	six_mask <<= 5;
		
	return (two_mask & num) || (six_mask & num);
}

int main()
{
char ch; 

printf("enter your number:");
scanf("%c",&ch);

if(FindOnB(ch))
{
	printf("true FUNC B\n");
}else {
  printf("false FUNC B\n");
      }
     
return 0; 
}
