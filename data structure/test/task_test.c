
#include <stdio.h>/*printf*/
/******************************************************************************/
#include "task.h"
/******************************************************************************/
int Add2(void *param);
/******************************************************************************/
static void CreateDestroyTest();
static void RunTest();
static void GetExeTimeTest();
static void GetUIDTest();
static void SetExeTimeTest();
/******************************************************************************/
int main()
{
	CreateDestroyTest();
	RunTest();
	GetExeTimeTest();
	GetUIDTest();
	SetExeTimeTest();
	
	return 0;
}
/******************************************************************************/
static void CreateDestroyTest()
{
	int val2 = 2;
	size_t inter = 2;
	
	task_ty *task = TaskCreate(Add2, inter, &val2);
	if(NULL == task)
	{
		printf("CreateDestroyTest : failed"); 
	}
	
	TaskDestroy(task);
}
/******************************************************************************/
int Add2(void *param)
{
	int num = *(int*)param;
	return (num + 2);
}
/******************************************************************************/
static void RunTest()
{
	int val2 = 2;
	size_t inter = 2;
	
	task_ty *task = TaskCreate(Add2, inter, &val2);
	
	if(4 != TaskRun(task))
	{
		printf("RunTest : failed got - %d\n", TaskRun(task)); 
	}
	
	TaskDestroy(task);
}
/******************************************************************************/
static void GetExeTimeTest()
{
	int val2 = 2;
	size_t inter = 2;
	
	task_ty *task = TaskCreate(Add2, inter, &val2);
	if(TaskGetTimeToRun(task) != time(NULL) + 2)
	{
		printf("GetExeTimeTest : failed got - %ld\n", TaskGetTimeToRun(task)); 
	}
	TaskDestroy(task);
}
/******************************************************************************/
static void GetUIDTest()
{
	int val2 = 2;
	size_t inter = 2;
	
	task_ty *task = TaskCreate(Add2, inter, &val2);
	task_ty *task2 = TaskCreate(Add2, inter, &val2);
	
	if(UIDSame(TaskGetUID(task), TaskGetUID(task2)))
	{
		printf("GetUIDTest : failed \n"); 
	}
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

/******************************************************************************/
static void SetExeTimeTest()
{
	int val2 = 2;
	size_t inter = 2;
	
	task_ty *task = TaskCreate(Add2, inter, &val2);
	
	TaskSetTimeToRun(task);
	
	if(TaskGetTimeToRun(task) != time(NULL) + 2)
	{
		printf("SetExeTimeTest : failed \n"); 
	}
	
	TaskDestroy(task);
	
}

