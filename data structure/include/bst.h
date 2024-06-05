/*******************************************************************************
 * Project: Data Structures - Binary Search tree
 * Date: 22/09/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0
*******************************************************************************/

#ifndef __BST_H_ILRD__
#define __BST_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct node node_ty; /* node for the tree */ 
typedef node_ty* bst_iter_ty; /* iter for the node - by value */

typedef struct bst bst_ty; /* tree struct */

/*******************************************************************************
** Compares between bst_data and new_data
** Return value: 1 - if bst_data is bigger than new_data
**				 -1 - if new_data is bigger than bst_data
**				 0 - if the datas are equal
** Complexity: O(1)
*******************************************************************************/
typedef int (*compare_ty)(const void *bst_data, const void *new_data, void *param);

/*******************************************************************************
** Return value: 0 - Success
** 		 		 1 - Failure
*******************************************************************************/
typedef int (*action_ty)(void *bst_data, void *param);

/*******************************************************************************
** Description: Creates a new bst
** Return Value: The new bst pointer
** Time Complexity: O(1)
*******************************************************************************/
bst_ty *BSTCreate(compare_ty compare_func, void *param);

/*******************************************************************************
** Description: Destroys the bst
** Time Complexity: O(n)
** Undefined Behavior: If bst is NULL
*******************************************************************************/
void BSTDestroy(bst_ty *bst);

/*******************************************************************************
** Description: Counts the nodes in bst
** Return Value: Number of nodes in bst
** Time Complexity: O(n)
** Undefined Behavior: If bst is NULL
*******************************************************************************/
size_t BSTSize(const bst_ty *bst);

/*******************************************************************************
** Description: Checks if the bst is empty
** Return Value: 1 - empty
**				 0 - otherwise
** Time Complexity: O(1)
** Undefined Behavior: If bst is NULL
*******************************************************************************/
int BSTIsEmpty(const bst_ty *bst);

/*******************************************************************************
** Description: Inserts new node with data to bst
** Return Value: Iter of the new node, or BSTEnd if failed
** Time Complexity: average - O(log(n)), worst case - O(n)
** Undefined Behavior: If bst is NULL
**					   If bst's compare_func is NULL
**					   If data is noncompatible with bst's compare_func
**					   If data is equal to one of the bst's node's datas
*******************************************************************************/
bst_iter_ty BSTInsert(bst_ty *bst, void *data);

/*******************************************************************************
** Description: Removes iter from bst
** Time Complexity: average - O(log(n)), worst case - O(n)
** Undefined Behavior: If iter has already been removed
**					   If iter is BSTEnd
*******************************************************************************/
void BSTRemove(bst_iter_ty iter);

/*******************************************************************************
** Description: Finds the smallest element in bst
** Return Value: Iterator of the smallest element in bst, or BSTEnd if bst is
** empty
** Time Complexity: average - O(log(n)), worst case - O(n)
** Undefined Behavior: If bst is NULL
*******************************************************************************/
bst_iter_ty BSTBegin(const bst_ty *bst);

/*******************************************************************************
** Return Value: Iterator of the dummy node
** Time Complexity: average - O(1)
** Undefined Behavior: If bst is NULL
*******************************************************************************/
bst_iter_ty BSTEnd(const bst_ty *bst);

/*******************************************************************************
** Description: Finds iter's previous node
** Return Value: Iter of node that its data is the largest one that is smaller
** 																than iter's data
** Time Complexity: average - O(log(n)), worst case - O(n)
** Undefined Behavior: If iter is BSTBegin
*******************************************************************************/
bst_iter_ty BSTPrev(bst_iter_ty iter);

/*******************************************************************************
** Description: Finds iter's next node
** Return Value: Iter of node that its data is the smallest one that is larger
** than iter's data. If iter has the largest data, return the dummy
** Time Complexity: average - O(log(n)), worst case - O(n)
*******************************************************************************/
bst_iter_ty BSTNext(bst_iter_ty iter);

/*******************************************************************************
** Description: Checks if two iters are equal
** Return Value: 1 - true
**				 0 - false
** Time Complexity: O(1)
*******************************************************************************/
int BSTIsSameIter(bst_iter_ty iter_1, bst_iter_ty iter_2);

/*******************************************************************************
** Return Value: Pointer to iter's data
** Time Complexity: O(1)
*******************************************************************************/
void *BSTGetData(bst_iter_ty iter);

/*******************************************************************************
** Description: Searches for iter in bst with same data as data_to_find
** Return Value: The iter with the matching data, or BSTEnd if not found
** Time Complexity: average - O(log(n)), worst case - O(n)
** Undefined Behavior: If bst is NULL
**					   If bst is empty
**					   If bst's compare_func is NULL
**					   If data_to_find is noncompatible with bst's compare_func
*******************************************************************************/
bst_iter_ty BSTFind(const bst_ty *bst, const void *data_to_find);

/*******************************************************************************
** Description: Executes action_func on all iters in [from, to)
** stops and returns Failure value if failed to execute on one iter
** Return Value: 0 - success
**				 1 - fail
** Time Complexity: O(n), n being number of iters in the given range
** Undefined behavior: If action_func is NULL
** 		   			   If to is before from
** 		  			   If from and to are not in the same bst
**					   If action func changes the order in which the bst should
**					   be sorted
*******************************************************************************/
int BSTForEach(bst_iter_ty from, bst_iter_ty to, action_ty action_func,
																   void *param);

#endif /* __BST_H_ILRD__ */
