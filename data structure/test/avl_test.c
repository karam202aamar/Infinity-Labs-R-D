/*******************************************************************************
 * Project: Data Structures - AVL Tree TEST
 * Date: 12/10/22
 * Name: karam Aamar
 * Reviewer: Ortal 
 * Version: 1.0
*******************************************************************************/
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* puts */
/******************************************************************************/
#include "avl.h"
/******************************************************************************/
static void CreateDestroyTest(void);
static void IsEmptyTest(void);
static void InsertSizeIsEmptyTest(void);
static void RemoveTest(void);
static void FindTest(void);
static void ForEachTest(void);
static void HeightTest(void);
/******************************************************************************/
int CompareFunc(const void *data, const void *new_data, void *param);
int AddParam(void *data, void *param);
/******************************************************************************/
int main()
{
	CreateDestroyTest();
	InsertSizeIsEmptyTest();
	FindTest();
	ForEachTest();
	HeightTest();

	return 0;
}
/******************************************************************************/
static void CreateDestroyTest(void)
{
	avl_ty *avl = AVLCreate(NULL, NULL);

	if(!avl)
	{
		puts("CreateDestroyTest : failed");
	}
	AVLDestroy(avl);
}
/******************************************************************************/
static void InsertSizeIsEmptyTest(void)
{
	avl_ty *avl = AVLCreate(CompareFunc, NULL);

	int a = 1;
	int b = 2; 
	int c = 3;
	int d = 4;

	if(!AVLIsEmpty(avl))
	{
		puts("ISEMPTY FAILED");
	}
	if(AVLInsert(avl, &a))
	{
		puts("InsertSizeTest : failed add");
	}
	if(AVLInsert(avl, &b))
	{
		puts("InsertSizeTest : failed add");
	}
	if(AVLInsert(avl, &c))
	{
		puts("InsertSizeTest : failed add");
	}
	if(AVLInsert(avl, &d))
	{
		puts("InsertSizeTest : failed add");
	}
	
	if(4 != AVLSize(avl))
	{
		puts("InsertSizeTest : failed size");
	}
 	
	AVLDestroy(avl);
}
/******************************************************************************/
static void FindTest(void)
{
	avl_ty *avl = AVLCreate(CompareFunc, NULL);

	int a = 1;
	int b = 2; 
	int c = 3;

	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);

	if(AVLFind(avl, &a) != &a)
	{
		printf("failed to find");
	}

}
/******************************************************************************/
static void ForEachTest(void)
{
	int a = 1;
	int b = 2; 
	int c = 3;
	int d = 4;
	
	avl_ty *avl = AVLCreate(CompareFunc, &b);
	AVLInsert(avl, &b);
	AVLInsert(avl, &a);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);

	if(AVLForEach(avl, AddParam, NULL))
	{
		puts("ForEachTest : failed");
	}

	if(3 != a)
	{
		puts("ForEachTest : failed");
	}
	if(4 != b)
	{
		puts("ForEachTest : failed");
	}
	if(5 != c)
	{
		puts("ForEachTest : failed");
	}
	if(6 != d)
	{
		puts("ForEachTest : failed");
	}

}
/******************************************************************************/
static void HeightTest(void)
{
	avl_ty *avl = AVLCreate(CompareFunc, NULL);

	int a = 1;
	int b = 2; 
	int c = 3;
	int d = 4;

	AVLInsert(avl, &a);
	AVLInsert(avl, &b);
	AVLInsert(avl, &c);
	AVLInsert(avl, &d);

	if(AVLHeight(avl) != 2)
	{
		puts("HeightTest : failed");
	}
}
/******************************************************************************/
int CompareFunc(const void *data, const void *new_data, void *param)
{
	if((int*)data > (int*)new_data)
	{
		return 1;
	}
	if((int*)data < (int*)new_data)
	{
		return -1;
	}
	return 0;
}
/******************************************************************************/
int AddParam(void *data, void *param)
{
	*(int*)data += *(int*)param;

	return 0;
}
/******************************************************************************/









