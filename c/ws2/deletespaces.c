#include <stdio.h>  /* prints*/
#include <assert.h> /*assert*/

#define MAX_NUM 50

static char *RemoveSpacesSE(char *str);
void RemoveSpaces(char *str);

int main()
{	
	char str[MAX_NUM]="\n   hi  guys    in   inf   \n";
	
	RemoveSpaces(str);	
	
	
	return 0;
}

static char *RemoveSpacesSE(char *str)
{
    char *last_space = str;
    char *start_pointer = str;
    char *return_ptr=NULL;
    
    return_ptr=str; 
    
    while(*last_space!='\0')
    {
    	last_space++;
    }
    
    last_space--;
    
    
    while(*last_space==' ')
    {
    	last_space--;
    }
    
    while(*start_pointer==' ')
    {
    	start_pointer++;
    }
    
    while(start_pointer<=last_space)
    {
    	*(str++)=*(start_pointer++);
    }
    *str='\0';
    return return_ptr;
}

void RemoveSpaces(char *str)
{
	
	assert(str != NULL); 
	RemoveSpacesSE(str);
	
	while(*str!='\0')
	{
		if(*str==' ' || *str=='\t')
		{
			if(*(str-1)==' ' || *(str-1)=='\t')
			{
				str++;
				continue;
			}
		}
		printf("%c",*str);
		str++;
	}
}






























