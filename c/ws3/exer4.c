#include <stdio.h>
#include <unistd.h> /* environ */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */

int CountRaws();
char** AllocMem(char *src[], size_t src_raws);
void StrCpyLowerCase();
void PrintStr();

int main ()
{
	extern char **environ;
	char **buffer = NULL;
	size_t count = 0;
	
	count = CountRaws (environ);
	buffer= AllocMem(environ, count);
	printf("%d\n", sizeof(buffer));
	StrCpyLowerCase(buffer, environ, count);
	PrintStr(buffer, count);
	
	return 0;
}


int CountRaws(char **str) /* number of rows */
{
	size_t count = 0;
	
	while (*(str + count))
	{
		++count;
	}
	
	return count;
}

char** AllocMem(char *src[], size_t src_raws) /* allocation */
{
	size_t i = 0;
	char **dest;
	dest = (char**)malloc(sizeof(char *) * src_raws);
	
	if (NULL == dest)
	{
		printf("Allocation Failed for dest");
	}
	
	for (i=0 ; i < src_raws ;++i)
	{
		dest[i] = malloc( strlen(src[i]) );
	}
	
	if (NULL == *dest)
	{
		printf("Allocation Failed for *dest");
	}
	return dest; 
}

void StrCpyLowerCase(char **dest, char **src, size_t src_raws) /* lowe case */
{
	size_t i = 0, j = 0;
	
	for (i=0 ; i < src_raws ;++i)   /* this loops checks all the letters */
	{
		for (j = 0 ; j < strlen( src[i] ) ;++j)
		{
		 *(*(dest+i)+j) = tolower(*(*(src +i)+j));
		}
	}
}

void PrintStr(char **str, size_t raws)
{
	size_t i = 0;
	
	for ( i = 0; i < raws ; ++i)
	{
		printf( "%s\n", str[i] );
	}
}
