#include <stdio.h> 

typedef void (*print_pointer)(int); /*pointer to function */

typedef struct
{
	int value;
	print_pointer PrintFunc;
}       print_me;

void Print(int x);
void Test();

int main()
{
	Test();
	
	return 0;
}

 void Test()
{
	print_me array[10];
	int i = 0;
	
	print_pointer print_call= Print; /*pointing to print function */
	
	for (i = 0; i < 10 ; ++i)
	{
		array[i].value = i;
		array[i].PrintFunc = print_call;
	
	}
	
	for (i = 0; i < 10; ++i)
	{
		array[i].PrintFunc(array[i].value); /*calling print function*/
	}
}

void Print(int x)
{
	printf("%d\n", x);
}


