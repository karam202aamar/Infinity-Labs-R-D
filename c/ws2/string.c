#include <stdio.h>  /* prints*/
#include <stddef.h> /* for size_t*/
#include <stdlib.h> /* for allocation */
#include <assert.h> /*assert*/
#include <ctype.h>/*Comprasions*/

#include "string.h" /* my header*/



size_t StrLen(const char *s)
{	
	size_t count=0;

	assert(s != NULL);

	while(*s!='\0')
	{
	count++;
	s++;
	}
	return count; 
}

/* 
char * ToLower(char* str)
{
	assert(str != NULL);
	
	while(*str)
	{
		if(*str >= 'A' && *str <= 'Z') 
		{
        	*str=*str + 32;
       	         return str;
		}
   	 str++; 
	}
	return str; 
}
helping function */

char * StrCpy(char * destination , char * source)
{	
	char * ptr_return=destination;
	
	assert(destination != NULL && source!= NULL);
	
	while (*source!= '\0')
	{
	*destination= *source;
        destination++;
        source++;
	}
    
	*destination= '\0';
	return ptr_return; 
}

char * StrNCpy(char* str1 , char* str2 , size_t n)
{
	assert(str1 != NULL && str2!= NULL);	 
	
	while (*str1  && n--)
	{
        *str2= *str1 ;
        str1++;
        str2++;
	}
	return str2; 
}

int StrNCmp(char* str1 , char* str2 , size_t n)
{	
	size_t counter=0;
	assert(str1 != NULL && str2!= NULL);
	
	while (*(str1+counter)==*(str2+counter) &&
	                         *(str1+counter) && *(str2+counter) && n--)
	{	
    		++counter;
        }
	return (*(str1+counter)-*(str2+counter));
}

int StrCaseCmp(const char * str1, const char * str2)
{
        int counter = 0;


        assert(str1 != NULL && str2 != NULL);
        
        while ( *(str1 + counter) && tolower(*(str1 + counter))==tolower(*(str2 + counter)))
        {
                ++counter;
        }
        return *(str1 + counter) - *(str2 + counter);
}



char *StrChr(const char *s , int c)
{       
	char* ptr_return=NULL;
	
	assert(s != NULL );
	
	while (*s != '\0')
	{
           if (*s==c) 
           {
         	  ptr_return=StrDup(s);
         	  return ptr_return;
	   }
	   s++;
	}
	return NULL;
}

char *StrDup(const char *s)
{
	
	char* ptr_copy=(char*)malloc(sizeof(char)*StrLen(s));
	char* ptr_return=ptr_copy;
	
	assert(s != NULL );
	
	if(ptr_copy == NULL) /*allocation failed*/
	{
		return NULL;
	}else{
		while(*s != '\0')
		{
			*ptr_copy=*s;
			 ptr_copy++;
			 s++;
		}
	     }
	
	return ptr_return; 
} 

char *StrCat(char *dest, const char *src)
{	
	char* ptr_return=dest;
	assert(dest != NULL && src!= NULL);
	
	dest+= StrLen(dest); /*here i get to the end*/
	         
	while(*src != '\0')
	{
	*(dest++) = *(src++);	 
	}
	*dest='\0';
	
	return ptr_return;
}

char *StrnCat(char *dest,const char *src,size_t n)
{
	char* ptr_return=dest;
	
	assert(dest!= NULL && src!= NULL);   
	dest+= StrLen(dest); /*here i get to the end*/ 
	         
	while(*src != '\0' && n--)
	{
	*(dest++) = *(src++);
	}
	
	*dest='\0';
	
	return ptr_return;
}

char *StrStr(const char *haystack , const char *needle)
{	
	
	char* needle_un=(char*)needle;
	char* haystack_un=NULL;
	size_t count; 
	
	assert(haystack!= NULL && needle!= NULL);
	
	while(*haystack!='\0')	
	{	
		if(*haystack==*needle)
		{	
			count=0;
			needle=needle_un;
			haystack_un=(char*)haystack;
			while(*needle!='\0' && *needle==*haystack_un)
			{
				++count;
				++needle; 
				++haystack_un;
			}
			if(StrLen(needle)==count)
			{
				return 	(char*) haystack;
			}
			
		}
		
		haystack++;
		needle++; 		
	}
	return NULL; 
}



size_t StrSpn(const char *str, const char *accept)
{	
	size_t count=0;
	
	while((*str) && StrChr(accept,*str)!=NULL)
	{
	count++; 
	str++;
	}
	return count ; 		
}

/*
char *StrTok(char *s, const char *delim)
{
	assert(s!= NULL && delim!= NULL);
	
	char* ptr_return=NULL;
	
	while(*s!=*delim)
	{
		*ptr_return=*s;
		 s++;
	}
	return StrDup(ptr_return);
} 
*/



