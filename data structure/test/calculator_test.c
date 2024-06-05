/*******************************************************************************
 * Project: CALCULTOR TEST
 * Date: 03/10/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>	
#include "calculator.h"
/******************************************************************************/
static void CalculateTest();
/******************************************************************************/
int main()
{
	CalculateTest();
	
	return 0;
}
/******************************************************************************/
static void CalculateTest()
{
	double calc_res = 0;
	
	char *str = "7 -6 + 1";
	char *str2 = "10 * 5 / 2";
	char *str3 = "(5 + 3*2) * 5";
	char *str4 = "5 + -3 + -10";
	
	Calculate(str , &calc_res);
	
	if(2 != calc_res)
	{
		puts("STAGE 1 FAILED \n");
	}
	
	Calculate(str2 , &calc_res);
	
	if(25 != calc_res)
	{
		puts("STAGE 2 FAILED \n");
	}
	
	Calculate(str3 , &calc_res);
	
	if(55 != calc_res)
	{
		puts("STAGE 3 FAILED \n");
	}
	
	Calculate(str4 , &calc_res);
	
	if(-8 != calc_res)
	{
		puts("STAGE 3 FAILED \n");
	}
}
/******************************************************************************/
	
