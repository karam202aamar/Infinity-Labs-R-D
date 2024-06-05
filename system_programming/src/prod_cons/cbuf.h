#ifndef __CBUF_H_ILRD__
#define __CBUF_H_ILRD__

#include <stddef.h> /* size_t */
#include <aio.h> /* ssize_t */

typedef struct cbuf cbuf_ty;

/*******************************************************************************
** Description: Creates a new buffer
** Return value: pointer to the new buffer created 
** Complexity: O(1)
*******************************************************************************/
cbuf_ty *CbufCreate(const size_t capacity);

/*******************************************************************************
** Description: Destroys the buffer
** Undefined behavior: if buffer is NULL
** Complexity: O(1)
*******************************************************************************/
void CbufDestroy(cbuf_ty *buffer);

/*******************************************************************************
** Description: Calculates how many free bytes there are in buffer
** Return value: number of free bytes in buffer
** Undefined behavior: if buffer is NULL
** Complexity: O(1)
*******************************************************************************/
size_t CbufFreeSpace(const cbuf_ty *buffer);

/*******************************************************************************
** Description: Returns capacity of buffer
** Return value: The capacity of buffer
** Undefined behavior: if buffer is NULL
** Complexity: O(1) 
*******************************************************************************/
size_t CbufSiz(const cbuf_ty *buffer);

/*******************************************************************************
** Description: Reads up to num_of_bytes bytes from buffer to dest
** Return value: The number of bytes read if succeeded,
** 				 or -1 when buffer is empty
** Undefined behavior: if buffer is NULL
** 					   if dest is NULL
** 					   if dest is not large enough
** 					   if num_of_bytes is larger than buffer's size
** Complexity: O(n)
*******************************************************************************/
ssize_t CbufRead(cbuf_ty *buffer, void *dest, size_t num_of_bytes);

/*******************************************************************************
** Description: Writes up to num_of_bytes bytes from src to buffer
** Return value: The number of bytes written if succeeded,
** 				 or -1 when buffer is full, or num_of_bytes is larger than free 
**																 space in buffer
** Undefined behavior: if buffer is NULL
** 					   if src is NULL, or num_of_bytes is larger than capacity
** Complexity: O(n)
*******************************************************************************/
ssize_t CbufWrite(cbuf_ty *buffer, const void *src, size_t num_of_bytes);

/*******************************************************************************
** Description: Checks if buffer is empty
** Return value: 1 - empty
** 		 0 - otherwise
** Undefined behavior: if buffer is NULL
** Complexity: O(1)
*******************************************************************************/
int CbufIsEmpty(cbuf_ty *buffer);

#endif /* __CBUF_H_ILRD__ */
