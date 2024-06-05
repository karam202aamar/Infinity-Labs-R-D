/*******************************************************************************
 * Project: Comparision Sort
 * Date: 21/09/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0
*******************************************************************************/
#ifndef __COMPARISON_SORTS_H_ILRD__
#define __COMPARISON_SORTS_H_ILRD__

#include <stddef.h> /*size_t*/

/*******************************************************************************
**Sorts integers from smallest to largest value
**Time Complexity: best- O(n), Avg- O(n^2), worst- O(n^2)
**Space Complexity: O(1)
**Stability: stable
*******************************************************************************/
void BubbleSort(int *arr_to_sort, size_t arr_size);

/*******************************************************************************
**Sorts integers from smallest to largest value
**Time Complexity: best- O(n^2), Avg- O(n^2), worst- O(n^2)
**Space Complexity: O(1)
**Stability: stable
*******************************************************************************/
void SelectionSort(int *arr_to_sort, size_t arr_size);

/*******************************************************************************
**Sorts integers from smallest to largest value
**Time Complexity: best- O(n), Avg- O(n^2), worst- O(n^2)
**Space Complexity: O(1)
**Stability: stable
*******************************************************************************/
void InsertionSort(int *arr_to_sort, size_t arr_size);

#endif /* COMPARISON_SORTS_H_ILRD */
