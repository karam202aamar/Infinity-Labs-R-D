/*******************************************************************************
* Project: Itask - cpp  for delete 
* Date: 05-Feb-2023
* Author: karam
* Reviewer: 
* Version: 1.0
*******************************************************************************/
#include "Itask.hpp"

using namespace ilrd::hrd26;
/******************************************************************************/
ITask::ITask(Priority priority_): m_priority(priority_) 
{
    //empty
}
bool ITask::operator<(const ITask& other_)
{
    return m_priority < other_.m_priority;
}

/******************************************************************************/
