#if 0

#include <stdio.h>	/*	printf, fgetc, fopen, fclose, rewind	*/
#include <string.h> /*	strcmp, memcpy							*/
#include <errno.h>	/* errno									*/
#include <stdlib.h> /* malloc, free								*/
#include <stddef.h> /* wchar_t									 */

#include "hash_table.h"

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YELL "\x1B[33m"
#define CYN "\x1B[36m"
#define DFLT_COL "\x1B[0m"
#define BOLD "\x1B[1m"
#define DFLT "\x1B[m"

#define PRINT_IF_FAILED(FUNCT)                       \
	if (FUNCT())                                     \
	{                                                \
		printf(RED #FUNCT " has failed\n" DFLT_COL); \
		++counter_funct_failed;                      \
	}

#define PRINT_IF_ALL_TST_SUCCEED()                               \
	if (0 == counter_funct_failed)                               \
	{                                                            \
		printf(BOLD GRN "ALL TESTS SUCCEEDED!\n" DFLT DFLT_COL); \
	}

#define PRINT_END_OF_TEST_FILE() printf(BOLD CYN "End of %s\n\n" DFLT_COL \
											DFLT,                         \
										__FILE__);

#define PRINT_FAIL_IN_LINE() printf(YELL "fail in line %d\n" DFLT_COL, \
									(__LINE__ - 2));

#define CHECK_IF_AS_EXPECTED(RET_VAL, EXP_VAL, PRT_TYPE_ESC)                       \
	if ((EXP_VAL) != (RET_VAL))                                                    \
	{                                                                              \
		PRINT_FAIL_IN_LINE()                                                       \
		printf(#RET_VAL " = " PRT_TYPE_ESC ",\t" #EXP_VAL " = " PRT_TYPE_ESC "\n", \
			   (RET_VAL), (EXP_VAL));                                              \
		DESTROY_RESOURCES()                                                        \
		return TEST_FAIL;                                                          \
	}

#define CREATE_HASH_TABLE()                \
	ht_ty *hash_tab = NULL;                \
	size_t capacity = 5;                   \
                                           \
	hash_tab = HTCreate(capacity, Modulo5, \
						CmpBetweenTwoInt); \
	if (NULL == hash_tab)                  \
	{                                      \
		PRINT_FAIL_IN_LINE()               \
                                           \
		return TEST_FAIL;                  \
	}

#define DESTROY_RESOURCES() \
	HTDestroy(hash_tab);    \
	hash_tab = NULL;

#define CREATE_RESOURCES()              \
	int data_to_ins[] =                 \
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; \
	int test_arr_size = 10;             \
	int exp_ret_val = 0;                \
	int i = 0;

#define INSERT_IN_HASH_TABLE(HASH_TAB, DATA_TO_INS_ARR, SIZE_ARR) \
	exp_ret_val = SUCCESS;                                        \
	for (i = 0; (SIZE_ARR) > i; ++i)                              \
	{                                                             \
		CHECK_IF_AS_EXPECTED(HTInsert((HASH_TAB),                 \
									  &(DATA_TO_INS_ARR)[i]),     \
							 exp_ret_val, "%d")                   \
	}

#define CAPACITY 53

#define CHARACTER_Anstrong 	197
#define CHARACTER_E_special 233
#define MAX_LENGTH_WORD		27

typedef enum test_status
{
	TEST_SUCCESS = 0,
	TEST_FAIL = 1
} test_status_ty;

enum status_function
{
	SUCCESS = 0,
	FAILURE = 1
};
enum boolean
{
	TRUE = 1,
	FALSE = 0
};

/* helper func - user functions */
/* receive a pointer to an integer as (void *) and returns integer modulo 5 */
static size_t Modulo5(void *integer);

/* compares between two integers (int) whose addresses are given as (void *) and
 returns a positive number, zero or a negative number if num1 is greater than,
 equal to, or smaller than num2 */
static int CmpBetweenTwoInt(const void *num1, const void *num2);

/* multiply by ten num and return SUCCESS = 1*/
static int Add5(void *num, const void *param);

