#include <stdio.h>  /* prints*/

int main()
{
	char *p="lalala";
	char arr[10]="lalala";
	
	++p;
	/*
	++arr; 
	*p='s';
	p[0]='s';
	*/
	arr[1]='s';
	*(arr+1)='s';
	1[arr]='s';
	
	printf("\n the size of sizeof(str):%lu \n",sizeof(p));
	printf("\n the size of sizeof(str):%lu \n",sizeof(arr));
	
	return 0; 
}

/* 
	error : 
	++arr
	*p=s
	p[0]
	
	a. 8 10 
*/
