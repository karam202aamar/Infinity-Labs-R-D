#include <stdio.h>
#include <stdlib.h>

int x;
static int y;

void foo();

int main()
{
	foo();
	
	return 0;
}

void foo()
{

char str1[20];
char *str2=malloc(sizeof(*str2)*20);
char *str3="what ever";
char str4[]="what ever";
int a=8;
int *p=&a;

printf("%p	stack         %p\n",&str1,str1);
printf("%p	malloc        %p\n",&str2,str2);
printf("%p	point to data %p\n",&str3,str3);
printf("%p	stack         %p\n",&str4,str4);
printf("%p	stack         %p\n",&p,&a);
printf("%p	global        %d\n",&x,x);
printf("%p	static        %d\n",&y,y);

}

