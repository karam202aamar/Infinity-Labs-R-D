/*******************************************************************************
 
*******************************************************************************/
#ifndef __UID_H_ILRD__
#define __UID_H_ILRD__

#include <sys/types.h>/*pid_t*/

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
int UIDIsSame(ilrd_uid_ty uid1, ilrd_uid_ty uid2);
#endif 
