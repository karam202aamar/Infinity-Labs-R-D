#include <stdio.h>  /* print */
#include <stdlib.h> /*dynamic allocation */
#include <assert.h> /*assert */
/******************************************************************************/
#include "linked_list_exercises.h"
/******************************************************************************/
#define MINUS -1 
/******************************************************************************/
enum STATUS {FAIL, SUCCESS} status_ty;
/******************************************************************************/
struct node
{
	void * data;
	node_t * next_node;
};
/******************************************************************************/
static void ImplementFunc();
static void FlipTest();
static void LoopTest();
static int CountNodes(node_t *head);
static void FindIntersectTest();
/******************************************************************************/
int main()
{
	/* call implementation function */
	ImplementFunc();
	
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	/* test flip function */
	FlipTest();
	
	/* test loop function */
	LoopTest();
	
	/* test intersection function */
	FindIntersectTest();
}
/******************************************************************************/
node_t *Flip(node_t *head)
{
	/* set nodes */
	node_t* head_node = head;
	node_t* current = head;
	
	/* define nodes */
	node_t* next = NULL;
	node_t* prev = NULL;
	
	/* loop untill we find NULL */
	while(NULL != current)
	{
		/* set the next node to put it in current*/
		next = current -> next_node;
		
		/* point to previous node */
		current -> next_node = prev;
		
		/* set previous node to hold current node */
		prev = current;
		
		/* move to next node */
                current = next;
                
        }
        
        /* point to the new head */
        head_node = prev;
        
        return head_node;
}
/******************************************************************************/
static void FlipTest()
{
	/* set values */
	int a = 10;
	int b = 20; 
	int c = 30;
	
	/* define nodes */
	node_t* reversed_head = NULL;
	node_t* head = NULL;
	node_t* second = NULL;
	node_t* third = NULL;
	
	/* dynamically allocate nodes */
	head = (node_t*)malloc(sizeof(node_t));
	second = (node_t*)malloc(sizeof(node_t));
	third = (node_t*)malloc(sizeof(node_t));
	
	/* set nodes */
	head->data = &a;
	head->next_node = second;
	
	second->data = &b;
	second->next_node = third;
	
	third->data = &c;
	third->next_node = NULL;
	
	/* call nodes flip function */
	reversed_head = Flip(head);
	
	/* check if the linked list flipped */
	if(*(int*)reversed_head->data == a && *(int*)reversed_head->next_node->
	     data == b && *(int*)reversed_head->next_node->next_node->data == c)
	{
		printf("Flip Failed");
	}
	
	/* free dynamic allocation */
	free(head);
	free(second);
	free(third);
		
}
/******************************************************************************/
int HasLoop(const node_t *head)
{
	/* define slow & fast nodes */
	const node_t* slow = head;
	const node_t* fast = head;
	
     /*loop until we get NULL value or we have same node location then looped*/
	while(slow && fast && fast -> next_node)
	{
		/* move one step to next node */
		slow = slow -> next_node;
		
		/* move two steps to beyond next node */
		fast = fast -> next_node -> next_node;
		
		/* if we have the same node */
		if(slow == fast)
		{
			return SUCCESS;
		}
	}
	return FAIL; 
}
/******************************************************************************/
static void LoopTest()
{
	/* set data */
	int a = 10;
	int b = 20; 
	int c = 30;
	int d = 40;
	
	/* nodes nodes */
	node_t* head = NULL;
	node_t* second = NULL;
	node_t* third = NULL;
	node_t* fourth = NULL;
	
	/* dynamically allocate nodes */
	head = (node_t*)malloc(sizeof(node_t));
	second = (node_t*)malloc(sizeof(node_t));
	third = (node_t*)malloc(sizeof(node_t));
	fourth = (node_t*)malloc(sizeof(node_t));
	
	/* set nodes */
	head->data = &a;
	head->next_node = second;
	
	second->data = &b;
	second->next_node = third;
	
	third->data = &c;
	third->next_node = fourth;
	
	fourth->data = &d;
	fourth->next_node = head;
	
	/* check if the function works */
	if(FAIL == HasLoop(head))
	{
		printf("LOOP Test Failed");
	}
	
	/* free dynamic allocation */
	free(head);
	free(second);
	free(third);
	free(fourth);	
}
/******************************************************************************/
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	/* set steps number of moves to equal distance 
	   for both linked list from instersection  */
	int steps = 0;
	int i;
	
	/* get number of nodes form each list & calculate the steps needed */
	steps = CountNodes(head_1)-CountNodes(head_2);
	

	/* if negative value we should move with head_2  */
	if(steps < 0)
	{
		
		steps = MINUS * steps;
		
		for(i = 0 ; i < steps ; i++ )
		{
			/* move needed steps */
			head_2 = head_2 -> next_node;
		}
	}else
	{	/* if positive value */
	
		for(i = 0 ; i < steps ; i++ )
		{
			/* move needed steps */
			head_1 = head_1 -> next_node;
			
		}
	}
	
	/* move with both heads step by step untill instersection  */
	while(NULL != head_1->next_node && NULL != head_1->next_node)
	{
		/* if we have same node/same intersection */
		if(head_1 == head_2)
		{
			return head_1;
		}
		
		/* move to next node */
		head_1 = head_1 -> next_node;
		head_2 = head_2 -> next_node;
	}
	
	return NULL;
}
/******************************************************************************/
static int CountNodes(node_t *head)
{
	/* set counter */
	int count = 0; 
	
	/* set runner */
	node_t* runner = head;
	
	/* assert */
	assert(head);
	
	/* loop untill the end */
	while(NULL != runner)
	{
		/* increment counter */
		++count;
		
		/* move to next node */
		runner = runner->next_node;
		
	}
	runner = NULL;
	
	/* returns number of nodes */
	return count;
}
/******************************************************************************/
static void FindIntersectTest()
{
	/* set datas */
	int a = 10;
	int b = 20; 
	int c = 30;
	int d = 40;
	
	int e = 50; 
	
	/* define nodes for first linked list */
	node_t* head = NULL;
	node_t* second = NULL;
	node_t* third = NULL;
	node_t* fourth = NULL;
	
	/* define nodes for second linked list */
	node_t* sec_head = NULL;
	node_t* sec_second = NULL;
	node_t* sec_third = NULL;
	
	/* dynamically allocate nodes fpr first linked list */
	head = (node_t*)malloc(sizeof(node_t));
	second = (node_t*)malloc(sizeof(node_t));
	third = (node_t*)malloc(sizeof(node_t));
	fourth = (node_t*)malloc(sizeof(node_t));
	
	/* dynamically allocate nodes fpr first second list */
	sec_head = (node_t*)malloc(sizeof(node_t));
	
	/* set nodes for first linked list */
	head->data = &a;
	head->next_node = second;
	
	second->data = &b;
	second->next_node = third;
	
	third->data = &c;
	third->next_node = fourth;
	
	fourth->data = &d;
	fourth->next_node = NULL;
	
	/* set nodes for second linked list */
	sec_head->data = &e;
	sec_third = fourth;
	sec_second = third;
	sec_head->next_node = sec_second;
	
	/* check if the function works */
	if(third != FindIntersection(head , sec_head))
	{
		printf("FindIntersection Test Failed");
	}
	
	/* free dynamic allocation */
	free(head);
	free(second);
	free(third);
	free(fourth);
	free(sec_head);
	
}
/******************************************************************************/
/*static void NodeDestroy(node_t* head)
{
	node_t * temp = NULL;
	
	while(NULL != head->next_node)
	{
		temp = head;
		head = head->next_node;
		
		free(temp);
	}
}*/


