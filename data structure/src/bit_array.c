#include <stdio.h>  /* print */
#include <assert.h>
#include <stdlib.h>

#include "bit_array.h"

#define LEFT_32_BITS 18446744069414584320
#define RIGHT_32_BITS 4294967295

#define LEFT_16_BITS 18446462603027742720
#define RIGHT_16_BITS 281470681808895

#define LEFT_8_BITS 18374966859414961920
#define RIGHT_8_BITS 71777214294589695

#define LEFT_4_BITS 17361641481138401520
#define RIGHT_4_BITS 1085102592571150095

#define LEFT_2_BITS 14757395258967641292
#define RIGHT_2_BITS 3689348814741910323

#define LEFT_1_BITS 12297829382473034410
#define RIGHT_1_BITS 6148914691236517205

#define NUMBERS_IN_BYTE 255

static size_t *LutInitCountOn();
static size_t *LutInitMirror();

enum State {ENTER= 0 , NO_PERMISSION = 1};

/*****************************************************************************/
/** typedef size_t bit_arr_ty**/ 
bit_arr_ty BitArraySetAll(bit_arr_ty bit_array)
{
	return bit_array = ~(bit_array & 0);

}
/*****************************************************************************/
bit_arr_ty BitArrayResetAll(bit_arr_ty bit_array)
{
	bit_array = 0;
	return bit_array;
}
/*****************************************************************************/
bit_arr_ty BitArraySetOn(bit_arr_ty bit_array, size_t index)
{
	size_t mask = 1;
	mask <<= index;
	bit_array |= mask;
	
	return bit_array;
}
/*****************************************************************************/
bit_arr_ty BitArraySetOff(bit_arr_ty bit_array, size_t index)
{
	size_t mask = 1;
	mask <<= index;	
	mask = ~mask;
	bit_array &= mask;
	
	return bit_array;
}
/*
bit_arr_ty BitArraySetOff(bit_arr_ty bit_array, size_t index)
{

	size_t mask = 1;
	
	assert(BITES_IN_SIZE_T > index);
	
	mask <<= index ;
	
	return (bit_array ^= mask);
}
*/
/*****************************************************************************/
bit_arr_ty BitArraySetBit(bit_arr_ty bit_array, size_t index, int val_to_set)
{
	if(val_to_set > 1)
	{
		val_to_set = 1;	
	}
	val_to_set <<= index;
	
	if(val_to_set)
	{
		return bit_array | val_to_set;
	}
	else
	{
		return bit_array & val_to_set;
	}	
}

