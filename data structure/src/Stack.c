#include <stdio.h>  /* print */
#include <assert.h> /* NULL pointers check */
#include <stdlib.h> /* allocation */
#include <string.h> /* memcpy strerror */
#include <errno.h>  /* errno perror */

#include "stack.h"

size_t SizeOfStruct();

/*****************************************************************************/
	/* definition of the struct*/
struct stack 
{
	void *array;
	size_t num_of_elem;
	size_t size_of_elemt;
	size_t current_num_of_elem;
};

/*****************************************************************************/
	
stack_ty *StackCreate(size_t max_num_of_elem, size_t size_of_elem)
{
	/* dynamic allocation for the array */
	char *ptr_to_array = (char*)malloc(max_num_of_elem * size_of_elem);
	
	/* dynamic allocation */
	stack_ty *stack_obj = (stack_ty*)malloc(sizeof(stack_ty));
	
	assert(max_num_of_elem);
	assert(size_of_elem);
	
	if(NULL == ptr_to_array)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	if(NULL == stack_obj)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	/* assignment the values */
	stack_obj->array = ptr_to_array;
	stack_obj->num_of_elem = max_num_of_elem;
	stack_obj->size_of_elemt = size_of_elem;
	stack_obj->current_num_of_elem = 0;
	
	return stack_obj;
}
/*****************************************************************************/

void StackDestroy(stack_ty *user_stack)
{
	free(user_stack -> array);
	free(user_stack);	
}

/*****************************************************************************/
void StackPush(stack_ty *user_stack, void *elem_to_push)
{
	assert(user_stack);
	assert(elem_to_push);
	assert(user_stack -> current_num_of_elem < user_stack -> num_of_elem);
	
	memcpy((char *)user_stack -> array + ((user_stack -> 
			current_num_of_elem) * (user_stack -> size_of_elemt)) 
				, elem_to_push , user_stack -> size_of_elemt);
					
	++(user_stack -> current_num_of_elem);
}

/*****************************************************************************/

void StackPop(stack_ty *user_stack)
{
	assert(user_stack);
	
	--(user_stack -> current_num_of_elem);
}

/*****************************************************************************/

void * StackPeek(stack_ty *user_stack)
{
	assert(user_stack);
	
	return ((char *)user_stack -> array +
		  ((user_stack -> current_num_of_elem - 1) 
	 	              * (user_stack -> size_of_elemt)));
/* this char* to use arithmetic on the pointer i know how mush steps to */
}
          
/*****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
size_t StackSize(stack_ty *user_stack)
{
	assert(user_stack);
	return (user_stack -> current_num_of_elem);
}
/*****************************************************************************/

int StackIsEmpty(stack_ty *user_stack)
{
	assert(user_stack);
	return (user_stack -> current_num_of_elem) == 0;
}

/*****************************************************************************/

size_t StackCapacity(stack_ty *user_stack)
{
	assert(user_stack);
	return (user_stack -> num_of_elem) * (user_stack -> size_of_elemt);
}

/*****************************************************************************/

size_t SizeOfStruct()
{
	return sizeof(stack_ty);
}

