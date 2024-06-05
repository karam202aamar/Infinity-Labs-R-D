/******************************************************************************
 * Project: Data Structures - Heap
 * Date: 26/10/22
 * Name: karam aamar
 * Reviewer: ortal
 * Version: 1.0
 * ****************************************************************************/
/******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "heap.h"
#include "dynamic_vector.h"
/******************************************************************************/
#define MATCH               1
#define BIGGER              1
/******************************************************************************/
static void HeapifyUp(heap_ty *heap);

static void SwapInsideVector(void** pt1, void** ptr2);

static void HeapifyDown(heap_ty *heap , size_t index);

static size_t CheckChildsSwap(heap_ty *heap, void** ptr_current, 
                   void** ptr_left, size_t left, void** ptr_right, size_t right);

static size_t LeftChild(size_t parent);
static size_t RightChild(size_t parent);
static size_t Parent(size_t index);
static size_t LastIndex(heap_ty *heap);
/******************************************************************************/
struct heap
{
    dynamic_vector_ty* items;
    heap_cmp_func_ty cmp;
};
/******************************************************************************/
heap_ty * HeapCreate(heap_cmp_func_ty cmp_func)
{
    heap_ty* heap = NULL;

    heap = (heap_ty*)malloc(sizeof(heap_ty));

    if(NULL == heap)
    {
        perror(strerror(errno));
		return NULL;
    }
    heap -> items = DynamicVectorCreate(sizeof(void*), 1);
    heap -> cmp = cmp_func;

    return heap;
}
/******************************************************************************/
void HeapDestroy(heap_ty *heap)
{
    assert(heap);

    DynamicVectorDestroy(heap->items);
    free(heap);
    heap = NULL;
}
/******************************************************************************/
int HeapPush(heap_ty *heap, const void *data)
{
    int status = 0;

    assert(heap);
    assert(heap->cmp);
    
    /* push element and then heapify up */
    status = DynamicVectorPushback(heap->items,&data);
       
    /* check if successed to push */
    if(1 == status)
    {
        return 1; /* fail */
    }

    HeapifyUp(heap);
       
    return 0;/* success */
}
/******************************************************************************/
void *HeapPop(heap_ty *heap)
{
    size_t first_index = 0;
    size_t last_index = 0;
    
    void **top_data = NULL;
    void **last_data = NULL;
    void *return_data = NULL;

    assert(heap);
    assert(heap->cmp);

    last_index = LastIndex(heap);
    
    top_data = (void**)DynamicVectorGetAccessToElement(heap->items, first_index);
    last_data = (void**)DynamicVectorGetAccessToElement(heap->items, last_index);

    if(1 == DynamicVectorCurrentSize(heap->items))
    {
        DynamicVectorPopBack(heap->items);
        return *last_data;
    }
    return_data = *top_data;

    /* swap between first and last element */
    SwapInsideVector(top_data, last_data);

    /* remove last element */
    DynamicVectorPopBack(heap->items);
    
    /* heapify down */
    HeapifyDown(heap, first_index);

    return return_data;
}
/******************************************************************************/
void *HeapPeek(const heap_ty *heap)
{
    size_t first_index = 0;

    return (void*)DynamicVectorGetAccessToElement(heap->items, first_index);
}
/******************************************************************************/
size_t HeapSize(const heap_ty *heap)
{
    assert(heap);
    return DynamicVectorCurrentSize(heap->items);
}
/******************************************************************************/
int HeapIsEmpty(const heap_ty *heap)
{
    assert(heap);

    return !(DynamicVectorCurrentSize(heap->items) >= 1);
}
/******************************************************************************/
void *HeapRemove(heap_ty *heap, heap_is_match_ty is_match, const void *param)
{
    size_t curr_index = 0;
    size_t last_index = 0;
    
    void **curr_data = NULL;
    void **last_data = NULL;
    void *return_data = NULL;

    assert(heap);
    assert(heap->cmp);

    last_index = LastIndex(heap);
 
    curr_data = (void**)DynamicVectorGetAccessToElement(heap->items, curr_index);
    last_data = (void**)DynamicVectorGetAccessToElement(heap->items, last_index);
   
    while(curr_index <= last_index)
    {
        if(MATCH == is_match(*curr_data, param))
        {
            return_data = *curr_data;

            SwapInsideVector(curr_data, last_data);
               
            DynamicVectorPopBack(heap->items);
               
            HeapifyUp(heap);

            HeapifyDown(heap, curr_index);

            return return_data;
        }
        ++curr_index;
        curr_data = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                    curr_index);
    }
    return return_data;
}
/******************************************************************************/
static void HeapifyDown(heap_ty *heap , size_t index)
{
    size_t index_of_last_ele = 0;
    size_t index_of_right_ele = 0;
    size_t index_of_left_ele = 0;

    void **data_to_check = NULL;
    void **left_data = NULL;
    void **right_data = NULL;

    index_of_last_ele = LastIndex(heap);

    index_of_left_ele = LeftChild(index);
    index_of_right_ele = RightChild(index);
    
    data_to_check = (void**)DynamicVectorGetAccessToElement(heap->items, index);

    while(index < index_of_last_ele)
    {
        index = CheckChildsSwap(heap, data_to_check, left_data,index_of_left_ele
                                              , right_data, index_of_right_ele);
        index_of_left_ele = LeftChild(index);
        index_of_right_ele = RightChild(index);
        
        data_to_check = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                        index);
        
        if(index_of_left_ele <= index_of_last_ele)
        {
            left_data = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                            index_of_left_ele);
        }
        if(index_of_right_ele <= index_of_last_ele)
        {
            right_data = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                            index_of_right_ele);
        }
    }
}
/******************************************************************************/
static size_t CheckChildsSwap(heap_ty *heap, void** ptr_current, 
                   void** ptr_left, size_t left, void** ptr_right, size_t right)
{
    size_t num_of_ele = LastIndex(heap);

    if(left > num_of_ele && right > num_of_ele)
    {
        return num_of_ele;
    }

    if(left < num_of_ele && right < num_of_ele)
    {
        if(BIGGER == heap->cmp(*ptr_left, *ptr_right) && BIGGER == 
                                             heap->cmp(*ptr_left, *ptr_current))
        {
            SwapInsideVector(ptr_current, ptr_left);
            return left;
        }
        if(BIGGER == heap->cmp(*ptr_right, *ptr_left) && BIGGER ==  
                                            heap->cmp(*ptr_right, *ptr_current))
        {
            SwapInsideVector(ptr_current, ptr_right);
            return right;
        }
    }
    if(left > num_of_ele && right < num_of_ele)
    {
        if(BIGGER == heap->cmp(*ptr_right, *ptr_current))
        {
            SwapInsideVector(ptr_current, ptr_right);
            return right;
        }
    }
    if(left < num_of_ele && right > num_of_ele)
    {
        if(BIGGER == heap->cmp(*ptr_left, *ptr_current))
        {
            SwapInsideVector(ptr_current, ptr_left);
            return left;
        }
    }
    return num_of_ele;
}
/******************************************************************************/
static size_t LeftChild(size_t parent)
{
    return ((parent * 2) + 1); 
}
/******************************************************************************/
static size_t RightChild(size_t parent)
{
    return ((parent * 2) + 2); 
}
/******************************************************************************/
static size_t Parent(size_t index)
{
    return ((index - 1) / 2); 
}
/******************************************************************************/
static size_t LastIndex(heap_ty *heap)
{
    return DynamicVectorCurrentSize(heap->items) - 1;
}
/******************************************************************************/
static void HeapifyUp(heap_ty *heap)
{
    size_t inserted_index = 0;
    size_t parent_index = 0;

    void **data_inserted = NULL;
    void **data_parent = NULL;
   
    inserted_index = LastIndex(heap);
    
    parent_index = Parent(inserted_index);

    data_inserted = (void**)DynamicVectorGetAccessToElement(heap->items, 
                                                                inserted_index);
    data_parent = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                 parent_index);
                                                                
  
        while(inserted_index != 0)
        {
          
            if(1 == heap->cmp(*data_inserted, *data_parent))
            {
          
            /* 2 stage pointers*/
            SwapInsideVector(data_inserted, data_parent);

            inserted_index = parent_index;
            parent_index = Parent(parent_index);

            data_inserted = (void**)DynamicVectorGetAccessToElement
                                                 (heap->items, inserted_index);
            data_parent = (void**)DynamicVectorGetAccessToElement
                                                   (heap->items, parent_index);
            }
            else
            {
                inserted_index = parent_index;
                parent_index = Parent(parent_index);
            }
            
        }  
}
/******************************************************************************/
static void SwapInsideVector(void** ptr1, void** ptr2)
{
    void* tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 =tmp;
    
}
/******************************************************************************/
#if 0
static void HeapifyDown(heap_ty *heap , size_t index)
{
    size_t index_of_last_ele = 0;
    size_t index_of_right_ele = 0;
    size_t index_of_left_ele = 0;

    void **data_to_check = NULL;
    void **data_left = NULL;
    void **data_right = NULL;

    index_of_last_ele = DynamicVectorCurrentSize(heap->items) - 1;

    /* check the index value */
    if(0 == index)
    {
        index_of_left_ele = 1;
        index_of_right_ele = 2;
    }
    else
    {
        index_of_left_ele = (index * 2) + 1;
        index_of_right_ele = (index_of_left_ele + 1);
    }
    
    data_to_check = (void**)DynamicVectorGetAccessToElement(heap->items, index);

    if(index_of_left_ele <= index_of_last_ele)
    {
        data_left = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                    index_of_left_ele);
        
    }
    if(index_of_right_ele <= index_of_last_ele)
    {
        data_right = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                   index_of_right_ele);
    }
    /*
    printf("index :  %ld \n",index);
    printf("last index :  %ld \n",last_index);
    */
    while(index <= index_of_last_ele && index_of_left_ele <= index_of_last_ele && index_of_right_ele <= index_of_last_ele)
    {
        index = HigherPriority(heap->cmp, data_to_check, data_left, index_of_left_ele, 
                                                       data_right, index_of_right_ele);
        index_of_left_ele = (index * 2) + 1;
        index_of_right_ele = (index_of_left_ele + 1);
        
        data_to_check = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                         index);
        
        if(index_of_left_ele <= index_of_last_ele)
        {
            data_left = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                    index_of_left_ele);
        }
        if(index_of_right_ele <= index_of_last_ele)
        {
            data_right = (void**)DynamicVectorGetAccessToElement(heap->items,
                                                                   index_of_right_ele);
        }
    }
    
}
#endif
