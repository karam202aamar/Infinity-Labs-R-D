/*******************************************************************************
 * Project: Data Structures - Bit Array
 * Date: 02/08/22
 * Name: HRD26
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/

#ifndef __BIT_ARRAY_H_ILRD__
#define __BIT_ARRAY_H_ILRD__

#include <stddef.h> /* size_t */

typedef size_t bit_arr_ty;

/* Turns on all bits */
/* Time complexity: O(1) */
bit_arr_ty BitArraySetAll(bit_arr_ty bit_array);

/* Turns off all bits */
/* Time complexity: O(1) */
bit_arr_ty BitArrayResetAll(bit_arr_ty array);

/* Turns on the bit in given index */
/* Time complexity: O(1) */
bit_arr_ty BitArraySetOn(bit_arr_ty bit_array, size_t index);

/* Turns off the bit in given index */
/* Time complexity: O(1) */
bit_arr_ty BitArraySetOff(bit_arr_ty bit_array, size_t index);

/* Set the bit in given index to val_to_set */
/* Time complexity: O(1) */
bit_arr_ty BitArraySetBit(bit_arr_ty bit_array, size_t index, int val_to_set);

/* Returns the bit in given index */
/* Time complexity: O(1) */

int BitArrayGetVal(bit_arr_ty bit_array, size_t index);

/* Flips the bit in given index */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
bit_arr_ty BitArrayFlip(bit_arr_ty bit_array, size_t index);

/* Mirrors the bit array */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
bit_arr_ty BitArrayMirror(bit_arr_ty bit_array);

/* Rotates right the bit_array shift times */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
bit_arr_ty BitArrayRotateRight(bit_arr_ty bit_array, size_t shift);

/* Rotates left the bit_array shift times */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
bit_arr_ty BitArrayRotateLeft(bit_arr_ty bit_array, size_t shift);

/* Counts the number of bits that are on in the bit_array */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
size_t BitArrayCountOn(bit_arr_ty bit_array);

/* Counts the number of bits that are off in the bit_array */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
size_t BitArrayCountOff(bit_arr_ty bit_array);

/* Returns a string representing the bit array */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
char *BitArrayToString(bit_arr_ty bit_array, char * str);

/* Returns 1 if the bit in given index is off, 0 otherwise */
/* Time complexity: O(1) */
/* Undefined behavior: if the bit_array is uninitialized */
int BitArrayIsOff(bit_arr_ty bit_array, size_t index);

/* Mirrors the bit array */
/* Time complexity:  O(sizeof(bit_arr_ty))*/
/* Undefined behavior: if the bit_array is uninitialized */
unsigned char BitArrayLUTMirror(unsigned char bit_array);

/* Counts the number of bits that are on in the bit_array */
/* Time complexity:  O(sizeof(bit_arr_ty))*/
/* Undefined behavior: if the bit_array is uninitialized */
size_t BitArrayLUTCountOn(unsigned char bit_array);

#endif /* __BIT_ARRAY_H_ILRD__ */


