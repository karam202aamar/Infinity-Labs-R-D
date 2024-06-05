/*******************************************************************************
 * Project: System Programming - Fixed Size Allocator
 * Date: 31/08/22
 * Name: karam aamar
 * Reviewer: Karin
 * Version: 1.0
*******************************************************************************/
/******************************************************************************/
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* allocation */
/******************************************************************************/
#include "fsa.h"
/******************************************************************************/
static void ImplemetFunc();
static void FSASuggestSizeTest();
static void FSAInitTest();
static void FSACountFreeTest();
static void FSAAllocTest();
static void FSAFreeTest();
/******************************************************************************/
int main()
{
	ImplemetFunc();
	
	return 0;
}
/******************************************************************************/
static void ImplemetFunc()
{
	FSASuggestSizeTest();
	FSAInitTest();
	FSACountFreeTest();
	FSAAllocTest();
	FSAFreeTest();
}
/******************************************************************************/
static void FSASuggestSizeTest()
{
	size_t num_of_blks = 2;
	size_t blk_size = 10;
	size_t pool_size = 0;
	
	pool_size = FSASuggestSize(num_of_blks,blk_size);
	
	if(56 != pool_size)
	{
		puts("FSASuggestSize FAILED");
	}
}
/******************************************************************************/
static void FSAInitTest()
{
	size_t num_of_blks = 2;
	size_t blk_size = 10;
	size_t pool_size = 0;
	void *pool = NULL;
	fsa_ty *fsa_check =NULL;
	
	pool_size = FSASuggestSize(num_of_blks,blk_size);
	pool =malloc(pool_size);
	fsa_check = FSAInit(pool , pool_size , blk_size);
	
	if(NULL == fsa_check)
	{
		puts("FAILED INIT");
	}
	
	fsa_check = FSAInit(pool , pool_size , 50);
	
	if(NULL != fsa_check)
	{
		puts("FAILED INIT");
	}
	free(pool);
}
/******************************************************************************/
static void FSACountFreeTest()
{
	size_t num_of_blks = 3;
	size_t blk_size = 10;
	size_t pool_size = 0;
	
	void *pool = NULL;
	const fsa_ty *fsa_check =NULL;
	
	pool_size = FSASuggestSize(num_of_blks,blk_size);
	
	pool =malloc(pool_size);
	
	fsa_check = FSAInit(pool , pool_size , blk_size);
	
	if(NULL == fsa_check)
	{
		puts("FAILED INIT");
	}
	
	if(3 != FSACountFree(fsa_check))
	{
		puts("COUNT INIT");
	}
	free(pool);
}
/******************************************************************************/
static void FSAAllocTest()
{
	size_t num_of_blks = 3;
	size_t blk_size = 10;
	size_t pool_size = 0;
	
	void *pool = NULL;
	fsa_ty *fsa_check =NULL;
	
	pool_size = FSASuggestSize(num_of_blks,blk_size);
	
	pool =malloc(pool_size);
	
	fsa_check = FSAInit(pool , pool_size , blk_size);
	
	if(NULL == fsa_check)
	{
		puts("FAILED INIT");
	}
	
	FSAAlloc(fsa_check);
	
	if(2 != FSACountFree(fsa_check))
	{
		puts("ALLOC FAILED");
	}
	free(pool);
}
/******************************************************************************/
static void FSAFreeTest()
{
	size_t num_of_blks = 3;
	size_t blk_size = 10;
	size_t pool_size = 0;
	
	void *allocated_ptr = NULL;
	void *pool = NULL;
	fsa_ty *fsa_check =NULL;
	
	pool_size = FSASuggestSize(num_of_blks,blk_size);
	
	pool =malloc(pool_size);
	
	fsa_check = FSAInit(pool , pool_size , blk_size);
	
	if(NULL == fsa_check)
	{
		puts("FAILED INIT");
	}
	
	allocated_ptr = FSAAlloc(fsa_check);
	
	FSAFree(fsa_check,allocated_ptr);

	if(3 != FSACountFree(fsa_check))
	{
		puts("ALLOC FAILED");
	}
	free(pool);
}
