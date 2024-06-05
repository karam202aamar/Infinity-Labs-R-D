/*******************************************************************************
 * Project: BINARY SEARCH TREE
 * Date: 22/09/22
 * Name: karam
 * Reviewer: evgani
 * Version: 1.0
*******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "bst.h"
/******************************************************************************/
#define HEAD_DUMMY (void *)0xDEADBEEF
/******************************************************************************/
static bst_iter_ty NewNode(void *data);
/******************************************************************************/
typedef enum STATUS { STOP = 0 , CONTINUE } status_ty;
/******************************************************************************/
struct bst
{
	bst_iter_ty dummy_node;
	compare_ty compare;
	void * param;	
};/* bst_ty */

struct node
{
	void * data;
	bst_iter_ty father_node;
	bst_iter_ty right_node;
	bst_iter_ty left_node;		
};/* node_ty */
/******************************************************************************/
bst_ty *BSTCreate(compare_ty compare_func, void *param)
{
	bst_ty *bst = NULL;
	bst_iter_ty dummy_node = NULL;
	
	/* Allocate BINARY SEARCH TREE */
	bst = (bst_ty*)malloc(sizeof(bst_ty));
	
	if(NULL == bst)
	{
		perror(strerror(errno));
		return NULL;
	}
	/*Allocate memory for the dummy node*/
	dummy_node = (bst_iter_ty)malloc(sizeof(node_ty));
	
	/* check malloc */
	if(NULL == dummy_node)
	{
		perror(strerror(errno));
		free(bst);
		bst = NULL;
		return NULL;
	}
	
	/* set dummy node */
	dummy_node -> data = HEAD_DUMMY;
	dummy_node -> father_node = NULL;
	dummy_node -> right_node = NULL;
	dummy_node -> left_node = NULL;
	
	/* set binary search tree */
	bst -> dummy_node = dummy_node;
	bst -> compare = compare_func;
	bst -> param = param;
	
	return bst;
}	
/******************************************************************************/
bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
	bst_iter_ty curr_node = NULL;
	bst_iter_ty new_node = NULL;
	
	status_ty status = CONTINUE;
	
	/* call the new node function */
	new_node = NewNode(data);
	
	/* set current node to first node in the tree */
	curr_node = bst->dummy_node->left_node;
	
	/* check the root node if NULL */
	if(curr_node)
	{
		/* CHECK THE VALUES OF COMPARE FUNCTION */ 
		while(status) 
		{
			/* if the new data is smaller then go left */
			if(1 == bst -> compare(curr_node->data , data , 
							    bst -> param))
			{
				/* 
				if the left node is NULL then set the value 
				in the left node and stop the loop - we found
				empty and appropriate place to set . 
				*/
				if(NULL == curr_node->left_node)
				{
					/* set new data */
					new_node->data = data;
					new_node->right_node = NULL;
					new_node->left_node = NULL;
					curr_node->left_node = new_node;
					new_node->father_node = curr_node;
					status = STOP;
					return new_node;
					
				}else /* if not NULL then move to next */
				{
					 curr_node = curr_node->left_node;
				}
			}else /* go right , (equal to zero is undefined) */
			{
				if(NULL == curr_node->right_node)
				{	
					/* set new data */
					new_node->data = data;
					new_node->right_node = NULL;
					new_node->left_node = NULL;
					
					curr_node->right_node = new_node;
					new_node->father_node = curr_node;
					
					status = STOP;
					return new_node;
					
				}else /* if not NULL then move to next */
				{
					 curr_node = curr_node->right_node;
				}
			}			
		}
	}else  /* there is no childs yet */
	{
		/* set new data */
		new_node->data = data;
		new_node->right_node = NULL;
		new_node->left_node = NULL;
		
		/* set new node father to be dummy */
		new_node->father_node = bst->dummy_node;
		/* dummy node left child = new node */
		bst->dummy_node->left_node = new_node;
		/* return the new node */
		return new_node;
	}
	return NULL;	
}
/******************************************************************************/
void *BSTGetData(bst_iter_ty iter)
{
	assert(iter);
	
	return iter -> data;
}
/******************************************************************************/
bst_iter_ty BSTBegin(const bst_ty *bst)
{
	bst_iter_ty curr_node = NULL;
	
	assert(bst);
	
	curr_node = bst->dummy_node;
	
	while(curr_node->left_node)
	{
		curr_node = curr_node->left_node;
	}
	return curr_node;
}
/******************************************************************************/
bst_iter_ty BSTEnd(const bst_ty *bst)
{
	assert(bst);
	
	return bst -> dummy_node;
}
/******************************************************************************/
/*
case 1: the node x has a right subtree.

case 2: the node x doesn't have a right subtree ,
	it's the right child of it's parent node.
	
case 3: there is no right subtree , it's the left child of it's parent node .
*/
bst_iter_ty BSTNext(bst_iter_ty iter)
{
	bst_iter_ty current_node = NULL; /* I dont know what is iter */
	bst_iter_ty parent_node = NULL;
	
	assert(iter);
	
	current_node = iter;
	parent_node = iter->father_node;
	
	if(NULL != current_node->right_node ) /* case 1*/
	{
		current_node = current_node->right_node;
		/* get the most left */
		while(current_node->left_node)
		{
			current_node = current_node->left_node;
		}
		return current_node;
	}
	else /* there is no right subtree */
	{
		/* case 3 , left node */
		if(parent_node->left_node == iter && parent_node->data != HEAD_DUMMY) 
		{
			return parent_node;
		}
		/* case 2 , right node */
		else if(parent_node->right_node == iter)
		{
			while(parent_node->left_node != current_node)
			{
				current_node = parent_node;
				parent_node = parent_node->father_node;
			}
			return parent_node;
		}
	}
	return NULL;
}
/******************************************************************************/
/*
case 1: the node x has a left subtree.

case 2: the node x doesn't have a left subtree ,
	it's the left child of it's parent node.
	
case 3: there is no left subtree , it's the right child of it's parent node .
*/
bst_iter_ty BSTPrev(bst_iter_ty iter)
{
	bst_iter_ty current_node = NULL;
	bst_iter_ty parent_node = NULL;
	
	assert(iter);
	
	current_node = iter->left_node;
	parent_node = iter->father_node;
	
	if(current_node) /* case 1*/
	{
		/* get the most right */
		while(current_node->right_node)
		{
			current_node = current_node->right_node;
		}
		return current_node;
	}
	else 
	{
		if(parent_node->right_node == iter) /* case 3 , right node */
		{
			return parent_node;
		}else /* case 2 , left node */
		{
			while(parent_node->right_node != current_node)
			{
				current_node = parent_node;
				parent_node = parent_node->father_node;
			}
			return parent_node;
		}
	}
}
/******************************************************************************/
int BSTIsSameIter(bst_iter_ty iter_1, bst_iter_ty iter_2)
{
	assert(iter_1);
	assert(iter_2);
	
	return (iter_1 == iter_2);
}
/******************************************************************************/
int BSTIsEmpty(const bst_ty *bst)
{
	assert(bst);
	
	if(NULL == bst->dummy_node->left_node)
	{
		return 1;
	}
	return 0;
}
/******************************************************************************/
size_t BSTSize(const bst_ty *bst)
{
	size_t count = 0;
	bst_iter_ty next_node = NULL;
	
	assert(bst);
	
	next_node = BSTBegin(bst);
	
	while(HEAD_DUMMY != BSTGetData((next_node)))
	{
		++count;
		next_node = BSTNext(next_node);
	}
	return count;
}
/******************************************************************************/
/*
	case 1: no child 
	case 2: one child 
	case 3: 2 childs 
*/
void BSTRemove(bst_iter_ty iter)
{
	bst_iter_ty curr_node = NULL;
	bst_iter_ty max_node = NULL;
	
	assert(iter);
	
	curr_node = iter;
	
	/* case 1 */
	if(NULL == curr_node->left_node && NULL == curr_node->right_node)
	{
		/* check which side this iter is */
		if(curr_node == curr_node->father_node->left_node)
		{	
			/* set parent left node NULL*/
			curr_node->father_node->left_node = NULL;
		}
		else
		{
			curr_node->father_node->right_node = NULL;
		}
		
		free(iter);
		iter = NULL;
	}
	/* case 2 - current node has a right child */
	else if(NULL == curr_node->left_node && curr_node->right_node)
	{
		/* check which side this iter is */
		if(curr_node == curr_node->father_node->right_node)
		{
			curr_node->father_node->right_node = curr_node
								->right_node;
			curr_node->right_node->father_node = curr_node
								->father_node;
		}
		else
		{
			curr_node->father_node->left_node = curr_node
								->right_node;
			curr_node->right_node->father_node = curr_node
								->father_node;
		}
		free(iter);
		iter = NULL;
	}
	/* case 2 - current node has a left child */
	else if(curr_node->left_node && NULL == curr_node->right_node)
	{
		/* check which side this iter is */
		if(curr_node == curr_node->father_node->right_node)
		{
			curr_node->father_node->right_node = curr_node
								->left_node;
			curr_node->left_node->father_node = curr_node
								->father_node;
		}
		else
		{
			curr_node->father_node->left_node = curr_node
								->left_node;
			curr_node->left_node->father_node = curr_node
								->father_node;
		}
		free(iter);
		iter = NULL;
	}
	/* case 3- node has 2 childs */
	else if(curr_node->left_node && curr_node->right_node)
	{
		
		curr_node = iter->left_node;
		max_node = curr_node->data;
		
		/* find max in left */
		while(curr_node->right_node)
		{
			/* find max */
			if(curr_node->data > max_node->data)
			{
				max_node = curr_node;
			}
			/* move to next */
			curr_node = curr_node->right_node;
		}
		iter->data = max_node->data;
		max_node->father_node->right_node = NULL;
		
		free(max_node);
		max_node = NULL;
	}
}
/******************************************************************************/
void BSTDestroy(bst_ty *bst)
{
	bst_iter_ty curr_node = NULL;
	bst_iter_ty next_node = NULL;
	
	assert(bst);
	
	curr_node = BSTBegin(bst);
	
	if(curr_node->data != HEAD_DUMMY)
	{
		next_node = BSTNext(curr_node);
	
		while(next_node)
		{
			
			BSTRemove(curr_node);
			curr_node = next_node;
			next_node = BSTNext(next_node);
		}
	}
	if(BSTGetData(curr_node) == HEAD_DUMMY)
	{
		free(bst->dummy_node);	
		bst->dummy_node = NULL;
		
		free(bst);
		bst = NULL;
	}
	else
	{
	free(curr_node);
	curr_node = NULL;
	
	free(bst->dummy_node);	
	bst->dummy_node = NULL;
		
	free(bst);
	bst = NULL;
	}
}
/******************************************************************************/
bst_iter_ty BSTFind(const bst_ty *bst, const void *data_to_find)
{
	bst_iter_ty curr_node = NULL;
	
	assert(bst);
	assert(data_to_find);
	
	curr_node = BSTBegin(bst);
	
	while(BSTNext(curr_node))
	{
		if(0 == bst->compare(data_to_find, BSTGetData(curr_node), 
								 bst->param))
		{
			return curr_node;
		}
		
		curr_node = BSTNext(curr_node);
	}
	return curr_node;
}
/******************************************************************************/
int BSTForEach(bst_iter_ty from, bst_iter_ty to, action_ty action_func,
								void *param)
{
	assert(action_func);
	assert(from);
	assert(to);
	
	while(from != to)
	{
		if(action_func(from->data, param)) 
		{
			/* which means failed */
			return 1;
		}
		/* move to next node */
		from = BSTNext(from);
	}
	return 0;
}															   
/******************************************************************************/
static bst_iter_ty NewNode(void *data)
{
	node_ty* new_node;
	
	new_node = (node_ty*)malloc(sizeof(node_ty));
	
	if(NULL == new_node)
	{
		perror(strerror(errno));
		return NULL;
	}
	new_node -> data = data;
	new_node -> right_node = NULL;
	new_node -> left_node = NULL;
	new_node -> father_node = NULL;
	
	return new_node;
}