static test_status_ty CreateDestroyTest(void);
static test_status_ty HTInsertIsEmptyTest(void);
#if 0
static test_status_ty HTInsertHTSizeTest(void);
static test_status_ty HTRemoveSizeTest(void);
#endif
static test_status_ty HTFindInsertTest(void);
static test_status_ty HTFindRemoveTest(void);
static test_status_ty HTFForEachTest(void);

static test_status_ty LoadLinuxDictionnaryTest(void);
static int StrCmp(const void *str1, const void *str2);
static size_t IndexAccordingToFirstLetter(void *word);

/* we can also test other cases if capacity is 0 */
/******************************************************************************/
int main()
{
	unsigned int counter_funct_failed = 0;

	PRINT_IF_FAILED(CreateDestroyTest)
	PRINT_IF_FAILED(HTInsertIsEmptyTest)
	#if 0
	PRINT_IF_FAILED(HTInsertHTSizeTest)
	PRINT_IF_FAILED(HTRemoveSizeTest)
	#endif
	PRINT_IF_FAILED(HTFindInsertTest)
	PRINT_IF_FAILED(HTFindRemoveTest)
	PRINT_IF_FAILED(HTFForEachTest)
	PRINT_IF_FAILED(LoadLinuxDictionnaryTest)

	PRINT_IF_ALL_TST_SUCCEED()

	PRINT_END_OF_TEST_FILE()

	return 0;
}

