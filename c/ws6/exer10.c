/*
Project: ex10 in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/

#include <stdio.h>


void FloatAnalysis(int* fnum);

int main()
{
	float number; 
	int *ptr;
	ptr=(int*)&number;
	
	printf("enter your float number:");
	scanf("%e",&number);
	
	FloatAnalysis(ptr);
	
	return 0;
}
void FloatAnalysis(int* fnum)
{
	int i;
	int *p;
	
	p = fnum;
	
	for (i = sizeof(float) * 8 - 1; i >= 0; i--)
	{   
		printf("%d", (*p) >> i & 1); 
	}   

	
}	



