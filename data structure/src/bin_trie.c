/*******************************************************************************
 * Project: 
 * Date: 
 * Name: karam
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <assert.h>	/*assert*/
#include <string.h>	/*strerro*/
#include <errno.h>	/*errno*/
#include <stdlib.h>	/*malloc, free*/
#include <stdio.h>	/*perror*/
/******************************************************************************/
#include "bin_trie.h"

/******************************************************************************/
typedef struct trie_node trie_node_ty;

typedef enum status{ MY_FALSE = 0 ,MY_TRUE } status_ty;
typedef enum recFUNC{ SUCCESS = 0 ,BLOCKED , NOT_EXIST, ALLOC_FAIL}recFUNC_ty;
typedef enum direction{ LEFT = 0 ,RIGHT }direction_ty;
/**********************************helper functions****************************/
static void RecNodeDestroyIMP(trie_node_ty* node);
static address_ty GetTrieRecIMP(trie_node_ty* node, address_ty* number_, 
                                                       unsigned int bit_lvl_);
static address_ty GetDirectionIMP(address_ty* number_, unsigned int bit_lvl_);
static void UpdateAddressIMP(address_ty* number_, unsigned int bit_lvl_);
static trie_node_ty* CreateNodeIMP();
static address_ty CreatePathIMP(trie_node_ty* parent_node, address_ty num_bits_, address_ty* number_);
static unsigned int NextBitIMP(unsigned int bit_to_check);
static int IsChildrenBlockedIMP(trie_node_ty* parent_node);
static void ReleaseAddressRecIMP(trie_node_ty* node_, address_ty num_,address_ty bit_lvl_);
static size_t CheckNumOfAdresIMP(trie_node_ty* node_, address_ty bit_lvl_);
static size_t PowFuncIMP(size_t base_, size_t exp_);
/******************************************************************************/
struct trie_node
{
    int IsBlocked;
    trie_node_ty* children[2];
};

struct trie
{
    trie_node_ty* root;
    unsigned int num_of_bits;
};/*trie_ty*/
/******************************************************************************/

