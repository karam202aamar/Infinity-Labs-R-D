#include <stdio.h>  /* prints*/

int main()
{
int i=0,j=0; 


/*first */
 int arr1[3][4] = {0, 1 ,2 ,3 ,4 , 5 , 6 , 7 , 8 , 9 , 10 , 11};
 
 
 /*second*/
 
 int arr2[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
 
 
  /*third*/
 int arr3[3][4];
 
 for( i = 0; i < 3; i++)
 {
	for( j = 0; j < 4; j++)
	{
        	scanf("%d",arr3[i][j]);
	}
 }
 
}
