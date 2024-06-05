/*******************************************************************************
 * Project: CALCULTOR TEST
 * Date: 03/10/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>	
#include "recursion.h"
/******************************************************************************/
static void ImplementFunc();
static void FibonacciTest();
static void FibonacciRecTest();
static void FlipListTest();
static void StrlenTest();
static void StrcmpTest();
static void StrcpyTest();
static void StrcatTest();
static void StrstrTest();
static void RecStackSortTest();
/******************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	FibonacciTest();
	FibonacciRecTest();
	FlipListTest();
	StrlenTest();
	StrcmpTest();
	StrcpyTest();
	StrcatTest();
	StrstrTest();
	RecStackSortTest();
}
/******************************************************************************/
static void FibonacciTest()
{
	int result = 0;
	
	result = Fibonacci(6);
	
	if(8 != result)
	{
		puts("FibonacciTest failed\n");
	}
}
/******************************************************************************/
static void FibonacciRecTest()
{
	int result = 0;
	
	result = Fibonacci(6);
	
	if(8 != result)
	{
		puts("FibonacciTest failed\n");
	}
}
/******************************************************************************/
static void FlipListTest()
{
	node_ty *first_node = (node_ty *)malloc(sizeof(node_ty));
	node_ty *second_node = (node_ty *)malloc(sizeof(node_ty));
	node_ty *third_node = (node_ty *)malloc(sizeof(node_ty));

	node_ty *runner = third_node;
	
	int a = 1;
	int b = 2;
	int c = 3;
	
	first_node->data = &a;
	first_node->next = second_node;
	second_node->data = &b;
	second_node->next = third_node;
	third_node->data = &c;
	third_node->next = NULL;

	FlipList(first_node);
	
	if(3 != *(int *)runner->data && 2 != *(int *)runner->next->data && 
						1 !=*(int *)runner->next->data)
	{
		puts("FlipListTest failed\n");
	}
	
	free(first_node);
	free(second_node);
	free(third_node);
}
/******************************************************************************/
static void StrlenTest()
{
	const char *str = "hello";
	
	if(5 != Strlen(str))
	{
		puts("StrlenTest failed\n");
	}
}
/******************************************************************************/
static void StrcmpTest()
{
	const char *str1 = "hello";
	const char *str2 = "hello";
	const char *str3 = "kello";
	
	if(0 != Strcmp(str1 , str2))
	{
		puts("StrcmpTest first test failed\n");
	}
	if(0 > Strcmp(str1 , str3))
	{
		puts("StrcmpTest second test failed\n");
	}
}
/******************************************************************************/
static void StrcpyTest()
{
	const char *str1 = "hello";
	char str2[6] = {'k','a','r','a','m','\0'};
	
	Strcpy(str2 , str1);
	
	if(0 != Strcmp(str1,str2))
	{
		puts("StrcpyTest failed\n");
	}
}
/******************************************************************************/
static void StrcatTest()
{
	char str1[30] = {'k','a','r','a','m','\0'};
	char str2[30] = {'a','a','m','a','r','\0'};
	char result[30] = {'k','a','r','a','m','a','a','m','a','r','\0'};
	
	Strcat(str1 , str2);

	if(0 != Strcmp(str1,result))
	{
		puts("StrcatTest failed\n");
	}
}
/******************************************************************************/
static void StrstrTest()
{
	char haystack[30] = {'k','a','r','a','m',' ','a','a','m','a','r','\0'};
	char needle[30] = {'a','a','m','a','r','\0'};
	
	if(0 != Strcmp(needle,Strstr(haystack , needle)))
	{
		puts("StrstrTest failed\n");
	}
}
/******************************************************************************/
static void RecStackSortTest()
{
	/* initialize the stack */
	stack_ty *ptr_stack = 	StackCreate(3, 4);
	
	int element1 = 15;
	int element2 = 10;
	int element3 = 5;
	
	/* push the three elements we have */
	StackPush(ptr_stack, &element1);
	StackPush(ptr_stack, &element2);
	StackPush(ptr_stack, &element3);
	
	RecStackSort(ptr_stack);
	
	if(15 != *(int*)StackPeek(ptr_stack))
	{
		puts("StrstrTest failed\n");
	}
	
	StackPop(ptr_stack);
	
	if(10 != *(int*)StackPeek(ptr_stack))
	{
		puts("StrstrTest failed\n");
	}
	
	StackPop(ptr_stack);
	
	if(5 != *(int*)StackPeek(ptr_stack))
	{
		puts("StrstrTest failed\n");
	}
	
	StackDestroy(ptr_stack);
}
/******************************************************************************/







