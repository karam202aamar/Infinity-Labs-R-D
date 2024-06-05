/*************************************************************************
Poject: struct part 2
Author: karam aamar
Reviewer: 
Date: 26/07/22
Version: 1.0
*************************************************************************/

#include <stdio.h>  /* print */
#include <string.h> /* memcpy */
#include <stdlib.h> /* allocation */
#include <stddef.h> /* size_t */
#include <assert.h> /* NULL pointers check */
#include <errno.h>  /* errors types */

#include "wbo.h"

void TestFunc();

#define WORD_SIZE 8

void *Memcpy2(void *dest, const void *src, size_t num_of_bytes);


int main()
{
	TestFunc();
	
	return 0;
}

void TestFunc()
{
	char array_cpy[10] = {'k','a','r','a','m'};
	char array_test[10];
	char array_test3[10] = {'k','a','r','a','m','s'};
	char * array_test2=array_test3;
	array_test2 += 2;
	
	Memcpy(array_test, array_cpy, 10);
	Memset(array_cpy,'$',2);
	
	printf("Memset function output: \n");
	printf("%s\n",array_test);
	
	printf("Memcpy function output: \n");
	printf("%s\n",array_test);
	
	printf("Memmove function output: \n");
	Memmove(array_test2 , array_test3 , 6);
	printf("%s\n",array_test2);
}
void *Memset(void *dest, int char_to_set, size_t num_of_bytes) 
{
	unsigned char *str_runner=dest;
	
	while(num_of_bytes--)
	{
		*str_runner = (unsigned char) char_to_set;
		str_runner++;
	}
	return dest;
}
/* src is aligned copy with word size*/
void *Memcpy(void *dest, const void *src, size_t num_of_bytes)
{
	size_t i;
	size_t chunks_num , reminder_num;
	
	char * dest_1_byte =(char *)dest;
	size_t * dest_8_byte =(size_t *)dest;
	
	char * src_1_byte =(char *)src;
	size_t * src_8_byte =(size_t *)src;
	
	assert(src);
	assert(dest);
	
	/* the number of wordsize in the string */ 
	chunks_num = num_of_bytes / WORD_SIZE;
	
	 /* the rest for byte byte*/ 
	reminder_num = num_of_bytes % WORD_SIZE;
	
	/* loop with wordsize length */ 
	for (i=0 ; i < chunks_num ; i++)
	{
		*dest_8_byte = *src_8_byte;
		++dest_8_byte;
		++src_8_byte;
	}
	/* after we finish chunks move byte byte*/
	dest_1_byte = (char *)dest_8_byte;
	src_1_byte = (char *)src_8_byte;
	
	for (i=0 ; i < reminder_num ; i++)
	{
		*dest_1_byte = *src_1_byte;
		++dest_1_byte;
		++src_1_byte;
	}
   	return dest;
}

/* Copies byte byte */ 
void *Memcpy2(void *dest, const void *src, size_t num_of_bytes)
{
	size_t i;
	char *csrc = (char *)src;
	char *cdest = (char *)dest;
	 /* update the values in the dest*/ 
	for (i=0; i < num_of_bytes; i++)
   		 cdest[i] = csrc[i];
   		 
	return dest;
}

void *Memmove(void *dest, const void *src, size_t num_of_bytes)
{
	size_t i , chunks_num , reminder_num;
	char *dest_end = (char *)dest + num_of_bytes - 1;
	char *src_end = (char *)src + num_of_bytes - 1;	
	size_t *dest_8_end , *src_8_end;
	
	if(dest_end < src_end)
	{
		return Memcpy(dest , src , num_of_bytes);
	}
	
	 /* the rest for byte byte*/ 
	reminder_num = num_of_bytes % WORD_SIZE;
	
	 /* copy the rest byte by byte*/ 
	for(i = 0 ; i < reminder_num ; i++)
	{
		*dest_end = *src_end;
		--dest_end;
		--src_end;
	}
	
	/* move to the beginnig of last word-size in the string of dest*/ 
	dest_end -= (WORD_SIZE - 1);
	
	/* move to the beginnig of last word-size in the string of src*/
	src_end -= (WORD_SIZE - 1);
	
	/* the number of wordsize in the string */ 
	chunks_num = num_of_bytes / WORD_SIZE;
	
	/* move the pointer of dest with 8 byte container */ 
	dest_8_end = (size_t *)dest_end;
	
	/* move the pointer of dest with 8 byte container */ 
	src_8_end = (size_t *)src_end;
	
	/* loop with wordsize length */ 
	for(i = 0; i < chunks_num; i++)
	{
		*dest_8_end = *src_8_end;
		--dest_8_end;
		--src_8_end;
	}
	
	
	return dest;
}


/*
void *Memcpy(void *dest, const void *src, size_t num_of_bytes) 
{
	size_t index_address , steps_for_aligned;
	const char *ptr_runner = (char *)src;
	char *ptr_dest = (char *)dest;
	size_t *ptrx ,*ptry;
	
	index_address = (size_t)dest; 
	
	if(num_of_bytes < WORD_SIZE)
	{
			
		while(ptr_runner && num_of_bytes--)
		{
			*ptr_dest=*ptr_runner;
			ptr_runner++;	
		}
		return dest;
	}
	else
	{
		
		if(0 !=(index_address % WORD_SIZE))
		{
			steps_for_aligned = WORD_SIZE - (index_address % WORD_SIZE);
			ptr_runner += steps_for_aligned;
		}
		
		ptrx = (size_t *)src;
		ptry= (size_t *)dest;
		
		while(ptrx != NULL)
		{
			*ptry  =  *ptrx;	
			
			ptrx++;
		}
		return dest;
	}
}

void *Memcpy(void *dest, const void *src, size_t num_of_bytes)
{
	size_t index_ad_src , index_ad_dest , steps_for_aligned;
	
	char *ptr_runner = src;
	char *ptr_dest = dest;
	
	size_t *ptrx , *ptry;
	
	
	if(num_of_bytes < WORD_SIZE) 
	{
			
		while(ptr_runner && num_of_bytes--)
		{
			*ptr_dest = *ptr_runner;
			ptr_runner++;	
		}
		return dest;
	}
	else    
	{
		
		if((index_ad_src % WORD_SIZE) == (index_ad_dest % WORD_SIZE))
		{
			steps_for_aligned = WORD_SIZE - (index_ad_src % WORD_SIZE);
			while(steps_for_aligned--)
			{
				*ptr_runner = *ptr_dest;
				ptr_runner++;
				ptr_dest++;
			}
			
			ptrx = (size_t *)src;
			ptry = (size_t *)dest;
			
			while(ptrx != NULL)
			{
				*ptry  =  *ptrx;	
				ptrx++;
			}
		}else {
				while(ptr_runner && num_of_bytes--)
				{
					*ptr_dest = *ptr_runner;
					ptr_runner++;	
				}
		      }
		return dest;
	}
}
*/
