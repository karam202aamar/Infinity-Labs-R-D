#include <stdio.h>  /* print */
/******************************************************************************/
void Permutations(char* str, int size);
char *CircularMove(char* str, int moves, int size);
/******************************************************************************/
int main()
{
	char str[3] = {'A', 'B', 'C'};
	Permutations(str, 3);
}
/******************************************************************************/
void Permutations(char* str, int size)
{
	int i;
	char tmp_str[size];
	int first_index = 0;
	int last_index = size - 1;
	char tmp; 
	
	for(i = 0; i < size; ++i)
	{
		tmp_str = CircularMove(str, i, size);
		
		while(first_index > last_index)
		{
			tmp = tmp_str[first_index];
			tmp_str[first_index] = tmp_str[last_index];
			tmp_str[last_index] = tmp;
			
			printf("%s ",tmp_str);
		}
	}
}
/******************************************************************************/
char *CircularMove(char* str, int moves, int size)
{
	int i, j;
	char tmp; 
	
	for(i = 0; i < moves; ++i)
	{
		tmp = str[size - 1]; 
		
		for(j = 0; j < moves; ++j)
		{
			str[i + 1] = str[i];
		}
		str[i] = tmp;
	}
	return str;
}
/******************************************************************************/
