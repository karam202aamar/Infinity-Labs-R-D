/******************************************************************************/
#include <stdio.h>  /* print */
/******************************************************************************/
/*********************************struct***************************************/
typedef struct queue_stack 
{
	stack_ty *first_stack;
	stack_ty *second_stack;
	
}queue_stack_ty;

struct stack 
{
	int *array;
	size_t num_of_elem;
	size_t num_of_curr_elem;
	
}stack_ty;
/******************************************************************************/
int main()
{

	return 0; 
}
/******************************************************************************/
	/* 
		  pseudo code:
		- stack contains two stacks .
		- enqueue elements into first stack .
		
		- check first first stack if empty , if not pop last element 
		   and push it
		  to the second stack , loop untill stack 1 empty .
		  
		- if first stack is empty then pop the elements back and push
		  it to first stack .
		  
		- suppose that the user already entered the number of elements 
		  he wants.
	*/
/******************************************************************************/
int QEnqueue(queue_stack_ty queue_2_stack, void *data)
{
	/* push the new value to the first stack */
	(queue_2_stack->first_stack)->
	memcpy(((char *)queue_2_stack->first_stack)->array + ((queue_2_stack->
				first_stack)->num_of_curr_elem * (sizeof(int)))
							, data , sizeof(int));
					
	++((queue_2_stack->first_stack)->num_of_curr_elem);
}
/******************************************************************************/
void QDequeue(queue_stack_ty queue_2_stack)
{
	while((queue_2_stack->first_stack)->num_of_curr_elem)
	{
		/* pop from first stack and push it to second stack */
	}
		/* pop last element in the current second stack */
		
		/* loop again and enter the elements to the first stack */
}
/******************************************************************************/
