#include <stdio.h>

int main()
{
struct student
{
char * name;
size_t age;
int grade;
char class[5];
}student;

struct karam
{
char a;
int x;
char b;
}karam;

struct katya
{
size_t a;
char x;
char b;
}katya;

struct ayman
{
char a;
size_t x;
char b;
}ayman;

printf("%ld\n",sizeof(student));
printf("%ld\n",sizeof(karam));
printf("%ld\n",sizeof(katya));
printf("%ld\n",sizeof(ayman));

return 0; 
}
