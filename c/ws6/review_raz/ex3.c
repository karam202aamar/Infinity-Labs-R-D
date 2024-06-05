/*
Project: Bitwise ex3
Date: 18/7/22
Reviewer: Karam
Version: 1.0 dosent work
*/
/*--------------------------------------------------*/

#include <stdio.h> /*pust printf scanf*/

int AddOne(int x);

/*--------------------------------------------------*/
int main() 
{
	int x = 0;
    
    puts("Enter x:");
    scanf("%d", &x);
    
  	printf("%d", AddOne(x)); 
  	return 0; 
} 
/*todo change the name of the variables to something more obvious */
int AddOne(int x) 
{ 
    int m = 1; 

    while((x & m)) 
    { 
        x = x ^ m; 
        m = m << 1; 
    } 
    x = x ^ m;
    
    return x; 
} 
  
