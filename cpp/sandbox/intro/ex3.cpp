#include <stdio.h>

int main()
{
    bool b1 = true;
    bool b2;
    int i = b1;
    i = 7; 
    b2 = i; // will be 1 because i == 7 then its not zero value 

    printf("%d\n", b2); 

    return 0;
}






















