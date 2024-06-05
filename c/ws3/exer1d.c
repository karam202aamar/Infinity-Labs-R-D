#include <stdio.h>
#include <stdlib.h>



void SumLinefunc(int *arr,int  row , int column, int *arrsum);

int main() {

	int i,row,column; 
	int *ptr1 , *ptr2 ;
	
	printf("please enter number of rows: \n");
	scanf("%d",&row);
	printf("please enter number of column: \n");
	scanf("%d",&column);

         ptr1 = (int *)malloc((row * column) * sizeof(int));
         ptr2 = (int *)malloc((row ) * sizeof(int));
         
	 printf("enter the values for the matrix : \n");
	 
	/*fill up the matrix*/   
	for (i = 0 ; i < row * column ; i++)
         {
		scanf("%d",ptr1+i);
	 }    	
        
         /* athol arraysum  */
         for (i = 0 ; i < row ; i++)
         {
		*(ptr2+i)=0;
	 }
	 
	SumLinefunc(ptr1,row,column,ptr2);
	
	 for(i=0 ; i<row ; i++)
	{
        	printf("The sum of the row %d is: %d\n" ,i+1,*(ptr2+i));
	}
	free(ptr1);
	free(ptr2);
	
    return 0;
}

void SumLinefunc(int *arr,int  row , int column, int *arrsum)
{
	int i; 
	for(i=0 ; i<(row*column) ; i++)
	{	
		*(arrsum+i/column) += *(arr+i);
	}
	
}

