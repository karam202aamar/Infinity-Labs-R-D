/*******************************************************************************
 * Project: Data Structures - Linked List
 * Date: 10/08/22
 * Name: HRD26
 * Reviewer: Liel
 * Version: 1.0 
 * Version: 2.0 updates:	
 		-SListCount was added
 		-In all functions addind return value on sucess and fail
 		-Typedef -slist_node slist_node_ty- correction
		-Destroy complexity fixed
 		-Undefined behaviour fixed- Destroy, SListForEach, 			    				 SListBegin, SListEnd,SlistNext, SlistGetdData, SlistSetData
 		-Icorrect complexity fixed SlistInsert
 		-SlistInsert replace "index" to "iter" in argument
 		-SlistRemove fixed argument
 		-SlistFind fixed from and too arguments
 		-SListForEach fixed arguments and complexity
 		-SListEnd fixed return value
 		-SListFind changed to SListIsFound- Not Approved
 
 * Version: 2.1 Updates:
 				-Typedef -slist_node_ty *slist_iter_ty- correction  			-Undefined behaviour fixed- SListRemove, SListForEach
 			         SListNext, SListGetData
 
 * Version: 2.2 Updates:
 			-Description of SListInsert fixed from after to before
 			-Undefined behaviour fixed- SListRemove, SListFind,
 						     SListInsert, SListForEach,
 						     SListBegin, SListEnd,
 						typedef int (*action_func_ty)(void *data, void *param);
typedef int (*is_match_func_ty)(const void *data, void *param);     SlistNext, SlistGetdData,
 						     SlistSetData
 				-SListFind description and return value fixed.
 				-SListBegin description fixed.
 				-SListEnd description fixed.
 				-SListNext description fixed.
 				-SListIterIsEqual description fixed.
 				-SListGetData description fixed.
 				-SListCount description fixed.
 
 * Version: 3.0 Updates:
 				-SListInsert return value changed
 				-SListRemove return value changed
 				-SlistAppend function added
 				
*******************************************************************************/
#ifndef __LINKED_LIST_H_ILRD__
#define __LINKED_LIST_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct slist_node slist_node_ty;

typedef slist_node_ty* slist_iter_ty;

typedef struct slist slist_ty;

typedef int (*action_func_ty)(void *data, void *param);
typedef int (*is_match_func_ty)(const void *data, void *param);

/*******************************************************************************
** Creates a new linked list
** Return value: pointer to the new list 
** Complexity: O(1)
*******************************************************************************/
slist_ty *SListCreate();

/*******************************************************************************
** Destroys linked list
** Undefined behavior: if list is NULL
** Complexity: O(n)
*******************************************************************************/
void SListDestroy(slist_ty *list);

/*******************************************************************************
** Inserts a new node before given iterator
** Return value: 0 - success 1 - fail
** Complexity: O(1)
** Undefined behavior: if the iterator is not a node in the list .
*******************************************************************************/
slist_iter_ty SListInsert(slist_iter_ty iterator, void *data);

/*******************************************************************************
** Removes node at the given iterator
** Return value: 0 - success 1 - fail
** Complexity: O(1)
** Undefined behaviour: if the iterator is not a node in the list .
*******************************************************************************/
slist_iter_ty SListRemove(slist_iter_ty iterator);

/*******************************************************************************
** Returns the first iterator in the given iterator range [from ; to] 
  (not including to) in which the param value is found according to match_func.
** Return value: iterator of the found node, or the "to" node if not found.
** Complexity: O(n)
** Undefined behaviour: if the from and/or to are/is not a node in the list.
*******************************************************************************/
slist_iter_ty SListFind(const slist_iter_ty from, const slist_iter_ty to,
				   is_match_func_ty match_func, void *param);
				   
/*******************************************************************************
** Executes action_func_ty on all nodes in range [from ; to] (not including to)
** Return value: 0 - success 1 - fail.
** Undefined behaviour: if the from and/or to are/is not a node in the list.
** Complexity: O(n)
*******************************************************************************/
int SListForEach(const slist_iter_ty from, const slist_iter_ty to,
					    action_func_ty func, void *param);
					    
/*******************************************************************************
** Returns the iterator of the beginning of linked list.
** Complexity: O(1)
** Undefined behavior: if list is NULL
*******************************************************************************/
slist_iter_ty SListBegin(const slist_ty *list);

/*******************************************************************************
** Returns the iterator of the dummy node
** Complexity: O(n) 
** Undefined behavior: if list is NULL
*******************************************************************************/
slist_iter_ty SListEnd(const slist_ty *list);

/*******************************************************************************
** Returns iterator of the next node 
** Complexity: O(1) 
** Undefined behavior: if iterator is the dummy node
*******************************************************************************/
slist_iter_ty SListNext(const slist_iter_ty iterator);

/*******************************************************************************
** Compares two iterators
** Return value: 1 - equal
**		  0 - different
** Complexity: O(1)
*******************************************************************************/
int SListIterIsEqual(const slist_iter_ty iterator1,
						const slist_iter_ty iterator2);
	
/*******************************************************************************
** This function gets the data of the iterator
   Return value: the data of the iterator
** Complexity: O(1)
** Undefined behavior: if iterator is the dummy node
*******************************************************************************/
void *SListGetData(const slist_iter_ty iterator);

/*******************************************************************************
** Writes data to iterator
** Complexity: O(1)
** Undefined behavior: if iterator is the dummy node  
*******************************************************************************/
void SListSetData(slist_iter_ty iterator, void *data);

/*******************************************************************************
** Counts the number of elements in the list
** Complexity: O(n)
** Undefined behavior: if the pointer to list is NULL
*******************************************************************************/
size_t SListCount(const slist_ty *list);

/*******************************************************************************
** Appends list_2 to the end of list_1
** Return value: Pointer to the merged list
** Complexity: O(n)
** Undefined behavior: If list_1 or list_2 are NULL
*******************************************************************************/
slist_ty *SListAppend(slist_ty *list_1, slist_ty *list_2);

#endif /* __LINKED_LIST_H_ILRD__ */

