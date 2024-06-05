/*******************************************************************************
 Project: Data Structure - DHCP
 Date:31/10/22
 Name: karam
 Reviewer: 
 Version: 1.0
*******************************************************************************/
#ifndef __DHCP_H_ILRD__
#define __DHCP_H_ILRD__

#include <stddef.h> /* size_t */

typedef struct DHCP dhcp_ty;
typedef unsigned int ip_ty;

/* the user provides subnet_id_ & num of bits */
dhcp_ty *DHCPCreate(ip_ty subnet_id_, unsigned int mask_bit_count_);

void DHCPDestroy(dhcp_ty* dhcp); 

/* Returns allocated address or NULL on failure. If specific address is of no
 * importance, request zero (preceeded by subnet id). */
size_t DHCPAllocateIP(dhcp_ty* dhcp_, size_t ip_requested_);

/* note: addresses 0, 254 & 255 are non-freeable */
void DHCPFreeIP(dhcp_ty* dhcp_, ip_ty ip_requested_);

size_t DHCPCountFree(const dhcp_ty *dhcp_);

#endif /*__DHCP_H_ILRD__*/



