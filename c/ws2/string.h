#ifndef __STRING_H_ILRD__
#define __STRING_H_ILRD__

#include <stddef.h> /*size_t*/


/*returns length of str1. if str1 is NULL -> undefined behavior.*/
size_t StrLen(const char *str);

/*compares str1 and str2. if str1>str2, ret val>0.*/
/* if str1<str2, retu val<0. else, ret 0. */
int StrCmp(const char *str1, const char *str2);

/*copies the string pointed to by src, including the terminate null,*/
/* to the buffer pointed to by dest.*/
/*size of the destination string should be large enough to store the copied */
/*string. Otherwise, it may result in undefined behavior.*/
char * StrCpy(char * destination , char * source);

/*copies the string pointed to by src, including the terminate null,*/
/* to the buffer pointed to by dest. at most, num bytes of src are copied.*/
char *StrnCpy(char *dest, const char *src, size_t num);

/*compares the two strings str1 and str2*/
/*0 if str1 equal to str2, negative value if str1<str2, positive if str1>str2*/
/*if str1 or str2 == NULL, undefined behaviour*/
/*compares only the first num bytes of str1 and str2*/
int StrnCmp(const char *str1, const char *str2, size_t num);

/*performs a byte-by-byte comparison of the strings str1 and str2,*/
/*ignoting the case of the characters.*/
/*returns integer less than, equal or greater than zero.*/
int StrCaseCmp(const char * str1, const char * str2);

/*returns a pointer to the first occurrence of character num_ch in string str*/
char *StrChr(const char *str, int num_ch);

/*returns a pointer to a new string which is a duplicate of the string str*/
/*memory for new string is obtained with malloc and can be freed with free*/
char *StrDup(const char *str);

/*appends the src string to the dest string, */
/*over writing the terminating null byte at the end of dest and adds a */
/*termination null byte*/
char *StrCat(char *dest, const char *src);

/*appends the src string to the dest string, */
/*over writing the terminateng null byte at the end of dest and adds a */
/*termination null byte. will use at most num bytes from src*/
/*does not need to be null-terminated if it contains num or more bytes.*/
char *StrnCat(char *dest, const char *src, size_t num);

/*finds the first ocurrence of the substring needle in the string haystack*/
/*the terminating null bytes are not compared.*/
char *StrStr(const char *haystack, const char *neendle);

/*calculates the length in bytes of the initial segment of str which consist */
/*entirely of bytes in accept.*/
size_t StrSpn(const char *str, const char *accept);

char * ToLower(char* str);

#endif /*__STRING_H_ILRD__*/

