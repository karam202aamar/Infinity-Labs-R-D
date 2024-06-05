
#include<stdio.h>
#include<string.h>
 
void myMemCpy(void *dest, const void *src, size_t n)
{
int i;
char *csrc = (char *)src;
char *cdest = (char *)dest;
 

for (i=0; i<n; i++)
    cdest[i] = csrc[i];
}
 

int main()
{

char csrc[] = "karam_aamar";
char cdest[100];
int isrc[] = {10, 20, 30, 40, 50};
int idest[5], i,n ;

myMemCpy(cdest, csrc, strlen(csrc)+1);
printf("Copied string is %s", cdest);
 
n = sizeof(isrc)/sizeof(isrc[0]);

myMemCpy(idest, isrc, sizeof(isrc));
printf("\nCopied array is ");

for(i=0; i<n; i++)
    printf("%d ", idest[i]);
    
	printf("\n");
return 0;
}