/*****************************************************************************/
int BitArrayGetVal(bit_arr_ty bit_array, size_t index)
{
	size_t mask = 1;
	mask <<= index;	
	
	if(mask & bit_array)
	{
		return 1; 
	}
	else
	{
		return 0;
	}
}
/*****************************************************************************/
bit_arr_ty BitArrayFlip(bit_arr_ty bit_array, size_t index)
{
	size_t mask = 1;
	mask <<= index;	
	bit_array = bit_array ^ mask;
	
	return bit_array;
}
/*****************************************************************************/
bit_arr_ty BitArrayMirror(bit_arr_ty bit_array)
{
	/* left_32_bits contains mask 1 32 time the 0 32 times te & give you 1 
	where you have one and zero where you have zero  in original */
/*
	bit_array = ((bit_array & LEFT_32_BITS) >> 32) | 
					((bit_array & RIGHT_32_BITS) << 32) ;
					
	bit_array = ((bit_array & LEFT_16_BITS) >> 16) | 
					((bit_array & RIGHT_16_BITS) << 16) ;
					
	bit_array = ((bit_array & LEFT_8_BITS) >>   8) | 
					((bit_array & RIGHT_8_BITS)  <<  8) ;
					
	bit_array = ((bit_array & LEFT_4_BITS) >>   4) | 
					((bit_array & RIGHT_4_BITS)  <<  4) ;
					
	bit_array = ((bit_array & LEFT_2_BITS) >>   2) | 
					((bit_array & RIGHT_2_BITS)  <<  2) ;
					
	bit_array = ((bit_array & LEFT_1_BITS) >>   1) |
					 ((bit_array & RIGHT_1_BITS)  <<  1) ;
	*/
	return bit_array;
}
/*****************************************************************************/
bit_arr_ty BitArrayRotateRight(bit_arr_ty bit_array, size_t shift)
{
	size_t mask = 0;
	mask = mask | (bit_array << (64 - shift));
	bit_array = bit_array >> shift;	
	bit_array = bit_array | mask; 
	
	return bit_array;
}
/*****************************************************************************/
bit_arr_ty BitArrayRotateLeft(bit_arr_ty bit_array, size_t shift)
{
	size_t mask = 0;/*TODO: same as for right rotate.*/
	mask = mask | (bit_array >> (64 - shift));
	bit_array = bit_array << shift;
	bit_array = bit_array | mask; 
	
	return bit_array;
}
/*****************************************************************************/
size_t BitArrayCountOn(bit_arr_ty bit_array)
{
	size_t count = 0; 
	size_t mask = 1;
	
	while (bit_array)
	{
		if(bit_array & mask)
		{
			++count;
		}
		bit_array >>= 1;
	}
	
	return count;
}
/*
dere5 2 
size_t BitArrayCountOn(bit_arr_ty bit_array)
{
    size_t count = 0;
   
    while(bit_array)
    {
    	bit_array = bit_array & (bit_array - 1);

        ++count;
    }
    
    return count;
}

*/
/*****************************************************************************/
size_t BitArrayCountOff(bit_arr_ty bit_array)
{
	size_t count = 0; 
	size_t mask = 1;
	size_t i;
	
	for(i = 0; i< 64; i++)
	{
		if((bit_array & mask) == 0)
		{
			++count;
		}
		bit_array >>= 1;
	}
	return count;
}
/*****************************************************************************/
char *BitArrayToString(bit_arr_ty bit_array, char * str)
{
	size_t i;
	size_t mask = 1;
	char *str_ptr = str;
	mask = mask << 63;
	
	assert(str);
	
	for(i = 0; i< 64; i++)
	{
		if(mask & bit_array)
		{
			*str_ptr = '1';
		}
		else
		{
			*str_ptr = '0';
		}
		str_ptr++;
		 bit_array = bit_array << 1;
	}
	*str_ptr = '\0';
	
	return str;
}
/*****************************************************************************/
int BitArrayIsOff(bit_arr_ty bit_array, size_t index)
{
	size_t mask = 1;
	mask = mask << (index - 1);
	
	if(bit_array & mask)
	{
		return 0;
	}else
	{
		return 1;
	}
	
}
/*****************************************************************************/

size_t BitArrayLUTCountOn(unsigned char bit_array)
{
	
	static size_t *ptr = NULL;
	ptr = LutInitCountOn();
	return ptr[bit_array];

}
/*****************************************************************************/	
size_t * LutInitCountOn()
{
	size_t i;
	static size_t is_init ;
	static size_t ptr[NUMBERS_IN_BYTE]; 
	
	if(ENTER == is_init)
	{
		for(i = 0; i < NUMBERS_IN_BYTE; i++)
		{
			ptr[i] = BitArrayCountOn(i);
		}
		
		is_init = NO_PERMISSION;
	}
	return ptr;
}
/*****************************************************************************/	
unsigned char BitArrayLUTMirror(unsigned char bit_array)
{
	static size_t *ptr = NULL;
	ptr = LutInitMirror();
	return ptr[bit_array];
}
/*****************************************************************************/	
size_t * LutInitMirror()
{
	size_t i;
	static size_t is_init ;
	static size_t ptr[NUMBERS_IN_BYTE]; 
	
	if(ENTER == is_init)
	{
		for(i = 0; i < NUMBERS_IN_BYTE; i++)
		{
			ptr[i] = BitArrayMirror(i);
		}
		
		is_init = NO_PERMISSION;
	}
	return ptr;
}
/*****************************************************************************/	



















