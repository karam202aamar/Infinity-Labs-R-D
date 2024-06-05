#include <stdio.h> /* printf */

#define NUMOFSOLDIERS 100

int main()
{
  
  int sword = 1;
  int counter = 0;
  int soldiers_alive = 100;
  int array[NUMOFSOLDIERS];
  int i = 0;
  
  for ( i=0 ; i < soldiers_alive; i++)
  {
    array[i] = 1;
  }
  
  i = 0;

  while (soldiers_alive > 1)
  {
    
    
    if (array[i] == 0)
    {
      ++i;
       if (i > NUMOFSOLDIERS - 1)
    {
    	i = 0;
    }
      continue;
    }
    
    if ((sword + counter) % 2 == 0)
    {
    	array[i] = 0;
    	--soldiers_alive;
    }
    ++i;
    ++counter;
    
    if (i > NUMOFSOLDIERS - 1)
    {
    	i = 0;
    }
  }
	
	i = 0;

  for (i = 0; i < NUMOFSOLDIERS; ++i)
  {
    printf("%i ", array[i]);
  }
  
  printf("\n");
  
  for (i = 0; i < NUMOFSOLDIERS; ++i)
  {
  	printf("%i ", i);
  }
  
printf("\n");
return 0;
}