trie_ty* TrieCreate(address_ty num_bits_)
{
    trie_ty* trie = NULL;
    trie_node_ty* root = NULL;
    address_ty initial_path = 0;

    trie = (trie_ty*)malloc(sizeof(trie_ty));

    if(NULL == trie)
	{
		perror(strerror(errno));
		return NULL;
	}

    root = CreateNodeIMP();

    if(NULL == root)
	{
		free(trie);
		trie = NULL;
		return NULL;
	}

    /*init*/
    trie->num_of_bits = num_bits_;
    trie->root = root;

    CreatePathIMP(root, num_bits_, &initial_path);
    
    return trie;
}
/******************************************************************************/
void TrieDestroy(trie_ty* trie_)
{
    assert(trie_);

    if(trie_->root)
    {
        RecNodeDestroyIMP(trie_->root);
    }
    free(trie_);
}
/******************************************************************************/
address_ty TrieGet(trie_ty* trie_, address_ty number_)
{
    assert(trie_);
    /* call recursive function */
    GetTrieRecIMP(trie_->root, &number_, trie_->num_of_bits);

    return number_;
}
/******************************************************************************/
void TrieRelease(trie_ty* trie_, address_ty number_)
{
    assert(trie_);

    ReleaseAddressRecIMP(trie_->root, number_, trie_->num_of_bits);
}
/******************************************************************************/
size_t TrieAvaliable(const trie_ty* trie_)
{
    size_t num_of_cur_adres = 0;

    assert(trie_);

    num_of_cur_adres = CheckNumOfAdresIMP(trie_->root, trie_->num_of_bits);

    return PowFuncIMP(2, trie_->num_of_bits) - num_of_cur_adres;
}
/******************************* helper functions *****************************/
/******************************************************************************/
static void RecNodeDestroyIMP(trie_node_ty* node)
{
    if(!node) 
    {
        return;
    }

    RecNodeDestroyIMP(node->children[RIGHT]);
    RecNodeDestroyIMP(node->children[LEFT]);

    free(node);
    node = NULL;
}
/******************************************************************************/
static trie_node_ty* CreateNodeIMP()
{
    trie_node_ty* trie_node = (trie_node_ty*)malloc(sizeof(trie_node_ty));

    if(NULL == trie_node)
	{
		perror("FAILED TO ALLOC");

		return NULL;
	}
    trie_node->IsBlocked = 0;
    trie_node->children[0] = NULL;
    trie_node->children[1] = NULL;

    return trie_node;
}
/******************************************************************************/
static address_ty GetTrieRecIMP(trie_node_ty* node, address_ty *address_, 
                                                       unsigned int bit_lvl_)
{
    /* define return value */
    address_ty return_value = 0;
    
    /* get the direction for the asked address  */
    address_ty direct = GetDirectionIMP(address_, bit_lvl_);

    /* check if node not exist - return NOT_exist */
    if(NULL == node)
    {
        return NOT_EXIST;
    }

    /* check if we get to the end & not blocked - RETURN SUCCESS */
    if(0 == bit_lvl_ && !node->IsBlocked)
    {
        node->IsBlocked = MY_TRUE;
        return SUCCESS;
    }

    /*if the node blocked - RETURN BLOCKED */
    if(node->IsBlocked == MY_TRUE)
    {
        return BLOCKED;
    }
    /* recursive call to next node */
    return_value = GetTrieRecIMP(node->children[direct], address_, (bit_lvl_ - 1));
    
    /* 
        if we get BLOCKED then move to another branch -
         update adress and call recursively 
    */
    if(return_value == BLOCKED)
    {
        if(direct == 0)
        {
            UpdateAddressIMP(address_, bit_lvl_);
            return_value = GetTrieRecIMP(node->children[!direct], address_, (bit_lvl_-1));
        }
        else
        {
            return BLOCKED;
        }
    }
    /* if its not exist then create path */
    if(return_value == NOT_EXIST)
    {
        return CreatePathIMP(node, (bit_lvl_), address_);
    }
    /* if we have success check childrens to block */
    if(return_value == SUCCESS)
    {
        if(IsChildrenBlockedIMP(node))
        {
            node->IsBlocked = MY_TRUE;
        }
        return SUCCESS;
    }
     /*check allocation */
    if(return_value == ALLOC_FAIL)
    {
        *address_ = 0;
        return 0;
    }
    
    return return_value;
}
/******************************************************************************/
static address_ty CreatePathIMP(trie_node_ty* parent_node, address_ty num_bits_, address_ty* number_)
{
    trie_node_ty* curr_node = NULL;
    address_ty direct = 0; 

   if(num_bits_ > 0)
   {
     while(num_bits_)
    {
        curr_node = CreateNodeIMP();
        direct = GetDirectionIMP(number_, num_bits_);

        /*check if allocation success*/
        if(NULL == curr_node)
        {
            return ALLOC_FAIL;
        }
        parent_node->children[direct] = curr_node;
        parent_node = curr_node;

        --num_bits_;
    }
    /* block last node */
    curr_node->IsBlocked = MY_TRUE;
   }
    return SUCCESS;
}
/******************************************************************************/
static void UpdateAddressIMP(address_ty* number_, unsigned int bit_lvl_)
{
    *number_ = (*number_ >> (bit_lvl_ - 1)) + 1;
    *number_ = (*number_ << (bit_lvl_ - 1));
}
/******************************************************************************/
static address_ty GetDirectionIMP(address_ty* number_, unsigned int bit_lvl_)
{
    /* define mask */
    address_ty mask = 1;
    address_ty direct = 0;

    if(bit_lvl_ > 0)
    {
        mask = (1 << (bit_lvl_ - 1));
        direct = (mask & (*number_)) >> (bit_lvl_ - 1);
    }
    else
    {
        direct = mask & (*number_);
    }
    
    return direct;
    /*3ad kan 3ovid */
}
/******************************************************************************/
static unsigned int NextBitIMP(unsigned int bit_to_check)
{
    return (bit_to_check - 1);
}
/******************************************************************************/
static int IsChildrenBlockedIMP(trie_node_ty* parent_node)
{
    if(parent_node->children[LEFT] && parent_node->children[RIGHT])
    {
        if(MY_TRUE == parent_node->children[LEFT]->IsBlocked && MY_TRUE == 
                                        parent_node->children[RIGHT]->IsBlocked)
        {
            return MY_TRUE;
        }
    }
    
    return MY_FALSE;
}
/******************************************************************************/
static void ReleaseAddressRecIMP(trie_node_ty* node_, address_ty num_,address_ty bit_lvl_)
{
    int direct = 0;
    
    if(0 == bit_lvl_)
    {
        node_->IsBlocked = MY_FALSE; 
        return;
    }
    /* get direction of the relevant num_ */
    direct = GetDirectionIMP(&num_, bit_lvl_);
    /* release the node if blocked */
    node_->children[direct]->IsBlocked = MY_FALSE;
    /* call the function again */
    ReleaseAddressRecIMP(node_->children[direct], num_, bit_lvl_ - 1);
}
/******************************************************************************/
static size_t PowFuncIMP(size_t base_, size_t exp_)
{
    size_t ret = 1;

    while (exp_ != 0)
    {
        ret *= base_;
        --exp_;
    }
    return ret;
}
/******************************************************************************/
static size_t CheckNumOfAdresIMP(trie_node_ty* node_, address_ty bit_lvl_)
{
    size_t left_count  = 0;
    size_t right_count = 0;
    /*if the path blocked / return condition*/
    if(node_->IsBlocked)
    {
        return PowFuncIMP(2 ,bit_lvl_);
    }

    if(node_->children[LEFT])
    {
       left_count = CheckNumOfAdresIMP(node_->children[LEFT], bit_lvl_-1);
    }

    if(node_->children[RIGHT])
    {
        right_count = CheckNumOfAdresIMP(node_->children[RIGHT], bit_lvl_-1);
    }

    return left_count + right_count;
}
/******************************************************************************/
