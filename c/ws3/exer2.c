#include <stdio.h>  /* prints*/
#include <stdlib.h>

enum Possibility{KILL=0,JUMP}; 

int joseProblem(int * array, int num);


int main()
{
	int i;
	int num_warriors;
	int *array=NULL;

	printf("please enter the number of warriors:");
	scanf("%d",&num_warriors);

	array=(int *)malloc(sizeof(int)*num_warriors);

	for(i=0;i<num_warriors;i++)
	{
		array[i]=i+1; 
	}
	printf("\n the winner is the player in the place : %d \n ",joseProblem(array,num_warriors)+1);
	
	
	
	return 0 ; 
}

int joseProblem(int * array, int size)
{
	int player_index=0; 
	int player_status=KILL; 
	
	while(array[player_index]!=player_index)
	{
		if(array[player_index]==size && player_status==KILL)   /* in the end of an array */
		{
			array[player_index]=array[0];
			player_status=JUMP;
		}
		if(array[player_index]==size && player_status==JUMP)  /* in the end of an array */
		{
			player_index=0;
			player_status=KILL;
		}
		
		if(player_status==KILL)
		{
			array[player_index]=array[array[player_index]];
			player_status=JUMP;
		}else
		{
			player_index=array[player_index];
			player_status=KILL;	
		}
	}
	return player_index;
	
	
}


