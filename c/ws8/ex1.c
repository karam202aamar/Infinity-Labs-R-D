/*
Project: ex1 in ws8
Date: 22.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/

#include <stdio.h> /* prints */ 
#include <stdlib.h> /* allocation */ 
#include <string.h> /* memcpy */ 

#include "ex1.h"

#define ARRAY_SIZE 3
#define INT_NUMBER 2
#define FLOAT_NUMBER 2.0
#define TEXT "hello "

void ImplementFunc(element_ty elementArr[]);
void InitFunc(element_ty elementArr[]);

/******************************************************/
int main()
{

element_ty elementArray[ARRAY_SIZE];

ImplementFunc(elementArray);

return 0; 
}
/******************************************************/
void ImplementFunc(element_ty elementArr[])
{
	
	
	InitFunc(elementArr);
	
		printf("The elements after addition:\n");
		
		elementArr[0].Print(&elementArr[0]);
		elementArr[1].Print(&elementArr[1]);
		elementArr[2].Print(&elementArr[2]);
		printf("i will add 2\n");
		printf("The elements after addition:\n");
		
		elementArr[0].Add(2, &elementArr[0]);
		elementArr[0].Print(&elementArr[0]);
		
		elementArr[1].Add(2, &elementArr[1]);
		elementArr[1].Print(&elementArr[1]);
		
		elementArr[2].Add(2, &elementArr[2]);
		elementArr[2].Print(&elementArr[2]);

	
}

void InitFunc(element_ty elementArr[])
{
	*(int*)&(elementArr[0].data) = INT_NUMBER;
	elementArr[0].Add = AddToInt;
	elementArr[0].Print = PrintInt;
	elementArr[0].Cleanup = CleanupInt;
	
	*(float*)&(elementArr[1].data) = FLOAT_NUMBER;
	elementArr[1].Add = AddToFloat;
	elementArr[1].Print = PrintFloat;
	elementArr[1].Cleanup = CleanupFloat;
	
	*((char**)&(elementArr[2].data)) = TEXT; /* pointer 2nd to point to the pointer that contains the TEXT*/
	elementArr[2].Add = AddToString;
	elementArr[2].Print = PrintString;
	elementArr[2].Cleanup = CleanupString;
}
/******************************************************/
void AddToString(int num, element_ty* element)
{
	
	int str_size = strlen((char *)element->data);
	/* int str_size = strlen(*(char **)&(element->data)); 
	
	   int str_size = strlen(*(char **)element->data); false way */
	char *num_str=NULL;
	char *str_final = NULL;
	int count = 0;
	int tmp=num;
	
	while(tmp)
	{
		tmp /= 10;
		++count;
	}
	
	num_str = (char *) malloc (count);
	str_final = (char *) malloc (str_size + count+1);
	
	sprintf(num_str, "%d", num);
	
	memcpy(str_final,*(char **)&element->data ,str_size+1);
	
	strcat(str_final , num_str);
	free(num_str);
	
	*(char**)&element->data = str_final;
	
	
}

void AddToFloat(int num, element_ty *element)
{
	*(float *)&element->data += (float)num;
}

void AddToInt(int num, element_ty *element)
{
	*(int *)&element->data += num;
}

/******************************************************/
void PrintInt(element_ty* element)
{
	printf("%d\n", *(int *)&element->data);
}

void PrintFloat(element_ty* element)
{
	printf("%f\n", *(float *)&element -> data);
}

void PrintString(element_ty* element)
{
	printf("%s\n", *(char**)&element->data);
}
/******************************************************/
void CleanupString(element_ty* element)
{
	char *str_print = element -> data;
	free(str_print);	
}
void CleanupInt(element_ty* element)
{
	NULL;
}  
void CleanupFloat(element_ty* element)
{
	NULL;
}


