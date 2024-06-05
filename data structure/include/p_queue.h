/*******************************************************************************
 * Project: Data Structures - Priority Queue
 * Date: 24/08/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0 
*******************************************************************************/
#ifndef __P_QUEUE_H_ILRD__
#define __P_QUEUE_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct priority_q pq_ty;

/*******************************************************************************
** Compares between p_queue_data and new_data
** Return value: 1 - if p_queue_data is bigger than new_data
**				 0 - if p_queue_data and new_data are equal
**				 -1 - if new_data is bigger than p_queue_data
** Complexity: O(1)
** Undefined behavior:
*******************************************************************************/
typedef int (*pq_cmp_ty)(const void *p_queue_data, const void *new_data);

/*******************************************************************************
** Determines whether p_queue_data matches specified term
** Return value: 1 - true
**				 0 - false
** Complexity: O(1)
** Undefined behavior: 
*******************************************************************************/
typedef int (*pq_is_match_ty)(void *p_queue_data, void *user_param);

/*******************************************************************************
** Creates a new priority queue
** Return value: Pointer to the new p_queue, if failed return NULL
** Complexity: O(1)
** Undefined behavior: If compare_func is NULL
*******************************************************************************/
pq_ty *PQCreate(pq_cmp_ty cmp_func);

/*******************************************************************************
** Destroys the queue
** Complexity: O(n)
** Undefined behavior: If queue is NULL
*******************************************************************************/
void PQDestroy(pq_ty *queue);

/*******************************************************************************
** Insert data to queue placed according to user provided sorting criteria.
** Equal priorities will be placed by FIFO order.
** Undefined behavior: If queue is NULL or if data is not in compliance with the 
					   							  user's compare function
** Return value: 1 on failure, 0 otherwise
** Complexity: O(n)
*******************************************************************************/
int PQEnqueue(pq_ty *queue, void *data);

/*******************************************************************************
** Removes highest priority element
** Return value : Data of removed element
** Complexity: O(1)
** Undefined behavior: If queue is NULL or empty
*******************************************************************************/
void *PQDequeue(pq_ty *queue);

/*******************************************************************************
** Returns pointer to the highest priority data element in the queue.
** Complexity: O(1)
** Undefined behavior: If queue is NULL or empty
*******************************************************************************/
void *PQPeek(const pq_ty *queue);

/*******************************************************************************
** Returns the current number of elements in the queue.
** Complexity: O(n)
** Undefined behavior: If queue is NULL
*******************************************************************************/
size_t PQSize(const pq_ty *queue);

/*******************************************************************************
** Checks if queue is empty
** Return value: 1 - empty
** 		 		 0 - otherwise
** Complexity: O(1)
** Undefined behavior: If queue is NULL
*******************************************************************************/
int PQIsEmpty(const pq_ty *queue);

/*******************************************************************************
** Clears the pqueue from its elements
** Complexity: O(n)
** notes : no operation performed if queue is empty 
** Undefined behavior: If queue is NULL
*******************************************************************************/
void PQClear(pq_ty *queue);

/*******************************************************************************
** Removes the first element in the queue that matches is_match function criteria.
** Return value: success - data of removed element
**				 failure - NULL
** Complexity: O(n)
** Undefined behavior: If is_match is NULL
** 		  		      If pqueue is NULL
*******************************************************************************/
void *PQErase(pq_ty *queue, pq_is_match_ty is_match, void *param);

#endif /* __P_QUEUE_H_ILRD__ */
