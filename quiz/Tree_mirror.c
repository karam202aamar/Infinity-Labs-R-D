void TreeMirror(node_ty* node)
{
	node_ty* tmp = NULL;
	
	if(NULL == node)
	{
		return;
	}
	
	if(NULL != node->left)
	{
		TreeMirror(node->left);
	}
	
	if(NULL != node->right)
	{
		TreeMirror(node->right);
	}
	tmp = node->left;
	node->left = node->right;
	node->right = tmp;
}

int main()
{
	return 0;
}
