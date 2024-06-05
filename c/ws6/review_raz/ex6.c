/*
Project: Bitwise ex6
Date: 19/7/22
Reviewer: Karam
Version: 1.0 work
*/
/*--------------------------------------------------*/

#include <stdio.h> /*printf scanf*/
#include <stddef.h> /*size_t*/ 

#define SIX 32
#define TWO 2
#define THREE 4
#define FIVE 16

typedef enum {FALSE = 0,TRUE} end_result;
/*--------------------------------------------------*/

end_result SixANDTwo(unsigned char num);
end_result SixOrTwo(unsigned char num);
end_result SwapThreeFive(unsigned char num);
end_result SwapThreeFive(unsigned char num);
/*--------------------------------------------------*/
int main() 
{
	unsigned char num = 18;
    
    printf("Enter num:");
    printf("And %d \n", SixANDTwo(num)); 
    printf("Or %d \n", SixOrTwo(num));    
    printf("After swap %d \n", SwapThreeFive(num));    
  	return 0; 
}
 
end_result SixANDTwo(unsigned char num)
{
	return ((SIX == (num & SIX)) && (TWO == (num & TWO)));
}

end_result SixOrTwo(unsigned char num)
{
	return ((SIX == (num & SIX)) || (TWO == (num & TWO)));
}

end_result SwapThreeFive(unsigned char num)
{
	unsigned char bit_three = (num & THREE);
	unsigned char bit_five = (num & FIVE);

	num = (bit_three ^ num) | bit_five >> TWO;
	num = (bit_five ^ num) | bit_three << TWO;	
	
	return num;
}


