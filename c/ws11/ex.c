/*************************************************************************
Poject: struct part 2
Author: karam aamar
Reviewer: 
Date: 26/07/22
Version: 1.0
*************************************************************************/

#include <stdio.h>  /* print */
#include <string.h> /* memcpy */
#include <stdlib.h> /* allocation */
#include <assert.h> /* NULL pointers check */
#include <errno.h>  /* errors types */

#include "wbo.h"

#define IsLittleEndian1 (*(char*)&(x)==1)? printf("little endian"):printf("Big endian") 
#define IsLittleEndian2 (1 & *(char *)"a")

#define ASCIIJUMP 6


int Atoi(char* str);
int AToIBase(const char *str, size_t base);
void Itoa(int num, char* str);
void ItoaBase(int num, char* str, size_t base);
int IsLittleEndian(void);

int main()
{

	return 0;
}

int Atoi(char* str)
{ 
    int res = 0;
 
	for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
 
	return res;
}

int AToIBase(const char *str, size_t base)
{
	int result,i;
	char *str_tmp;
	size_t i , len , char_count ;
	
	str_tmp = str;
	
	if (10 >= base)
	{
		while(('0' <= *(str_tmp)) && (*(str_tmp) <= ('0' + base)))
		{
			++char_count;
			++str_tmp;
		}
	}
	else
	{
		while ((('0' <= *(str_tmp)) && (*(str_tmp) <= ('0' + 10)))
	 ||(('A' <= *(str_tmp)) && ((*str_tmp) <= ('A' + base - 10))))
		{
			++char_count;
			++str_tmp;
		}
	}

	for(i = 0; i < char_count ; ++i)
	{
		
		result = result * base;
		
		if (('0' <= str[i]) && (str[i] <= '9'))
		{
			
			result = result + str[i] - '0';
		}
		else
		{
				
			result = result + str[i] - ASCIIJUMP;
		}
	}
	return result ;
}

void ItoaBase(int num, char* str, size_t base)
{
	int rem , count=0 , i=0;
   	
   	
	if (num == 0)
	{
        	str[i++] = '0';
		str[i] = '\0';
      
	}
	
 	tmp_num = num;
 	
	while (num != 0)
	{
		rem = num % base;
		
		if(rem > 9)
			str[i++](rem - 10) + 'a';
			else
			str[i++]rem + '10';
		count++;
		num = num/base;
	}
 	while(i < count)
 	{
 		str[i] = str[count];
		i++
		count--;
 	}
	str[i] = '\0'; 
}
void Itoa(int num, char* str)
{
	int tmp=0;
	
	while(*str != '\0')
	{
		num = (str[i] - 48) * 10 ;
		i++;
	}
	
	while(num > 0)
	{
		tmp = tmp * 10; 
		tmp += num % 10;
		num = num / 10;	
	}
	num = tmp;	
}

int IsLittleEndian(void)
{
	unsigned int x = 0x76543210;
	char *c = (char*) &x;
  
	if (*c == 0x10)
		return 0;
	else
		return 1; 
 
}

void PrintCommonLetters(const char *str1, size_t size1, const char *str2,
 			          size_t size2, const char *str3, size_t size3)
{
	int ascii_table[255];
	
	memset(ascii_table , 0 ,255);
	
	for (i = 0; i < size1; ++i)
	{
		ascii[str1[i]] += 1;
	}
	
	for (i = 0; i < size2; ++i)
	{
		ascii[str2[i]] += 1;
	}
	
	for (i = 0; i < size3; ++i)
	{
		ascii[str3[i]] += 1;
	}
	
	
	for (i = 0; i < 255 ; ++i)
	{
		if (3 == ascii[i])
		{
			printf("%c", ascii[i]);
			
		}
	}
}