/******************************************************************************/
static test_status_ty CreateDestroyTest(void)
{
	ht_ty *hash_tab = NULL;
	hash_func_ty hash_func = NULL;
	ht_cmp_func_ty cmp_func = NULL;
	size_t capacity = 10;

	hash_tab = HTCreate(capacity, hash_func, cmp_func);
	if (NULL == hash_tab)
	{
		PRINT_FAIL_IN_LINE()

		return TEST_FAIL;
	}

	HTDestroy(hash_tab);
	hash_tab = NULL;

	return TEST_SUCCESS;
}
/******************************************************************************/
static test_status_ty HTInsertIsEmptyTest(void)
{
	int data_to_ins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int test_arr_size = 10;
	int exp_ret_val = 0;
	int i = 0;
	CREATE_HASH_TABLE()
	/* check if is empty */
	exp_ret_val = TRUE;
	CHECK_IF_AS_EXPECTED(HTIsEmpty(hash_tab), exp_ret_val, "%d")

	/* insert data_to_insert and check the return value */
	exp_ret_val = SUCCESS;
	for (i = 0; test_arr_size > i; ++i)
	{
		CHECK_IF_AS_EXPECTED(HTInsert(hash_tab, &data_to_ins[i]), exp_ret_val, "%d")
	}

	/* check if is empty */
	exp_ret_val = FALSE;
	CHECK_IF_AS_EXPECTED(HTIsEmpty(hash_tab), exp_ret_val, "%d")

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}
#if 0
/******************************************************************************/
static test_status_ty HTInsertHTSizeTest(void)
{
	size_t exp_size = 0;
	CREATE_RESOURCES()
	CREATE_HASH_TABLE()

	/* check if the size is as expected to be */
	exp_size = 0;
	CHECK_IF_AS_EXPECTED(HTSize(hash_tab), exp_size, "%ld")

	/* insert data_to_insert and check the return value */
	exp_ret_val = SUCCESS;
	for (i = 0; test_arr_size > i; ++i)
	{
		CHECK_IF_AS_EXPECTED(HTInsert(hash_tab, &data_to_ins[i]), exp_ret_val, "%d")

		/* check if the size is as expected to be */
		++exp_size;
		CHECK_IF_AS_EXPECTED(HTSize(hash_tab), exp_size, "%ld")
	}

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}
/******************************************************************************/
static test_status_ty HTRemoveSizeTest(void)
{
	size_t exp_size = 0;
	int ret_val_rem = 0;
	int inexistent_val = 30;

	CREATE_RESOURCES()
	CREATE_HASH_TABLE()

	INSERT_IN_HASH_TABLE(hash_tab, data_to_ins, test_arr_size)

	/* remove all existing values */
	exp_ret_val = SUCCESS;
	exp_size = test_arr_size;

	for (i = 0; test_arr_size > i; ++i)
	{
		ret_val_rem = HTRemove(hash_tab, &(data_to_ins[i]));
		CHECK_IF_AS_EXPECTED(ret_val_rem, exp_ret_val, "%d")

		--exp_size;
		CHECK_IF_AS_EXPECTED(HTSize(hash_tab), exp_size, "%ld")
	}

	/* test case 2: try to remove inexistent val */
	exp_ret_val = FAILURE;
	ret_val_rem = HTRemove(hash_tab, &inexistent_val);

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}
#endif
/******************************************************************************/
static test_status_ty HTFindInsertTest(void)
{
	int arr_exp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int inexistent_val = 30;

	CREATE_RESOURCES()
	CREATE_HASH_TABLE()

	INSERT_IN_HASH_TABLE(hash_tab, data_to_ins, test_arr_size)

	/* remove all existing values */
	exp_ret_val = SUCCESS;

	for (i = 0; test_arr_size > i; ++i)
	{
		CHECK_IF_AS_EXPECTED(HTFind(hash_tab, (void *)&arr_exp[i]),
							 (void *)&data_to_ins[i], "%p")
	}

	/* test case 2: try to find inexistent val */

	CHECK_IF_AS_EXPECTED(HTFind(hash_tab, (void *)&inexistent_val), NULL, "%p")

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}
/******************************************************************************/
static test_status_ty HTFindRemoveTest(void)
{
	int ret_val_rem = 0;

	CREATE_RESOURCES()
	CREATE_HASH_TABLE()

	INSERT_IN_HASH_TABLE(hash_tab, data_to_ins, test_arr_size)

	/* remove all existing values */
	exp_ret_val = SUCCESS;

	for (i = 0; test_arr_size > i; ++i)
	{
		ret_val_rem = HTRemove(hash_tab, &(data_to_ins[i]));
		CHECK_IF_AS_EXPECTED(ret_val_rem, exp_ret_val, "%d")

		CHECK_IF_AS_EXPECTED(HTFind(hash_tab, (void *)&data_to_ins[i]), NULL, "%p")
	}

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}
/******************************************************************************/
static test_status_ty HTFForEachTest(void)
{
	int exp_arr[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int exp_ret_val_for_each = 0;

	CREATE_RESOURCES()
	CREATE_HASH_TABLE()

	INSERT_IN_HASH_TABLE(hash_tab, data_to_ins, test_arr_size)
	exp_ret_val_for_each = SUCCESS;

	CHECK_IF_AS_EXPECTED(HTForEach(hash_tab, Add5, NULL), exp_ret_val_for_each, "%d")
	for (i = 0; test_arr_size > i; ++i)
	{
		CHECK_IF_AS_EXPECTED(HTFind(hash_tab, (void *)&exp_arr[i]), (void *)&data_to_ins[i], "%p")
	}

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}

/***************   HELPER FUNCTIONS   *****************************************/
static size_t Modulo5(void *integer)
{
	return (size_t)(*(int *)integer % 5);
}
/*----------------------------------------------------------------------------*/
static int CmpBetweenTwoInt(const void *num1, const void *num2)
{
	return *(int *)num1 - *(int *)num2;
}
/*----------------------------------------------------------------------------*/
static int Add5(void *num, const void *param)
{
	*(int *)num += 5;

	return SUCCESS;
}

/******************************************************************************/
/******************************************************************************/
static test_status_ty LoadLinuxDictionnaryTest(void)
{
	size_t capacity = 26 * 2 + 1; /*Upper cases  + Lower_cases + 2 special characters at same entry*/
	static char **word_buffer = {NULL};
	size_t num_of_word = 0;
	char *word = NULL;
	char letter = '\0';
	int size_of_word = 0;
	int max_size_of_word = 0;
	int is_found = 0;
	size_t i = 0;
	size_t j = 0;
	ht_ty *hash_tab = NULL;
	FILE *dict_file = NULL;
	char ch = '\0';
	char input_buffer[MAX_LENGTH_WORD] = {'\0'};
	wchar_t string_to_find[10] = {CHARACTER_E_special, 't', 'u', 'd', 'e', 's', '\0'};

	dict_file = fopen("/usr/share/dict/words", "r");
	if (NULL == dict_file)
	{
		PRINT_FAIL_IN_LINE()

		DESTROY_RESOURCES();
		return TEST_FAIL;
	}

	/* create hash table */
	hash_tab = HTCreate(capacity, IndexAccordingToFirstLetter, StrCmp);
	if (NULL == hash_tab)
	{
		PRINT_FAIL_IN_LINE()
		return TEST_FAIL;
	}
	/*_______________________________________________________________*/

	/* calculate the number of words in the dictionary */
	while (EOF != (ch = fgetc(dict_file)))
	{
		if ('\n' == ch)
		{
			++num_of_word;
			max_size_of_word = size_of_word;
			size_of_word = 0;
		}
		else 
		{
			++size_of_word;
		}
	}
	/*_______________________________________________________________*/

	/*++num_of_word; */ /* because we need to add the last word that ended by EOF and not '\n' */
	printf("num_of_words = %ld\n", num_of_word);

	/* allocate mem for the array of pointers to words */
	word_buffer = (char **)malloc(sizeof(char *) * num_of_word);

	if (NULL == word_buffer)
	{
		perror(strerror(errno));

		return TEST_FAIL;
	}

	/* set the file indicator to the biginning */
	fclose(dict_file);
	dict_file = fopen("/usr/share/dict/words", "r");

	/* read from the dictionnary file of linux each word, create a pointer to
	the word ans save into an array */
	for (i = 0; num_of_word > i; ++i)
	{
		j = 0;
		size_of_word = 0;

		word_buffer[i] = (char *)malloc(max_size_of_word + 1);

		if (NULL == word_buffer[i])
		{
			for (j = 0; i > j; ++j)
			{
				free(word_buffer[j]);
				word_buffer[j] = NULL;
			}

			free(word_buffer);
			word_buffer = NULL;

			DESTROY_RESOURCES()

			return TEST_FAIL;
		}
		while ('\n' != (letter = fgetc(dict_file)))
		{
			/* copy the word char by char */
			word_buffer[i][j] = letter;

			++j;
		}

		word_buffer[i][j] = '\0';
	}

	fclose(dict_file);
	dict_file = NULL;

	/* add words from the arr to the hash_table */
	for (i = 0; num_of_word > i; ++i)
	{
		CHECK_IF_AS_EXPECTED(HTInsert(hash_tab, word_buffer[i]), SUCCESS, "%d");
	}
	

	/* get input fron the user and check if it is in table */
	fgets(input_buffer, MAX_LENGTH_WORD ,stdin);
	fflush(stdin);
	*(strchr(input_buffer, '\n')) = '\0';
	is_found = (NULL != (char *)HTFind(hash_tab, input_buffer));
	
	if (is_found)
	{
		printf("%s is in the linux dictionary\n", input_buffer);                                                                   
	}
	else
	{
		printf("%s is NOT in the linux dictionary\n", input_buffer);
	}

	/* printf("%s =? found\n", (char *)HTFind(hash_tab, string_to_find)); */
	 

	/*_______________________________________________________________*/
	/* destroy the dict_buffer */
	for (i = 0; num_of_word > i; ++i)
	{
		free(word_buffer[i]);
		word_buffer[i] = NULL;
	}

	free(word_buffer);
	word_buffer = NULL;

	DESTROY_RESOURCES()

	return TEST_SUCCESS;
}
/***************   HELPER FUNCTIONS   *****************************************/
static size_t IndexAccordingToFirstLetter(void *word)
{
	char first_letter = *(char *)word;
	if ('a' <= first_letter)
	{
		return (first_letter - 'a' + 26);
	}
	else if ('a' <= first_letter)
	{
		return (first_letter - 'A');
	} 

	else 
	{
		return CAPACITY - 1;
	}
}
/*----------------------------------------------------------------------------*/
static int StrCmp(const void *str1, const void *str2)
{
	return strcmp((char *)str1, (char *)str2);
}
/*##########################	END OF FILE		##############################*/

#endif
/******************************************************************************
 * Project: Data Structures - Hash Table
 * Date: 24/10/22
 * Name: karam aamar
 * Reviewer: shirly 
 * Version: 1.0
 * ****************************************************************************/
#include <stdio.h>	/*puts, perror*/
#include <stdlib.h>	/*malloc, free*/
#include <errno.h>	/*errno*/
#include <assert.h>	/*assert*/
#include <string.h>	/*strcmp*/
/******************************************************************************/
#include "hash_table.h"

#define WORD_LENGTH 26
#define NUM_OF_LETTERS 26
/******************************************************************************/
typedef enum STATUS {SUCCESS = 0 , FAIL} STATUS_ty;
/******************************************************************************/
static void ImplementFunc();

static void HTCreateTest();
static void HTInsertRemoveTest();
static void HTIsEmptyTest();
static void HTFindTest();
static void HTForEachTest();
static void HTSizeTest();

static void DictonaryFunc();

static int CmpFuncInts(const void *data, const void *data2);
static int CmpFuncStrs(const void *data, const void *data2);
static size_t KeyFindFunc(void *data);
static int Action(void *data, const void *param);

static size_t KeyFindDictFunc(void *data);
/******************************************************************************/
int main()
{
	ImplementFunc();
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	HTCreateTest();
	HTInsertRemoveTest();
	HTIsEmptyTest();
	HTFindTest();
	HTForEachTest();
	HTSizeTest();

	DictonaryFunc();
}
/******************************************************************************/
static void HTCreateTest()
{
	size_t size = 10; 
	ht_ty *new_table = NULL;
	
	new_table = HTCreate(size, &KeyFindFunc, &CmpFuncInts);
	
	if(NULL == new_table)
	{
		puts("FAILED TO CREATE");
	}
	
	HTDestroy(new_table);
}
/******************************************************************************/
static void HTInsertRemoveTest()
{
	ht_ty *new_table = NULL;
	size_t size = 10; 
	int a = 1;
	int b = 11;
	
	new_table = HTCreate(size, &KeyFindFunc, &CmpFuncInts);
	
	if(1 == HTInsert(new_table, &a))
	{
		puts("FAILED TO INSERT");
	}
	if(1 == HTInsert(new_table, &b))
	{
		puts("FAILED TO INSERT");
	}
	if(1 == HTRemove(new_table, &a))
	{
		puts("FAILED TO REMOVE1");
	}
	if(1 == HTRemove(new_table, &b))
	{
		puts("FAILED TO REMOVE2");
	}
	HTDestroy(new_table);
}
/******************************************************************************/
static void HTIsEmptyTest()
{
	ht_ty *new_table = NULL;
	size_t size = 10; 
	int a = 1;
	int b = 11;
	
	new_table = HTCreate(size, &KeyFindFunc, &CmpFuncInts);
	
	if(1 == HTInsert(new_table, &b))
	{
		puts("FAILED TO INSERT");
	}
	if(1 == HTInsert(new_table, &a))
	{
		puts("FAILED TO INSERT");
	}

	if(1 == HTIsEmpty(new_table))
	{
		puts("ISEMPTY FAILED");
	}
	
	HTDestroy(new_table);
}
/******************************************************************************/
static void HTFindTest()
{
	ht_ty *new_table = NULL;
	size_t size = 10; 
	int a = 1;
	int b = 11;
	int c = 111;
	
	new_table = HTCreate(size, &KeyFindFunc, &CmpFuncInts);
	
	HTInsert(new_table, &a);
	HTInsert(new_table, &b);
	HTInsert(new_table, &c);

	if(NULL == HTFind(new_table, &b))
	{
		puts("FAILED TO FIND");
	}
	HTDestroy(new_table);
}
/******************************************************************************/
static void HTSizeTest()
{
	ht_ty *new_table = NULL;
	size_t size = 10; 
	int a = 1;
	int b = 11;
	int c = 111;

	int d = 2;
	int e = 22;
	
	new_table = HTCreate(size, &KeyFindFunc, &CmpFuncInts);
	
	HTInsert(new_table, &a);
	HTInsert(new_table, &b);
	HTInsert(new_table, &c);
	HTInsert(new_table, &d);
	HTInsert(new_table, &e);

	if(5 != HTSize(new_table))
	{
		puts("HTSIZE FAILED");
	}
	HTDestroy(new_table);
}
/******************************************************************************/
static void HTForEachTest()
{
	ht_ty *new_table = NULL;
	size_t size = 10; 
	int a = 1;
	int b = 11;
	int c = 111;
	
	new_table = HTCreate(size, &KeyFindFunc, &CmpFuncInts);
	
	HTInsert(new_table, &a);
	HTInsert(new_table, &b);
	HTInsert(new_table, &c);
	
	if(1 == HTForEach(new_table, &Action , &a))
	{
		puts("FOREACH FAILED");
	}
	HTDestroy(new_table);
}
/******************************************************************************/
static void DictonaryFunc()
{
	FILE *file = NULL;
	size_t i = 0;
	size_t num_of_words = 0;
	char char_runner = '\0';
	char* words_chunk = NULL;
	char input_to_check[WORD_LENGTH] = {0};
	size_t word_chunk_runner = 0;
	ht_ty *table = NULL;
	
	/* open file */
	file = fopen("/usr/share/dict/words","r");

	assert(file);	
	/* while we didnt get to the end */
	while(EOF != (char_runner = fgetc(file)))
	{
		if('\n' == char_runner)
		{
			++num_of_words;
		}
	}
	/* close the file */
	fclose(file);
	/* open file again*/
	file = fopen("/usr/share/dict/words","r");
	/* allocation for each pointer for words */
	words_chunk = (char*)malloc(num_of_words * WORD_LENGTH);
	/* check allocations */
	if(NULL == words_chunk)
	{
		puts("faile to allocate");
		
	}
	/* allocate for each word (the maximum size of word 26) */
	for(i = 0; i < num_of_words; ++i)
	{
		/* fetch words from file into words chunk */
		fgets((words_chunk + word_chunk_runner), WORD_LENGTH, file);
		/* increment runner to next word */
		word_chunk_runner += WORD_LENGTH;
	}
	fclose(file);

	table = HTCreate(NUM_OF_LETTERS, &KeyFindDictFunc, &CmpFuncStrs);

	/* create hash table words_chunk */
	for(i = 0; i < num_of_words; ++i)
	{
		HTInsert(table,words_chunk + WORD_LENGTH);
	}
	
	/* insert the values from the */
	puts("Enter a word to check if exists\n");
    scanf("%s", input_to_check);

	*(strchr(input_to_check, '\0')) = '\n';

	if(NULL == HTFind(table, input_to_check))
    {
        puts("the word in not found\n");
    }
    else
    {
        puts("The word is found\n");
    }
	free(words_chunk);
    words_chunk = NULL;

    HTDestroy(table);
}
/******************************************************************************/
static int CmpFuncInts(const void *data, const void *data2)
{
	return !(*(int *)data == *(int *)data2);
}
/******************************************************************************/
static size_t KeyFindFunc(void *data)
{
	return *(int*)data % 10;
}
/******************************************************************************/
static int Action(void *data, const void *param)
{
	return (*(int*)data + *(int*)param);
}
/******************************************************************************/
static size_t KeyFindDictFunc(void *data)
{
	if(*(char*)data >= 'A' && *(char*)data <= 'Z')
	{
		return (*(char*)data - 'A');
	}
	else if(*(char*)data >= 'a' && *(char*)data <= 'z')
	{
		return (*(char*)data - 'a');
	}
	return 0;
}
/******************************************************************************/
static int CmpFuncStrs(const void *data, const void *data2)
{
	if(!strcmp((const char*)data,(const char*)data2))
	{
		return 0;
	}
	return 1;
}
/******************************************************************************/



