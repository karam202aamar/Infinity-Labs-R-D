/*******************************************************************************
 * Project: DATA STRUCTURE EXAM
 * Date: 29/09/22
 * Name: karam
 * Reviewer: 		
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/******************************************************************************/

/******************************************************************************/
typedef struct fsa 
{
	fsa_ty *next_free_block;   	
}fsa_ty;

typedef struct vsa 
{
	size_t next_free_block;   	
}vsa_ty;

typedef struct node
{
	void * data;
	node_ty * next_node;
}node_ty;

typedef struct d_node
{
	void * data;
	d_node_ty * next_node;
	d_node_ty * prev_node;
}d_node_ty;

typedef struct queue
{
	char m_queue[q_size];   /* the array */
	size_t m_elements_in_q; /* current number of elements */ 
	size_t m_first_elements_index; /* index of first ele */
}queue_ty;
/******************************************************************************/
int main()
{

	return 0;
}
/******************************************************************************/
void * MallocFSA(fsa_ty *fsa)
{
	void * curr_blk = NULL;
	
	if(NULL != fsa->next_free_block)
	{
		/* set return ptr */
		curr_blk = (char*)fsa->next_free_block + sizeof(fsa_ty);
		
		/* set next free place */
		fsa->next_free_block = (fsa->next_free_block)->next_free_block;
		
		return curr_blk;
	}
	return NULL;
}
/******************************************************************************/
void FreeFSA(fsa_ty *fsa, void *block)
{
	/* move to the meta data of the allocated block */
	block = (char*)block - sizeof(fsa_ty);
	/* 
	read void ptr block as fsa_ty* .
	set the ptr inside next_free_block to point to current next_free_block.
	set the ptr inside fsa .
	*/
	((fsa_ty*)block)->next_free = (fsa_ty*)fsa->next_free_block;

	fsa->next_free_block = block;
}
/******************************************************************************/
void * MallocVSA(vsa_ty *vsa , size_t blk_siz)
{
	vsa_ty * curr_blk = vsa;
	vsa_ty * next_blk = vsa;
	size_t updated_value = 0;
	
	/* loop untill the end */
	while(0 != curr_blk->next_free_block)
	{
		/* then allocate */
		if(curr_blk->next_free_block < 0 && -(curr_blk->next_free_block)
						   > (blk_siz + sizeof(vsa_ty)))
		{
			/* the rest space in the pool */
			updated_value = curr_blk->next_free_block + blk_siz 
							       + sizeof(vsa_ty);
			/* set the value that allocated */
			curr_blk->next_free_block = blk_siz;
			/* move to next block to set value*/
			next_blk = (char*)curr_blk + sizeof(vsa_ty) + blk_siz;
			/* set the value inside */
			next_blk->next_free_block = updated_value;
			
			return curr_blk;
		}
		/* move to next */
		curr_blk = (vsa_ty*)((char*)vsa + sizeof(vsa_ty) + curr_blk->			
							       next_free_block);
		
		return NULL;
	}
}
/******************************************************************************/
void FreeVSA(void *block)
{
	void* runner = block;
	/* go the start of the meta data */
	runner = (vsa_ty*)((char*)block - VSA_SIZE);
	/* update the data in the meta data */
	((vsa_ty*)runner)->next_free_block = -(((vsa_ty*)block)->next_free_block);
}
/******************************************************************************/
node_ty* FlipList(node_ty* list)
{
	node_ty* curr_node = list;
	node_ty* next = NULL;
	node_ty* prev = NULL;
	
	node_ty* tmp_node = NULL;
	
	/* traverse the linked list untill the end */
	while(NULL != curr_node)
	{
		
		next = curr_node -> next_node;
		
		curr_node -> next_node = prev;
	
		prev = current;
		/* move to next */ 
		current = next;
	}
	/* the new head of the linked list */
	return prev;
}
/******************************************************************************/
/* 
	quest 3: 
		create  o(1)
		destroy o(n)
		insert  o(1)
		remove 	o(1)
		find    o(n)
		begin   o(1)
		end     o(n)
		next    o(1)
		count   o(n)
*/
/******************************************************************************/
/*
	returns: 1 if there is loop 
		 0 if there is no loop 
		 
	pseudo: set fast and slow runner 
		fast moves two nodes forward 
		slow moves one node forward 
		
		while(loop to the end)
		if(slow == fast)-then there is loop 
	
*/
int IsThereLoop(node_ty* list)
{
	node_ty* slow = list;
	node_ty* fast = list;
	 
	 while(slow && fast && fast->next_node)
	{
		slow = slow->next_node;

		fast = fast->next_node->next_node;

		if(slow == fast)
		{
			return 1;
		}
	}
	return 0; 
}
/******************************************************************************/
void OpenLoop(node_ty* list)
{
	node_ty* check_node = list;

	node_ty* slow = list;
	node_ty* prev = list;
	node_ty* fast = list->next_node;
	
	/* check if there is a loop */
	if(1 == IsThereLoop(list))
	{
		while(slow && fast && fast->next_node)
		{
		
			if(check_node == slow && check_node == fast)
			{
				prev->next_node = NULL;
			}
			prev = slow;
			
			slow = slow->next_node;

			fast = fast->next_node->next_node;
		}
	}
}
/******************************************************************************/
/*
	returns: returns the intersect node if found
		 else returns NULL 
*/
node_ty* IsThereIntersect(node_ty* list1 , node_ty* list2)
{
	node_ty* check_node_1 = list1;
	node_ty* check_node_2 = list2;
	
	while(check_node_1)
	{
		while(check_node_2)
		{
			if(check_node_1 == check_node_2)
			{
				return check_node_1;
			}
		}
		check_node_1 = check_node_1->next_node;
	}
	return NULL; 
}	
/******************************************************************************/
void CancelInter(node_ty* list1 , node_ty* list2)
{
	node_ty* inter_node = NULL;
	node_ty* check_node2 = list2;
	
	/* check if there is intersection */
	inter_node = IsThereIntersect(list1 , list2)
	
	if(NULL == inter_node)
	{
		return;
	}else 
	{
		while(check_node2->next_node != inter_node)
		{
			check_node2 = check_node2->next_node;
		}
		while(inter_node)
		{
			/* duplicate */
			check_node2->next_node = CreateNode(inter_node->data);
			
			inter_node = inter_node->next_node;
		}
	}
}
/******************************************************************************/
static node_ty* CreateNode(void *data)
{
	node_ty* new_node;
	
	new_node = (node_ty*)malloc(sizeof(node_ty));
	
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node -> data = data;
	new_node -> next_node = NULL;
	
	return new_node;
}
/******************************************************************************/
node_ty* RemoveNode(node_ty* node_to_remove)
{
	/* hold next node */
 	node_ty* tmp_node = node_to_remove->next_node;
	
	/* copy next node data to current */
	node_to_remove->data = node_to_remove->next_node->data;
	
	/* point to next next node of the removed node */
	node_to_remove->next_node = node_to_remove->next_node->next_node;
	

	free(tmp_node);
	tmp_node = NULL; 

	return node_to_remove;
}
/******************************************************************************/
d_node_ty* DInsertNode(d_node_ty* node , void *data)
{
	
	d_node_ty* new_node = (d_node_ty*)malloc(sizeof(d_node_ty));
	
	new_node->next = node;
	
	node->prev->next = new_node;
	
	new_node->prev = node->prev;
	
	node->prev = new_node;

	new_node->data = data;

	return new_node;
}
/******************************************************************************/
int MissingNumber(int arr[] , size_t arr_size)
{
	int *lut = NULL , i = 0;
	lut = (int*)malloc(sizeof(int)*arr_size);
	
	for(i; i < arr_size; ++i)
	{
		lut[i] = 0;
	}
	
	for(i; i < arr_size; ++i)
	{
		lut[arr[i]] = 1;
	}
	
	for(i; i < arr_size; ++i)
	{
		if(lut[i] == 0)
		{
			return i;
		}
	}
}
/******************************************************************************/
/* 
	return: 1 success
		0 fail
*/
int QueuePushChar(queue_ty* queue , char char_to_add)
{
	/* check if full */
	if(queue->m_elements_in_q == Q_SIZE)
	{
		return 0;
	}
	
	queue->m_queue[(m_first_elements_index + m_elements_in_q)	
						      % Q_SIZE] = char_to_add;
	++(queue->m_elements_in_q);
		
	return 1;	
}
/******************************************************************************/
/* 
	return: 1 success
		0 fail
*/
int QueuePopChar(queue_ty* queue)
{
	/* check if empty */
	if(0 == queue->m_elements_in_q)
	{
		return 0;
	}
	
	queue->m_first_elements_index = (queue->m_first_elements_index + 1) 
								      % Q_SIZE;
	
	--(queue->m_elements_in_q);
		
	return 1;	
}
/******************************************************************************/
/* 
	return: 1 inside
		0 fail
*/
int BitMap(int bit_map[] ,int point_row, int point_c , int row , int col)
{
	int i = 0;
	

	for(i = -1 ; i < 2 ; ++i)
	{
		if(!IsLegalLocation(point_row + i , point_c + i 
							, row , col))
		{
			if(bit_map[point_row + i , point_c + i])
			{
				return 1;
			}
		}
	}
	return 0;
}
/******************************************************************************/
static int IsLegalLocation(int r , int c , int row , int col)
{
	if(r < 0 || c < 0 || c >= col || r >= col)
	{
		return 1;
	}
	return 0;
}
/******************************************************************************/



























