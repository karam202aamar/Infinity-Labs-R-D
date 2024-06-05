/*******************************************************************************
 * Project: Data Structures - UID
 * Date: 24/08/22
 * Name: HRD26
 * Reviewer: Rina
 * Version: 1.0 
*******************************************************************************/
#ifndef __UID_H_ILRD__
#define __UID_H_ILRD__

#include <unistd.h> /*pid_t*/
#include <time.h> /*time_t*/
#include <sys/types.h>

typedef struct ilrd_uid
{
	pid_t process_id;
	size_t counter;
	time_t id_time;
	
}ilrd_uid_ty;

/*UID signifying error*/
extern const ilrd_uid_ty UIDBadUID;

/*******************************************************************************
** Creates a new UID
** Return value: a new UID, on failure returns UIDBadUID
** Complexity: O(1)
*******************************************************************************/
ilrd_uid_ty UIDCreate(void);

/*******************************************************************************
** Checks if both UIDs given are the same
** Return value: 1 if same, else 0
** Complexity: O(1)
*******************************************************************************/
int UIDSame(ilrd_uid_ty uid1, ilrd_uid_ty uid2);

#endif /* __UID_H_ILRD__ */
