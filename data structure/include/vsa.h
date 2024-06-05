/*******************************************************************************
 * Project: System Programming - Variable Size Allocator
 * Date: 05/09/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0			
*******************************************************************************/
#ifndef __VSA_H_ILRD__
#define __VSA_H_ILRD__

#include <stddef.h>

typedef struct vsa vsa_ty;

/*******************************************************************************
** Description: Creates an VSA - Memory Pool (blk_size in bytes)
** Return value: Pointer to the new VSA or NULL in case pool size is not enough 
				 for at least metadata. 
** Undefined Behavior: If allocated_memory is NULL
** Notes: mem_pool should be alinged. 
** Complexity: O(1)
*******************************************************************************/
vsa_ty *VSAInit(void *mem_pool, size_t pool_size);

/*******************************************************************************
** Description: Allocs memory block from the pool with giving blk size in bytes
** Return value: Pointer to the allocated block or NULL if can't find enough 
				 size or blk_size is zero.				
** Undefined Behavior: If VSA is NULL
** Complexity: O(n)
*******************************************************************************/
void *VSAAlloc(vsa_ty *vsa, size_t blk_size);

/*******************************************************************************
** Description: Free allocated memory block and return it to the pool
** Undefined Behavior: If blk_to_free is NULL or doesn't belong to an VSA
** Complexity: O(1)
*******************************************************************************/
void VSAFree(void *blk_to_free);

/*******************************************************************************
** Description: return the size of the largest blk available in bytes
** Undefined Behavior: If VSA is NULL
** Complexity: O(n)
*******************************************************************************/
size_t VSALargestChunkAvailable(const vsa_ty *vsa);

#endif /* __VSA_H_ILRD__ */
