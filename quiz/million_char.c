/******************************************************************************/
#include <stdio.h>  /* print */
/******************************************************************************/
static void NumOfCalls(char x);
static int SetOnBits(long num);
/******************************************************************************/
int main()
{
	long x = 15;
	
	printf(" q2 num of set bits is: %d \n", SetOnBits(x));
	
	return 0;
}
/******************************************************************************/
static void NumOfCalls(char x)
{
	static int LUT[256];
	static char Most_Freq = 0;
	
	LUT[Most_Freq] = 1;
	
	if(0 == x)
	{
		printf("most called char is %c num of calls is %d ",
						      Most_Freq,LUT[Most_Freq]);
	}else
	{
		LUT[x] = LUT[x] + 1;
		
		if(LUT[x] > LUT[Most_Freq])
		{
			Most_Freq = x;
		}
	}
}
/******************************************************************************/
static int SetOnBits(long num)
{
	int count = 0;
	
	/* how much i have to turn off right most set bit */
	while(num)
	{
		num = num & (num-1);
		count++;
	}
	return count; 
}
/******************************************************************************/
