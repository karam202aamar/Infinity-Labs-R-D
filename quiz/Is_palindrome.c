/******************************************************************************/
int IsPalindrome(slist_ty *list);
/******************************************************************************/
int main()
{
	return 0;
}
/******************************************************************************/
int IsPalindrome(slist_ty *list)
{
	int i;
	node_ty *curr_node = NULL;
	node_ty *pali_node = NULL;
	size_t end = SListCount(list);
	size_t start = 0;
	
	while(start < end)
	{
		curr_node = list -> head_node;
		pali_node = list -> head_node;
		
		for(i = 0; i < (end - 1); ++i)
		{
			pali_node = pali_node->next_node;
		}
		for(i = 0; i < start; ++i)
		{
			curr_node = curr_node->next_node;
		}
		if(curr_node->data != pali_node->data)
		{
			return 0;
		}
		
		start++;
		end--;
	}
	return 1;
}
/******************************************************************************/
