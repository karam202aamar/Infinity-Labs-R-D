/******************************************************************************
Project: DS - Stack
Date: 01/08/22
Name: 
Reviewer: 
Version: 
*******************************************************************************/
#ifndef __STACK_H_ILRD__
#define __STACK_H_ILRD__

#include <stddef.h>/*size_t*/

typedef struct stack stack_ty;

/*creates a new empty stack that can hold max_num_of_elem of a given 
size_of_elem. returns the pointer to the created stack.*/
stack_ty *StackCreate(size_t max_num_of_elem, size_t size_of_elem);

/*destroys the user_stack. user_stack must be a stack created by StackCreate 
(otherwise undefined behavior)*/
void StackDestroy(stack_ty *user_stack);

/*pushes the elem_to_push to the top of user_stack. size of elem_to_push should
be equal to size_of_elem*/
void StackPush(stack_ty *user_stack, void *elem_to_push);

/* Removes the last element that was inserted to my_stack */
void StackPop(stack_ty *user_stack);

/* Returns the last element that was inserted to my_stack */
void *StackPeek(stack_ty *user_stack);

/* Returns the number of elements currently in my_stack */
size_t StackSize(stack_ty *user_stack);

/* Checks if my_stack is empty, return 1 if it yes, otherwise 0 */
int StackIsEmpty(stack_ty *user_stack);

/* Returns the capacity of my_stack */
size_t StackCapacity(stack_ty *user_stack);

#endif /*__STACK_H_ILRD__*/

