/*
Project: Bitwise ex8
Date: 19/7/22
Reviewer: Karam
Version: 1.0 work
*/
/*--------------------------------------------------*/

#include <stdio.h> /*printf scanf*/

void UserInput();

void SwapToVar(unsigned int *first_num, unsigned int *second_num);
/*--------------------------------------------------*/
int main() 
{
	UserInput();
  	return 0; 
}

 void UserInput()
{
	unsigned int first_num = 0;
	unsigned int second_num = 0;
	
	printf("Enter first number:");
	scanf("%u", &first_num);
	printf("Enter first number:");
	scanf("%u", &second_num);
	printf("Numbers befor swap:%u , %u \n", first_num, second_num);
	SwapToVar(&first_num, &second_num);
} 

void SwapToVar(unsigned int *first_num, unsigned int *second_num)
{
    *first_num = *first_num ^ *second_num;
    *second_num = *first_num ^ *second_num;
    *first_num = *first_num ^ *second_num;
	printf("Numbers after swap:%u, %u \n",*first_num,*second_num);
}

