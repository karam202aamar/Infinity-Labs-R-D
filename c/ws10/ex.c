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

void TestFUNCTION(); 

#define IsLittleEndian1 (*(char*)&(x)==1)? printf("little "):printf("Big ") 
#define IsLittleEndian2 (1 & *(char *)"a")

#define ASCIIRANGE 255
 
#define ASCIILETTERS 'A' + 10

int main()
{
	TestFUNCTION();
	return 0;
}

void TestFUNCTION()
{
	char *str = "12345";
	char str_arr[5];
	size_t base = 10 ; 
	int number = 25;
	char *str1 = "abcd";
	char *str2 = "xbcr";
	char *str3 = "erbj";
	size_t sizestr = 4;
	
	printf("Atoi function test: the string we send %s \n" , str);
	printf("the value we get = %d\n", Atoi(str));
	
	printf("\nItoa function test: the number is %d \n" , number);
	Itoa(number , str_arr);
	printf("the value we get = %s\n", str_arr);
	
	printf("\nItoaBase function test: the number is %d & base 2\n" , number);
	ItoaBase(number , str_arr , 2);
	printf("the value we get = %s\n" , str_arr);

	printf("\nAToIBase function test: the string we send %s & base %lu \n",
								 str , base);
	printf("the value we get = %d\n", AtoiBase(str, base));	
	
	printf("\nthe function PrintCommonLetters output :");
	
	PrintCommonLetters(str1 , sizestr , str2 , sizestr , str3 , sizestr);
}

int Atoi(const char *str)
{ 
    int res = 0 , i;
 	/* i take the char of the string and convert it by ascii table*/
	for (i = 0; str[i] != '\0'; ++i)
	{
        	res = res * 10 + str[i] - '0';
        }
 
	return res;
}
	/* string to number */
int AtoiBase(const char *str, size_t base)
{
	/* final result */
	int result = 0;
	
	/* runner on the string */
	const char *str_tmp;
	
	size_t i , char_count=0 ;
	
	str_tmp = str;
	
	/* base range  */
	if (10 >= base)
	{
                      /* numbers i can display untill my base 
                         it will include just numbers(no letters)*/
		while(('0' <= *(str_tmp)) && (*(str_tmp) <= (char)('0' + base)))
		{
			++char_count;
			++str_tmp;
		}
	}
	else
		/* numbers i can display untill my base with letters too */
		while ((('0' <= *(str_tmp)) && (*(str_tmp) <= (char)('0' + 10)))
	||(('A' <= *(str_tmp)) && ((*str_tmp) <= (char)('A' + base - 10))))
		{ /* exmp base 12 i need 2 more steps from A */
			++char_count;
			++str_tmp;
		}
	}

	for(i = 0; i < char_count ; ++i)
	{
		/* calculate result */
		result = result * base;
		
		if (('0' <= str[i]) && (str[i] <= '9'))
		{
			/* calculate result */
			result +=  str[i] - '0';
		}
		else
		{
			/* take the value of the letter */
			result += str[i] - 'A' + 10;
		}
	}
	return result ;
}

void ItoaBase(int num, char* str, size_t base)
{
	int rem , count=0 , i=0 ;
   	char tmp;
   	
   	/* if the number is zero then zero char */	
	if (num == 0)
	{
        	str[i++] = '0';
		str[i] = '\0';
	}
	/* loop on the number */
	while (num != 0)
	{	
		/* i take the rest */
		rem = num % base;
		
		if(rem > 9)
		{
			str[i++] = (rem - 10) + 'A';
		}
			else
		{	/* then i have number until the base*/
			str[i++] = rem + '0';
		}
		count++;
		num = num/base;
	}
	
	count--;
	i=0;
	
 	while(i <= count)
 	{
 		tmp = str[i];
 		str[i] = str[count];
 		str[count] = tmp;
		i++;
		count--;
 	}
 	
}

void Itoa(int num, char* str)
{
	/* i call function ItoaBase with base 10*/
	ItoaBase(num,  str , 10);	
}

int IsLittleEndian(void)
{
	unsigned int x = 0x76543210;
	char *c = (char*) &x;
  	/* chech if i have this number at the first byte */
	if (*c == 0x10)
	{
		return 0;
	}
	else
	{
		return 1; 
	}
 
}

void PrintCommonLetters(const char *str1, size_t size1, const char *str2,
 			          size_t size2, const char *str3, size_t size3)
{
	size_t i = 0;
	int ascii_table[ASCIIRANGE];
	
	for(i=0 ; i < ASCIIRANGE ; i++)
	{
		ascii_table[i] = 0;
	}
	
	for (i = 0; i < size1; ++i)
	{
		ascii_table[(int)str1[i]] += 1;
	}
	
	for (i = 0; i < size3; ++i)
	{
		ascii_table[(int)str3[i]] = 0;
	}
	
	for (i = 0; i < size2; ++i)
	{
	
		if (1 == ascii_table[( int)str2[i]])
		{
			printf(" %c\n", str2[i]);
			ascii_table[(int)str2[i]] = 0;
		}
	}
}
