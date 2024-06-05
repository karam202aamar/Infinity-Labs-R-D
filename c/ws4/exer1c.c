#include <stdio.h> /* printf */
#include <stdlib.h> /* typedef */

#define SIZE 127
#define ESC 27

typedef void (*input)(void); /* pointer to func takes void argument and returns void argument  */

void Default(void);
void PrintAfunc(void);
void PrintTfunc(void);
void Exitprogram(void); 

int main()
{

int i;
char ch = ' ';
input inputArray[SIZE];

for(i = 0 ; i<SIZE ; i++)
{
	inputArray[i] = Default;
}

inputArray['a'] = PrintAfunc;
inputArray['A'] = PrintAfunc;
inputArray['t'] = PrintTfunc;
inputArray['T'] = PrintTfunc;
inputArray[ESC] = Exitprogram;

system("stty -icanon -echo");

while(1)
{
	scanf("%c",&ch);
	inputArray[ch]();
}

return 0; 
}

void Default(void)
{
	return;
}
void PrintAfunc(void) 
{
	printf("A-pressed\n");
}

void PrintTfunc(void)
{
	printf("T-pressed\n");
}

void Exitprogram(void) 
{ 
	system("stty icanon echo"); /* cancel then exit */
 	exit(0); 
}


		

	

