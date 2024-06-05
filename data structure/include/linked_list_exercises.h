/*******************************************************************************
 * Project: Data Structures - Linked List Exercises
 * Date: 14/08/22
 * Name: HRD26
 * Reviewer: Liel
* Version: 1.0 		
*******************************************************************************/

#ifndef __LINKED_LIST_H_ILRD__
#define __LINKED_LIST_H_ILRD__

typedef struct node node_t;

/******************************************************************************/

/* Reverses the order of a given slist */
node_t *Flip(node_t *head);

/* Tells whether a given slist has loop */
int HasLoop(const node_t *head);

/* Returns a pointer to a first node mutual to both slists, if any */
node_t *FindIntersection(node_t *head_1, node_t *head_2);

#endif /* __LINKED_LIST_H_ILRD__ */


