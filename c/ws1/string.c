#include <stdio.h>
#include "string.h"




 int StrLen(const char *s)
    {
       int count = 0;
       while(*s!='\0')
        {
        count++;
        s++;
        }
      
       return count;
    }
    
 int StrCmp(const char* str1, const char* str2)
    {
      int i , count=0;
      if(StrLen(str1)==StrLen(str2))
      {
        for (i=0;i<StrLen(str1);i++)
        {
          if(*str1==*str2)
          {
            count++;
          }
        }
            if(count==StrLen(str1))
             {
              return 0;
             }
        
      }
      else
      {
       return 1;
      } 
    }

 
