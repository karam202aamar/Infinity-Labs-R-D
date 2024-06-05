/*******************************************************************************
 * Project: System Programming - Fixed Size Allocator
 * Date: 31/08/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0
 			1.1 Updates:
 					- Modified Function descriptions and 
 					  undefined behavior 
 					- Changed complexity of count to O(n)
 					- Added Notes to FSAInit.
*******************************************************************************/
#ifndef __FSA_H_ILRD__
#define __FSA_H_ILRD__

#include <stddef.h>

typedef struct fsa fsa_ty;

/*******************************************************************************
** Description: Calculates the size needed for the memory pool (blk_size in 
				bytes)
** Return value: Suggested size in bytes to allocate
** Undefined Behavior: If num_of_elem or elem_size is 0;
** Complexity: O(1)
*******************************************************************************/
size_t FSASuggestSize(size_t num_of_blks, size_t blk_size);

/*******************************************************************************
** Description: Creates an FSA - Memory Pool (blk_size in bytes)
** Return value: Pointer to the new FSA or NULL in case failed to alloc at least 
   				 one block
** Undefined Behavior: If allocated_memory is NULL
** Notes:
		- mem_pool should be alinged. 
** Complexity: O(n)
*******************************************************************************/
fsa_ty *FSAInit(void *mem_pool, size_t pool_size, size_t blk_size);

/*******************************************************************************
** Description: Allocs memory block from the pool
** Return value: Pointer to the allocated block or NULL if full
** Undefined Behavior: If fsa is NULL
** Complexity: O(1)
*******************************************************************************/
void *FSAAlloc(fsa_ty *fsa);

/*******************************************************************************
** Description: Free allocated memory block and return it to the pool
** Undefined Behavior: If blk_to_free is NULL or doesn't belong to an FSA
** Complexity: O(1)
*******************************************************************************/
void FSAFree(fsa_ty *user_fsa, void *blk_to_free);

/*******************************************************************************
** Description: return number of free blocks
** Return value: 
** Undefined Behavior: If fsa is NULL
** Complexity: O(n)
*******************************************************************************/
size_t FSACountFree(const fsa_ty *fsa);

#endif /* __FSA_H_ILRD__ */
