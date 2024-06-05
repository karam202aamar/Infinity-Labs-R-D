#include <stdio.h>/*printf puts*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/

#include "cbuf.h"

#define TEST(res) ((SUCCESS != res) ? printf("%d failed\n",__LINE__) : puts(""))

typedef enum {SUCCESS = 0, FAILED} test_status_ty;

static void RunTest();
static test_status_ty CbufCreateAndDestroyTest();
static test_status_ty CbufFreeSpaceTest();
static test_status_ty CbufSizTest();
static test_status_ty CbufWriteAndReadTest();
static test_status_ty CbufIsEmptyTest();

static void DestroyAndSetNull(cbuf_ty **buffer);

/******************************************************************************/
int main()
{
	RunTest();

	return 0;
}

/******************************************************************************/
static void RunTest()
{
	TEST(CbufCreateAndDestroyTest());
	TEST(CbufFreeSpaceTest());
	TEST(CbufSizTest());
	TEST(CbufWriteAndReadTest());
	TEST(CbufIsEmptyTest());
}

/******************************************************************************/
static test_status_ty CbufCreateAndDestroyTest()
{
	size_t capacity = 3;
	cbuf_ty *cbuf = CbufCreate(capacity);
	
	DestroyAndSetNull(&cbuf);
	
	return SUCCESS;
}

/******************************************************************************/
static test_status_ty CbufFreeSpaceTest()
{
	size_t capacity = 20;
	size_t expected_frees_cpace_res = 20;
	cbuf_ty *cbuf = CbufCreate(capacity);
	size_t func_free_space_res = CbufFreeSpace(cbuf);
	
	/*since cbuf is empty, free space should be as capacity*/
	if(expected_frees_cpace_res != func_free_space_res)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	DestroyAndSetNull(&cbuf);
	
	return SUCCESS;
}

/******************************************************************************/
static test_status_ty CbufSizTest()
{
	size_t capacity = 3;
	cbuf_ty *cbuf = CbufCreate(capacity);
	size_t func_size_res = CbufSiz(cbuf);
	
	/*since cbuf is empty the size shoud be zero*/
	if(capacity != func_size_res)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	DestroyAndSetNull(&cbuf);
	
	return SUCCESS;
}

/******************************************************************************/
static test_status_ty CbufWriteAndReadTest()
{
	size_t capacity = 10;
	char *str= "DanaShapso";
	size_t str_len1 = strlen(str);
	char *str2 = "heey";
	size_t str_len2 = strlen(str2);
	char *expected_read_res = "Shapsoheey";
	char dest1[10] = {'\0'};
	char dest2[10] = {'\0'};
	ssize_t write_res = 0;
	ssize_t read_res = 0;
	size_t read_write_memcmp_res = 0;
	cbuf_ty *cbuf = CbufCreate(capacity);
	
	/*expected : cbuf will have DanaShapso*/
	write_res = CbufWrite(cbuf, str, str_len1);
	/*exepcted : dest1 to have Dana*/
	read_res = CbufRead(cbuf, dest1, str_len2);
	
	if(write_res != (ssize_t)str_len1 && read_res != (ssize_t)str_len2)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	/*first comparsion should be between Dana and Dana as strlen2 is 4*/
	read_write_memcmp_res = memcmp(str, dest1, str_len2);
	
	if(0 != read_write_memcmp_res)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	/*expected : cbuf will have heeyShapso*/
	write_res = CbufWrite(cbuf, str2, str_len2);
	
	if(write_res != (ssize_t)str_len2)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	/*expected : dest2 : Shapsoheey as the read offset starts at S*/
	read_res = CbufRead(cbuf, dest2, capacity);
	read_write_memcmp_res = memcmp(expected_read_res, dest2, capacity);
	
	if(0 != read_write_memcmp_res)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	DestroyAndSetNull(&cbuf);

	return SUCCESS;
}

/******************************************************************************/
static test_status_ty CbufIsEmptyTest()
{
	size_t capacity = 5;
	char *str= "Dana";
	size_t str_len = strlen(str);
	int expected_case1_res = 1;
	int expected_case2_res = 0;
	int is_empty_func_case1_res = -1;
	int is_empty_func_case2_res = -1;
	ssize_t write_res = 0;
	cbuf_ty *cbuf = CbufCreate(capacity);
	
	is_empty_func_case1_res = CbufIsEmpty(cbuf);
	
	if(is_empty_func_case1_res != expected_case1_res)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	write_res = CbufWrite(cbuf, str, str_len);
	is_empty_func_case2_res = CbufIsEmpty(cbuf);
	
	assert(write_res == (ssize_t)str_len);
	
	if(is_empty_func_case2_res != expected_case2_res)
	{
		DestroyAndSetNull(&cbuf);
		
		return FAILED;
	}
	
	DestroyAndSetNull(&cbuf);
		
	return SUCCESS;	
}

/****************************helper function***********************************/
static void DestroyAndSetNull(cbuf_ty **buffer)
{
	CbufDestroy(*buffer);
	*buffer = NULL;
}

