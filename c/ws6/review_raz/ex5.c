/*
Project: Bitwise ex5
Date: 19/7/22
Reviewer: Karam
Version: 1.0 work
*/
/*--------------------------------------------------*/

#include <stdio.h> /*printf scanf*/

static void UserInput();

static unsigned char ByteMirrorWithLoop(unsigned char num);
static unsigned char ByteMirrorNoLoop(unsigned char num);
/*--------------------------------------------------*/
int main() 
{
	UserInput();
  	return 0; 
}

static void UserInput()
{
	unsigned char num = 0;
	
	printf("Enter a number:");
	scanf("%hhu", &num);
	
	printf("Mirror byte with loop: %hhu \n",ByteMirrorWithLoop(num));
	printf("Mirror byte no loop: %hhu \n",ByteMirrorNoLoop(num));
} 

static unsigned char ByteMirrorWithLoop(unsigned char num) 
{ 
	unsigned char rev_num = 0;
	size_t num_size = sizeof(num)*8;
	size_t i = 0;

    while(i < num_size) 
    { 
    	rev_num = (num & 1) | (rev_num << 1);
		num = num >> 1;
		++i;
    } 
    
    return rev_num; 
} 

static unsigned char ByteMirrorNoLoop(unsigned char num) 
{
	num = (num & 0xF0) >> 4 | (num & 0x0F) << 4;
	num = (num & 0xCC) >> 2 | (num & 0x33) << 2;
	num = (num & 0xAA) >> 1 | (num & 0x55) << 1;
   
   return num;

}



