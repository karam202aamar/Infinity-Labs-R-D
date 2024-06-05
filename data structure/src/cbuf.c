#include<stddef.h>/*size_t*/
#include <stdlib.h>/*malloc, free*/
#include <string.h> /*strerro memcpy */
#include <errno.h> /*errno*/
#include <stdio.h> /*perror*/
#include <assert.h> /*assert*/

#include "cbuf.h"

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

struct cbuf 
{
	size_t cbuf_capacity;
	size_t cbuf_size;
	size_t cbuf_read_offset;
	char cbuf_arr[1];
};

/******************************************************************************/
cbuf_ty *CbufCreate(const size_t capacity)
{
	/*create new cbuf by allocation*/
	cbuf_ty *new_cbuf = (cbuf_ty*)malloc(capacity - 1 + sizeof(cbuf_ty));
	
	/*check if allocation failed*/
	if (NULL == new_cbuf)
	{
		/*print error per errno*/
		perror(strerror(errno));
		
		/*return NULL*/
		return NULL;
	}
	
	/*init new cbuf*/
	new_cbuf->cbuf_capacity = capacity;
	new_cbuf->cbuf_size = 0;
	new_cbuf->cbuf_read_offset = 0;
	
	/*return new cbuf*/
	return new_cbuf;
}

/*******************************************************************************/
void CbufDestroy(cbuf_ty *buffer)
{
	/*assert for buffer*/
	assert(buffer);
	
	/*free buffer*/
	free(buffer);
	/*set buffer to null*/
	buffer = NULL;
}

/******************************************************************************/
size_t CbufFreeSpace(const cbuf_ty *buffer)
{
	/*assert for buffer*/
	assert(buffer);
	
	/*return free bytes quantity*/
	return buffer->cbuf_capacity - buffer->cbuf_size;
}

/******************************************************************************/
size_t CbufSiz(const cbuf_ty *buffer)
{
	/*assert for buffer*/
	assert(buffer);
	
	/*return size*/
	return buffer->cbuf_capacity;
}

/******************************************************************************/
ssize_t CbufRead(cbuf_ty *buffer, void *dest, size_t num_of_bytes)
{
	/*create size var to have the size from struct and init it to 0*/
	size_t cbuf_size = 0;
	/*create capacity var to have the capacity from struct and init it to 0*/
	size_t cbuf_capacity = 0;
	/*create new read_index to have the offset from struct and init it to 0*/ 
	size_t read_index = 0;
	/*cerate new index for loop and init to zero*/
	size_t i = 0;
	
	/*assert for NULL*/
	assert(buffer);
	assert(dest);
	/*assert for trying to read more than size ( current written bytes)*/
	assert(num_of_bytes > cbuf_size);
	
	/*update size var to size from struct*/
	cbuf_size = buffer->cbuf_size;
	/*update capacity var to capacity from struct*/
	cbuf_capacity = buffer->cbuf_capacity;
	/*update read_index to offset from struct*/ 
	read_index = buffer->cbuf_read_offset;
	
	/*check if num_of_bytes is zero*/
	if(0 == num_of_bytes) 
	{
		/*return zero per man of read*/
		return 0;
	} 
	
	/*check if buffer is empty*/
	if(0 == cbuf_size)
	{
		/*return -1 for failure*/
		return -1;
	} 
	
	/*loop num_of_bytes times*/
	while( i < num_of_bytes)
	{
		memcpy((char*)dest + i, buffer->cbuf_arr + read_index, 1);
		/*decrement size by one*/
		--buffer->cbuf_size;
		/*update read_index by one*/
		read_index = (read_index + 1)%cbuf_capacity;	
		++i;
	}
	
	/*update struct read to be the index*/
	buffer->cbuf_read_offset = read_index;
	
	return num_of_bytes;
}

/******************************************************************************/
ssize_t CbufWrite(cbuf_ty *buffer, const void *src, size_t num_of_bytes)
{
	/*create size var to have the size from struct and init it to 0*/	
	size_t cbuf_size = 0;
	/*create capacity var to have the capacity from struct and init it to 0*/
	size_t cbuf_capacity = 0;
	/*create new write_index and init it to 0*/ 
	size_t write_index = 0;
	/*create new index for loop and init to zero*/
	size_t i = 0;
	/*create free_space var and set it to zero*/
	size_t free_space = 0;
	
	/*assert for NULL*/
	assert(buffer);
	assert(src);
	/*assert for num_of_bytes larger than capacity*/
	assert(cbuf_capacity < num_of_bytes);
	
	/*update size var to size from struct*/
	cbuf_size = buffer->cbuf_size;
	/*update capacity var to capacity from struct*/
	cbuf_capacity = buffer->cbuf_capacity;
	/*update write_index to be offset from struct plus size*/ 
	write_index = buffer->cbuf_read_offset + cbuf_size ;
	free_space = cbuf_capacity - cbuf_size;
	
	/*check failure situation - cbuf is full*/
	if((free_space < num_of_bytes) || (cbuf_capacity == cbuf_size))
	{
		/*return failure*/
		return -1;
	} 
	
	/*update write_index to be modulo capacity*/
	write_index = write_index%cbuf_capacity;
	/*loop num of bytes times*/
	while( i < num_of_bytes)
	{
		/*copy byte byte from src to buf per index*/
		memcpy(buffer->cbuf_arr + write_index ,(char*)src + i, 1);
		/*increment size by one*/
		++buffer->cbuf_size;
		/*update write index to inceremnted by one but moduled by capacity*/
		write_index = (write_index + 1)%cbuf_capacity;
		/*increment i by one*/
		++i;	
	}

	/*return num of bytes for success*/
	return num_of_bytes;
}

