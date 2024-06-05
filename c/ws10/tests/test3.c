#include <stdlib.h>

void * my_memmove(void* dest, const void* src, unsigned int n)
{
	char *pDest = (char*)dest;
	const char *pSrc = (const char*)src;
	int i = 0;
   
	char *tmp  = (char *)malloc(sizeof(char) * n);
	if(NULL == tmp)
	{
		return NULL;
	}
	else
	{
	for(i =0; i < n ; ++i)
        {
		*(tmp + i) = *(pSrc + i);
        }

	for(i =0 ; i < n ; ++i)
	{
		*(pDest + i) = *(tmp + i);
        }
        
	free(tmp); 
	}
	return dest;
}

int main()
{
return 0;
}
