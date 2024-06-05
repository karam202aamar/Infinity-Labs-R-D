/*
Project: ex5 in ws8
Date: 22.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

#define MAX2(a, b) a > b ? a : b

#define MAX3(a, b, c) ( ( a>b && a>c ) ? a : ( b>c ) ? b : c )

int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    
    
    printf("%d\n", MAX2(a,b));
    printf("%d\n", MAX3(a,b,c));
 

    return 0;
}


