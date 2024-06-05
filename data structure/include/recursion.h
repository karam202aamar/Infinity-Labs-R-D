/*******************************************************************************
 Project: Data Structures - Recursion
 Date: 09.10.22
 Name: HRD26
 Reviewer: Rina
 Version: 1.0
*******************************************************************************/
#ifndef __RECURSION_H_ILRD__
#define __RECURSION_H_ILRD__

#include <stddef.h> /*  size_t  */
#include "stack.h"

typedef struct node node_ty;
struct node
{
    void *data;
    node_ty *next; 
}; 

/*******************************************************************************
** Description:         calculats the element in the index position in fibonacci
**                      sequence itrativly 
** Time complexity:     O(n)
*******************************************************************************/
int Fibonacci(int index);

/*******************************************************************************
** Description:         calculats the element in the index position in fibonacci
**                      sequence recursivly 
** Time complexity:     O(n)
** Return Value:        Returns the element in the index place. 
*******************************************************************************/
int FibonacciRec(int index);

/*******************************************************************************
** Description:         Flips the list 
** Time complexity:     O(n)
** Return Value:        Returns the first node of flipped linked list. 
** Undefined Behavior:  If head is NULL
*******************************************************************************/
node_ty* FlipList(node_ty* head);

/*******************************************************************************
** Description:         Sorts unsorted stack from smaller to bigger integers.
                        stack must contain only native numbers.
** Time complexity:     O(n)       
** Undefined Behavior:  If stack is NULL
*******************************************************************************/
void RecStackSort(stack_ty* stack);

/*******************************************************************************
** Description:         Returns the length of str.
** Time complexity:     O(n)
** Undefined Behavior:  If str is NULL
*******************************************************************************/
size_t Strlen(const char *str);

/*******************************************************************************
** Description:         Compares between two strings: str1, str2
** Time complexity:     O(n)
** Return Value:        - If str1 < str2 --> return < 0 
**                      - If str1 = str2 --> return = 0
**                      - If str1 > str2 --> return > 0
** Undefined Behavior:  If str1 or str2 are NULL
*******************************************************************************/
int Strcmp(const char *str1, const char *str2);

/*******************************************************************************
** Description:         Copies src into dest.
** Time complexity:     O(n)
** Undefined Behavior:  If dest or src are NULL
**                      If dest is shorter than src
**                      If dest and src are overlapping
*******************************************************************************/
char *Strcpy(char *dest, const char *src);

/*******************************************************************************
** Description:         Appends the src string to the dest string.
** Time complexity:     O(n)
** Return Value:        Begining of dest
** Undefined Behavior:  If dest or src are NULL
**                      If dest isn't long enough to contain both, dest and src
*******************************************************************************/
char *Strcat(char *dest, const char *src);

/*******************************************************************************
** Description:         Finds the first ocurrence of the substring needle in the
**                      string haystack the terminating null bytes are not 
**                      compared.
** Time complexity:     O(n)
** Undefined Behavior:  If haystack or needle are NULL     
*******************************************************************************/
char *Strstr(const char *haystack, const char *needle);

#endif /*__RECURSION_H_ILRD__*/
