/*******************************************************************************
 * Project: Data Structures - Sorts
 * Date: 21/09/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0
 			1.1 - Add linear sorts
            2.0 - Added BinarySearch, QuickSort & MergeSort
            2.1 - Added #include <sys/types.h> for ssize_t
                  Added ; at definition of BinarySearch
                  Added definition of BinarySearch iterative
*******************************************************************************/
#ifndef __SORTS_H_ILRD__
#define __SORTS_H_ILRD__

#include <stddef.h>     /* size_t  */
#include <sys/types.h>  /* ssize_t */

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

/*******************************************************************************
**Sorts integers from smallest to largest value, unsigned int only
** Return value: 0 - success
** 		 		 1 - failure
**Time Complexity: O(n+k)
**Space Complexity: O(n+k)
**Note: n = arr_size, k = range from min to max array value
**Stability: stable
*******************************************************************************/
int CountSort(unsigned int *arr_to_sort, size_t arr_size);

/*******************************************************************************
**Sorts integers from smallest to largest value, unsigned int only
**Time Complexity: O(n*k)
**Space Complexity: O(n*k)
** Return value: 0 - success
** 		 		 1 - failure
**Note: n = decimal base, k = max number of digits
**Stability: stable
*******************************************************************************/
int RadixSort(unsigned int *arr_to_sort, size_t arr_size);

/*******************************************************************************
** Searches a sorted array for query
** Time Complexity: O(log-n)
** Return value: index of found element, or -1 if not found.
*******************************************************************************/
ssize_t BinarySearchIterative(const int *arr, size_t arr_size, int query);

/*******************************************************************************
** Searches a sorted array for query
** Time Complexity: O(log-n)
** Return value: index of found element, or -1 if not found.
*******************************************************************************/
ssize_t BinarySearch(const int *arr, size_t arr_size, int query);

/*******************************************************************************
** Sorts integers from smallest to largest value
** Time Complexity: best/average: O(n log(n)) worst: O(n^2)
** Space Complexity: O(1)
** Stability: not stable
*******************************************************************************/
void QuickSort(int *arr, size_t arr_size);

/*******************************************************************************
** Sorts integers from smallest to largest value
** Return Value: 0 - Success
**               1 - Failure
** Time Complexity: O(n log(n))
** Space Complexity: O(n)
** Stability: stable
*******************************************************************************/
int MergeSort(int* arr, size_t arr_size);

#endif /* SORTS_H_ILRD */



