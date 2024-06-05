/******************************************************************************/
#include <stdio.h>  /* print */
#include <assert.h> /* NULL pointers check */
#include <stdlib.h> /* allocation */
#include <string.h> /* memcpy strerror */
#include <errno.h>  /* errno perror */
/******************************************************************************/
#include "uid.h"
#include "task.h"
/******************************************************************************/
struct task
{
    ilrd_uid_ty id;		     /* id for each function */
    size_t interval;                 /* repeative time of function */
    time_t time_to_run; 	     /* when to implement */
    void *param;		     /* argument from the user to the function*/
    task_op_func_ty operation;     /* function to do  */
    
}; /* task_ty */
/******************************************************************************/
task_ty *TaskCreate(task_op_func_ty operation, size_t interval,void *param)
{
	/* define a new task*/
	task_ty *task = NULL;
	
	/* dynamically allocate new task */
	task =  (task_ty*)malloc(sizeof(task_ty));
	
	/* check allocation */
	if(NULL == task)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	/* init task */
	task -> id = UIDCreate();
	
	/* check if UID worked */
	if(UIDSame(UIDBadUID , task->id))
	{
		free(task);
		task = NULL;
		return NULL;
	}
	
	task -> interval = interval;
	task -> time_to_run = time(NULL) + interval;
	task -> param = param;
	task -> operation = operation;
	
	/* return the new task */
	return task;
}
/******************************************************************************/
void TaskDestroy(task_ty *task)
{
	/* assert task */
	assert(task);

	free(task);
	task = NULL;
}
/******************************************************************************/
int TaskRun(task_ty *task) 
{
	assert(task);
	
	return task -> operation(task -> param);
}
/******************************************************************************/
ilrd_uid_ty TaskGetUID(task_ty *task)
{	
	assert(task);
	
	return task -> id;
}
/******************************************************************************/
void TaskSetTimeToRun(task_ty *task)
{
	assert(task);
	
	task -> time_to_run = time(NULL) + task ->interval;
	
}
/******************************************************************************/
time_t TaskGetTimeToRun(const task_ty *task)
{
	assert(task);
	
	return task -> time_to_run;
}
/******************************************************************************/
