/*******************************************************************************
 * Project: Data Structures - Sorted List
 * Date: 21/08/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0 
 *
*******************************************************************************/
#ifndef __SORTEDLIST_H_ILRD__
#define __SORTEDLIST_H_ILRD__

#include <stddef.h> /* size_t */

#include "dlist.h"

typedef dlist_iter_ty sort_list_iter_ty;

typedef struct sort_list sort_list_ty;

/*******************************************************************************
** Compares between list_data and new_data
** Return value: 1 - if list_data is bigger than inserted_data
**				 0 - if list_data and inserted_data are equal
**				 -1 - if inserted_data is bigger than list_data
** Complexity: O(1)
** Undefined behavior:
*******************************************************************************/
typedef int (*compare_ty)(const void *list_data, const void *new_data);

/*******************************************************************************
** Return value: 0 - Success
** 		 		 1 - Failure
*******************************************************************************/
typedef int (*action_func_ty)(void *list_data, void *param);

/*******************************************************************************
** Determines whether list_data matches specified term
** Return value: 1 - true
**				 0 - false
** Complexity: O(1)
** Undefined behavior: 
*******************************************************************************/
typedef int (*is_match_func_ty)(void *list_data, void *user_param);

/*******************************************************************************
** Creates a pointer to a new sorted list
** Return value: Pointer to the new sorted list, if failed return NULL
** Complexity: O(1)
** Undefined behavior: If compare_func is NULL
*******************************************************************************/
sort_list_ty *SortListCreate(compare_ty compare_func);

/*******************************************************************************
** Destroys the list
** Complexity: O(n)
** Undefined behavior: If list is NULL
*******************************************************************************/
void SortListDestroy(sort_list_ty *list);

/*******************************************************************************
** Insert data to list placed according to user provided sorting criteria 
** Undefined behavior: If list is NULL or if data is not in compliance with the 
					   							  compare function from the user
** Return value: The inserted iterator, else SortListEnd dummy
** Complexity: O(n)
*******************************************************************************/
sort_list_iter_ty SortListInsert(sort_list_ty *list, void *data);

/*******************************************************************************
** Removes iter from the list
** Return value: The iterator after the deleted one
** Complexity: O(1)
** Undefined behavior: If iter is the dummy
*******************************************************************************/
sort_list_iter_ty SortListRemove(sort_list_iter_ty iter);

/*******************************************************************************
** Returns the current number of elements in the list.
** Complexity: O(n)
** Undefined behavior: If list is NULL
*******************************************************************************/
size_t SortListSize(const sort_list_ty *list);

/*******************************************************************************
** Checks if list is empty
** Return value: 1 - empty
** 		 		 0 - otherwise
** Complexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
int SortListIsEmpty(const sort_list_ty *list);

/*******************************************************************************
** Removes iter from the beginning of the list
** Return value: pointer to the data of removed element
** Complexity: O(1)
** Undefined behavior: If list is NULL
** 					   If list is empty
*******************************************************************************/
void *SortListPopFront(sort_list_ty *list);

/*******************************************************************************
** Removes the last element from the list.
** Return value: pointer to the data of the removed element
** Complexity: O(1)
** Undefined behavior: If list is NULL
** 					   If list is empty
*******************************************************************************/
void *SortListPopBack(sort_list_ty *list);

/*******************************************************************************
** Finds the first element of list
** Return value: Iterator of the first element, or SortListEnd if list is empty
** Complexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
sort_list_iter_ty SortListBegin(const sort_list_ty *list);

/*******************************************************************************
** Finds the list terminator (dummy)
** Return value: Iterator of the last element of list (dummy)
** Complexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
sort_list_iter_ty SortListEnd(const sort_list_ty *list);

/*******************************************************************************
** Finds the next element of curr
** Return value: Iterator of the next iterator of curr
** Complexity: O(1)
** Undefined behavior: If curr is the dummy
*******************************************************************************/
sort_list_iter_ty SortListNext(sort_list_iter_ty curr);

/*******************************************************************************
** Finds the previous element of curr
** Return value: Iterator of the previous element of curr
** Complexity: O(1)
** Undefined behavior: If curr is SortListBegin
*******************************************************************************/
sort_list_iter_ty SortListPrev(sort_list_iter_ty curr);

/*******************************************************************************
** Checks if two iterators point to the same elements
** Return value: 1 - If iterators are the same
** 				 0 - Otherwise
** Complexity: O(1)
** Undefined behavior: If either of the iters are NULL
*******************************************************************************/
int SortListIsSameIter(sort_list_iter_ty iter_1, sort_list_iter_ty iter_2);

/*******************************************************************************
** Returns the data of iter
** Return value: Pointer to the data of iter
** Complexity: O(1)
** Undefined behavior: If iter is SortListEnd
*******************************************************************************/
void *SortListGetData(sort_list_iter_ty iter);

/*******************************************************************************
** Executes action_func on all elements in the given range [from, to),
** stops and returns Failure value if failed to execute on one element
** Return value: 0 - Success
** 		 		 1 - Failure
** Complexity: O(n)
** Undefined behavior: If action_func is NULL
** 		   			   If to is before from
** 		  			   If from and to are not in the same list
**					   If action func changes the order in which the list should
**					   be sorted
*******************************************************************************/
int SortListForEach(sort_list_iter_ty from, sort_list_iter_ty to, action_func_ty action_func, void *param);

/*******************************************************************************
** Merge list_2 into list_1 according to list_1's compare_func.
** list_2 is left empty
** Return value: list_1 pointer
** Complexity: O(n+m) (n and m are the sizes of list_1 and list_2)
** Undefined behavior: If either list pointer is NULL
** 				       If the compare_ty criteria is different between the lists
*******************************************************************************/
sort_list_ty *SortListMerge(sort_list_ty *list_1, sort_list_ty *list_2);

/*******************************************************************************
** Searches data_to_find in the given range [from, to) using list's sorting
** 																		criteria
** Return value: First iterator matched, or iterator "to" if no match
** Complexity: O(n)
** Undefined behavior: If "to" is before from
** 		  			   If "from" and to are not in the same list 
*******************************************************************************/
sort_list_iter_ty SortListFind(sort_list_ty *list, sort_list_iter_ty from, 
									  sort_list_iter_ty to, void *data_to_find);
/*******************************************************************************
** Returns first iterator matching match_func criteria 
** Return value: First iterator matched, or iterator "to" if no match
** Complexity: O(n)
** Undefined behavior: If is_match is NULL
** 		   			   If to is before from
** 		  			   If from and to are not in the same list 
*******************************************************************************/
sort_list_iter_ty SortListFindIf(sort_list_iter_ty from, 
				  sort_list_iter_ty to, is_match_func_ty is_match, void *param);

#endif /* __SORTEDLIST_H_ILRD__ */
