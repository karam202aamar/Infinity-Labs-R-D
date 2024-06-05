#include <stdio.h>  /* print */
#include <string.h>  /* strlength */
/******************************************************************************/
void reverseFunc(char str1[],int length);
/******************************************************************************/
int main()
{ 

	return 0;
}
/******************************************************************************/
void reverseFunc(char str1[],int length)
{
	int word_start,word_end,i,index = 0;
	char reversed[length];
	
	word_start = length - 1;
	word_end = length - 1;
	
	while(word_start > 0)
	{
		if(str1[word_start] == ' ')
		{
			i = word_start + 1 ;
			
			while(i <= word_end)
			{
				reversed[index] = str1[i];
				i++;
				index++;
			}
			
			reversed[index++] = ' ';
			word_end = word_start - 1;
		}
		word_start--;
	}
	/* last word*/ 
	for(i = 0 ; i <= word_end ; i++)
	{
		reversed[index] = str1[i];
		index++;	
	}
	reversed[index] = '\0';
}
/******************************************************************************/
