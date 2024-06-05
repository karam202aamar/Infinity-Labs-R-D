/*******************************************************************************
 * Project: Data Structures - DList
 * Date: 18/08/22
 * Name: HRD26
 * Reviewer: Liel
 * Version: 1.0 
 * Version: 1.1 - Fixed minor typos
*******************************************************************************/

#ifndef __DLIST_H_ILRD__
#define __DLIST_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct dlist_node dlist_node_ty;

typedef dlist_node_ty* dlist_iter_ty;

typedef struct dlist dlist_ty;

typedef int (*action_ty)(void *list_data, const void *param);
typedef int (*match_ty)(const void *list_data, const void *param);

/*******************************************************************************
** Creates a new dlist
** Return value: Pointer to the new list
** Complexity: O(1)
*******************************************************************************/
dlist_ty *DListCreate(void);

/*******************************************************************************
** Destroys the list
** Complexity: O(n)
** Undefined behavior: if list is NULL
*******************************************************************************/
void DListDestroy(dlist_ty *list);

/*******************************************************************************
** Returns the currernt number of elements in the list, excluding the dummy
** Complexity: O(n)
** Undefined behavior: If list is NULL
*******************************************************************************/
size_t DListSize(const dlist_ty *list);

/*******************************************************************************
** Checks if list is empty
** Return value: 1 - empty
** 		 		 0 - otherwise
** Complexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
int DListIsEmpty(const dlist_ty *list);

/*******************************************************************************
** Finds the first node of list
** Return value: Iterator of the first node of list
** Complexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
dlist_iter_ty DListBegin(const dlist_ty *list);

/*******************************************************************************
** Finds the last node of list
** Return value: Iterator of the last node of list
** Complexity: O(n)
** Undefined behavior: If list is NULL
*******************************************************************************/
dlist_iter_ty DListEnd(const dlist_ty *list);

/*******************************************************************************
** Finds the next node of curr
** Return value: Iterator of the next node of curr
** Complexity: O(1)
** Undefined behavior: If curr is NULL or the dummy
*******************************************************************************/
dlist_iter_ty DListNext(dlist_iter_ty curr);

/*******************************************************************************
** Finds the previous node of curr
** Return value: Iterator of the previous node of curr
** Complexity: O(1)
** Undefined behavior: If curr is NULL or the first node
*******************************************************************************/
dlist_iter_ty DListPrev(dlist_iter_ty curr);

/*******************************************************************************
** Checks if two iterators are the same
** Return value: 1 - if iterators are the same
** 				 0 - otherwise
** Complexity: O(1)
** Undefined behavior: If either of the iters are NULL
*******************************************************************************/
int DListIsSameIter(dlist_iter_ty iter_1, dlist_iter_ty iter_2);

/*******************************************************************************
** Returns the data of iter
** Return value: Pointer to the data of iter
** Complexity: O(1)
** Undefined behavior: If iter is NULL
*******************************************************************************/
void *DListGetData(const dlist_iter_ty iter);

/*******************************************************************************
** Sets the data of iter to be "data"
** Complexity: O(1)
** Undefined behavior: If iter is NULL
*******************************************************************************/
void DListSetData(dlist_iter_ty iter, void *data);

/*******************************************************************************
** Inserts iterator with data before iter
** Return value: The inserted iterator
** Complexity: O(1)
** Undefined behavior: If iter is NULL
*******************************************************************************/
dlist_iter_ty DListInsert(dlist_iter_ty iter, void *data);

/*******************************************************************************
** Removes iter from the list
** Return value: The iterator after the deleted one
** Complexity: O(1)
** Undefined behavior: If iter is NULL or the dummy
*******************************************************************************/
dlist_iter_ty DListRemove(dlist_iter_ty iter);

/*******************************************************************************
** Inserts iterator with data at the beginning of the list
** Return value: The inserted iterator
** Complexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
dlist_iter_ty DListPushFront(dlist_ty *list, void *data);

/*******************************************************************************
** Inserts iterator with data at the end of the list
** Return value: The inserted iterator
** Complexity: O(n)
** Undefined behavior: If list is NULL
*******************************************************************************/
dlist_iter_ty DListPushBack(dlist_ty *list, void *data);

/*******************************************************************************
** Removes iter from the beginning of the list
** Return value: Data of the beginning iter
** Coplexity: O(1)
** Undefined behavior: If list is NULL
*******************************************************************************/
void *DListPopFront(dlist_ty *list);

/*******************************************************************************
** Removes iter from the end of the list
** Return value: Data of the end iter
** Coplexity: O(n)
** Undefined behavior: If list is NULL
*******************************************************************************/
void *DListPopBack(dlist_ty *list);

/*******************************************************************************
** Executes action_func on all nodes in the given range
** Return value: 0 - success
** 		 		 1 - failure
** Coplexity: O(n)
** Undefined behavior: If from, to or action_func are NULL
** 		   			   If to is before from
** 		  			   If from and to are not in the same list 
*******************************************************************************/
int DListForeach(const dlist_iter_ty from, const dlist_iter_ty to,
					    					action_ty action_func, void *param);

/*******************************************************************************
** Slices a list in the given range, and inserts the sliced range after dest
** Return value: Iterator of the last sliced range element inserted before dest
** Coplexity: O(1)
** Undefined behavior: If from, to, or dest are NULL
** 				       If dest is sliced range
** 				       If from and to are the same
** 				       If to is before from
** 				       If from and to are not in the same list 
*******************************************************************************/
dlist_iter_ty DListSplice(dlist_iter_ty from, dlist_iter_ty to,
							    dlist_iter_ty dest);

/*******************************************************************************
** Executes match_func on all nodes in the given range
** Return value: The first matching iterator or to if no match found
** Complexity: O(n)
** Undefined behavior: If from, to or match_func are NULL
** 		   			   If to is before from
** 		  			   If from and to are not in the same list 
*******************************************************************************/
dlist_iter_ty DListFind(const dlist_iter_ty from, const dlist_iter_ty to,
					      					  match_ty match_func, void *param);

/*******************************************************************************
** Executes match_func on all nodes in the given range and fills dest_list with
** 							      							  all matching nodes
** Return value: 0 - success
** 				 1 - failure
** Complexity: O(n)
** Undefined behavior: If from, to, match_func or dest_list are NULL
** 		   			   If to is before from
** 		  			   If from and to are not in the same list 
*******************************************************************************/
int DListMultiFind(const dlist_iter_ty from, const dlist_iter_ty to,
			 			 match_ty match_func, void *param, dlist_ty *dest_list);
				   
#endif /* __DLIST_H_ILRD__ */

