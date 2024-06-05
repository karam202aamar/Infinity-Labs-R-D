#include <stdio.h>
#include <stdlib.h>

int main()
{
	/*last argument for override*/
	setenv("MYENV", "hello from enviroment variable", 1);
	printf("RESULT : %s\n", getenv("MYENV"));
	return 0;
}
