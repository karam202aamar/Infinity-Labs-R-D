/*
Project: ex6 in ws8
Date: 22.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>
#define SIZEOF_VAR( var ) ((size_t)(&(var)+1) - (size_t)(&(var)))

int main()
{
    int a = 1;
    long b=2;
   
    printf("the size of int: %ld\n", SIZEOF_VAR(a));
    printf("the size of long long:%ld\n", SIZEOF_VAR(b));
  

    return 0;
}





