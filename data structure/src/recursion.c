/*******************************************************************************
 Project: Data Structures - Recursion
 Date: 09.10.22
 Name: 
 Reviewer: 
 Version: 1.0
*******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "recursion.h"
/******************************************************************************/
#define STR_END '\0'
/******************************************************************************/
static void InsertSorted(stack_ty* stack , int data);
/******************************************************************************/
int Fibonacci(int index)
{
	int i = 0;
	int array[3] = {0,1,1}; 
  
	if(0 == index)
	{
		return 0;
	}
	else if(1 == index)
	{
		return 1;
	}
	else 
	{
		for (i = 2 ; i <= index ; i++)
		{
			array[2] = array[1] + array[0];
			array[0] = array[1];
			array[1] = array[2];
		}
	} 
	return array[2]; 
}
/******************************************************************************/
int FibonacciRec(int index)
{
	if(0 == index)
	{
		return 0;
	}
	else if(1 == index)
	{
		return 1;
	}
	else 
	{
		return FibonacciRec(index - 1) + FibonacciRec(index - 2);
	} 	
}
/******************************************************************************/
node_ty* FlipList(node_ty* head)
{
	/* define ptr to the last last */
	node_ty *return_last_node = NULL;
	
	assert(head);
	
	if(head->next)
	{
		/* recursive call */
		return_last_node = FlipList(head->next);
		/* flip next pointer */
		head->next->next = head;
		head->next = NULL;
	}
	else
	{
		/* return last head - (else if) */
		return head;
	}
	return return_last_node;
}
/******************************************************************************/
size_t Strlen(const char *str)
{
	const char* str_runner = str;
	
	assert(str);
	
	if(STR_END == *str_runner)
	{
		return 0;
		
	}
	return 1 + Strlen(++str_runner);
}
/******************************************************************************/
int Strcmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	
	/* the strings are equal */
	if(STR_END == *str1 && STR_END == *str2)
	{
		return 0;
	}
	if(*str1 > *str2)
	{
		return (*str1 - *str2);
	}
	if(*str1 < *str2)
	{
		return (*str2 - *str1);;
	}
	return Strcmp(++str1 , ++str2);
}
/******************************************************************************/
char *Strcpy(char *dest, const char *src)
{
	assert(dest);
	assert(src);
	
	if(STR_END == *src)
	{
		/* copy the NULL terminator */
		*dest = *src;
		return dest;
	}
	/* copy chars */
	*dest = *src;
	/* call the function again */ 
	Strcpy(++dest , ++src);
	
	return dest;
}
/******************************************************************************/
char *Strcat(char *dest, const char *src)
{
	assert(dest);
	assert(src);
	
	/* if I reached the end of dest */
	if(STR_END == *dest)
	{
		/* cpy the value of src into dest */
		Strcpy(dest , src);
		return NULL;
	}
	/* move to next char*/
	Strcat(++dest , src);
	
	return dest;
}
/******************************************************************************/
char *Strstr(const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);
	
	if(STR_END == *haystack)
	{
		return NULL;
	}
	else if(strncmp(haystack , needle , strlen(needle)) == 0)
	{
		return (char*)haystack;
	}
	else
	{
		return Strstr(++haystack,needle);
	}
}
/******************************************************************************/
void RecStackSort(stack_ty* stack)
{
	int data = 0;
	
	assert(stack);
	
	if(!StackIsEmpty(stack))
	{
		/* set the value in the stack to data */
		data = *(int*)StackPeek(stack);
		/* pop this value */
		StackPop(stack);
		/* call the function again */
		RecStackSort(stack);
		/* call helper function */
		InsertSorted(stack , data);
	}
}
/******************************************************************************/
static void InsertSorted(stack_ty* stack , int data)
{
	int curr_data;
	
	/* if the stack is empty then insert data */
	if(StackIsEmpty(stack))
	{
		StackPush(stack , &data);
	}
	/* If current data bigger than the value in the stack - push it*/
	else if(data > *(int*)StackPeek(stack))
	{
		StackPush(stack , &data);
	}
	/* if current value in the stack bigger than data - replace it */
	else if(*(int*)StackPeek(stack) > data)
	{
		curr_data = *(int*)StackPeek(stack);
		
		StackPop(stack);
		
		InsertSorted(stack , data);
		
		StackPush(stack , &curr_data);
	}	
}
/******************************************************************************/



















