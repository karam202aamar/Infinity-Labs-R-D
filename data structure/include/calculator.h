/*******************************************************************************
 Project: System Programming - Calculator
 Date: 02.10.22
 Name: HRD26
 Reviewer: Rina
 Version: 1.0
*******************************************************************************/
#ifndef __CALCULATOR_H_ILRD__
#define __CALCULATOR_H_ILRD__


typedef enum status{SUCCESS = 0, ALLOC_FAIL = 1, SYNTAX_ERROR = 2, 
                                                       MATH_ERROR = 3}status_ty;

/* Gets an expression input as a pointer to string and set res as the pointer to 
the result of the calculus. 
Returns values:   SUCCESS - in case of success
               	 SYS_FAIL - in case of issue in operation
             SYNTAX_ERROR - in case of unexpected char that causes syntax issue
               MATH_ERROR - in case of forbidden operation or overflow double.
Notes: - The expression can include +, -, *, \, (, ) operators. 
       - Spaces can be included in the expression.
Complexity: O(n) */
status_ty Calculate(const char *expression, double *res);

#endif /*__CALCULATOR_H_ILRD__*/
