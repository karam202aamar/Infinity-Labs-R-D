#include <stdio.h>

unsigned int countSetBitsNoLoop(unsigned int num)
{
    
	int result = num;
	result = result - ((result >> 1) &1431655765); 
	/* 01010101010101010101010101010101 */
	
	result = (result &858993459) + ((result >> 2) &858993459);
	/* 00110011001100110011001100110011 */
	
	result = (result + (result >> 4)) &252645135;
	/* 1111000011110000111100001111 */
	
	result = result + (result >> 8);
	/* 1000 */
	
	result = result + (result >> 16);
	result = result &63;
	
	return result;
}
 
/* Program to test function countSetBits */
int main()
{
	unsigned int number;
	printf("enter your number honey:");
	scanf("%u",&number);
	printf("%d\n", countSetBitsNoLoop(number));
    return 0;
}
