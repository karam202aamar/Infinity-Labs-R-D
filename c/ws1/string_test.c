#include <stdio.h>
#include "string.h"
#include <string.h>
#include <assert.h>

int test_strcmp(const char* str1, const char* str2);
int test_strlenght(const char* str);

int main()
{
 char str1[100];
 char str2[100];
 
 printf("enter the first string:  ");
 fgets(str1,sizeof(str1),stdin);
 printf("enter the second string:  ");
 fgets(str2,sizeof(str2),stdin);
 
 if(test_strcmp(str1,str2)==1)
 {
  printf("\n i have the same functions in comparing function\n");
 }else {
  assert(strcmp(str1,str2)==StrCmp(str1,str2));
 
 }
 
 
 if(test_strlenght(str1)==1)
 {
  printf("\n strlen works \n");
 }else { assert(strlen(str1)==StrLen(str1));
 }
 
 
 return 0 ;
}
 
int test_strlenght(const char* str)
{
 if(strlen(str)==StrLen(str))
 {
  return 1; 
 }
 else
 {
  return 0 ; 
  assert(0);
 }
}


int test_strcmp(const char* str1, const char* str2)
{
 if(strcmp(str1,str2)==StrCmp(str1,str2))
 {
  return 1; 
 }
 else
 {
  return 0 ;
 }
}

