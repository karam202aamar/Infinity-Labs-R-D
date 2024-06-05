/*
Project: ex5 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

#define SIZE_OF_BYTE 8

int ByteMirros(unsigned char num)
{
	int i,reversed,size=8;
	
	for (i = 1 << 7 ; i > 0 ; i = i / 2)
	{
		(num & i) ? printf("1") : printf("0");
	}
	
	printf("\n");	
	
	 while (size--)
	{
		reversed = (reversed << 1) | (num & 1);
		num >>= 1;
	}
	printf("function one :\n ");	
	for (i = 1 << 7 ; i > 0 ; i = i / 2)
	{
		(reversed & i) ? printf("1") : printf("0");
	}
	return 0; 
}
int ByteMirrosNoLoop(unsigned char num)
{	
	int i;
	num = ((num & 0xf0) >> 4) | ((num & 0x0f) << 4);
	num = ((num & 0xcc) >> 2) | ((num & 0x33) << 2);
	num = ((num & 0xaa) >> 1) | ((num & 0x55) << 1);
	printf("\n");
	
	for (i = 1 << 7 ; i > 0 ; i = i / 2)
	{
		(num & i) ? printf("1") : printf("0");
	}
	printf("function two :\n ");	
}

int main()
{
	ByteMirros('a');
	ByteMirrosNoLoop('a');
return 0; 
}
