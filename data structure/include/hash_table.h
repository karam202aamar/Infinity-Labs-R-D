/******************************************************************************
 * Project: Data Structures - Hash Table
 * Date: 24/10/22
 * Name: HRD 26
 * Reviewer: Rina
 * Version: 1.0
 * ***************************************************************************/
#ifndef __HASH_TABLE_H_ILRD__
#define __HASH_TABLE_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct table ht_ty;

/*******************************************************************************
** Return Value: index of appropriate element.
*******************************************************************************/
typedef size_t (*hash_func_ty)(void *data);/* key find */
/*******************************************************************************
** Return Value: 0 = SUCCESS, 1 = FAILURE
*******************************************************************************/
typedef int (*ht_action_ty)(void *data, const void *param); /* for each */
/*******************************************************************************
** Return Value: -1 = data1 is SMALLER than data2,
                  0 = data1 is EQUAL than data2, 
                  1 = data1 is GREATER than data2
*******************************************************************************/
typedef int (*ht_cmp_func_ty)(const void *data1, const void *data2);

/*******************************************************************************
** Initializes a hash table.
** Time Complexity: O(k) where k is table_size.
** Space Complexity: O(n)
** Return Value: hash table pointer to the newly created table, or NULL if
**               creation fails.
*******************************************************************************/
ht_ty *HTCreate(size_t table_size, hash_func_ty hash_func, 
                                                        ht_cmp_func_ty cmp_func);

/*******************************************************************************
** Destroys a hash table.
** Time Complexity: O(n + k) / O(n) (worst)
** Undefined Behavior: if table is NULL.
*******************************************************************************/
void HTDestroy(ht_ty *table);

/*******************************************************************************
** Removes table entry corresponding to provided data.
** Time Complexity: O(1) (average) / O(n) (worst)
** Return Value: 0 = SUCCESS, 1 = NOT FOUND
** Undefined Behavior: if data is not compatible with hash function
                       if table is NULL
                       if hash_func is NULL
                       if cmp_func is NULL
*******************************************************************************/
int HTRemove(ht_ty *table, const void *data);

/*******************************************************************************
** Inserts a hash-set into provided table.
** Time Complexity: O(1) (average)
** Space Complexity: O(1) (average)
** Return Value: 0 = SUCCESS, 1 = FAILURE
** Undefined Behavior: if data is not compatible with hash function.
                       if table is NULL; 
                       if hash_func is NULL
*******************************************************************************/
int HTInsert(ht_ty *table, void *data);

/*******************************************************************************
** Returns number of occupied elements in hash table.
** Time Complexity: O(n + k) where k is table_size and n is number of occupied
**                  elements.
** Undefined Behavior: if table is NULL.
*******************************************************************************/
size_t HTSize(const ht_ty *table);

/*******************************************************************************
** Checks whether table is empty.
** Time Complexity: O(n)
** Return Value: 1 = EMPTY, 0 = NOT EMPTY
** Undefined Behavior: if table is NULL.
*******************************************************************************/
int HTIsEmpty(const ht_ty *table);

/*******************************************************************************
** Searches table by data, according to cmp_func.
** Time Complexity: O(1) (average) / O(n) (worst)
** Return Value: pointer to appropriate value if found, NULL otherwise.
** Undefined Behavior: if table is NULL.
                       if cmp_func is NULL.
*******************************************************************************/
void *HTFind(const ht_ty *table, const void *data);

/*******************************************************************************
** Performs action_ty on each table entry.
** Time Complexity: O(n + k) where k is table_size and n is number of occupied
**                  elements.
** Space Complexity: action_ty's complexity.
** Return Value: 0 = SUCCESS, 1 = FAILURE
** Undefined Behavior: if action_func is NULL.
*******************************************************************************/
int HTForEach(ht_ty *table, ht_action_ty action, const void *param);

#endif /*__HASH_TABLE_H_ILRD__*/
