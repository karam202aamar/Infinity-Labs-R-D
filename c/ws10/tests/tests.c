#include <stdio.h>  /* print */
#include <string.h> /* memcpy */
#include <stdlib.h> /* allocation */
#include <assert.h> /* NULL pointers check */
#include <errno.h>  /* errors types */

void Memcpy(void *src);

int main()
{
	char array[10]={'k','a','r','a','m'};
	
	Memcpy(array);
	return 0;
}

void Memcpy( void *src)
{
	size_t index_address,is_aligned;
	char *ptr_runner=src;
	
	index_address=(size_t)src;
	printf("%ld\n",index_address);
	is_aligned=(index_address%8);
	printf("%ld\n",is_aligned);
	ptr_runner++;
	ptr_runner++;
	index_address=(size_t)ptr_runner;
	is_aligned=(index_address%8);
	printf("%ld\n",is_aligned);
}
