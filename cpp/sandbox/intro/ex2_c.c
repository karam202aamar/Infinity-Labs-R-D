#include <stdio.h>

enum E {AA, BB, CC, DD};
enum E2 {TT, KK};
enum E e;           
enum E2 e2 = AA;  

//E2 e22 = KK;

int main()
{
    int i= e;
    ++e;
    
    return 0;
}




