/*******************************************************************************
 * Project: Data Structures - AVL Tree
 * Date: 12/10/22
 * Name: karam Aamar
 * Reviewer: Ortal 
 * Version: 1.0
*******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "avl.h"
/******************************************************************************/
#define ITR_TO_NODE(ITR)           ITR
#define NODE_TO_ITR(NODE)          NODE
#define ITR_INIT                   NULL
#define HEAD_DUMMY           (void *)0xDEADBEEF
#define ROOT(AVL)          AVL->dummy->children[0]
#define DUMMY(AVL)               AVL->dummy
#define LEFT_NODE(NODE)       NODE->children[0]
#define RIGHT_NODE(NODE)      NODE->children[1]
#define CMP_FUNC(AVL)           AVL->compare
#define DATA(NODE)              NODE->data
#define DIRECTION(x)           x==1 ? 1 : 0
/******************************************************************************/
typedef struct node node_ty; /* nodes of the tree */ 
/****************************** helper functions ******************************/
/* creates new node */
static node_ty* NewNode(void *data);

/* destroy recursively the nodes */
static void AVLDestroyRecursive(avl_ty *avl, node_ty *node);



/* check height recursively of the tree */
static ssize_t AVLHeightRecursive(node_ty* curr_node);

/* check maximum height */
static ssize_t MaxHeight(ssize_t x, ssize_t y);

/* inserts recursively to the tree */
static int AVLInsertRecursive(node_ty* node, void *data, compare_ty 
							   compare, void *param);
							   
/* foreach recursively function */							  
static int AVLForEachRecursive(node_ty* node, action_ty action_func, 
								   void *param);

/* size of the AVL recursively */
static size_t AVLSizeRecursive(node_ty* curr_node);

/* rotate the avl in left direction */
static node_ty* LeftRotate(node_ty* node_x);

/* rotate the avl in right direction */
static node_ty* RightRotate(node_ty* node_y);

/* destroy the avl recursively */
static void AVLDestroyRecursive(avl_ty *avl, node_ty *node);
/* removes nodes recursively */
static node_ty* AVLRemoveRecursive(node_ty* node, void *data, compare_ty compare
								    ,int* flag);
/* find node recursively*/
static void* AVLFindRecur(node_ty* node , compare_ty compare , void * data , 
								   void *param);
/* minimum data in tree */
static node_ty* MinDataNode(node_ty* node);



static ssize_t GetHeight(node_ty *node);
static void Rotate(node_ty *node, int direction);
static int GetBalance(node_ty *node);
static void CheckBalance(node_ty* node);
/******************************************************************************/
struct avl
{
	void * param;
	compare_ty compare;
	node_ty* dummy;		
};/* avl_ty */

