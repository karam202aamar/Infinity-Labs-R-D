
#include <stdio.h>
#include <string.h>
  
#define MAX_LEN 100

int AreRotated(char *str1, char *str2)
{
	int size1,size2;
	void *ptr;
  
	size1   = strlen(str1);
	size2   = strlen(str2);
  
	if (size1 != size2)
	return 0;
  
	strcat(str1, str1);
  
	ptr = strstr(str1, str2);
  
	if (ptr != NULL)
		return 1;
	else
    		return 0;
}
  
int main()
{
    char *str1 = "ABCD";
    char *str2 = "CDAB";
  
    if ( AreRotated(str1, str2))
       printf("Strings are rotations of each other\n");
    else
       printf("Strings are not rotations of each other\n");
  
  
    return 0;
}
