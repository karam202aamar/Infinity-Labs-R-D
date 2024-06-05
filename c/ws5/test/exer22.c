#include <stdio.h> /* printf */
#include <stdlib.h> /* typedef */
#include <string.h> /* strings */
#include <assert.h> /* strings */

#define SIZE 4

/* SUCCESS 0 , FAIL 1*/
typedef enum {SUCCESS, FAIL} Status;

typedef Status(*comp)(char*,char*);
typedef Status(*action)(char*,char*);

/* properties for the struct */
typedef struct command
{
	char cmd[10];
	comp compare; 
	action implement;
	
}command;


/*                                                                          FUNTIONS TO BE USED                                                            */

Status StrCmp(char * str1,char *str2);

/*  implementation function */
Status implement_func(char *ptr);

/*  implementation of count line function */
Status count_func(char *ptr,char *str);

/*  implementation of < function & adds regular string to file  */
Status Default_func(char *ptr_FILE,char *str);

/*  implementation of count line function */
Status remove_func(char *ptr,char *str);

Status exit_func(char * ptr_func,char *str);

/* 	                                                                       MAIN                                                                          */	

int main(int argc,char *argv[])
{

	char *ptr;
	printf("enter your file name:");
	/*ptr=argv[1];*/
	gets(ptr);
	
	implement_func(ptr);

return 0; 

}
/* 	                                                                    END OF MAIN                                                                      */



Status implement_func(char *ptr_FILE)
{
int i,flag=0;

char *ptr_func = ptr_FILE;
char * input_cmd=(char *)malloc(sizeof(int)*80);
							/* {command.cmd , command.compare , command.action} */
	command structs_array[SIZE];
 
	strcpy(structs_array[0].cmd,"DEFAULT");  
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
	printf("enter your command:");
	gets(input_cmd);
	
	for(i=1 ; i<SIZE ; ++i)
	{	
		
		if(structs_array[i].compare(structs_array[i].cmd,input_cmd)==SUCCESS)
		{
			printf("flag");
			flag=1;
			structs_array[i].implement(ptr_func,input_cmd);
			
		}
	}
	
	if(flag==0)
	{
		structs_array[0].implement(ptr_func,input_cmd);		    
	}
	free(input_cmd);
}

Status count_func(char * ptr_func , char *str)
{
    FILE *fileptr;
    int count_lines = 0;
    char chr;
    
    printf("im here");
    fileptr = fopen(ptr_func, "r");
   
   
    if(NULL==fileptr)
    {
	printf("ERROR: Cannot open input file.\n");
        exit(1);
        
    }else{
   
	chr = getc(fileptr);
	while (chr != EOF)
	{
		if (chr == '\n')
        	{
			count_lines = count_lines + 1;
        	}
		chr = getc(fileptr);
    	}
    
	
	printf("There are %d lines \n", count_lines);
    	fclose(fileptr); 
	return SUCCESS;
	}
}

Status remove_func(char *ptr, char *str)
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

Status exit_func(char * ptr_func,char *str)
{
	printf("BYE");
	exit(1);
}

Status Default_func(char *ptr_FILE,char *str)
{
	
	FILE *file_ptr;
	char *str_input;
	
	
	file_ptr = fopen(ptr_FILE,"a");
	str_input=str;
	/*
	printf("Enter the text you wanna add it to your file:");
	fgets(str,100,stdin);
	*/ 
	printf("__line__");
	if (NULL==file_ptr)
	{
	
        	printf("ERROR: Cannot EDIT this file.\n");
        	return FAIL;
        	
        
	}else	{
			if(*str_input=='<')
			{
				fseek(file_ptr, 0, SEEK_SET);
				fputs(str_input, file_ptr);
				fclose(file_ptr);
   
				return SUCCESS;
			}else	{
			
				fseek(file_ptr,0, SEEK_END);
				fputs(str_input,file_ptr);
				fclose(file_ptr);
				
				return SUCCESS;	
				}
		}
}

Status StrCmp(char * str1,char *str2)
{
	if(0==strcmp(str1,str2))
	{
		return SUCCESS;
		
	}else return FAIL;
}


