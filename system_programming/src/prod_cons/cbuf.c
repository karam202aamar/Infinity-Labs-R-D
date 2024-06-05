#include <stdio.h> /* perror */
#include <string.h> /* strerror */
#include <errno.h> /* ernno */
#include <stdlib.h> /* malloc, free*/
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof */

#include "cbuf.h"

struct cbuf /* cbuf_ty */
{
	size_t capacity;
	char *read;
	char *write;
	char arr[1];
};



/*****************************************************************************/
cbuf_ty *CbufCreate(const size_t capacity)
{
	/* allocat memory for the new buffer */
	cbuf_ty *new_buf = (cbuf_ty *)malloc(sizeof(cbuf_ty) + capacity + 1);
	
	if(NULL == new_buf)
	{
		perror(strerror(errno));
		
		return NULL;
	}
	
	/* set the read and write ptr to the start of the array */
	new_buf->read = new_buf->arr;
	new_buf->write = new_buf->arr;
	
	/* set the capacity size */
	new_buf->capacity = capacity ;

	/* return pointer to the new buffer */
	return new_buf;
}
/*****************************************************************************/

void CbufDestroy(cbuf_ty *buffer)
{
	assert(buffer);
	
	free(buffer);
	buffer = NULL;
}
/*****************************************************************************/

size_t CbufFreeSpace(const cbuf_ty *buffer)
{
	size_t free_bytes = 0;
	
	
	/* set indexes for write and read */
	long write_index = ((char *)buffer->write - (char *)buffer->arr);
	long read_index = ((char *)buffer->read - (char *)buffer->arr);
	
	/* calcolate the delta between the indexes */
	long indexes_delta = (write_index - read_index);
	
	assert(buffer);
	
	/* if the delta is negetive we need to incramemnt the  */
	free_bytes = (indexes_delta >= 0 ? 
	(buffer->capacity - indexes_delta) : (long unsigned int)
							 (-1 * indexes_delta -1));

	return free_bytes;
}
/*****************************************************************************/

size_t CbufSiz(const cbuf_ty *buffer)
{
	return buffer->capacity;
}
/*****************************************************************************/

int CbufIsEmpty( cbuf_ty *buffer)
{
	assert(buffer);
	
	if(buffer->capacity == CbufFreeSpace(buffer))
	{
		return 1;
	}
	
	return 0;
}
/******************************************************************************/

ssize_t CbufRead(cbuf_ty *buffer, void *dest, size_t num_of_bytes)
{
	size_t bytes_read = 0;
	
	/* set indexes for write and read */
	long write_index = ((char *)buffer->write - (char *)buffer->arr);
	long read_index = ((char *)buffer->read - (char *)buffer->arr);
	size_t runner_dest = 0 ;

	assert(buffer);
	assert(dest);
	assert(buffer->capacity >= num_of_bytes);
	
	/* check if thers bytes to read */
	if(write_index == read_index)
	{
		return -1;
	}
	
	/* while bytes_read is smaller from num of bytes*/
	while(bytes_read < num_of_bytes)
	{
		/* copy one byte from buffer to dest */
		memcpy((char *)dest + runner_dest ,buffer->read, 1);
		
		/* move the read ptr one step forward */
		buffer->read = (buffer->arr + (++read_index % (buffer->capacity + 1)));
		
		/* update the read index*/
		read_index = ((char *)buffer->read - (char *)buffer->arr);
		
		/* increas bytes_read and runner dest by one */
		++bytes_read;
		++runner_dest;
		
		/* check if thers bytes to read */
		if(write_index == read_index)
		{
			return -1;
		}
	}
	
	/* retern number of writen bytes */
	return bytes_read;
}
/******************************************************************************/

ssize_t CbufWrite(cbuf_ty *buffer, const void *src, size_t num_of_bytes)
{
	size_t bytes_writen = 0;
	
	/* set indexes for write and read */
	size_t write_index = ((char *)buffer->write - (char *)buffer->arr);
	size_t read_index = ((char *)buffer->read - (char *)buffer->arr);
	size_t runner_src = 0 ;

	assert(buffer);
	assert(src);
	assert(buffer->capacity >= num_of_bytes);

	while(bytes_writen < num_of_bytes)
	{
		/* check if thers free bytes left to write on */
		if(write_index == (read_index - 1) || write_index == 
						 (read_index + buffer->capacity))
		{
			return -1;
		}
	
		/* copy one byte from src to buffer */
		memcpy(buffer->write, (char *)src + runner_src, 1);
		
		/* move the write ptr one step forward */
		buffer->write = (buffer->arr + (++write_index % (buffer->capacity + 1)));
		
		/* update the write index*/
		write_index = ((char *)buffer->write - (char *)buffer->arr);
		
		/* increas bytes_writen and runner dest by one */
		++bytes_writen;
		++runner_src;
	}
	
	/* retern number of writen bytes */
	return bytes_writen;
}

