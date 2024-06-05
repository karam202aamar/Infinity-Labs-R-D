/*******************************************************************************
 * Project: CALCULTOR
 * Date: 03/10/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "calculator.h"
#include "stack.h"
/******************************************************************************/
#define ASCII_SIZE 256
#define STATE 3
#define EVENT 3 
int minus_num = 1;
/******************************************************************************/
/* ptr to the functions (values inside main LUT) */
typedef int(*ptr_to_func)(stack_ty* , stack_ty* , char**);

typedef enum event_input{NUM = 0 , OPERATOR  , SPACE , INVALID , OPEN_PAREN ,
						     CLOSE_PAREN}event_input_ty;
								
typedef enum state_input{WAITING_FOR_OPERAND = 0 , WAITING_FOR_OPERATOR , 
						     ERROR_STATE}state_input_ty;
                                                
/******************************************************************************/
static void InitLuts(ptr_to_func transition_lut[][EVENT] , int ascii_lut[]);

static int PushNumInput(stack_ty* numbers , stack_ty* operators , char ** str);
static int PushOpInput(stack_ty* numbers , stack_ty* operators , char ** str);
static int ErrorInput(stack_ty* numbers , stack_ty* operators , char ** str);
static int CalcParen(stack_ty* numbers , stack_ty* operators , char** str);

static void CalcCurrent(stack_ty* numbers , stack_ty* operators);
						   								     	   
