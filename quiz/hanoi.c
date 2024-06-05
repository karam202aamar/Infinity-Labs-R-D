#include <stdio.h>
/******************************************************************************/
void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);
/******************************************************************************/
int main()
{
	int n = 3;
	printf("DISK \n");
	TowerOfHanoi(n, 'A', 'B', 'C');
	
	return 0;
}
/******************************************************************************/
void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
	/* if I get to the last disk */
	if(0 == n)
	{
		printf("DISK %d moved from %c to %c \n", n + 1, from_rod, to_rod);
	}
	TowerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	
	printf("DISK %d moved from %c to %c\n", n, from_rod, aux_rod);
	
	TowerOfHanoi(n - 1, to_rod, aux_rod, from_rod);
}
/******************************************************************************/
