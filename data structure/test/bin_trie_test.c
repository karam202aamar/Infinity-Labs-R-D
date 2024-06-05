/*******************************************************************************
 * Project: 
 * Date: 
 * Name: karam
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* puts */
#include <time.h>   /*  clock_t */
#include <stdlib.h> /* qsort */
/******************************************************************************/
#include "bin_trie.h"

/******************************************************************************/
typedef enum {SUCCESS, FAIL} SORT_STATUS_ty;
/******************************************************************************/
static void ImplementFunc();

static void CreateDestroyTest(void);
static void TrieGetTest(void);
static void ReleaseCountTest(void);
/******************************************************************************/
int main()
{
	ImplementFunc();
    
	return 0;
}
/******************************************************************************/
static void ImplementFunc()
{
	CreateDestroyTest();
    TrieGetTest();
    ReleaseCountTest();
}
/******************************************************************************/
static void CreateDestroyTest()
{
    trie_ty* trie = TrieCreate(4);

    if(NULL == trie)
    {
        puts("creation failed");
    }

    TrieDestroy(trie);
}
/******************************************************************************/
static void TrieGetTest()
{
     trie_ty* trie = TrieCreate(3);
    address_ty res = 0;
    
    res = TrieGet(trie, 0);
    if(1 != res)
    {
        puts("TrieGetTest FAILED");
        
    }
    res = TrieGet(trie, 3);
    if(3 != res)
    {
        puts("TrieGetTest FAILED");
        
    }
    res = TrieGet(trie, 3);
    if(4 != res)
    {
        puts("TrieGetTest FAILED");
       
    }
    res = TrieGet(trie, 3);
    if(5 != res)
    {
        puts("TrieGetTest FAILED");
        
    }
    TrieDestroy(trie);
}
/******************************************************************************/
static void ReleaseCountTest()
{
    trie_ty* trie = TrieCreate(3);
    address_ty res = 0;
    size_t curr_free = 0;

    TrieGet(trie, 0);
    TrieGet(trie, 0);
    TrieGet(trie, 0);
  
    res = TrieGet(trie, 0);
  
    curr_free = TrieAvaliable(trie);

    if(curr_free != 3)
    {
        puts("ReleaseCountTest : failed to count ");
    }

    TrieRelease(trie, res);

    curr_free = TrieAvaliable(trie);

    if(curr_free != 4)
    {
        puts("ReleaseCountTest : failed to free ");
    }
    TrieDestroy(trie);
}


