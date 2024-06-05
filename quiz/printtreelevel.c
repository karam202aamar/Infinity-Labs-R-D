/******************************************************************************/
#include <stdio.h>  /* print */
#include <stdlib.h> /* allocation */
/******************************************************************************/
#include "bst.h"
#include "Stack.h"
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
void PrintByLevel(bst_ty *bst);
static void PushChilds(bst_iter_ty node , stack_ty *new_stack);
/******************************************************************************/
int main()
{

	return 0;
}
/******************************************************************************/
void PrintByLevel(bst_ty *bst)
{
	bst_iter_ty parent_node = NULL;
	bst_iter_ty curr_left = NULL;
	bst_iter_ty curr_right = NULL;
	
	stack_ty *new_stack = StackCreate(BSTSize(bst) , sizeof(int));
	
	parent_node = bst->dummy_node->left_node;
	
	if(NULL == parent_node)
	{
		puts("NOTHING TO PRINT");
		
		return;
	}
	
	/* push first the root */
	StackPush(new_stack , parent_node);

	/* loop untill the end of the tree */
	while(!StackIsEmpty(new_stack))
	{
		parent_node = StackPeek(new_stack);
		printf("%d " , parent_node->data);
		
		StackPop(new_stack);
		StackPush(new_stack , curr_node->right_node);
		StackPush(new_stack , curr_node->left_node);
		/*
		if(parent_node->left_node || parent_node->left_node)
		{
			curr_left = parent_node->left_node;
			curr_right = parent_node->right_node;
				
			if(curr_left != NULL)
			{
				PushChilds(curr_left , new_stack);
			}
			if(curr_right != NULL)
			{
				PushChilds(curr_right , new_stack);
			}
		}
		*/	
	}
}
/******************************************************************************/
static void PushChilds(bst_iter_ty node , stack_ty *new_stack)
{
	bst_iter_ty curr_node = NULL;

	curr_node = node;

	if(curr_node->left_node)
	{
		StackPush(new_stack , curr_node->left_node->data);
	}
	if(curr_node->right_node)
	{
		StackPush(new_stack , curr_node->right_node->data);
	}		
}
/******************************************************************************/