/******************************************************************************/
int CbufIsEmpty( cbuf_ty *buffer)
{
	/*assert for null buffer*/
	assert(buffer);
	
	/*return 1 if size is zero*/
	return (0 == buffer->cbuf_size);
}


#if 0
#include <stdio.h> /*perror*/
#include <stdlib.h> /*malloc, free*/
#include <errno.h> /*errno*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy, sterror*/
/******************************************************************************/
#include "cbuf.h"
/******************************************************************************/
struct cbuf
{
	size_t capacity;
	char *read;
	char *write;
	char arr[1];
};
/******************************************************************************/
cbuf_ty *CBufCreate(const size_t capacity)
{
	/*dynamic allocation for circular buffer*/
	cbuf_ty *cbuf = (cbuf_ty *)malloc(sizeof(cbuf_ty) + capacity - 1);
	
	/*check if NULL*/
	if (NULL == cbuf)
	{
		perror(strerror(errno));
		
		return NULL;
	}
	
	/*intialize struct components*/
	cbuf->capacity = capacity;
	cbuf->read = cbuf->arr;
	cbuf->write = cbuf->arr;
	
	/*return the circular buffer*/
	return cbuf;
}
/******************************************************************************/
void CBufDestroy(cbuf_ty *cbuf)
{
	/*assert*/
	assert(cbuf);
	
	/*free the circular buffer*/
	free(cbuf);
	
	cbuf = NULL;
}
/******************************************************************************/
size_t CBufFreeSpace(const cbuf_ty *cbuf)
{
	size_t free_space_buf = 0;
	
	/*assert*/
	assert(cbuf);
	
	if (cbuf->read == cbuf->write)
	{
		/*return space val*/
		return cbuf->capacity;
	}
	
	/*check how much space i have*/
	if (cbuf->read < cbuf->write)
	{
		free_space_buf = (cbuf -> capacity) - ((size_t)cbuf->write -
							(size_t)cbuf->read);
		return free_space_buf;												
	}
	else
	{
		free_space_buf =  ((size_t)cbuf->read - (size_t)cbuf->write);
		return free_space_buf;									   
	}
	
}
/******************************************************************************/
size_t CbufSize(const cbuf_ty *buffer)
{
	/*assert*/
	assert(buffer);
	
	return buffer -> capacity;
}
/******************************************************************************/
ssize_t CbufRead(cbuf_ty *buffer, void *dest, size_t num_of_bytes)
{
	size_t count = 0;
	
	/*assert*/
	assert(buffer);
	assert(dest);
	assert(num_of_bytes > 0);
	
	/*check if nothingto read*/
	if(0 == (buffer->write) - (buffer->read))
	{
		return -1;
	}
	
	/*loop num of bytes*/
	while(count < num_of_bytes)
	{
		/*read the value & set it in dest*/
		*(char*)dest = *(char*)(buffer -> read);
		
		/*check if we got to the end*/
		if((size_t)(buffer->read - buffer->arr)==buffer->capacity)
		{	
			/*reset read*/
			buffer->read = buffer->arr;
		}
		
		/*incremnt values*/
		++count;
		++buffer->read;
	}
	/*return count value*/
	return count;
}
/******************************************************************************/
ssize_t CbufWrite(cbuf_ty *buffer, const void *src, size_t num_of_bytes)
{
	/*moves in circular buffer*/
	size_t steps = 0;
	
	/*assert*/
	assert(buffer);
	assert(src);
	assert(num_of_bytes <= buffer->capacity);
	
	for(steps = 0; steps < num_of_bytes; ++steps)
	{	
		/* set the value in buffer write/pointed place */
		*buffer->write = *((char*)src + steps);
		
		/* check if we got to the end of the array */
		if(buffer->write == ((char*)&buffer->arr + buffer->capacity))
		{
			/* move to the beginnig of the array */
			buffer->write = (char*)&buffer->arr;
		}
		/* move write index to next one */
		++buffer->write;
	}
	
	return steps ;
}
/******************************************************************************/
int CbufIsEmpty(cbuf_ty *buffer)
{	
	/*check if the circular buffer EMpty*/
	if(0 == buffer->write - buffer->read)
	{
		return 1;
	}else
	{
		return 0;
	}
}
/******************************************************************************/
#endif

	







































