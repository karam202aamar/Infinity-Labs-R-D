/******************************************************************************/
#include <stdio.h>  /* print */
#include <stdlib.h> /*dynamic allocation */
/******************************************************************************/
typedef struct node node_t;
/******************************************************************************/
struct node
{
	void * data;
	node_t * next_node;
};
/******************************************************************************/
int IsThereLoop(node_t *head);
/******************************************************************************/
int main()
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
	if(0 == IsThereLoop(head))
	{
		printf("IsThereLoop Failed\n");
	}
	
	/* free dynamic allocation */
	free(head);
	free(second);
	free(third);
	free(fourth);	
	
	return 0;
}
/******************************************************************************/
int IsThereLoop(node_t *head)
{
	/* define slow & fast nodes */
	node_t* slow = head;
	node_t* fast = head;
	
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
			return 1;
		}
	}
	return 0; 
}
/******************************************************************************/
