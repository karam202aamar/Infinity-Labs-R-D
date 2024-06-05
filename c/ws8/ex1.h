/*************************************************************************/
/*Poject: Add Int 
author: karam aamar
reviewer:katya
Date:  
Version:
/*
/*************************************************************************/
#ifndef __EX1_H_ILRD__
#define __EX1_H_ILRD__

typedef struct element element_ty;

typedef void (*AddFunc_ty)(int num, element_ty* element);
typedef void (*PrintFunc_ty)(element_ty* element);
typedef void (*CleanupFunc_ty)(element_ty* element);


struct element
{
	/*input of data -- any data type*/
	void *data;
	AddFunc_ty Add;
	PrintFunc_ty Print;
	CleanupFunc_ty Cleanup;
};

/**********************************add functions*******************************/

/* Adds num to the int stored in data */
void AddToInt(int num, element_ty* element);

/* Adds num to the float stored in data */
void AddToFloat(int num, element_ty* element);

/* Concatenates num to the end of the string stored in data by dynamically
   allocating memory for the string.
   Memory will not be freed in this function. */
void AddToString(int num, element_ty* element);


/**********************************print functions*****************************/

/* Prints the int stored in data */
void PrintInt(element_ty* element);

/* Prints the float stored in data */
void PrintFloat(element_ty* element);

/* Prints the string stored in data */
void PrintString(element_ty* element);


/*********************************cleanup functions****************************/

/* Does nothing */
void CleanupInt(element_ty* element);

/* Does nothing */
void CleanupFloat(element_ty* element);

/* Frees memory that was allocated for the string stored in data */
void CleanupString(element_ty* element);

#endif /*__EX1_H_ILRD__*/
