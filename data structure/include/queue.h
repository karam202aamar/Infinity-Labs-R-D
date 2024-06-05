/*******************************************************************************
 * Project: Data Structures - Queue
 * Date: 15/08/22
 * Name: HRD26
 * Reviewer: Liel
 * Version: 1.0 		
*******************************************************************************/

#ifndef __QUEUE_H_ILRD__
#define __QUEUE_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct queue queue_ty;

/*******************************************************************************
** Description: Creates a new queue
** Return value: Pointer to the queue that was created
** Complexity: O(1)
*******************************************************************************/
queue_ty *QCreate();

/*******************************************************************************
** Description: Destroys the queue
** Undefined behavior: If the queue pointer is NULL
** Complexity: O(n)
*******************************************************************************/
void QDestroy(queue_ty *queue);

/*******************************************************************************
** Description: Adds an element to the end of the queue
** Return value: 0 - success
** 				 1 - fail
** Undefined behavior: If the queue pointer is NULL
** Complexity: O(1)
*******************************************************************************/
int QEnqueue(queue_ty *queue, void *data);

/*******************************************************************************
** Description: Remove the first element in the queue
** Undefined behavior: If the queue pointer is NULL or the queue is empty
** Complexity: O(1)
*******************************************************************************/
void QDequeue(queue_ty *queue);

/*******************************************************************************
** Description: Shows element data at front of queue
** Return value: Pointer to the first element data
** Undefined behavior: If the queue pointer is NULL or the queue is empty
** Complexity: O(1)
*******************************************************************************/
void *QPeek(const queue_ty *queue);

/*******************************************************************************
** Description: Checks if queue is empty
** Return value: 1 - if empty
** 				 0 - otherwise
** Undefined behavior: If the queue pointer is NULL
** Complexity: O(1)
*******************************************************************************/
int QIsEmpty(const queue_ty *queue);

/*******************************************************************************
** Description: Counts elements in queue
** Return value: number of elements in queue
** Undefined behavior: If the queue pointer is NULL
** Complexity: O(n)
*******************************************************************************/
size_t QSize(const queue_ty *queue);

/*******************************************************************************
** Description: Appends queue_2 to the end of queue_1
** Return value: Pointer to the merged queue
** Undefined behavior: If queue_1 or queue_2 are NULL
** Complexity: O(n)
*******************************************************************************/
queue_ty *QAppend(queue_ty *queue_1, queue_ty *queue_2);

#endif /* __QUEUE_H_ILRD__ */

