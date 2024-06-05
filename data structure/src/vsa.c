/*******************************************************************************
 * Project: System Programming - Variable Size Allocator
 * Date: 06/09/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0			
*******************************************************************************/
#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdio.h>  /* printf puts*/
/******************************************************************************/
#include "vsa.h"
/******************************************************************************/
#define WORD_SIZE sizeof(size_t)
#define VSA_SIZE AlignedFunc(sizeof(vsa_ty))
/******************************************************************************/
static size_t AlignedFunc(size_t num_to_fix); /* aligne the sent number */
static size_t ABS(size_t num); /* send the number with opposite sign */
static vsa_ty* VsaNext(vsa_ty* vsa); /* returns next vsa */
static void DeFrag(vsa_ty* vsa); /* defragmentation of free momory location */
/******************************************************************************/
struct vsa
{
	signed long blk_size;
	
};/* vsa_ty */
/******************************************************************************/
vsa_ty *VSAInit(void *mem_pool, size_t pool_size)
{	
	/* define vsa's to the beginning & end of the pool */
	vsa_ty *vsa_head = NULL;
	vsa_ty *vsa_end = NULL;
	/* assert check mem_pool not NULL*/
	assert(mem_pool);
	
	pool_size = AlignedFunc(pool_size);
	
	if(pool_size < (2 * WORD_SIZE))
	{
		return NULL;
	}
	/* set the ptr vsa_end to the end of the pool & set the the blk_size */
	vsa_end = (vsa_ty*)((char *)mem_pool + (pool_size - sizeof(vsa_ty)));
	vsa_end -> blk_size = 0;

	/* set the vsa in the start of the pool */
	vsa_head = (vsa_ty*)mem_pool;
	vsa_head -> blk_size = ABS(pool_size - 2 * sizeof(vsa_ty));
	
	return vsa_head;
}
/******************************************************************************/
void *VSAAlloc(vsa_ty *vsa, size_t blk_size)
{
	vsa_ty *vsa_runner = NULL;
	vsa_ty *vsa_tmp_runner = NULL;
	long current_value = 0; 
	
	vsa_runner = vsa;
	blk_size = AlignedFunc(blk_size);
	
	assert(vsa);
	assert(blk_size);
	
	/*loop untill the end of the pool*/
	while(vsa_runner->blk_size)
	{	
	
		/*check if there free mem but not enough then defrag*/
		if(0 > vsa_runner->blk_size && ABS(vsa_runner->blk_size)
								     < blk_size)
		{	
		
			/*set tmp runner on current vsa*/
			vsa_tmp_runner = vsa_runner;
			
			if(0 < VsaNext(vsa_tmp_runner) -> blk_size)
			{
				/* move to next */
				vsa_runner = VsaNext(vsa_runner);
			}else
			{
				/* defrag sequential free mem */
				while(0 > VsaNext(vsa_tmp_runner) -> blk_size)
				{
					DeFrag(vsa_tmp_runner);
					vsa_tmp_runner = VsaNext(vsa_tmp_runner);
				}
			}
		}/* else if i can allocate */
		else if(0 > vsa_runner->blk_size && ABS(vsa_runner->
							blk_size) >= (blk_size)) 
		{
			/* 
			   if the allocation(blk_siz) untill the end of VSA
			   if i have less than 16 bytes in the end then give it 
			   to the allocation call .
		        */
			if(ABS(vsa_runner->blk_size) - blk_size < 2 * WORD_SIZE)
			{
				vsa_runner->blk_size = ABS(vsa_runner->blk_size);
				return (char*)vsa_runner + VSA_SIZE;
			}
			current_value = vsa_runner->blk_size; /* -90 */
			vsa_tmp_runner = vsa_runner;
			
			/* update the value in the empty VSA */ 
			vsa_runner->blk_size =  blk_size;
			/* move to the new vsa location */ 
			vsa_runner = (vsa_ty*)((char*)vsa_runner + VSA_SIZE
								    + blk_size);
			/* update the value in the VSA */ 
			vsa_runner->blk_size = current_value + blk_size 	 
								     + VSA_SIZE;
			
			return (char*)vsa_tmp_runner + VSA_SIZE;
		}else 
		{
			/* move to next */
			vsa_runner = VsaNext(vsa_runner);
		}
	}
	return NULL;
}
/******************************************************************************/
void VSAFree(void *blk_to_free)
{
	assert(blk_to_free);
	/* get to the beginning of the VSA */
	blk_to_free = (vsa_ty*)((char*)blk_to_free - VSA_SIZE);
	/* turn the sign to + */
	((vsa_ty*)blk_to_free)->blk_size = ABS(((vsa_ty*)blk_to_free)->blk_size);
}
/******************************************************************************/
size_t VSALargestChunkAvailable(const vsa_ty *vsa)
{
	size_t curr_blk_siz = 0;
	size_t max_blk_siz = 0;
	
	vsa_ty *vsa_runner = NULL;

	assert(vsa);
	vsa_runner = (vsa_ty*)vsa;
	
	/*loop untill the end of the pool*/
	while(vsa_runner->blk_size)
	{
		/* if it's positive then compare chunks*/
		if(0 < vsa_runner->blk_size)
		{
			if(curr_blk_siz > max_blk_siz)
			{
				/* set max block */
				max_blk_siz = curr_blk_siz;
			}
			/* set current to zero because new chunk */
			curr_blk_siz = 0;	
		}else
		{	/* it's neg value then add it */
			curr_blk_siz += (size_t)ABS(vsa_runner->blk_size);
		}
		/* move to next */
		vsa_runner = VsaNext(vsa_runner);
	}
	if(0 == max_blk_siz)
	{
		return curr_blk_siz;
	}
	return max_blk_siz;
}
/******************************************************************************/
static size_t AlignedFunc(size_t num_to_fix)
{
	/* check if it's a fixed number */
	if(!(num_to_fix % WORD_SIZE))
	{
		return num_to_fix;
	}
	/* fix the number by giving more bytes */
	num_to_fix += WORD_SIZE - (num_to_fix % WORD_SIZE);
	/* return the fixed number */
	return num_to_fix;
}
/******************************************************************************/
static size_t ABS(size_t num)
{
	if(num > 0)
	{
		return -1 * num;
	}
	return -1 * num;
}
/******************************************************************************/
static vsa_ty* VsaNext(vsa_ty* vsa)
{
	vsa_ty* vsa_next = NULL;
	
	if(vsa->blk_size < 0)
	{
		/* get to the beginning of next VSA*/
		vsa_next = (vsa_ty*)((char*)vsa + VSA_SIZE + ABS(vsa->blk_size));
	}else
	{
		vsa_next = (vsa_ty*)((char*)vsa + VSA_SIZE + vsa->blk_size);
	}
	return vsa_next;
}
/******************************************************************************/
static void DeFrag(vsa_ty* vsa)
{
	vsa->blk_size += VsaNext(vsa)->blk_size + VSA_SIZE;
}
/******************************************************************************/

























