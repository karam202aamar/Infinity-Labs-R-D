
#ifndef __SCHEDULER_H_ILRD__
#define __SCHEDULER_H_ILRD__

#include "p_queue.h"
#include "uid.h"
/******************************************************************************/
typedef struct scheduler scheduler_ty;
/******************************************************************************/
typedef enum {FAIL = -1, SUCCESS = 0, REPEAT = 1}func_status_ty;
/*******************************************************************************
** Description: This is a user defined task 
** Return value: 	-1 - fail 	
					 0 - success
					 1 - repeat
** Complexity: O(1)
*******************************************************************************/
typedef func_status_ty (*operation_func_ty)(void *param);

/*******************************************************************************
** Description: Creates a new scheduler
** Return value: Pointer to the new scheduler, return NULL if fail
** Complexity: O(1)
*******************************************************************************/
scheduler_ty *SchedulerCreate(void);

/*******************************************************************************
** Description: Destroys the scheduler
** Undefined Behavior: If the scheduler pointer is NULL
** Complexity: O(n)
*******************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler);

/*******************************************************************************
** Description: Adds a new task to the scheduler
** Return value: Task UID, if Failed return "BAD UID"
** Undefined Behavior: 
**					   If operation is NULL or is not of type operation_func_ty
**					   If scheduler pointer is NULL
**					   If interval == 0
** Complexity: O(n)
*******************************************************************************/
ilrd_uid_ty SchedulerAddTask(scheduler_ty *scheduler, size_t interval , 
									  operation_func_ty operation, void *param);

/*******************************************************************************
** Description: Removes a task from the scheduler
** Return value: 0 - Success 
**				 1 - Failure
** Undefined Behavior:  If scheduler pointer is NULL
** Complexity: O(n)
*******************************************************************************/
int SchedulerRemoveTask(scheduler_ty *scheduler, ilrd_uid_ty id);

/*******************************************************************************
** Description: Runs all tasks on the scheduler
** Return value:   0 - success
				   1 - task fail
				   2 - stopped
				   3 - sysfail 
** Notes: 
		- If task fails, Run is stopped
		- If a task's run time has passed, it will be run again
		- If two or more tasks are supposed to run at the same time, 
		  it's unspecified in which order tasks will run
** Undefined Behavior: If scheduler pointer is NULL
** Complexity: O(n)
*******************************************************************************/
int SchedulerRun(scheduler_ty *scheduler);

/*******************************************************************************
** Description: Stops all running tasks on the scheduler
** Undefined Behavior: If scheduler pointer is NULL
** Complexity: O(1)
*******************************************************************************/
void SchedulerStop(scheduler_ty *scheduler);

/*******************************************************************************
** Description: Counts all tasks in the scheduler
** Return value: Number of tasks of the scheduler
** Undefined Behavior: If scheduler pointer is NULL
** Complexity: O(n)
*******************************************************************************/
size_t SchedulerCount(const scheduler_ty *scheduler);

/*******************************************************************************
** Description: Checks if the scheduler is empty
** Return value: 1 - True
**				 0 - False
** Undefined Behavior: If scheduler pointer is NULL
** Complexity: O(1)
*******************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler);

/*******************************************************************************
** Description: Removes all tasks from the scheduler
** Undefined Behavior: If scheduler pointer is NULL
** Complexity: O(n)
*******************************************************************************/
void SchedulerClear(scheduler_ty *scheduler);

#endif /* __SCHEDULER_H_ILRD__ */
