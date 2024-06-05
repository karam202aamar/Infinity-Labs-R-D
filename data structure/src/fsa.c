/*******************************************************************************
 * Project: System Programming - Fixed Size Allocator
 * Date: 31/08/22
 * Name: karam aamar
 * Reviewer: Karin
 * Version: 1.0
*******************************************************************************/
/******************************************************************************/
#include <stddef.h>  
#include <assert.h> 
/******************************************************************************/
#include "fsa.h"

#define WORD_SIZE 8
/******************************************************************************/
typedef struct blk_head blk_head_ty;

struct blk_head 
{
	blk_head_ty *next_free;   /* 8 bytes */
};

struct fsa
{
	fsa_ty *first_free;      /* 8 bytes */
	
};/* fsa_ty */

/******************************************************************************/
size_t FSASuggestSize(size_t num_of_blks, size_t blk_size)
{
	size_t blk_fixed_size = blk_size; 
	
	size_t pool_fixed_size = 0;
	
	assert(num_of_blks);
	assert(blk_size);
	
	
	/* check the alignment case we have 8 bytes WORDSIZE */
	if(blk_size % WORD_SIZE)
	{
	       blk_fixed_size = blk_size + (WORD_SIZE - (blk_size % WORD_SIZE));
	}
	
	pool_fixed_size = sizeof(fsa_ty) + (sizeof(blk_head_ty) + 
						blk_fixed_size) * num_of_blks;
	return pool_fixed_size;
}
/******************************************************************************/
fsa_ty *FSAInit(void *mem_pool, size_t pool_size, size_t blk_size)
{
	char *runner = NULL;
	fsa_ty* fsa = NULL;
	blk_head_ty* blk_head = NULL;
	
	/* fixed size to align the block */
	if(blk_size % WORD_SIZE)
	{
	       blk_size = blk_size + (WORD_SIZE - (blk_size % WORD_SIZE));
	}
	
	/* assert */	
	assert(mem_pool);
	
	/* check we can insert one block at least */
	if(blk_size > (pool_size - (sizeof(fsa_ty) + sizeof(blk_head_ty))))
	{
		return NULL;
	}
	
	/* set runner (byte by byte) */	
	runner = (char*)mem_pool;
	
	/* set fsa to the beginning of the pool - and cast to fsa_ty ptr */	
	fsa = (fsa_ty*)runner;
	
	/* update runner to the beginning if block head */	
	runner += sizeof(fsa_ty);
	
	/* 
		set first block head 
		set next free to point to NULL
	*/
	blk_head = (blk_head_ty*)runner;
	blk_head -> next_free = NULL;
	
	/* set the ptr of fsa first free to first block head */	
	fsa -> first_free = (fsa_ty*)blk_head;
	
	/* update the pool size */	
	pool_size = pool_size - (blk_size + sizeof(blk_head_ty) + sizeof(fsa_ty));
	
	/* loop and allocate block untill the no more space */	
	while(pool_size > (blk_size + sizeof(blk_head_ty)))
	{
		/* update runner to next block head */
		runner += sizeof(blk_head_ty) + blk_size;
		/* set block head next to the beginng of the new head node */
		blk_head -> next_free = (blk_head_ty*)runner;
		/* update block head to the next head node */
		blk_head = blk_head -> next_free;
		/* set the head node next to NULL */
		blk_head -> next_free = NULL;
		
		/* update size of the pool */
		pool_size -=  blk_size + sizeof(blk_head_ty);
	}
	return fsa;
}
/******************************************************************************/
void *FSAAlloc(fsa_ty *fsa)
{ 
	/* set return pointer */
	void *return_ptr = NULL; 
	
	/* assert */
	assert(fsa);
	
	/* if there is no free space then the head will be NULL */
	if(NULL != fsa->first_free)
	{
		/* save the return addresse*/
		return_ptr = fsa->first_free;
		/* update first free to next block */
		fsa->first_free = (fsa_ty*)((blk_head_ty*)(fsa->first_free))->next_free;
		
		/* return the address of the allocated area */
		return ((char*)return_ptr + sizeof(blk_head_ty));
	}
	
	return NULL;
}
/******************************************************************************/
size_t FSACountFree(const fsa_ty *fsa)
{
	/* set counter */
	size_t count = 0;
	
	/* iter for the blocks */
	blk_head_ty *iter = NULL;
	
	/* assert */
	assert(fsa);
	
	iter =(blk_head_ty*)fsa;
	
	while(iter)
	{
		++count;
		iter = iter -> next_free;
	}
	return count;
}
/******************************************************************************/
void FSAFree(fsa_ty *user_fsa, void *blk_to_free)
{
	assert(blk_to_free);
	
	/* go to the head pointer*/
	blk_to_free = (char*)blk_to_free - sizeof(blk_head_ty);
	/* inside next free set the value inside fsa->first_free */
	((blk_head_ty*)blk_to_free)->next_free = (blk_head_ty*)user_fsa->first_free;
	
	/* update the first free of user_fsa */ 
	user_fsa->first_free = blk_to_free;
}
/******************************************************************************/






















