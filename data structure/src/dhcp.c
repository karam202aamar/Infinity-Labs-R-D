/*******************************************************************************
 * Project: DHCP
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
#include <stddef.h>     /*size_t*/
/******************************************************************************/
#include "dhcp.h"
#include "bin_trie.h"
/******************************************************************************/
enum {ONE_BIT_MASK = 1};
enum {SERVER_ADDRESS = 254, BROADCAST_ADDRESS = 255};
/******************************************************************************/
struct DHCP
{
	trie_ty *bin_trie;
	ip_ty subnet_id;
	ip_ty mask_bit_count_;
};/*dhcp_ty*/

/******************************************************************************/
dhcp_ty *DHCPCreate(ip_ty subnet_id_, unsigned int mask_bit_count_)
{
	size_t server_address = SERVER_ADDRESS;
	size_t broadcast_address = BROADCAST_ADDRESS;
	/* Dyanmically Allocate memory for the dhcp */
	dhcp_ty *new_dhcp = (dhcp_ty *)malloc(sizeof(dhcp_ty));

    /* check if allocation failed */
	if(!new_dhcp)
	{
		perror("dhcp Allocation failed");
		return NULL;
	}
	/*Create a new bin_trie and initialize.*/
	new_dhcp->bin_trie = TrieCreate(mask_bit_count_);
	new_dhcp->subnet_id = subnet_id_;
    new_dhcp->mask_bit_count_ = mask_bit_count_;

	/* check if allocation failed */
	if(!new_dhcp->bin_trie)
	{
		perror("trie Allocation failed");
		free(new_dhcp);
		new_dhcp = NULL;
		return NULL;
	}
	/* shift left to get subnet mask with zeros in the right side */
	new_dhcp->subnet_id = subnet_id_<< mask_bit_count_;
	
	/* allocate address for broadcast address - 255 */
	DHCPAllocateIP(new_dhcp, broadcast_address);
	/* allocate address for server address - 254*/
	DHCPAllocateIP(new_dhcp, server_address);

	return new_dhcp;
}
/******************************************************************************/
void DHCPDestroy(dhcp_ty* dhcp_)
{
	assert(dhcp_);

	TrieDestroy(dhcp_->bin_trie);
	dhcp_->bin_trie = NULL;
	free(dhcp_);
}
/******************************************************************************/
size_t DHCPAllocateIP(dhcp_ty* dhcp_, size_t ip_requested_)
{
	size_t requested_host_adres = 0;

	assert(dhcp_);
	/* get HOST Address */
	requested_host_adres =  ip_requested_ ^ dhcp_->subnet_id;

	return (dhcp_->subnet_id | TrieGet(dhcp_->bin_trie, requested_host_adres));

}
/******************************************************************************/
void DHCPFreeIP(dhcp_ty* dhcp_, ip_ty ip_requested_)
{
	assert(dhcp_);

	if(ip_requested_ != 0 && ip_requested_ != SERVER_ADDRESS && 
											 ip_requested_ != BROADCAST_ADDRESS)
	{
		/* call BinTrieRelease */
		TrieRelease(dhcp_->bin_trie, ip_requested_);
	}
}
/******************************************************************************/
size_t DHCPCountFree(const dhcp_ty *dhcp_)
{
	assert(dhcp_);
	
	return TrieAvaliable(dhcp_->bin_trie);
}
/******************************************************************************/




