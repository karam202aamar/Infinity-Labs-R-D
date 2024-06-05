/*******************************************************************************
 * Project: Data Structures  - Scheduler
 * Date: 28/08/22
 * Name: karam
 * Reviewer: idan
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>  /* perror */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc , free */
#include <string.h> /* strerror */
#include <errno.h>  /* errno */
#include <time.h>  /* time */
#include <sys/types.h>  /* time_t */
#include <unistd.h>  /* sleep */
/******************************************************************************/
#include "p_queue.h"
#include "uid.h"
#include "task.h"
#include "scheduler.h"
/******************************************************************************/
static int SortingType(const void *list_data,const void *new_data);
static int CompareData(void *data, void *param);
/******************************************************************************/
typedef enum STOP_STATUS {STOP = 0 , RUN } stop_status_ty;
typedef enum RUN_FUNC {SUCCESSED = 0 , FAILED , STOPPED , SYSFAILED} run_func_ty;
/******************************************************************************/
struct scheduler 
{
	pq_ty * pqueue;
	int status;
	
}; /* scheduler_ty */
/******************************************************************************/
scheduler_ty *SchedulerCreate()
{
	/* define a new scheduler*/
	scheduler_ty *scheduler = NULL;
	
	/* dynamically allocate new scheduler */
	scheduler =  (scheduler_ty*)malloc(sizeof(scheduler_ty));

	/* check allocation */
	if(NULL == scheduler)
	{
		perror(strerror(errno));
		return NULL;
	}
	
	/* init p-queue call create func of pqueue list */
	scheduler->pqueue = PQCreate(SortingType);
	
	/* check allocation */
	if(NULL == scheduler->pqueue)
	{
		free(scheduler);
		scheduler = NULL;
		
		return NULL;
	}
	scheduler->status = RUN ;
	return scheduler;
}
/******************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler)
{
	/* assert scheduler */
	assert(scheduler);
	
	SchedulerClear(scheduler);
	
	PQDestroy(scheduler -> pqueue);
	scheduler -> pqueue = NULL;
	
	free(scheduler);
	scheduler = NULL;
}
/******************************************************************************/
ilrd_uid_ty SchedulerAddTask(scheduler_ty *scheduler, size_t interval , 
				operation_func_ty operation, void *param)
{	
	/* void ptr_new_task TO new task */
	task_ty *ptr_new_task = NULL;
	
	assert(operation);
	assert(scheduler);
	assert(interval != 0);

	/* ptr_new_task - holds ptr to task */
	ptr_new_task = TaskCreate(operation,interval,param);
	
	/* insert it to the queue */
	if(PQEnqueue(scheduler -> pqueue , ptr_new_task))
	{
		return UIDBadUID;
	}
	
	/* retrun the UID */
	return TaskGetUID(ptr_new_task);
}
/******************************************************************************/
int SchedulerRemoveTask(scheduler_ty *scheduler, ilrd_uid_ty id)
{
	task_ty *task = NULL;
	pq_is_match_ty compare_func = CompareData;
	
	assert(scheduler);
	
	task = (task_ty*)PQErase(scheduler -> pqueue , compare_func,&id);
	
	if(NULL == task)
	{
		return 1;
	}else
	{
		TaskDestroy(task);
		return  0;
	}
}
/******************************************************************************/
int SchedulerRun(scheduler_ty *scheduler)
{
	/* define variable contains func retrun value */
	int  return_val = 0;
	
	/* define variable contains current time */
	time_t curr_time = time(NULL);
	
	/* define ptr to current task */
	task_ty *curr_task = NULL;
	
	/* loop while scheduler not empty & NO order to stop */
	while(SchedulerIsEmpty(scheduler) != 1 && scheduler->status == RUN)
	{
		
		curr_time = time(NULL);
		curr_task = PQDequeue(scheduler -> pqueue);
		
		/* check if system function works */
		if(FAIL == curr_time)
		{
			return SYSFAILED;
		}
		
		/* check if the time of the function passed */
		if(TaskGetTimeToRun(curr_task) < curr_time)
		{
			/* call the run function and set the return value */
			return_val = TaskRun(curr_task);
			
			
		}else /* if not then sleep untill the desired time */
		{
			/* sleep untill the desired time */
			sleep(TaskGetTimeToRun(curr_task) - curr_time);
			/* implement run after sleep */
			return_val = TaskRun(curr_task);	
		}
		/* check if we want to repeat */
		if(REPEAT == return_val)
		{
			/* 
			repeat the function-enqueue by priority 
			 update the task time 
			*/
			PQEnqueue(scheduler -> pqueue , curr_task);
			TaskSetTimeToRun(curr_task);
		}else if(FAIL == return_val)
		{
			TaskDestroy(curr_task);
			/* return fail */
			return FAILED;
			
		}else if(SUCCESS == return_val)
		{
			TaskDestroy(curr_task);
		}	
	}
	/*If the running process has been stopped. */
	if(0 == scheduler->status)
	{	
		return STOPPED;
	}
	
	return SUCCESSED;
}
 /* typedef enum {FAIL = -1, SUCCESS = 0, REPEAT = 1}func_status_ty; */
/******************************************************************************/
void SchedulerStop(scheduler_ty *scheduler)
{
	assert(scheduler);
	
	scheduler->status = STOP;
}
/******************************************************************************/
size_t SchedulerCount(const scheduler_ty *scheduler)
{
	assert(scheduler);
	
	return PQSize(scheduler -> pqueue);
}
/******************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(scheduler);
	
	return PQIsEmpty(scheduler -> pqueue);
}
/******************************************************************************/
void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *task = NULL;
	assert(scheduler);
	
	while(1 != SchedulerIsEmpty(scheduler))
	{
		task = PQDequeue(scheduler -> pqueue);
		free(task);
		task = NULL;
	}
}
/********************************sorting rule**********************************/
static int SortingType(const void *list_data,const void *new_data)
{
	
	/*
	   the sorting is by TaskGetTimeToRun function  
	   we take the whole struct task as a void ptr 
	   and use the function to get the time
	*/
	if(TaskGetTimeToRun(list_data) > TaskGetTimeToRun(new_data))
	{
		return 1;
	}else
	{
		if(TaskGetTimeToRun(list_data) < TaskGetTimeToRun(new_data))
		{
			return -1;
		}else
		{
			return 0;
		}
	}
}
/**********************************compare data********************************/
static int CompareData(void *task, void *uid)
{
	if(UIDSame(TaskGetUID(task),*(ilrd_uid_ty*)uid))
	{
		return 1;
	}
	return 0;
}
/******************************************************************************/




