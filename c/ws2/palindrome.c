#include <stdio.h>  /* prints*/
#include <string.h>  

#define MAX_NUM 50

int palindrome_func(char *str);

int main()
{
	char str[MAX_NUM];
	char *str2="is palindrome";
	char *str3="is not palindrome";
	
	printf("please enter your string to check if palindrome: "); 
	fgets(str,MAX_NUM,stdin);
	
	if(palindrome_func(str)==1)
	{
		printf("\n %s \n",str2);
	}else
	{
		printf("\n %s \n",str3);
	}
	 
	
	return 0;
}

int palindrome_func(char *str)
{	
	size_t  i;
	int steps=strlen(str);
	
	for(i=0;i<(steps/2);i++)
	{
		if(str[i] != str[steps-2-i])
		{
			return 0;
		}
	}
	
	return 1;
}
