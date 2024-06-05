/*******************************************************************************
** Project: Data Structures - Heap
** Date: 26/10/22
** Name: HRD 26
** Reviewer: Rina
** Version: 1.0
*******************************************************************************/
#ifndef __HEAP_H_ILRD__
#define __HEAP_H_ILRD__

#include <stddef.h> /*size_t*/

typedef struct heap heap_ty;

/*******************************************************************************
** Return Value: -1 = data1 is SMALLER than data2,
                  0 = data1 is EQUAL than data2, 
                  1 = data1 is GREATER than data2
*******************************************************************************/
/*TODO */
typedef int (*heap_cmp_func_ty)(const void *data1, const void *data2);

/*******************************************************************************
** Return Value: 1 = data1 is EQUAL than data2, 
                 0 = data1 is DIFFERENT than data2
*******************************************************************************/
typedef int (*heap_is_match_ty)(const void *data1, const void *data2);

/*******************************************************************************
** Initializes a heap.
** Time Complexity:  O(1)
** Space Complexity: O(1)
** Return Value: pointer to the newly created heap, or NULL if allocation fails.
*******************************************************************************/
heap_ty *HeapCreate(heap_cmp_func_ty cmp_func);

/*******************************************************************************
** Destroys a heap.
** Time Complexity:  O(1)
** Space Complexity: O(1)
** Undefined Behavior: if heap is NULL.
*******************************************************************************/
void HeapDestroy(heap_ty *heap);

/*******************************************************************************
** Inserts data into provided heap.
** Time Complexity:  O(log(n)) 
** Space Complexity: O(1)
** Return Value: 0 = SUCCESS, 1 = FAILURE
** Undefined Behavior: if heap's cmp_func is NULL.
                       if data is not compatible with cmp_func.
                       if heap is NULL.
*******************************************************************************/
int HeapPush(heap_ty *heap, const void *data);

/*******************************************************************************
** Removes the top element in the heap.
** Time Complexity:  O(log(n))
** Space Complexity: O(1)
** Return value: pointer to the popped data.
** Undefined Behavior: if heap is NULL.
                       if heap's cmp_func is NULL.
                       if heap is empty.
*******************************************************************************/
void *HeapPop(heap_ty *heap);

/*******************************************************************************
** Returns the data of top element in the heap.
** Time Complexity:  O(1)
** Space Complexity: O(1)
** Return Value: pointer to the peeked element.
** Undefined Behavior: if heap is NULL.
                       if heap is empty.
*******************************************************************************/
void *HeapPeek(const heap_ty *heap);

/*******************************************************************************
** Returns number of elements in the heap.
** Time Complexity:  O(1)
** Space Complexity: O(1)
** Undefined Behavior: if heap is NULL.
*******************************************************************************/
size_t HeapSize(const heap_ty *heap);

/*******************************************************************************
** Checks whether heap is empty.
** Time Complexity:  O(1)
** Space Complexity: O(1)
** Return Value: 1 = EMPTY, 0 = NOT EMPTY
** Undefined Behavior: if heap is NULL.
*******************************************************************************/
int HeapIsEmpty(const heap_ty *heap);

/*******************************************************************************
** Removes heap entry corresponding to provided data.
** Time Complexity:  O(n)
** Space Complexity: O(1)
** Return Value: 0 = SUCCESS, 1 = NOT FOUND
** Undefined Behavior: if data is not compatible with is_match
                       if heap is NULL
                       if cmp_func is NULL
*******************************************************************************/
void *HeapRemove(heap_ty *heap, heap_is_match_ty is_match, const void *param);

#endif /*__HEAP_H_ILRD__*/
