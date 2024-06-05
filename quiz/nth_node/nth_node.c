#include <stdio.h>
#include <assert.h>
/*****************************************************************************/
#include "linked_list.h"
/*****************************************************************************/
slist_iter_ty NthNode();
/*****************************************************************************/
int main()
{

	return 0; 
}
/*****************************************************************************/
slist_iter_ty NthNode(const slist_ty *list , size_t n)
{
	/*Point to the head of the list.*/
	slist_iter_ty node = SListBegin(list);
	
	/*create new iter point to node */
	slist_iter_ty tmp_node = node;
	
	/*assert for null list */
	assert(list);
	
	/*Iterate until dummy node has been reached.*/
	while(SListNext(SListNext(node)))
	{	
		/*move to next node */
		node = SListNext(node);
		tmp_node = node;
	}
	
	while(n)
	{
		tmp_node = SListNext(tmp_node);
		
		--n;	
	}
	return tmp_node;
}
/*****************************************************************************/
