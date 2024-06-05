#include <stdio.h> /* printf */
#include <stdlib.h> /* typedef */
#include <string.h> /* strings */
#include <assert.h> /* strings */

#define SIZE 4

/* SUCCESS 0 , FAIL 1*/
typedef enum {SUCCESS, FAIL} Status;

typedef Status(*comp)(char* , char*);
typedef Status(*action)(char*);

/* properties for the struct */
typedef struct command
{
	char cmd[10];
	comp compare; 
	action implement;
	
}command;


/*                                                                          FUNTIONS TO BE USED                                                            */
/* compare function */
Status StrCmp(char* str1 , char* str2);

/*  implementation function */
Status implement_func(char *ptr);

/*  implementation of count line function */
Status count_func(char *ptr);

/*  implementation of < function & adds regular string to file  */
Status Default_func(char *ptr);

/*  implementation of count line function */
Status remove_func(char *ptr);

Status exit_func(char * ptr_func);

/* 	                                                                 MAIN                                                                          */	

int main(int argc,char *argv[])
{

	char *ptr;

	ptr=argv[1];
	
	implement_func(ptr);

return 0; 

}
/* 	                                                                    END OF MAIN                                                                      */



Status implement_func(char *ptr)
{
int i;

char *ptr_func = ptr;
							/* {command.cmd , command.compare , command.action} */
	command structs_array[SIZE];
 
	strcpy(structs_array[0].cmd," ");  
	structs_array[0].compare = StrCmp;  
	structs_array[0].implement = Default_func; 
	
	strcpy(structs_array[1].cmd,"-remove");  
	structs_array[1].compare = StrCmp;  
	structs_array[1].implement = remove_func;
	
	strcpy(structs_array[2].cmd,"-count");  
	structs_array[2].compare = StrCmp;  
	structs_array[2].implement = count_func;
	
	strcpy(structs_array[3].cmd,"-exit");  
	structs_array[3].compare = StrCmp;  
	structs_array[3].implement = exit_func;
	
	/*
	strcpy(command[4].cmd,"<");  
	command[3].compare = StrCmp;  
	command[3].implement = Default_func;
	*/
	
	
	for(i=0 ; i<SIZE ; ++i)
	{	
		/* THIS IF MEANS THERE IS A THIRD VALUE OF STRING */
		
		if(structs_array[i].compare==SUCCESS)
		{
			
			structs_array[i].implement(ptr_func);
		}
	}
}

Status count_func(char * ptr_func)
{
    FILE *fileptr;
    int count_lines = 0;
    char chr;
    
    chr = getc(fileptr);
    fileptr = fopen(ptr_func, "r");
    
    if(fileptr==NULL)
    {
    
	printf("ERROR: Cannot open input file.\n");
        exit(1);
        
    }else{
    
	while (chr != EOF)
	{
		if (chr == '\n')
        	{
			count_lines = count_lines + 1;
        	}
		chr = getc(fileptr);
    	}
    
	fclose(fileptr); 
	printf("There are %d lines \n", count_lines);
    
	return SUCCESS;
	}
}

Status remove_func(char *ptr)
{
char *filename = ptr;

	if(filename==NULL)
	{
        printf("ERROR: Cannot remove this file.\n");
        exit(1);
	}else{
		if (remove(filename) == SUCCESS)
		{
 			printf("The file %s was deleted.", filename);
			return SUCCESS;
		}
		else
		{
		printf("Error deleting the file %s.", filename);
		return FAIL;
		}
	}
}
Status exit_func(char * ptr_func)
{
	printf("BYE");
	
	exit(1);
	return SUCCESS;
}

Status Default_func(char *ptr)
{
	FILE *file_ptr;
	char str[20];

	file_ptr = fopen(ptr,"a");
	
	
	fgets(str,20,stdin);
	
	if (NULL==file_ptr)
	{
	
        	printf("ERROR: Cannot EDIT this file.\n");
        	return FAIL;
        	
        
	}else	{
			if(*str=='<')
			{
				fseek(file_ptr, 0, SEEK_SET);
				fputs(str, file_ptr);
				fclose(file_ptr);
   
				return SUCCESS;
			}else	{
			
				fseek(file_ptr, 2, SEEK_END);
				fputs(str,file_ptr);
				fclose(file_ptr);
				
				return SUCCESS;	
				}
		}
}

Status StrCmp(char* str1 , char* str2 )
{	
	size_t counter=0;
	assert(str1 != NULL && str2!= NULL);
	
	while (*(str1+counter)==*(str2+counter) &&
	                         *(str1+counter) && *(str2+counter) )
	{	
    		++counter;
        }
        if((*(str1+counter)-*(str2+counter))==0)
	return SUCCESS;
	else return FAIL; 
}

