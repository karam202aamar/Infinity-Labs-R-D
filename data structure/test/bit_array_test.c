/*******************************************************************************
 * Project: Data Structures - Bit Array
 * Date: 02/08/22
 * Name: 
 * Reviewer:
 * Version: 1.0
*******************************************************************************/
#include "bit_array.h"

#include <stdio.h> /*printf*/
#include <string.h> /*memcmp*/

static void BitSetAllTest();
static void SetOnSetOffTest();
static void BitSetTest();
static void FlipTest();
static void MirorrTest();
static void RotateTest();
static void CountTest();
static void ToStringTest();
static void BitArrayIsOffTest();
static void BitArrayLUTCountOnTest();


/*****************************************************************************/
int main()
{
	BitSetAllTest();
	SetOnSetOffTest();
	BitSetTest();
	FlipTest();
	MirorrTest();
	RotateTest();
	CountTest();
	ToStringTest();
	BitArrayIsOffTest();
	BitArrayLUTCountOnTest();
	
	return 0;	
}
/*****************************************************************************/
static void BitSetAllTest()
{
	bit_arr_ty bit_arr = 0;
	bit_arr = BitArraySetAll(bit_arr);	
	
	if(0xffffffffffffffff == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArraySetAll failed\n");
	}
	
	bit_arr = BitArrayResetAll(bit_arr);
	if(0 ==bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayResetAll failed\n");
	}
}
/*****************************************************************************/
static void SetOnSetOffTest()
{
	bit_arr_ty bit_arr = 0;
	bit_arr = BitArraySetOn(bit_arr, 1);	
	
	if(2 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArraySetOn failed\n");
	}
	
	bit_arr = BitArraySetOff(bit_arr ,1);
	if(0 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArraySetOff failed\n");
	}
}
/*****************************************************************************/
static void BitSetTest() 
{
	bit_arr_ty bit_arr = 0;
	bit_arr = BitArraySetBit(bit_arr, 4 , 4);	
	
	if(16 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArraySetBit failed\n");
	}
}
/*****************************************************************************/
/*
static void GetValTest()
{
	bit_arr_ty bit_arr = 4;
	bit_arr = BitArrayGetVal(bit_arr, 3);	
	
	if(1 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayGetVal failed\n");
	}
}
*/
/*****************************************************************************/
static void FlipTest()
{
	bit_arr_ty bit_arr = 0xf0f0f0f0f0f0f0f0;
	bit_arr = BitArrayFlip(bit_arr, 4);	
	
	if(0xf0f0f0f0f0f0f0e0 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayFlip failed\n");
	}
}
/*****************************************************************************/
static void MirorrTest()
{
	bit_arr_ty bit_arr = 0xf0f0f0f0f0f0f0f0;
	bit_arr = BitArrayMirror(bit_arr);	
	
	if(0x0f0f0f0f0f0f0f0f == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayMirror failed\n");
	}
}
/*****************************************************************************/
static void RotateTest()
{
	bit_arr_ty bit_arr = 0xf;
	bit_arr = BitArrayRotateRight(bit_arr, 4);	
	
	if(0xf000000000000000 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayRotateRight failed\n");
	}
	
	bit_arr = 0xf000000000000000;
	bit_arr = BitArrayRotateLeft(bit_arr, 4);	
	
	if(0xf== bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayRotateLeft failed\n");
	}
}
/*****************************************************************************/
static void CountTest()
{
	/*  0xf = 0x0000000f */
	bit_arr_ty bit_arr = 0xf;
	bit_arr = BitArrayCountOn(bit_arr);	
	
	if(4 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayCountOn failed\n");
	}
	
	bit_arr = 0xf00000000;
	bit_arr = BitArrayCountOff(bit_arr);	
	
	if(60 == bit_arr)
	{
		NULL;
	}
	else
	{
		printf("BitArrayCountOff failed %ld\n", bit_arr);
	}
}
/*****************************************************************************/
static void ToStringTest()
{
	bit_arr_ty bit_arr = 6;
	char str_to_set[64];
	char* str_to_test = "0000000000000000000000000000000000000000000000000000000000000110";
	
	if(0 == memcmp(BitArrayToString(bit_arr, str_to_set) , str_to_test , 64))
	{
		NULL;
	}else
	{
		printf("BitArrayToString failed\n");
	}
}
/*****************************************************************************/
static void BitArrayIsOffTest()
/* argu: bit_arr_ty bit_array, size_t index */
{
	bit_arr_ty bit_arr = 6;  /* 0110 */
	size_t index_to_check1 = 1;
	size_t index_to_check2 = 2;
	
	if(1 == BitArrayIsOff(bit_arr,index_to_check1) && 0 == 	
					BitArrayIsOff(bit_arr,index_to_check2))
	{
		NULL;
	}else
	{
		printf("BitArrayIsOff failed\n");
	}
}

/*****************************************************************************/
static void BitArrayLUTCountOnTest()
{
	bit_arr_ty test = 3;
	bit_arr_ty num = 0;
	
	num = BitArrayLUTCountOn(test);
	if(num == BitArrayCountOn(test))
	{
		NULL;
	}else
	{
		printf("BitArrayLUTCountOn failed\n");
	}
			
}
/*****************************************************************************/









