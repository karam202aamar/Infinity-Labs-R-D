/*******************************************************************************
 * Project: Data Structures - Bin Trie
 * Date: 31/10/22
 * Name: 
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#include <stdio.h>
#include "dhcp.h"
/******************************************************************************/
void DHCPCreateAndDestroyTest(void);
void DHCPAllocateIpTest(void);
void DHCPFreeIpTest(void);
void DHCPCountFreeTest(void);
/******************************************************************************/
int main()
{
	DHCPCreateAndDestroyTest();
	DHCPAllocateIpTest();
	DHCPFreeIpTest();
	DHCPCountFreeTest();
	
	return 0;
}
/******************************************************************************/
/*Note: the number 12626142 represents the subnet mask for: 192.168.111*/

void DHCPCreateAndDestroyTest(void)
{
	dhcp_ty *new_dhcp = DHCPCreate(12626142, 8);
	
	if(!new_dhcp)
	{
		puts("DHCP creation failed");
	}
	
	DHCPDestroy(new_dhcp);
}
/******************************************************************************/
void DHCPAllocateIpTest(void)
{
	dhcp_ty *new_dhcp = DHCPCreate(12626142, 8);
	
	ip_ty address = DHCPAllocateIP(new_dhcp, 3232292552);
	
	if(3232292552 != address)
	{
		puts("DHCP allocation failed.");
	}
	
	address = DHCPAllocateIP(new_dhcp, 3232292552);
	
	if(3232292553 != address)
	{
		puts("DHCP allocation test2 failed.");
	}
	
	address = DHCPAllocateIP(new_dhcp, 0);
	
	if(3232292353 != address)
	{
		puts("DHCP allocation test3 failed.");
	}
	
	address = DHCPAllocateIP(new_dhcp, 0);
	
	if(3232292354 != address)
	{
		puts("DHCP allocation test4 failed.");
	}
	
	DHCPDestroy(new_dhcp);
}
/******************************************************************************/
void DHCPFreeIpTest(void)
{
	dhcp_ty *new_dhcp = DHCPCreate(12626142, 8);
	
	ip_ty address = DHCPAllocateIP(new_dhcp, 3232292552);
	DHCPFreeIP(new_dhcp, 3232292552);
	address = DHCPAllocateIP(new_dhcp, 3232292552);
	
	if(3232292552 != address)
	{
		puts("DHCP allocation test failed.");
	}
	
	DHCPDestroy(new_dhcp);
}
/******************************************************************************/
void DHCPCountFreeTest(void)
{
	dhcp_ty *new_dhcp = DHCPCreate(12626142, 8);
	
	size_t idx = 0;
	
	if(253 != DHCPCountFree(new_dhcp))
	{
		puts("DHCP count free test1 failed.");		
	}
	
	DHCPAllocateIP(new_dhcp, 3232292552);
	DHCPAllocateIP(new_dhcp, 3232292552);
	DHCPAllocateIP(new_dhcp, 0);
	
	if(250 != DHCPCountFree(new_dhcp))
	{
		puts("DHCP count free test2 failed.");		
	}
	
	for(idx = 0; idx < 250; ++idx)
	{
		DHCPAllocateIP(new_dhcp, 0);
	}
	
	if(0 != DHCPCountFree(new_dhcp))
	{
		puts("DHCP count free test2 failed.");		
	}
	
	DHCPFreeIP(new_dhcp, 3232292552);
	DHCPFreeIP(new_dhcp, 3232292554);
	
	if(2 != DHCPCountFree(new_dhcp))
	{
		puts("DHCP count free test2 failed.");		
	}
	
	DHCPDestroy(new_dhcp);
}
/******************************************************************************/
