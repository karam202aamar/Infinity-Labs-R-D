/*
Project: ex3 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

int AddOne(int num);

int main()
{
printf("%d",AddOne(-12));
return 0; 
}

int AddOne(int num)
{
	int number_one=1;
	/*we need to flip all the bits after the rightmost 0 bit */
	/*while we have 1 int the two bits continue i want zero */
	while(num & number_one)
	{
		num=num^number_one;
		number_one<<=1;
	}
	/*flip the last zero*/
	num=num^number_one;
	return num;
	
}
