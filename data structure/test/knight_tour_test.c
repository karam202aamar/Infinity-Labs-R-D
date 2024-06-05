/*******************************************************************************
 * Project: Data Structures - 
 * Date: 
 * Name: 
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>
#include "knight_tour.h"
/******************************************************************************/
static void ImplmentFunc();
/******************************************************************************/
int main()
{	
	ImplmentFunc();

	return 0;
}
/******************************************************************************/
static void ImplmentFunc()
{
	int i = 0;

	unsigned char start_position = 0;

	unsigned char tour[64];
	
	if(1 == KnightTour(tour, start_position))
	{
		puts("KnightTour function failed");
	}

	for(i = 0; i < 64; ++i)
	{
		printf("%d ->",tour[i]);

		if(i == 7)
		{
			puts(" ");
		}
	}
}
/******************************************************************************/
