/******************************************************************************
 * Project: Worksheets 10 & 11 - "Word Boundry / Atoi & Itoa"
 * Date: 27/7/22
 * Name: 
 * Reviewer: 
 * Version: 1.0
 * ***************************************************************************/

#ifndef __EX1_H_ILRD__
#define __EX1_H_ILRD__

/*TODO: include undefined behavior in each function */

/* Sets contiguous n bytes of memory to a char of the user's choice */
void *Memset(void *dest, int char_to_set, size_t num_of_bytes); 

/* Copies n bytes of memory from one void pointer to the next */ 
void *Memcpy(void *dest, const void *src, size_t num_of_bytes);

/* Similar to Memcpy, but allows for copying of overlapping data */ 
void *Memmove(void *dest, const void *src, size_t num_of_bytes);

/* Converts a string to an integer where possible, otherwise returns 0 */
int Atoi(const char *str);

/* Converts a string to an integer in a base of the user's choice (up to 36) */
int AtoiBase(const char *str, size_t base);

/* Converts an integer to a string */
void Itoa(int num, char* str);

/* Converts an integer to a string in a base of the user's choice (up to 36) */
void ItoaBase(int num, char* str, size_t base);

/* Prints out letters that appear in str1 & str2, but not in str3 */
void PrintCommonLetters(const char *str1, size_t size1,
                  const char *str2, size_t size2,
                  const char *str3, size_t size3);

/* Returns 1 if a system is little-endian, 0 otherwise */
int IsLittleEndian(void);
#endif
