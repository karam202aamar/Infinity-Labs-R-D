/*
Project: ex7 in ws8
Date: 22.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include <stdio.h>

#define SIZEOF_TYPE(t) ((size_t)(1 + (t*)0))

int main()
{ 
    printf("the size of int: %ld\n ", SIZEOF_TYPE(int));
    printf("the size of char:%ld\n ", SIZEOF_TYPE(char));
  
    return 0;
}




