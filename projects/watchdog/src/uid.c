/*******************************************************************************

*******************************************************************************/
#include <errno.h>/*errno*/
#include <stdio.h>/*perror*/
#include <unistd.h> /*getpid*/
#include <time.h> /*time_t*/

#include "uid.h"
/*UID signifying error*/
const ilrd_uid_ty UIDBadUID = {0,0,0};

ilrd_uid_ty UIDCreate(void)
{
	/*Initialize static counter*/
	static size_t counter = 0;
	/*Set the unique UID*/
	ilrd_uid_ty new_uid;	
	new_uid.process_id = getpid();
	new_uid.counter = ++counter;
	new_uid.id_time = time(NULL);
	/*If there is an error*/
	if(errno)
	{
		return UIDBadUID;
	}
	
	return new_uid;
}

int UIDIsSame(ilrd_uid_ty uid1, ilrd_uid_ty uid2)
{
	int is_same_process_id = uid1.process_id == uid2.process_id;
	int is_same_counter = uid1.counter == uid2.counter;
	int is_same_id_time = uid1.id_time == uid2.id_time;
	
	return is_same_process_id && is_same_counter && is_same_id_time;
}
