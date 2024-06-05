/*******************************************************************************
 * Project: System Programming - Variable Size Allocator
 * Date: 06/09/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0			
*******************************************************************************/
#include <stdio.h>  /* printf puts*/
#include <stdlib.h> /* malloc free */
/******************************************************************************/
#include "vsa.h"
/******************************************************************************/
static void ImplementFunc();
static void VSAInitTest();
static void VSAAllocTest();
static void VSAFreeTest();
static void VSALargestChunkTest();
/******************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	VSAInitTest();
	VSAAllocTest();
	VSAFreeTest();
	VSALargestChunkTest();
}
/******************************************************************************/
static void VSAInitTest()
{
	size_t size_of_pool = 15;
	void * pool = NULL;
	vsa_ty * vsa = NULL;
	
	pool = malloc(size_of_pool);
	vsa = VSAInit(pool,size_of_pool);
	
	if(NULL != vsa)
	{
		puts("VSAInit FAILED");
	}
	
	free(pool);
	
	size_of_pool = 50;
	pool = malloc(size_of_pool);
	vsa = VSAInit(pool,size_of_pool);
	
	if(NULL == vsa)
	{
		puts("VSAInit FAILED");
	}
	free(pool);
}
/******************************************************************************/
static void VSAAllocTest()
{
	vsa_ty *vsa_test = VSAInit(malloc(106),106);
	
	if(NULL == vsa_test)
	{
		puts("VSAInit FAILED");
	}
	/*
	printf("%p start location \n",vsa_test);
	printf("%p first alloc \n",VSAAlloc(vsa_test,8));
	printf("%p second alloc \n",VSAAlloc(vsa_test,16));
	printf("%p third alloc \n",VSAAlloc(vsa_test,40));
	*/
	if(NULL == VSAAlloc(vsa_test,8))
	{
		puts("VSAAlloc FAILED");
	}
	if(NULL == VSAAlloc(vsa_test,16))
	{
		puts("VSAAlloc FAILED");
	}
	if(NULL == VSAAlloc(vsa_test,40))
	{
		puts("VSAAlloc FAILED");
	}
	
	if(NULL != VSAAlloc(vsa_test,8))
	{
		puts("VSAAlloc FAILED");
	}
	
	free(vsa_test);
}
/* printf("%ld\n",(vsa_runner->blk_size)); */	
/******************************************************************************/	
static void VSAFreeTest()
{
	void *blk1 = NULL;
	void *blk2 = NULL;
	vsa_ty *vsa_test = VSAInit(malloc(100),100);

	blk1 = VSAAlloc(vsa_test,8);
	blk2 = blk1;
	
	VSAFree(blk1);
	
	blk1 = VSAAlloc(vsa_test,8);
	if(blk1 != blk2)
	{
		puts("FAILED TO FREE \n");
	}

	free(vsa_test);
}
/******************************************************************************/
static void VSALargestChunkTest()
{
	vsa_ty *vsa_test = VSAInit(malloc(106),106);
	void* blk = NULL;
	
	/*printf("%d\n",VSALargestChunkAvailable(vsa_test));*/
	
	if(90 != VSALargestChunkAvailable(vsa_test))
	{
		puts("failed");
	}
	
	blk = VSAAlloc(vsa_test,8);
	
	if(74 != VSALargestChunkAvailable(vsa_test))
	{
		puts("failed");
	}

	VSAFree(blk);
	
	if(82 != VSALargestChunkAvailable(vsa_test))
	{
		puts("failed");
	}
	
	free(vsa_test);
}
/******************************************************************************/






