#include <stdio.h> /* printf */
#include <stdlib.h> /* typedef */


#define SIZE 5

typedef enum {SUCCESS, FAIL} Status;

typedef Status_ty(*comp)(char*,char*);
typedef Status_ty(*action)(char*,char*);

typedef struct command
{
	char cmd[10];
	comp compare; 
	action implement;
	
}       command_ty;


Status_ty StrCmp(char * str1,char *str2);/*TODO:each typedef defined by user need the suffix typename_ty*/
Status_ty ImplementFunc(char *ptr);
Status_ty CountFunc(char *ptr,char *str);
Status_ty AppendStart(char *file_to_change, char *string_to_add); 
Status_ty AppendEnd(char *file_to_change,char *string_to_add);/
Status_ty RemoveFunc(char *ptr_to_file,char *str);
Status_ty ExitFunc(char * ptr_func,char *str);
Status_ty StrCmpChar(char * str1,char *str2);

/*         MAIN           */	

int main(int argc,char *argv[])
{
	char *ptr;

	ptr=argv[1];
	ImplementFunc(ptr);

return 0; 
}
/*     END OF MAIN        */


Status_ty ImplementFunc(char *ptr_FILE)
{
int i,flag=0;

char *ptr_func = ptr_FILE;
char *input_cmd = (char *)malloc(sizeof(int)*80);
	command_ty structs_array[SIZE];

	strcpy(structs_array[0].cmd,"<");  
	structs_array[0].compare = StrCmpChar;  
	structs_array[0].implement = Append_start; 
	
	strcpy(structs_array[1].cmd,"-remove");  
	structs_array[1].compare = StrCmp;  
	structs_array[1].implement = remove_func;
	
	strcpy(structs_array[2].cmd,"-count");  
	structs_array[2].compare = StrCmp;  
	structs_array[2].implement = count_func;
	
	strcpy(structs_array[3].cmd,"-exit");  
	structs_array[3].compare = StrCmp;  
	structs_array[3].implement = exit_func;
	
	strcpy(structs_array[4].cmd,"");  
	structs_array[4].compare = StrCmp;  
	structs_array[4].implement = Append_end;
	/*end of what could be in an init function*/
	printf("\n  enter your command:");
	gets(input_cmd);
	
	if(structs_array[0].compare(structs_array[0].cmd,input_cmd) == SUCCESS)/*TODO: i have added a space before and after ==*//*SUCCESS must be in the left side*/
	{
		structs_array[0].implement(ptr_func,input_cmd);
		flag=1;/*TODO: need for spaces before and after =*//*another name more descriptive please*//*TODO: need for spaces before and after =*//*TODO: 1 is magic number*/
	}
	for(i=1; i<SIZE-1 ; ++i) /*TODO: need for spaces before and after = and <*/
	{	
		/*TODO:no need for space here*/
		if(structs_array[i].compare(structs_array[i].cmd,input_cmd) == SUCCESS)/*SUCCESS must be in the left side*/
		{
			flag=1;/*TODO: need for spaces before and after =*//*another name more descriptive please*/
			structs_array[i].implement(ptr_func,input_cmd);/*TODO: need for spaces before and after ,*/
			/*TODO: why do you separate the first case (i = 0) ?*/
		}
	}
	
	if(flag==0)/*TODO: need for spaces before and after =*//*0 TODO:0 is magic number here and must be in the left side*/
	{
		structs_array[4].implement(ptr_func,input_cmd);		    
	}
	free(input_cmd);
}

Status_ty CountFunc(char * ptr_func , char *str)
{
    FILE *fileptr;/*TODO: put _ as: file_ptr*/
    int count_lines = 0;
    char chr;
    
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
    
	
	printf("\n There are %d lines \n", count_lines);
    	fclose(fileptr); 
	return SUCCESS;
	}
}

Status_ty RemoveFunc(char *ptr_to_file, char *str)
{
FILE *file = NULL;
	
	file = fopen(ptr_to_file, "r");
	
	if(NULL == file)
	{
		printf("ERROR: Cannot remove this file.\n");
	}
	
	fclose(file);
	remove(ptr_to_file);
	exit(0);
}

Status_ty ExitFunc(char * ptr_func,char *str)
{
	printf("BYE");
	exit(1);
}

Status_ty AppendStart(char *file_to_change, char *string_to_add)
{
	FILE *file = NULL;
	FILE *temp_file = NULL;
	char char_to_move = '\0';
	
	temp_file = fopen("temp.txt", "a+");
	
	if(NULL == temp_file)
	{
		printf("ERROR: Cannot open this file1.\n");
	}
	
	fputs(string_to_add, temp_file);
	
	file = fopen(file_to_change, "r");
	
	if(NULL == file)
	{
		printf("ERROR: Cannot open this file2.\n");
	}
	
	char_to_move = fgetc(file);
	fputc('\n', temp_file);
	/*move the old value to the end */ 
	while(EOF != char_to_move)
	{
		fputc(char_to_move, temp_file);
		char_to_move = fgetc(file);
	}
	
	fclose(file);
	remove(file_to_change);
	file = fopen(file_to_change, "w+");
	
	/* now i wanna move it from temp to final file */ 
	
	if(NULL == file)
	{
		printf("ERROR: Cannot open this file3.\n");
	}
	
	fseek(temp_file, 0, SEEK_SET);
	char_to_move = fgetc(temp_file);
	
	while(EOF != char_to_move)
	{
		fputc(char_to_move, file);
		char_to_move = fgetc(temp_file);
	}
	
	fclose(temp_file);
	fclose(file);
	remove("temp.txt");
}

Status_ty AppendEnd(char *file_to_change,char *string_to_add)
{
	FILE *file = NULL;
	
	file = fopen(file_to_change, "a");
	
	if(NULL == file)
	{
		printf("ERROR: Cannot open this file 4.\n");
	}
	
	fputs(string_to_add, file);
	fclose(file);
}

Status_ty StrCmp(char * str1,char *str2)
{
	if(0==strcmp(str1,str2))
	{
		return SUCCESS;
		
	}else return FAIL;
}

Status_ty StrCmpChar(char * str1,char *str2)
{
	if(*str1==*str2)
	{
		return SUCCESS;
		
	}else return FAIL;
}



