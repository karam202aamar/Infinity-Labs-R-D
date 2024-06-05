#include <stdio.h>

int main()
{
	char ch = ' ';
	
	system("stty -icanon -echo");
	
	while(ch != 27)	
	{	
		scanf("%c",&ch);
		
		if(ch == 'A')
		{
			printf("A-pressed\n");    
		}
 			   
		else if(ch == 'T')
		{
			printf("T-pressed\n");       
 		}	
 			
 		else if(ch == 27)
 		{
 			system("stty icanon echo");
 		}
	}
	system("stty icanon echo");
	
	return 0;
}


