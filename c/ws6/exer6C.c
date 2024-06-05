/*
Project: ex6 C in ws6
Date: 19.7.22
Name: Karam Aamar
Reviewer: Katya
Version:1.0
*/
#include<stdio.h>
 
 #define POS_ONE 3
 #define POS_TWO 5
 

unsigned char swapBits(unsigned char num)
{
	unsigned char x,result ;
        unsigned char bit1,bit2;
        
	bit1 =  (num >> POS_ONE) & 1;
	bit2 =  (num >> POS_TWO) & 1;
	x = (bit1 ^ bit2);
 
             /* original positions */
	x = (x << POS_ONE) | (x << POS_TWO);
 
    /* XOR 'x' with the original number so that the
       two sets are swapped */
	result = num ^ x;
	return result;
}
 

int main()
{
    
    return 0;
}
