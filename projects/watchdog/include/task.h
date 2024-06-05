/*******************************************************************************

*******************************************************************************/
#ifndef __TASK_H_ILRD__
#define __TASK_H_ILRD__

#include <sys/types.h> /* time_t , size_t */

#include "uid.h"

/*******************************************************************************
** Description: This is a user defined task 
** Return value: 	-1 - fail 	
					 0 - success
					 1 - repeat
** Complexity: O(1)
*******************************************************************************/
typedef int (*task_op_func_ty)(void *param);
/******************************************************************************/
typedef struct task task_ty;
/*******************************************************************************
** Description: Creates a new task
** Return value: pointer to the task , return NULL if fail
** Undefined Behavior: If interval == 0
					   If operation is not of type operation_func_ty
** Complexity: O(1)
*******************************************************************************/
task_ty *TaskCreate(task_op_func_ty operation, size_t interval, void *param);

/*******************************************************************************
** Description: Destroys a task
** Undefined Behavior: If task is NULL
** Complexity: O(1)
*******************************************************************************/
void TaskDestroy(task_ty *task);

/*******************************************************************************
** Description: Runs a task
** Return value:   -1 - fail
					0 - success 
					1 - repeat
** Undefined Behavior:  If task is NULL
** Complexity: O(1)
*******************************************************************************/
int TaskRun(task_ty *task);

/*******************************************************************************
** Description: The function should retrieve task's uid to the user
** Return value: UID of task
** Undefined Behavior: If task is NULL
** Complexity: O(1)
*******************************************************************************/
ilrd_uid_ty TaskGetUID(task_ty *task);

/*******************************************************************************
** Description: Sets time to run 
** Undefined Behavior: If task is NULL
** Complexity: O(1)
*******************************************************************************/
void TaskSetTimeToRun(task_ty *task);

/*******************************************************************************
** Description: Retrieves the time to run 
** Return value: Time to run
** Undefined Behavior: If task is NULL
** Complexity: O(1)
*******************************************************************************/
time_t TaskGetTimeToRun(task_ty *task);

#endif /* __TASK_H_ILRD__ */
