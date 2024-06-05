#include <stdio.h>
#include <stdlib.h>

int main()
{
	char ch = ' ';
	
	system("stty -icanon -echo");
	
	scanf("%c",&ch);
	
	switch(ch)	
	{	
		case 'A': 
		{
			printf("A-pressed\n");  
			break;  
 		}
 			   
		case 'T':
		{
			printf("T-pressed\n");   
			break;     
 		}	
 			
 		case 27:
 		{
 			system("stty icanon echo");
 			break; 
 		}
	}
	
	
	return 0;
}


