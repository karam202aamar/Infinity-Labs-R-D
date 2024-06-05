/*******************************************************************************
 * Project: Data Structures - UID
 * Date: 24/08/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0 
*******************************************************************************/
#include <unistd.h>
#include <time.h>
#include <errno.h>


#include "uid.h"
/******************************************************************************/
const ilrd_uid_ty UIDBadUID = {0 , 0 , 0};
/******************************************************************************/
ilrd_uid_ty UIDCreate()
{
	ilrd_uid_ty pid;
	
	static size_t count = 0;
	
	pid.process_id = getpid();
	pid.id_time = time(0);
	
	if(-1 == pid.id_time)
	{
		return UIDBadUID;
	}else
	{
		pid.counter = ++count;
	}
	
	return pid;
}
/******************************************************************************/
int UIDSame(ilrd_uid_ty uid1, ilrd_uid_ty uid2)
{
	if(uid1.process_id == uid2.process_id && uid1.counter == uid2.counter 
						&& uid1.id_time == uid2.id_time)
	{
		return 1;					
	}
	return 0; 
}
/******************************************************************************/