/******************************************************************************/
status_ty Calculate(const char *expression, double *res)
{
	/* define first state as success*/
	status_ty status = SUCCESS;
	
	/* define luts */
	ptr_to_func transition_lut[STATE][EVENT];
	int ascii_lut[ASCII_SIZE];
	
	/* define stacks */
	stack_ty *operators_stack = NULL;
	stack_ty *operands_stack = NULL;
	
	/* define variable hold num of chars in expression */
	size_t num_of_elem = strlen(expression);
	
	/* set current status WAITING_FOR_OPERAND*/
	int current_state = WAITING_FOR_OPERAND;
	
	/* define runner for the expression */
	char *str_runner = (char*)expression;
	
	/* define ptr to the static functions */
	ptr_to_func ptr_func = NULL;
	
	/* init luts */
	InitLuts(transition_lut , ascii_lut);
	
	/* create stacks */
	operators_stack = StackCreate(num_of_elem, sizeof(char));
	
	/*Check if allocation has success*/
	if(NULL == operators_stack)
	{
		perror(strerror(errno));
		return ALLOC_FAIL;
	}
	operands_stack = StackCreate(num_of_elem, sizeof(double));
	
	/*Check if allocation has success*/
	if(NULL == operators_stack)
	{
		perror(strerror(errno));
		operands_stack = NULL;
		StackDestroy(operators_stack);
		operators_stack = NULL;
		return ALLOC_FAIL;
	}
	
	while(*str_runner && current_state != ERROR_STATE)
	{
		/* space input - then move to next */
		if(SPACE == ascii_lut[*str_runner])
		{
			++str_runner;
		}
		else
		{
			ptr_func = transition_lut[current_state][ascii_lut
							        [*str_runner]];				    
			/* update state */
			current_state = ptr_func(operands_stack,operators_stack
								  ,&str_runner);
		}
	}
	
	if(current_state == ERROR_STATE)
	{
		status = SYNTAX_ERROR;
	}
	
	while(!StackIsEmpty(operators_stack) && ERROR_STATE != current_state)
	{
		CalcCurrent(operands_stack, operators_stack);	
	}
	/* peek the result value inside the stack operand */
	*res = *(double *)StackPeek(operands_stack);

	StackDestroy(operators_stack);
	StackDestroy(operands_stack);

	return status;
}
/******************************************************************************/
static void InitLuts(ptr_to_func transition_lut[][EVENT] , int ascii_lut[])
{
	int i = 0 ;
	
	/* init ascii_lut */
	for(i = 0 ; i < ASCII_SIZE ; ++i)
	{
		if(i >= '0' && i <= '9')
		{
			ascii_lut[i] = NUM;
		}
		else if('+' == i || '-' == i || '*' == i || '/' == i)
		{
			ascii_lut[i] = OPERATOR;
		}
		else if(' ' == i)
		{
			ascii_lut[i] = SPACE;
		}
		else if('('== i)
		{
			ascii_lut[i] = OPEN_PAREN;
		}
		else if(')' == i)
		{
			ascii_lut[i] = CLOSE_PAREN;
		}
		else 
		{
			ascii_lut[i] = INVALID;
		}
	}
	/* init transition_lut */
	transition_lut[WAITING_FOR_OPERAND][NUM] = PushNumInput;
	transition_lut[WAITING_FOR_OPERAND][OPERATOR] = PushNumInput;
	transition_lut[WAITING_FOR_OPERAND][INVALID] = ErrorInput;
	transition_lut[WAITING_FOR_OPERAND][OPEN_PAREN] = PushOpInput;
	transition_lut[WAITING_FOR_OPERAND][CLOSE_PAREN] = ErrorInput;
	
	transition_lut[WAITING_FOR_OPERATOR][NUM] = ErrorInput;
	transition_lut[WAITING_FOR_OPERATOR][OPERATOR] = PushOpInput;
	transition_lut[WAITING_FOR_OPERATOR][INVALID] = ErrorInput;
	transition_lut[WAITING_FOR_OPERATOR][OPEN_PAREN] = ErrorInput;
	transition_lut[WAITING_FOR_OPERATOR][CLOSE_PAREN] = CalcParen;
	
	transition_lut[ERROR_STATE][NUM] = ErrorInput;
	transition_lut[ERROR_STATE][OPERATOR] = ErrorInput;
	transition_lut[ERROR_STATE][INVALID] = ErrorInput;
	transition_lut[ERROR_STATE][OPEN_PAREN] = ErrorInput;
	transition_lut[ERROR_STATE][CLOSE_PAREN] = ErrorInput;
}
/*****************************************************************************/
static int PushNumInput(stack_ty* numbers , stack_ty* operators , char** str)
{
	double num_tod = 0;

	num_tod = strtod(*str, str);
	/*printf("%lf\n",num_tod);*/
	num_tod = minus_num * num_tod;
	minus_num = 1;
	
	StackPush(numbers , &num_tod);	
	
	return WAITING_FOR_OPERATOR;		     
}
/*****************************************************************************/
static int PushOpInput(stack_ty* numbers , stack_ty* operators , char** str)
{
	char *curr_operator = *str;
	char *prev_operator = NULL;
	
	char *plus_char = "+";
	
	if(!StackIsEmpty(operators))
	{
		prev_operator = (char*)StackPeek(operators);
		
		if(*prev_operator == '*' || *prev_operator == '/')
		{
			CalcCurrent(numbers , operators);
		}
		
	}
	
	if(*curr_operator == '-')
	{
		minus_num = -1;
		StackPush(operators , plus_char);
	}
	else
	{
		StackPush(operators , curr_operator);
	}
	++(*str);
	
	return WAITING_FOR_OPERAND;
}								     
/*****************************************************************************/
static int ErrorInput(stack_ty* numbers , stack_ty* operators , char** str)
{
	return ERROR_STATE;
}						     
/*****************************************************************************/
static void CalcCurrent(stack_ty* numbers , stack_ty* operators)
{
	double num1 = 0 , num2 = 0 , result = 0;
	
	char curr_op;
	
	num1 = *(double*)StackPeek(numbers);
	StackPop(numbers);
	
	num2 = *(double*)StackPeek(numbers);
	StackPop(numbers);
	
	curr_op = *(char*)StackPeek(operators);
	StackPop(operators);
	
	switch(curr_op)
	{
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num2 - num1;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num2 / num1;
			break;
	}
	
	StackPush(numbers , &result);
}
/*****************************************************************************/
static int CalcParen(stack_ty* numbers , stack_ty* operators , char** str)
{
	while('(' != *(char*)StackPeek(operators))
	{
		CalcCurrent(numbers, operators);	
	}
	StackPop(operators);
	++(*str);
	
	return WAITING_FOR_OPERATOR;
}
/*****************************************************************************/
