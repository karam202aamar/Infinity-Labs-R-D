#include <stdio.h>  /* print */
/******************************************************************************/
void Permutations(char* str, int size);
char *CircularMove(char* str, int moves, int size);
/******************************************************************************/
int main()
{
	char str[3] = {'A', 'B', 'C'};
	Permutations(str, 3);
	
	return 0;
}
/******************************************************************************/
void Permutations(char* str, int size)
{
	int i;
	char *tmp_str = str;
	int first_index, last_index;
	char tmp; 
	
	for(i = 0; i < size; ++i)
	{
		tmp_str = CircularMove(tmp_str, i, size);
		first_index = 0;
		last_index = size - 1;
		
		printf("%s ",tmp_str);
	
		
		while(first_index < last_index)
		{
			tmp = tmp_str[first_index];
			tmp_str[first_index] = tmp_str[last_index];
			tmp_str[last_index] = tmp;
			
			printf("%s ",tmp_str);
			
			++first_index;
			--last_index;
		}
	}
}
/******************************************************************************/
char *CircularMove(char* str, int moves, int size)
{
	int i, j;
	char tmp; 
	
	tmp = str[0];
	
	for(i = 0; i < (size - 1); ++i)
	{
		str[i] = str[i+1];
	}
	
	str[size - 1] = tmp;
	
	return str;
}
/******************************************************************************/
#if 0
	for(i = 0; i < moves; ++i)
	{
		tmp = str[size - 1]; 
		
		for(j = 0; j < moves; ++j)
		{
			str[i + 1] = str[i];
		}
		str[i] = tmp;
	}
	#endif
