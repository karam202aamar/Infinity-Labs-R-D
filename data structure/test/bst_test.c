/*******************************************************************************
 * Project: BINARY SEARCH TREE
 * Date: 22/09/22
 * Name: karam
 * Reviewer: evgani
 * Version: 1.0
*******************************************************************************/
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* puts */
/******************************************************************************/
#include "bst.h"
/******************************************************************************/
static void ImplementFunc();

static void BSTCreateDestroy();
static void BSTInsertTest();
static void BstRemoveTest();
static void BSTFindIsSameTest();
static void BSTForEachTest();
static void BSTIsEmptySizeTest();

/*  Compares between bst_data and new_data */
static int CompareFunction(const void *bst_data , const void *new_data , void 
									*param);
/* adds the value of the param to bst_data */
static int BSTActionTest(void *bst_data, void *param);
/******************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	BSTCreateDestroy();
	BSTInsertTest();
	BstRemoveTest();
	BSTFindIsSameTest();
	BSTForEachTest();
	BSTIsEmptySizeTest();
}
/******************************************************************************/
static void BSTCreateDestroy()
{
	int param = 1;
	int a = 1;
	
	bst_ty *bst = BSTCreate(CompareFunction, &param);
	BSTInsert(bst, &a);
	
	if(NULL == bst)
	{
		puts(" FAILED TO CREATE ");
	}
	
	BSTDestroy(bst);
}
/******************************************************************************/
static void BSTInsertTest()
{
	int param = 1;
	
	bst_ty *bst = BSTCreate(CompareFunction, &param);
	
	bst_iter_ty iter = NULL;
	
	int a = 1;
	int b = 2;
	int c = 0;
	int d = 3;
	
	if(!bst)
	{
		puts("CREATION OF THE BST FAILED");
	}
	
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);
	BSTInsert(bst, &d);
	
	iter = BSTBegin(bst);
	/*printf("%d\n",*(int*)BSTGetData(iter));*/
	if(0 != *(int *)BSTGetData(iter))
	{
		puts("INSERTION FAILED");
	}
	
	iter = BSTNext(iter);
	
	if(1 != *(int *)BSTGetData(iter))
	{
		puts("INSERTION FAILED");
	}
	
	iter = BSTNext(iter);
	
	if(2 != *(int *)BSTGetData(iter))
	{
		puts("INSERTION FAILED");
	}
	
	iter = BSTNext(iter);

	if(3 != *(int *)BSTGetData(iter))
	{
		puts("INSERTION FAILED");
	}

	BSTDestroy(bst);
}

/******************************************************************************/
static void BstRemoveTest()
{
	bst_ty *new_bst = NULL;
	
	int param = 1;
	int data = 1;
	
	bst_iter_ty new_iter= NULL;
	
	new_bst = BSTCreate(CompareFunction, &param);
	
	new_iter = BSTInsert(new_bst, &data);
	
	BSTRemove(new_iter);
	
	if(!BSTIsEmpty(new_bst))
	{
		puts("TestBSTRemove failed ");	
	}
	
	BSTDestroy(new_bst);
	new_bst = NULL;	
}
/******************************************************************************/
static void BSTFindIsSameTest()
{
	int param = 1;
	bst_iter_ty check_iter = NULL;
	
	bst_ty *bst = BSTCreate(CompareFunction, &param);

	int a = 1;
	int b = 2;
	int c = 3;
	
	int d = 3;
	
	if(!bst)
	{
		puts("CREATION OF THE BST FAILED");
	}
	
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	
	check_iter = BSTInsert(bst, &c);
	
	if(check_iter!= BSTFind(bst,&d))
	{
		puts("BSTFind failed");
	}
	if(1 != BSTIsSameIter(BSTFind(bst,&d),check_iter))
	{
		puts("BSTIsSameIter failed");
	}
	
	BSTDestroy(bst);
	bst = NULL;	
}
/******************************************************************************/
static void BSTForEachTest()
{
	int param = 1;
	
	bst_ty *bst = BSTCreate(CompareFunction, &param);
	
	bst_iter_ty from_iter = NULL;
	bst_iter_ty to_iter = NULL;
	
	int a = 1;
	int b = 2;
	int c = 0;
	int d = 3;
	
	if(!bst)
	{
		puts("CREATION OF THE BST FAILED");
	}
	
	from_iter = BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);
	to_iter = BSTInsert(bst, &d);
	
	BSTForEach(from_iter , to_iter , BSTActionTest , &param);
	
	if(2 != *(int *)BSTGetData(from_iter))
	{
		puts("BST FOR EACH FAILED");
	}
	BSTDestroy(bst);
	bst = NULL;
}
/******************************************************************************/
static void BSTIsEmptySizeTest()
{
	int param = 1;
	
	bst_ty *bst = BSTCreate(CompareFunction, &param);
	
	int a = 1;
	int b = 2;
	int c = 0;
	int d = 3;
	
	if(!bst)
	{
		puts("CREATION OF THE BST FAILED");
	}
	
	if(1 != BSTIsEmpty(bst))
	{
		puts("ISEMPTY FAILED");
	}
	
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);
	BSTInsert(bst, &d);

	if(4 != BSTSize(bst))
	{
		puts("BSTSize FAILED");
	}
	
	BSTDestroy(bst);
	bst = NULL;
}
/*******************************compare function*******************************/
static int CompareFunction(const void *bst_data , const void *new_data , 
							            void *param)			
{
	if(*(int *)bst_data > *(int *)new_data * (*(int *)param))
	{
		return 1;	
	}
	
	else if(*(int *)bst_data < *(int *)new_data * (*(int *)param))
	{
		return -1;
	}
	
	else
	{
		return 0;
	}
}
/******************************action_ty function******************************/
static int BSTActionTest(void *bst_data, void *param)
{

	*(int *)bst_data += *(int *)param;
	
	if(NULL == bst_data || NULL == param)
	{
		return 1;
	}
	
	return 0;

}
