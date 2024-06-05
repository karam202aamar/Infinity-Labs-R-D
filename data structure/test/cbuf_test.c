/*******************************************************************************
 * Project: Data Structures - Circular Buffer
 * Date: 16/08/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0	
*******************************************************************************/
#include <stdio.h>/*printf*/
#include <string.h>/*memcmp*/
/******************************************************************************/
#include "cbuf.h" 
/******************************************************************************/
void CreateDestoyTest();
void SizeTest();
void FreeSpaceTest();
void WriteTest();
void WriteReadTest();
void IsEmptyTest();
/******************************************************************************/
int main()
{
	CreateDestoyTest();
	SizeTest();
	FreeSpaceTest();
	WriteTest();
	WriteReadTest();
	IsEmptyTest();
	
	return 0;
}
/******************************************************************************/
void CreateDestoyTest()
{
	cbuf_ty *buff = NULL;
	size_t space = 3;
	
	buff = CBufCreate(space);
	CBufDestroy(buff);
	
}
/******************************************************************************/
void SizeTest()
{
	cbuf_ty *buff = NULL;
	size_t size = 0;
	size_t space = 3;
	
	buff = CBufCreate(space);
	size = CbufSize(buff);
	
	if(3 != size)
	{
		printf("SizeTest : failed got val - %ld\n", size);
	}
	
	CBufDestroy(buff);
}
/******************************************************************************/
void FreeSpaceTest()
{
	cbuf_ty *buff = NULL;
	size_t space = 6;
	
	buff = CBufCreate(space);
	space = CBufFreeSpace(buff);
	
	if(6 != space)
	{
		printf("SizeTest : failed got val - %ld\n", space);
	}
	
	CBufDestroy(buff);
}
/******************************************************************************/
void WriteTest()
{
	cbuf_ty *buff = CBufCreate(6);
	char *str1 = "hah";
	size_t space = 0;
	
	CbufWrite(buff, str1, 3);
	
	space = CBufFreeSpace(buff);
	
	if(3 != space)
	{
		printf("WriteTest : failed got val - %ld\n", space);
	}
	
	CBufDestroy(buff);
}
/******************************************************************************/
void WriteReadTest()
{
	cbuf_ty *buff = CBufCreate(10);
	char *str1 = "1234567890";
	char str2[10] = {'\0'};
	ssize_t status  = 0;
	
	CbufWrite(buff, str1, 7);

	status = CbufRead(buff, str2, 3);

	if(3 !=status)
	{
		printf("WriteReadTest : failed got val - %ld %s\n", status, str2);
	}
	CBufDestroy(buff);
}
/******************************************************************************/
void IsEmptyTest()
{
	cbuf_ty *buff = CBufCreate(10);
	char *str1 = "1234567890";
	ssize_t status  = 0;
	
	CbufWrite(buff, str1, 0);

	status = CbufIsEmpty(buff);
	if(status != 1)
	{
		printf("IsEmptyTest : failed got val - %ld\n", status);
	}
}
/******************************************************************************/

