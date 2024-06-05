#include "scheduler.h"
#include <stdio.h>/*puts*/
/*****************************************************************************/
static void ImplementFunc();
static void CreateDestroyFunc();
static void SchedulerAddTaskTest();
static void RemoveCountIsEmptyTest();
static void SchedulerRunTest();
static void SchedulerClearTest();
static void SchedulerStopTest();

static func_status_ty TestFuncNeg(void *param);
static func_status_ty StopFuncTest(void *scheduler);
/*****************************************************************************/
int main()
{
	ImplementFunc();
	
	return 0; 
}
/*****************************************************************************/
static void ImplementFunc()
{
	CreateDestroyFunc();
	SchedulerAddTaskTest();
	RemoveCountIsEmptyTest();
	SchedulerRunTest();
	SchedulerClearTest();
	SchedulerStopTest();
}
/******************************CREATE DESTROY TEST******************************/
static void CreateDestroyFunc()
{
	scheduler_ty *scheduler = NULL;
	
	scheduler = SchedulerCreate();
	
	if(NULL == scheduler)
	{
		puts("CREATION FAILED");
	}
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
}
/*******************************ADD TASK TEST**********************************/
static void SchedulerAddTaskTest()
{
	ilrd_uid_ty id_task;
	size_t interval = 1;
	int param = -5; 
	
	scheduler_ty *scheduler = SchedulerCreate();
	
	id_task = SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	
	if(UIDSame(UIDBadUID,id_task))
	{
		puts("ADD TASK FAILED");
	}
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
}
/**************************REMOVE COUNT ISEMPTY TEST***************************/
static void RemoveCountIsEmptyTest()
{
	ilrd_uid_ty id_task;
	size_t interval = 1;
	int param = -5; 
	
	scheduler_ty *scheduler = SchedulerCreate();
	
	id_task = SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	
	if(1 != SchedulerCount(scheduler))
	{
		puts("COUNT FAILED");
	}
	
	if(SchedulerRemoveTask(scheduler,id_task))
	{
		puts("REMOVE TASK FAILED");
	}
	
	if(0 != SchedulerCount(scheduler))
	{
		puts("COUNT AND COUNT FAILED");
	}
	
	if(1 != SchedulerIsEmpty(scheduler))
	{
		puts("ISEMPTY FAILED");
		
	}
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
}
/********************************* RUN TEST ***********************************/
static void SchedulerRunTest()
{
	size_t interval = 1;
	int param = -2; 
	scheduler_ty *scheduler = SchedulerCreate();
	
	SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	
	if(0 != SchedulerRun(scheduler))
	{
		puts("SchedulerRunTest FAILED");
	}
	
	if(1 != SchedulerIsEmpty(scheduler))
	{
		puts("FAILED TO EMPTY AFTER RUN1");
	}
	
	param = -4;
	
	SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	
	if(0 != SchedulerRun(scheduler))
	{
		puts("SchedulerRunTest FAILED");
	}
	
	if(1 != SchedulerIsEmpty(scheduler))
	{
		puts("FAILED TO EMPTY AFTER RUN1");
	}
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
}
/******************************** CLEAR TEST **********************************/
static void SchedulerClearTest()
{
	size_t interval = 1;
	int param = -5; 
	scheduler_ty *scheduler = SchedulerCreate();
	
	SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	
	SchedulerClear(scheduler);
	
	if(1 != SchedulerIsEmpty(scheduler))
	{
		puts("CLEAR FAILED");
	}
	SchedulerDestroy(scheduler);
	scheduler = NULL;
}
/******************************** STOP TEST **********************************/
static void SchedulerStopTest()
{
	size_t interval = 1;
	size_t stop_interval = 2;
	int param = -3; 
	
	scheduler_ty *scheduler = SchedulerCreate();
	
	SchedulerAddTask(scheduler , interval , TestFuncNeg , &param);
	SchedulerAddTask(scheduler , stop_interval , StopFuncTest , scheduler);
	
	
	if(2 != SchedulerRun(scheduler))
	{
		puts("SchedulerStop FAILED");
	}
	
	if(0 != param)
	{
		puts("FAILED TO STOP AT THE TIME");
	}
	
	if(2 != SchedulerCount(scheduler))
	{
		puts("COUNT NUM OF TASKS FAILED ");
	}
	SchedulerDestroy(scheduler);
	scheduler = NULL;
}
/********************************* test func **********************************/
static func_status_ty TestFuncNeg(void *param)
{
	if(*(int *)param > 0)
	{
		return FAIL;
	}
	
	if(*(int *)param < 0)
	{
		*(int*)param = *(int*)param + 1;
		
		return REPEAT;
	}
	return SUCCESS;	
}
/********************************* stop func **********************************/
static func_status_ty StopFuncTest(void *scheduler)
{
	SchedulerStop((scheduler_ty *)scheduler);
	
	return REPEAT;
}






