struct node
{
	void * data;
	ssize_t height;
	node_ty* children[2];
};/* node_ty */
/******************************************************************************/
enum side{LEFT = 0, RIGHT = 1};
/******************************************************************************/
avl_ty *AVLCreate(compare_ty compare_func, void *param)
{
	avl_ty * avl = NULL;
	node_ty * dummy_node = NULL;
	
	/* Allocate AVL */
	avl = (avl_ty*)malloc(sizeof(avl_ty));
	
	if(NULL == avl)
	{
		perror(strerror(errno));
		return NULL;
	}
	/* create dummy node & initialize dummy node */
	dummy_node = NewNode(HEAD_DUMMY);
	
	/* initialize the avl */
	avl->param = param;
	avl->compare = compare_func;
	avl->dummy = dummy_node;
	
	return avl; 
}
/******************************************************************************/
void AVLDestroy(avl_ty *avl)
{
	assert(avl);
	
	/* call recursive destroy function */
	AVLDestroyRecursive(avl, ROOT(avl));
	
	/* destroy dummy */
	free(DUMMY(avl));
	DUMMY(avl) = NULL;
	
	free(avl);
	avl = NULL;
}
/******************************************************************************/
static void AVLDestroyRecursive(avl_ty *avl, node_ty *node)
{
	if(NULL == node)
	{
		return;
	}
	
	AVLDestroyRecursive(avl, node->children[LEFT]);
	AVLDestroyRecursive(avl, node->children[RIGHT]);
	
	if(node)
	{
		free(node);
		node = NULL;
	}
}
/******************************************************************************/
ssize_t AVLHeight(const avl_ty *avl)
{
	assert(avl);
	
	return AVLHeightRecursive(ROOT(avl));
}
/******************************************************************************/
size_t AVLSize(const avl_ty *avl)
{
	assert(avl);
	
	return AVLSizeRecursive(ROOT(avl));
}
/******************************************************************************/
int AVLIsEmpty(const avl_ty *avl)
{
	assert(avl);
	
	if(NULL == ROOT(avl))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
/******************************************************************************/
void *AVLFind(const avl_ty *avl, const void *data_to_find)
{
	assert(avl);
	assert(data_to_find);

	return AVLFindRecur(ROOT(avl) , CMP_FUNC(avl) , (void*)data_to_find ,
								  avl -> param);
}
/******************************************************************************/
static void* AVLFindRecur(node_ty* node , compare_ty compare , void * data 
								  , void *param)
{
	int is_data_found = 0;
	
	if(NULL == node)
	{
		return NULL;
	}
	
	is_data_found = compare(node->data , data , param);
	
	if(0 == is_data_found)
	{
		return node->data;
	}
	else if(is_data_found > 0)
	{
		return AVLFindRecur(LEFT_NODE(node) , compare , data , param);
	}
	else if(is_data_found < 0)
	{
		return AVLFindRecur(RIGHT_NODE(node) , compare , data , param);
	}
	return NULL;
}
/******************************************************************************/
static size_t AVLSizeRecursive(node_ty* curr_node)
{
	if(NULL == curr_node)
	{
		return 0;
	}
	else
	{
		return (1 + AVLSizeRecursive(LEFT_NODE(curr_node)) + 
				       AVLSizeRecursive(RIGHT_NODE(curr_node)));
	}
}
/******************************************************************************/
static ssize_t AVLHeightRecursive(node_ty* curr_node)
{
	if(NULL == curr_node)
	{
		return -1;
	}
	return 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(curr_node)),
				      AVLHeightRecursive(RIGHT_NODE(curr_node)));
}
/******************************************************************************/
static ssize_t MaxHeight(ssize_t x, ssize_t y)
{
	return (x > y)? x : y;
}
/******************************************************************************/
static node_ty* NewNode(void *data)
{
	node_ty* new_node = NULL;
	
	new_node = (node_ty*)malloc(sizeof(node_ty));
	
	if(NULL == new_node)
	{
		perror(strerror(errno));
		return NULL;
	}
	new_node -> data = data;
	new_node -> children[0] = NULL;
	new_node -> children[1] = NULL;
	new_node -> height = 0;
	
	return new_node;
}
/******************************************************************************/
int AVLForEach(avl_ty *avl, action_ty action_func, void *param)
{
	assert(avl);
	
	return AVLForEachRecursive(ROOT(avl),action_func,param);
}
/******************************************************************************/
static int AVLForEachRecursive(node_ty* node, action_ty action_func, void *param)
{
	int return_val = 0;
	
	if(NULL == node)
	{
		return return_val;
	}
	AVLForEachRecursive(LEFT_NODE(node), action_func, param);
	
	return_val = action_func(node->data, param);
	
	if(return_val)
	{
		return return_val;
	}
	AVLForEachRecursive(RIGHT_NODE(node), action_func, param);
	
	return return_val;
}
/******************************************************************************/
static void CheckBalance(node_ty* node)
{
	if (1 < GetBalance(node))
	{
	if (GetBalance(node->children[LEFT]) < 0)
        {
            /* LEFT RIGHT*/
            Rotate(node->children[LEFT], LEFT);
            Rotate(node, RIGHT);
        }
        else
        {
            /*LEFT LEFT*/
            Rotate(node, RIGHT);
        }
	}
	if (-1 > GetBalance(node))
	{
       		if (GetBalance(node->children[RIGHT]) > 0)
        	{
        		/* RIGHT LEFT*/
			Rotate(node->children[RIGHT], RIGHT);
			Rotate(node, LEFT);
        	}
        else
        	{
			/* RIGHT RIGHT*/
			Rotate(node, LEFT);
       		 }
        }
}
/******************************************************************************/
int AVLInsert(avl_ty *avl, void *data)
{
	node_ty* root_node = NULL;
	node_ty* new_node = NULL;
	
	assert(avl);
	assert(data);
	
	root_node = ROOT(avl);
	
	if(NULL == root_node)
	{
		new_node = NewNode(data);
		
		if(NULL == new_node)
		{
			return 1;
		}
		
		ROOT(avl) = new_node;
		return 0;
	}
	
	AVLInsertRecursive(root_node, data, CMP_FUNC(avl), avl->param);
	ROOT(avl)->height = GetHeight(ROOT(avl));
	
	/* check if needs balance */
	CheckBalance(ROOT(avl));
	
	return 0;
}
/******************************************************************************/
static int AVLInsertRecursive(node_ty* node, void *data, compare_ty 
							   compare, void *param)
{
	int side_direction = 0;
	int check_status = 0;
	
	side_direction = DIRECTION(compare(DATA(node), data, param));
	
	/* if there is an empty node then assign */
	if(NULL == node->children[side_direction])
	{
		node->children[side_direction] = NewNode(data);
		
		
		if(!node->children[side_direction])
		{
			return 1;
		}
		
		node->height = GetHeight(node);
		
		return 0;
	}
	check_status = AVLInsertRecursive(node->children[side_direction], 
						      data, compare, param);
	node->height = GetHeight(node);
	CheckBalance(node);
	
	return check_status;
/******************************************************************************/

/******************************************************************************/
	#if 0
	int balance_check = 0;
	
	int cmp_result = 0;
	
	if(NULL == node)
	{
		return new_node;
	}
	
	cmp_result = compare(DATA(node), DATA(new_node), param); 
	
	if(1 == cmp_result)
	{
	/* go left */
	LEFT_NODE(node) = AVLInsertRecursive(LEFT_NODE(node), new_node, 
								compare, param);
	}
	else if(-1 == cmp_result)
	{
	/* go right */
	RIGHT_NODE(node) = AVLInsertRecursive(RIGHT_NODE(node), new_node,
							        compare, param);
	}
	
	node->height = 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(node)),
				           AVLHeightRecursive(LEFT_NODE(node)));
	
	
	balance_check = CheckBalance(node);
	
	/* check left left rotation */
	if(balance_check > 1 && 1 == compare(DATA(LEFT_NODE(node)), 
							 DATA(new_node), param))
	{
		return RightRotate(node);
	}
	/* check right right rotation */
	if(balance_check < -1 && -1 == compare(DATA(RIGHT_NODE(node)),
							 DATA(new_node), param))
	{
		return LeftRotate(node);
	}
	/* left right rotation */
	if(balance_check > 1 && -1 == compare(DATA(LEFT_NODE(node)),
							 DATA(new_node), param))
	{
		LEFT_NODE(node) = LeftRotate(LEFT_NODE(node));
		return RightRotate(node);
	}
	/* right left rotation */
	if(balance_check < -1 && 1 == compare(DATA(RIGHT_NODE(node)),
							 DATA(new_node), param))
	{
		RIGHT_NODE(node) = RightRotate(RIGHT_NODE(node));
		return LeftRotate(node);
	}
	return node;
	#endif
}
/******************************************************************************/
static ssize_t GetHeight(node_ty* node)
{
	ssize_t right_height = -1; /* or -1 */
	ssize_t left_height = -1;
	
	if(node->children[RIGHT])
	{
		right_height = GetHeight(node->children[RIGHT]);
	}
	if(node->children[LEFT])
	{
		left_height = GetHeight(node->children[LEFT]);
	}
	return (MaxHeight(right_height, left_height));
}
/******************************************************************************/
static node_ty* RightRotate(node_ty* node_y)
{
	node_ty* node_x = LEFT_NODE(node_y);
	node_ty* node_t2 = RIGHT_NODE(node_x);
	
	RIGHT_NODE(node_x) = node_y;
	LEFT_NODE(node_y) = node_t2;
	
	/* update heights */
	node_y->height = 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(node_y)),
	                                AVLHeightRecursive(RIGHT_NODE(node_y)));
	node_x->height = 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(node_x)),
	                                AVLHeightRecursive(RIGHT_NODE(node_x)));   
	return node_x;                                                           
}
/******************************************************************************/
static node_ty* LeftRotate(node_ty* node_x)
{
	node_ty* node_y = RIGHT_NODE(node_x);
	node_ty* node_t2 = LEFT_NODE(node_y);
	
	LEFT_NODE(node_y) = node_x;
	RIGHT_NODE(node_x) = node_t2;
	
	/* update heights */
	node_y->height = 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(node_y)),
	                                AVLHeightRecursive(RIGHT_NODE(node_y)));
	node_x->height = 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(node_x)),
	                                AVLHeightRecursive(RIGHT_NODE(node_x)));   
	return node_y;                                                           
}
/******************************************************************************/
static node_ty* MinDataNode(node_ty* node)
{
	node_ty* curr_node = node;
	
	while(NULL != LEFT_NODE(curr_node))
	{
		curr_node = LEFT_NODE(curr_node);
	}
	return curr_node;
}
/******************************************************************************/
static void Rotate(node_ty *node, int direction)
{
    node_ty *children = NULL;
    void *temp_data = NULL;
    assert(node);

    children = node->children[!direction];
    temp_data = children->data;

    children->data = node->data;
    node->data = temp_data;
    /*link next next to curr*/
    node->children[!direction] = children->children[!direction];
    /*flip child subtree*/
    children->children[!direction] = children->children[direction];
    children->children[direction] = node->children[direction];
    /*link back*/
    node->children[direction] = children;

    children->height = GetHeight(children);
    node->height = GetHeight(node);
}
/******************************************************************************/
static int GetBalance(node_ty *node)
{
    int right = -1;
    int left = -1;
    if(NULL == node)
    {
        return 0;
    }
    if(node->children[RIGHT])
    {
        right = node->children[RIGHT]->height;
    }
    if(node->children[LEFT])
    {
        left = node->children[LEFT]->height;
    }
    /*returns positiv if right subtree is smaller then left */
    return (left - right);
}
/******************************************************************************/
#if 0
int AVLRemove(avl_ty *avl, void *data)
{
	int flag = 0;
	
	assert(avl);

	if(NULL == ROOT(avl))
	{
		return 1;
	}
	else
	{
		/* check if the value exists */
		if(NULL != AVLFind(avl,(const void*)data))
		{
		       AVLRemoveRecursive(ROOT(avl), data, CMP_FUNC(avl),&flag);
			
		       if(1 == flag)
		       {
		      		return 1;
		       }
		}
		/*
		puts("*******delete*********\n");
		PrintTree(ROOT(avl));
		*/
	}
	return 0;
}
/******************************************************************************/
static node_ty* AVLRemoveRecursive(node_ty* node, void *data, compare_ty compare 
								     ,int* flag)
{
	node_ty* tmp_node = NULL;
	int balance_check = 0;
	int param = 1;
	int comp_result = 0;
	
	if(NULL == node)
	{
		*flag = 1;
		return node;
	}
	
	comp_result = compare(node->data , data , &param);
	
	if(comp_result > 0)
	{
		
			LEFT_NODE(node) = AVLRemoveRecursive(LEFT_NODE(node), 
							     data,compare,flag);
		
	}
	else if(comp_result < 0)
	{
		
			RIGHT_NODE(node) = AVLRemoveRecursive(RIGHT_NODE(node),
							    data, compare,flag);
		 
	}
	else
	{
		if(LEFT_NODE(node) == NULL || RIGHT_NODE(node) == NULL)
		{
			tmp_node = LEFT_NODE(node) ? LEFT_NODE(node) :
							       RIGHT_NODE(node);
			/* IF NO CHILD */
			if(NULL == tmp_node)
			{
				tmp_node = node;
				node = NULL;
			}
			else /* one child */
			{
				DATA(node) = DATA(tmp_node);
			}
			free(tmp_node);
		}
		else
		{
			tmp_node = MinDataNode(RIGHT_NODE(node));
			
			DATA(node) = DATA(tmp_node);
			
			RIGHT_NODE(node) = AVLRemoveRecursive(RIGHT_NODE(node), 
						  DATA(tmp_node), compare,flag);
		}
	}
	if(1 == *flag)
	{
		return node;
	}
	/*
	node->height = 1 + MaxHeight(AVLHeightRecursive(LEFT_NODE(node)),
					   AVLHeightRecursive(RIGHT_NODE(node)));
	*/
	balance_check = CheckBalance(node);
	
	/* do the rotations */
	/* check left left rotation */
	if(balance_check > 1 && 1 == compare(DATA(LEFT_NODE(node)), data,
								        &param))
	{
		return RightRotate(node);
	}
	/* check right right rotation */
	else if(balance_check < -1 && -1 == compare(DATA(RIGHT_NODE(node)), data, 
									&param))
	{
		return LeftRotate(node);
	}
	/* left right rotation */
	else if(balance_check > 1 && -1 == compare(DATA(LEFT_NODE(node)), data,
								        &param))
	{
		LEFT_NODE(node) = LeftRotate(LEFT_NODE(node));
		return RightRotate(node);
	}
	/* right left rotation */
	else if(balance_check < -1 && 1 == compare(DATA(RIGHT_NODE(node)), data,
								        &param))
	{
		RIGHT_NODE(node) = RightRotate(RIGHT_NODE(node));
		return LeftRotate(node);
	}
	
	return NULL;
}
#endif
/******************************************************************************/
