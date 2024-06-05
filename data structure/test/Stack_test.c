#include <stdio.h>  /* print */
#include <assert.h> /* NULL pointers check */
#include <stdlib.h> /* allocation */

#include "stack.h"

static void ImplementFunc();
static void CreateDestroyFunc();
static void StackPeekTest(stack_ty *user_stack);
static void StackCapacityTest(stack_ty *user_stack);
static void StackSizeTest(stack_ty *user_stack);
static void StackIsEmptyTest(stack_ty *user_stack);

/*****************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0;
}

/*****************************************************************************/

static void ImplementFunc()
{
	/* initialize the stack */
	stack_ty *ptr_stack = 	StackCreate(3, 4);
	
	int element1 = 5;
	int element2 = 10;
	int element3 = 15;
	
	/* push the three elements we have */
	StackPush(ptr_stack, &element1);
	StackPush(ptr_stack, &element2);
	StackPush(ptr_stack, &element3);
	
	/* check if the peek func works */
	StackPeekTest(ptr_stack);
	
	/* check if the capacity func works */
	StackCapacityTest(ptr_stack);	
	
	/* pop an elemt and check if the size updates */
	StackPop(ptr_stack);
	StackSizeTest(ptr_stack);
	
	/* pop the second and third and check if it's empty */
	StackPop(ptr_stack);
	StackPop(ptr_stack);
	StackIsEmptyTest(ptr_stack);
	
	 CreateDestroyFunc(); 
}

/*****************************************************************************/

static void CreateDestroyFunc()
{
	stack_ty *test_stacks = (stack_ty*)malloc(SizeOfStruct());
	
	StackDestroy(test_stacks);
}

/*****************************************************************************/

static void StackPeekTest(stack_ty *user_stack)
{
	assert(user_stack);
	
	if(15 == *(int*)StackPeek(user_stack))
	{
		NULL;
	}else
	{
		printf("failed to peek\n");
		printf("failed to push\n");
	}
}

/*****************************************************************************/

static void StackCapacityTest(stack_ty *user_stack)
{
	assert(user_stack);
	
	if(12 == StackCapacity(user_stack))
	{
		NULL;
	}else
	{
		printf("\nstack capacity doesn't works \n");
	}
	
}

/*****************************************************************************/

static void StackSizeTest(stack_ty *user_stack)
{
	assert(user_stack);

	if(2 == StackSize(user_stack))
	{
		NULL;
	}else 
	{
		printf("\nstack size doesn't works \n");
		printf("failed to pop\n");
	}
}

/*****************************************************************************/

static void StackIsEmptyTest(stack_ty *user_stack)
{
	assert(user_stack);
	
	if(1 == StackIsEmpty(user_stack))
	{
		NULL;
	}else
	{
		printf("\nstackisempty doesn't works \n");
	}
}

/*****************************************************************************/
