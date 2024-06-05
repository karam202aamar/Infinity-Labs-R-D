#include <stdio.h>  /* print */
#include <stdlib.h> /* allocation */
/******************************************************************************/
#include "Stack.h"
/*********************************struct***************************************/
typedef struct min stack 
{
	stack_ty *push_stack;
	stack_ty *min_stack;
}min_stack_ty;
/*********************************create***************************************/
min_stack_ty MinStackCreate(capacity) /* for ints */ 
{
	/* define struct & stacks */
	min_stack_ty *min_stack = NULL;
	stack_ty *push_stack = NULL;
	stack_ty *min_stack = NULL;
	
	/* dynamically allocate memory for min stack struct */
	min_stack = (min_stack_ty*)malloc(sizeof(min_stack_ty));
	
	/* check fail allocation */
	if(NULL == min_stack)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	/* dynamically allocate memory for push_stack */
	push_stack = StackCreate(capacity,sizeof(int));
	
	/* check fail allocation */
	if(NULL == push_stack)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	/* dynamically allocate memory for min_stack */
	min_stack = StackCreate(capacity,sizeof(int));
	
	/* check fail allocation */
	if(NULL == min_stack)
	{
		perror(strerror(errno));
		return NULL;
	}
	return min_stack;
}
/********************************* push ***************************************/
void MinStackPush(min_stack_ty *stack_wrapper , int data)
{
	/* stackpush (push stack)*/
	StackPush(stack_wrapper->push_stack , &data);
	
	/* if(StackIsEmpty(min stack) || data <= stackpeek(min stack))*/
	if(StackIsEmpty(stack_wrapper) || data <= stackpeek(stack_wrapper->min_stack))
	{
		/* if true push to min stack */
		StackPush(stack_wrapper->min_stack , &data);
	}else
	{
		/* else push to min_stack the current minimum sowe dont 
					have to check every time if equals */
		StackPush(stack_wrapper->min_stack , GetMinValue(stack_wrapper));
	}
							
}
/*********************************  pop ***************************************/
void MinStackPop(min_stack_ty * stack_wrapper)
{
	/* pop from both stacks */
	StackPop(stack_wrapper->min_stack);
	StackPop(stack_wrapper->push_stack);
}
/*********************************get value************************************/
int GetMinValue(min_stack_ty * stack_wrapper)
{
	/* peek from min stack */
	return *(int*)StackPeek(stack_wrapper->min_stack);
}



