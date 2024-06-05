/*******************************************************************************
* Project: thread pool - cpp  
* Date: 05-Feb-2023
* Author: karam
* Reviewer: 
* Version: 1.0
*******************************************************************************/
#include <iostream>
#include "thread_pool.hpp"
/******************************************************************************/
namespace ilrd
{
namespace hrd26
{
/******************************************************************************/
bool Cmp(const std::shared_ptr<ITask>& IT1, const std::shared_ptr<ITask>& IT2)
{
    //pointers to instances (we defined < operator)
    return (*IT1 < *IT2);
}
/******************************************************************************/
ThreadPool::ThreadPool(size_t size_): m_threads(size_), m_num_of_threads(size_), m_tasks(Cmp)
{
    //init threads 
    ThreadsInit(m_num_of_threads); 
}
/******************************************************************************/
ThreadPool::~ThreadPool()
{
    Stop();
}
/******************************************************************************/
void ThreadPool::AddTask(std::shared_ptr<ITask> task_)
{
    m_tasks.Push(task_);
}
/******************************************************************************/
void ThreadPool::Stop()
{
    /* std::cout <<"5"<<std::endl; */
    /* assign stop task to all threads */
    for(size_t i = 0; i < m_num_of_threads; ++i)
    {
        std::shared_ptr<Stoptask> stoptask(new Stoptask());
        AddTask(stoptask);
    }
    /* check if joinable threads & join them */
    for(auto &threads_iter : m_threads)
    {
        if(threads_iter.joinable())
        {
            threads_iter.join();
        }
    }
}
/******************************************************************************/
void ThreadPool::Resume()
{
    m_cond.notify_all();
}
/******************************************************************************/
void ThreadPool::Suspend()
{
    for(std::size_t i=0; i < m_num_of_threads; ++i)
    {
        std::shared_ptr<Suspend_Itask> suspendtask(new Suspend_Itask);
        AddTask(suspendtask);
    }
}
/******************************************************************************/
void ThreadPool::ReSize(std::size_t new_size)
{
    /*check if the new_size is bigger the curr size*/
    if(new_size > m_num_of_threads)
    {
        ThreadsInit(new_size - m_num_of_threads);
    }
    /* if we got less threads than current */
    else
    {
        //add stop task
        for(std::size_t i=0; i < -(new_size - m_num_of_threads); ++i)
        {
            std::shared_ptr<Stoptask> stoptask(new Stoptask());
            AddTask(stoptask);
        }
    }
    //update numofthreads
    m_num_of_threads = new_size;
}
/******************************************************************************/
void ThreadPool::ThreadsInit(std::size_t num_of_threads)
{
    /* std::cout <<"9"<<std::endl; */
    for(std::size_t i=0; i < num_of_threads; ++i)
    {
        /*the threads in RUN mode*/
        m_threads.push_back(std::thread(&ThreadPool::AdministerFunc, this));
    }
}
/******************************************************************************/
void ThreadPool::AdministerFunc()
{
    while(1)
    {   
        /* keep looping & executing */
        try
        {
            while(1)
            {
                std::shared_ptr<ITask> curr_task;

                if (!m_tasks.IsEmpty())
                {
                    curr_task = m_tasks.Pop();
                    /*execute current task*/
                    curr_task->Execute();
                }
            }
        }
        catch(const Suspend_Itask& e)
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_cond.wait(lock); 
        }
        catch(const Stoptask& e)
        {
            return;
        }
    }

}
/******************************************************************************/
}
}