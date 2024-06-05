
#include <time.h> /*time_t*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h>/*assert*/
#include <unistd.h>/*sleep*/
#include <errno.h>/*errno*/
#include <string.h>/*strerror*/
#include <stdio.h>/*perror*/

#include "p_queue.h"
#include "uid.h"
#include "scheduler.h"
#include "task.h"
/******************************************************************************/
static int CompareFunction(const void *task1, const void *task2);
static int UidCompare(void *task_uid, void *search_uid);
/******************************************************************************/
struct scheduler
{
	pq_ty *p_q;
	int action_status;
};
/******************************************************************************/
typedef enum RUN_STATUS {RUN_SUCCESS = 0, TASK_FAIL = 1, STOPPED = 2,
													   SYSFAIL = 3} run_stat_ty;			
																	
typedef enum STOP_STATUS {STOP = 0, RUN} stop_stat_ty;

typedef enum STATUS {REMOVE_SUCCESS = 0, REMOVE_FAIL = 1} status_ty;
/******************************************************************************/
scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *scheduler = NULL;
	scheduler = (scheduler_ty*)malloc(sizeof(scheduler_ty));
	/*Check if scheduler's allocation has been successful*/
	if(NULL == scheduler)
	{
		perror(strerror(errno));
		return NULL;
	}
	/*Allocate memory for the priority queue.*/
	scheduler->p_q = PQCreate(CompareFunction);
	/*Check if p-q allocation has been successful*/
	if(!scheduler->p_q)
	{
		free(scheduler);
		
		scheduler = NULL;
		scheduler->p_q = NULL;
		return NULL;
	}
	/*Initialize run flag.*/
	scheduler->action_status = STOP;
	
	return scheduler;
}
/******************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(scheduler);
	/*Destroy the scheduler and it's elements.*/
	SchedulerClear(scheduler);
	PQDestroy(scheduler->p_q);
	scheduler->p_q = NULL;
	free(scheduler);
	scheduler = NULL;
}
/******************************************************************************/
ilrd_uid_ty SchedulerAddTask(scheduler_ty *scheduler, size_t interval , 
									   operation_func_ty operation, void *param)
{
	/*Create a new task.*/
	task_ty *task = NULL;
	ilrd_uid_ty uid = UIDBadUID;
	int status = 0;
	
	assert(interval > 0);
	assert(scheduler);
	
	task = TaskCreate(operation, interval, param);
	
	if(!task)
	{
		return UIDBadUID;
	}
	/*Get task's uid.*/
	uid = TaskGetUID(task);
	/*Check task's status and enqueue the newly create task to the p_q.*/
	status = PQEnqueue(scheduler->p_q, task);

	/*If the task addition has failed.*/
	if(status)
	{
		TaskDestroy(task);
		return UIDBadUID;
	}
	/*If the enqueue has been successful-return the uid.*/

	return uid;

}
/******************************************************************************/
int SchedulerRemoveTask(scheduler_ty *scheduler, ilrd_uid_ty id)
{
	task_ty *task= NULL;
	pq_is_match_ty match_func = UidCompare; 
	
	assert(scheduler);
	/*Check if the given task uid is present within the p_q.*/
	task = (task_ty *)PQErase(scheduler->p_q, match_func, &id);
	
	if(!task)
	{
		return REMOVE_FAIL;
	}
	TaskDestroy(task);
	/*Check if remove has been successfully performed.*/
	if(!task)
	{
		return REMOVE_FAIL;
	}
	
	return REMOVE_SUCCESS;
}
/******************************************************************************/
int SchedulerRun(scheduler_ty *scheduler)
{	
	task_ty *task = NULL;
	time_t run_time = time(NULL);
	time_t current_time = time(NULL);
	int task_status = 0;
	int enqueue_status = 0;
	
	assert(scheduler);
	/*Set the running flag to a run state.*/
	scheduler->action_status = RUN;
	/*Run until there are no more missions inside the p_q and stopping hasn't 
	been issued.*/
	while(RUN == scheduler->action_status && !PQIsEmpty(scheduler->p_q))
	{
		/*Get the task which will be executed.*/
		task = (task_ty *)PQDequeue(scheduler->p_q);
		/*Get the run time of the given task.*/
		run_time = TaskGetTimeToRun(task);
		/*Current time*/
		current_time = time(NULL);

		/*Check if there is a need for waiting.*/
		while(current_time < run_time)
		{
			sleep(run_time - current_time);
			current_time = time(NULL);
		}
		/*Run the task and save it's status.*/
		task_status = TaskRun(task);
		/*If task status is a fail status.*/
		if(FAIL == task_status)
		{
			TaskDestroy(task);
			return TASK_FAIL;
		}
		/*If the task has been successfully finished.*/
		else if(SUCCESS == task_status)
		{
			TaskDestroy(task);
			task = NULL;
		}
		/*If a given task should be repeated.*/
		else
		{
			/*Set mission's new time to run*/
			TaskSetTimeToRun(task);
			/*Enqueue the task to the p_q*/
			enqueue_status = PQEnqueue(scheduler->p_q, task);
			if(enqueue_status)
			{
				return SYSFAIL;
			}
		}
	}
	/*If the running process has been stopped.*/
	if(STOP == scheduler->action_status)
	{
		scheduler->action_status = RUN;
		return STOPPED;
	}
	
	return RUN_SUCCESS;
}
/******************************************************************************/
void SchedulerStop(scheduler_ty *scheduler)
{
	assert(scheduler);
	
	scheduler->action_status = STOP;
}
/******************************************************************************/
size_t SchedulerCount(const scheduler_ty *scheduler)
{
	assert(scheduler);
	
	return PQSize(scheduler->p_q);
}
/******************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(scheduler);
		
	return PQIsEmpty(scheduler->p_q);
}
/******************************************************************************/
void SchedulerClear(scheduler_ty *scheduler)
{
	assert(scheduler);
	
	while(!PQIsEmpty(scheduler->p_q))
	{
		TaskDestroy(PQDequeue(scheduler->p_q));
	}
}
/*****************************Auxilary functions*******************************/
static int CompareFunction(const void *task1, const void *task2)
{
	task_ty *list_task = (task_ty *)task1;
	task_ty *node_task = (task_ty *)task2;
	
	time_t time_to_run = TaskGetTimeToRun(node_task);
	time_t list_time = TaskGetTimeToRun(list_task);
	/*Sort the p_q by time to run.*/
	if(list_time > time_to_run)
	{
		return 1;	
	}
	
	else if(list_time < time_to_run)
	{
		return -1;
	}
	
	else
	{
		return 0;
	}
}
/******************************************************************************/
static int UidCompare(void *task_uid, void *search_uid)
{
	/*Compare uid's*/
	ilrd_uid_ty uid = *(ilrd_uid_ty *)search_uid;
	task_ty *task = (task_ty *)task_uid;
	
	int result = UIDIsSame(TaskGetUID(task), uid);
	
	return result;	
}


