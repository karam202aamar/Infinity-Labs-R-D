/*******************************************************************************
 Project: Data Structure -  Binary Trie - DHCP
 Date: 31/10/22
 Name: 
 Reviewer: Evald
 Version: 1.0
*******************************************************************************/
#ifndef __BIN_TRIE_H_ILRD__
#define __BIN_TRIE_H_ILRD__

#include <stddef.h>	/*size_t*/

typedef struct trie trie_ty;
typedef unsigned int address_ty;

/*******************************************************************************
Creats a trie compatible with input_len_ long numbers 
returns a pointer to it 
*******************************************************************************/
trie_ty* TrieCreate(address_ty num_bits_);
 
/*******************************************************************************
Destroys trie pointed to by trie_ 
NULL is OK
Time complexity O(size)
*******************************************************************************/
void TrieDestroy(trie_ty* trie_);

/*******************************************************************************
Returns the closest nubmer avaliable to the requested number_ 
Request 0 if address does not matter
Returns 0 if failed
Do not send NULL as trie_*/
address_ty TrieGet(trie_ty* trie_, address_ty number_);

/*******************************************************************************
Releases number_ 
Undefined if allready is released 
Do not send NULL as trie_*/
void TrieRelease(trie_ty* trie_, address_ty number_);

/*******************************************************************************
Returns the number of avaliable element 
Do not send NULL as trie_*/
size_t TrieAvaliable(const trie_ty* trie_);

#endif /*__BIN_TRIE_H_ILRD__*/
/***************/
