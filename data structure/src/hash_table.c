/******************************************************************************
 * Project: Data Structures - Hash Table
 * Date: 24/10/22
 * Name: karam aamar
 * Reviewer: shirly
 * Version: 1.0
 * ****************************************************************************/
/******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "hash_table.h"
#include "dlist.h"
/******************************************************************************/
typedef enum status{MY_FALSE = 0 , MY_TRUE}status_ty;
/******************************************************************************/
static size_t GetKeyIMP(const ht_ty *table, const void *data);
static dlist_ty * RelevantListIMP(size_t key, ht_ty *table);
/******************************************************************************/
struct table
{
    hash_func_ty hash_func;
    ht_cmp_func_ty cmp_func;
    void **ptr_to_array;
    size_t table_size;
};
/******************************************************************************/
ht_ty *HTCreate(size_t table_size, hash_func_ty hash_func, ht_cmp_func_ty cmp_func) 
{
	size_t key = 0;
	
	ht_ty *ret = (ht_ty *)malloc(sizeof(ht_ty));
	
	if(NULL == ret)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	ret -> ptr_to_array = (void**)malloc(sizeof(void*) * table_size);
	
	if(NULL == ret -> ptr_to_array)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	ret -> hash_func = hash_func;
	ret -> cmp_func = cmp_func;
	ret -> table_size = table_size;
	
	for(key = 0; key < table_size; ++key)
	{
		ret->ptr_to_array[key] = DListCreate();
	}
	return ret;
}
/******************************************************************************/
void HTDestroy(ht_ty *table)
{
	size_t key = 0;
	
	assert(table);
	
	for(key = 0; key < (table->table_size); ++key)
	{
		DListDestroy(RelevantListIMP(key, table));
		table->ptr_to_array[key] = NULL;
	}
	
	free(table->ptr_to_array);
	table->ptr_to_array = NULL;
	
	free(table);
}
/******************************************************************************/
int HTRemove(ht_ty *table, const void *data)
{
	dlist_iter_ty found_iter = NULL;	
	dlist_ty *relevant_list = NULL;
	size_t key_found = 0;
	
	assert(table);
	assert(data);
	
	/* find the key of relevant dlist */
	key_found = table -> hash_func((void*)data);
	
	/* access to the list by using relevant key */
	relevant_list = RelevantListIMP(key_found, table);
	
	/* find iter */
	found_iter = DListFind(DListBegin(relevant_list),
			   DListEnd(relevant_list), table->cmp_func, (void*)data); 
			   
	/* check if the data found */
	if(DListIsSameIter(found_iter, DListEnd(relevant_list)))
	{
		return MY_TRUE;
	}
	
	DListRemove(found_iter);
	
	return MY_FALSE;
}
/******************************************************************************/
int HTInsert(ht_ty *table, void *data)
{
	size_t key_found = 0;
	
	dlist_ty *relevant_list = NULL;
	dlist_iter_ty first_iter = NULL;
	dlist_iter_ty inserted_iter = NULL;
	
	assert(table);
	assert(data);
	
	/* find the key of relevant dlist */
	key_found = GetKeyIMP(table,data);
	
	/* access to the list by using relevant key */
	relevant_list = RelevantListIMP(key_found, table);
	
	/* get the first iter */
	first_iter = DListBegin(relevant_list);
	
	inserted_iter = DListInsert(first_iter, data);
	
	if(DListIsSameIter(inserted_iter, DListEnd(relevant_list)))
	{
		return MY_TRUE;
	}
	return MY_FALSE;
}
/******************************************************************************/
int HTIsEmpty(const ht_ty *table)
{
	size_t i = 0;
	
	assert(table);
	
	for(i = 0; i < table->table_size; ++i)
	{
		if(MY_TRUE != DListIsEmpty(table->ptr_to_array[i]))
		{
			return MY_FALSE;
		}
	}
	return MY_TRUE;
}
/******************************************************************************/
void *HTFind(const ht_ty *table, const void *data)
{
	size_t key_found = 0;
	dlist_ty *relevant_list = NULL;
	dlist_iter_ty found_iter = NULL;
	
	assert(table);
	
	/* find the key of relevant dlist */
	key_found = GetKeyIMP(table,data);
	
	/* access to the list by using relevant key */
	relevant_list = RelevantListIMP(key_found, (ht_ty *)table);
	
	/* find iter */
	found_iter = DListFind(DListBegin(relevant_list),
			   DListEnd(relevant_list), table->cmp_func,(void*)data);
	
	/* check if the data found */
	if(!DListIsSameIter(found_iter, DListEnd(relevant_list)))
	{
		return found_iter;
	}		  
	return NULL;
}
/******************************************************************************/
size_t HTSize(const ht_ty *table)
{
	size_t ret = 0;
	size_t i = 0;
	size_t table_size = table->table_size;
	
	dlist_ty **array_list = (dlist_ty **)table->ptr_to_array;
	
	assert(table);
	
	for(i = 0 ; i < table_size ; ++i)
	{
		ret += DListSize(array_list[i]);
	}

	return ret;
}
/******************************************************************************/
int HTForEach(ht_ty *table, ht_action_ty action, const void *param)
{
	int ret = 0;
	size_t i = 0;
	size_t size = table->table_size;
	
	dlist_ty *relevant_list = NULL;
	
	assert(action);
	assert(table);
	
	while(i < size && 0 == ret)	
	{
		relevant_list = RelevantListIMP(i, table);
		
		ret = DListForeach(DListBegin(relevant_list),DListEnd
					(relevant_list), action, (void*)param);
		++i;
	}
	return ret;
}
/******************************************************************************/
size_t GetKeyIMP(const ht_ty *table, const void *data)
{
	return (table -> hash_func((void*)data));
}
/******************************************************************************/
static dlist_ty * RelevantListIMP(size_t key, ht_ty *table)
{
	return ((dlist_ty*)table->ptr_to_array[key]);
}
/******************************************************************************/
























