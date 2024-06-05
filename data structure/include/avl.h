/*******************************************************************************
 * Project: Data Structures - AVL Tree
 * Date: 12/10/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.2
 *              -additon of ssize_t and sys/types.h
 *              -AVLHeight fixed description
*******************************************************************************/

#ifndef __AVL_H_ILRD__
#define __AVL_H_ILRD__

#include <stddef.h>     /*size_t    */
#include <sys/types.h>  /*ssizet    */

typedef struct avl avl_ty;

/*******************************************************************************
** Compares between avl_data and new_data
** Return value: 1 - 	if avl_data is bigger than new_data
**				 -1 - 	if new_data is bigger than avl_data
**				 0 - 	if the datas are equal
** Complexity: O(1)
*******************************************************************************/
typedef int (*compare_ty)(const void *avl_data, const void *new_data, void *param);

/*******************************************************************************
** Return value: 	0 - Success
** 		 			1 - Failure
*******************************************************************************/
typedef int (*action_ty)(void *avl_data, void *param);

/*******************************************************************************
** Description: Creates a new avl
** Return Value: The new avl pointer
** Time Complexity: O(1)
*******************************************************************************/
avl_ty *AVLCreate(compare_ty compare_func, void *param);
	
/*******************************************************************************
** Description: Destroys the avl
** Time Complexity: O(n)
** Undefined Behavior: If avl is NULL
*******************************************************************************/
void AVLDestroy(avl_ty *avl);

/*******************************************************************************
** Return Value:    height of root 
                    if avl is empty returns -1
** Time Complexity: O(1)
** Undefined Behavior: If avl is NULL
*******************************************************************************/
ssize_t AVLHeight(const avl_ty *avl);

/*******************************************************************************
** Return Value: Number of nodes in avl
** Time Complexity: O(n)
** Undefined Behavior: If avl is NULL
*******************************************************************************/
size_t AVLSize(const avl_ty *avl);

/*******************************************************************************
** Description: Checks if the avl is empty
** Return Value: 1 - empty
**				 0 - otherwise
** Time Complexity: O(1)
** Undefined Behavior: If avl is NULL
*******************************************************************************/
int AVLIsEmpty(const avl_ty *avl);

/*******************************************************************************
** Description: Inserts new node with data to avl
** Return Value: 	0 if success 1 if fail.
** Time Complexity: O(log(n))
** Undefined Behavior: If avl is NULL
**					   If avl's compare_func is NULL
**					   If data is noncompatible with avl's compare_func
**					   If data is equal to one of the avl's node's datas
*******************************************************************************/
int AVLInsert(avl_ty *avl, void *data);

/*******************************************************************************
** Description: 	Removes node containing data from avl
** Time Complexity: O(log(n))
** Return Value: 	0 if success 1 if data is not found. 
** Notes : 			no operations will be performed if data is not found.
** Undefined Behavior: 	If avl is NULL
**					   	If avl's compare_func is NULL
**					   	If data is noncompatible with avl's compare_func
*******************************************************************************/
int AVLRemove(avl_ty *avl, void *data);

/*******************************************************************************
** Description: Searches for data in avl
** Return Value: pointer to matching data, or NULL if not found
** Time Complexity: O(log(n))
** Undefined Behavior: If avl is NULL
**					   If avl's compare_func is NULL
**					   If data_to_find is noncompatible with avl's compare_func
*******************************************************************************/
void *AVLFind(const avl_ty *avl, const void *data_to_find);

/*******************************************************************************
** Description: Executes action_func on all avl
** stops and returns Failure value if failed to execute
** Return Value: 0 - success
**				 1 - fail
** Time Complexity: O(n)
** Undefined behavior: If action_func is NULL
**					   If action func changes the order in which the avl should
**					   be sorted
*******************************************************************************/
int AVLForEach(avl_ty *avl, action_ty action_func, void *param);



#endif /* __AVL_H_ILRD__ */

