#include <stdio.h>

int main()
{
    const int i = 3; //both clang & g++ keeps it value even after line 8 , c changes to 5 after line 8
    int *ip = (int *)&i;
    
    printf("i = %d, *ip = %d\n", i, *ip);
    printf("&i = %p, *&ip = %p\n", &i, ip);

    *ip = 5;
    int arr[i]; //cannot compile in c 
    
    printf("i = %d, *ip = %d\n", i, *ip);
    printf("&i = %p, *&ip = %p\n", &i, ip);
    
    return 0;
}

