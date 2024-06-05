#include <stdio.h>  /* printf() */
#include <stdlib.h> /* system() */

#define ASCII 256
#define ESC 27

void Apressed()
{
	puts("A-pressed");
}

void Tpressed()
{
	puts("T-pressed");
}

void AnyPressed()
{
/* Does nothing :) */
}
typedef void (*Ascii_List)();

static void Implement()
{	
char input_key = '\0';
	Ascii_List KeyValue[ASCII];
	int index = 0;

	/* tfunction creates the Ascii_list 
	we defined in *typedef* */
	for(index = 0; index < ASCII ; ++index)
	{
		KeyValue[index] = AnyPressed;
	}
	
	KeyValue['A'] = Apressed;
	KeyValue['T'] = Tpressed;
	system("stty -icanon -echo");
	
	while(input_key != ESC)	
	{	
		scanf("%c",&input_key);
		KeyValue[input_key]();
	}

	system("stty icanon echo");
	
}



int main()
{
	Implement();
	return 0;
}

