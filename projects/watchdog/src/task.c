/*******************************************************************************

*******************************************************************************/
#include <sys/types.h> /* time_t , size_t */
#include <time.h>/*time*/
#include <assert.h> /*assert*/
#include <stdlib.h>/*malloc, free*/
#include <errno.h>/*errno*/
#include <stdio.h>/*perror*/
#include <string.h>/*strerr*/

#include "uid.h"
#include "task.h"

/******************************************************************************/
struct task
{
	void *param;
	task_op_func_ty task_func;
	size_t interval;
	time_t time_to_run;
	ilrd_uid_ty uid;
};
/******************************************************************************/
task_ty *TaskCreate(task_op_func_ty operation, size_t interval, void *param)
{
	task_ty *task = (task_ty *)malloc(sizeof(task_ty));
	time_t curr_time = time(NULL);
	
	assert(interval > 0);
	/*Allocate memory for a new task.*/
	if(NULL == task)
	{
		perror(strerror(errno));
		task = NULL;
		return NULL;
	}
	/*Set all the task's fields.*/
	task->param = param;
	task->task_func = operation;
	task->interval = interval;
	/*Get the current time.*/
	curr_time = time(NULL);
	task->time_to_run = curr_time + interval;
	task->uid = UIDCreate();
	
	return task;
}
/******************************************************************************/
void TaskDestroy(task_ty *task)
{
	assert(task);
	
	free(task);
	task = NULL;
}
/******************************************************************************/
int TaskRun(task_ty *task)
{
	void *param = task->param;
	
	assert(task);
	return task->task_func(param);	
}
/******************************************************************************/
ilrd_uid_ty TaskGetUID(task_ty *task)
{
	assert(task);
	return task->uid;
}
/******************************************************************************/
void TaskSetTimeToRun(task_ty *task)
{
	assert(task);
	task->time_to_run = time(NULL) + task->interval;
}
/******************************************************************************/
time_t TaskGetTimeToRun(task_ty *task)
{
	assert(task);
	return task->time_to_run;
}

