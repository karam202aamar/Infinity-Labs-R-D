#include <stdio.h>  /* prints*/

void foo(int a[] , int size)
{
	int i=0;
	
	for(i=0 ; i<size ; ++i)
	{
		a[i]=i*2;
	}
	printf("\n the size of a :%lu \n",sizeof(a));
}

int main(int argc,char **argv,char **envp)
{
	char str[]="welcome";
	int arr[10]={0};
	foo(arr,10);
	
	printf("\n the size of sizeof(str):%lu \n",sizeof(str));
	printf("\n the size of strlen(str):%lu \n",strlen(str));
	
	printf("\n the size of arr :%lu \n",sizeof(arr));
	


return 0 ; 
}

/*
we get 8 because of the \0 in the end 
we get 7 because it's the lenght of the string 

we get 40 the size of arr 4byte *10
we get 8 the size of a because its an address 8 bytes
 */
