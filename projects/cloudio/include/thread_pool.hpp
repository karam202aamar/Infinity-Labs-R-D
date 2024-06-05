/*******************************************************************************
 * Project: thread pool
 * Date: 05-Feb-2023
 * Author: HRD26
 * Reviewer: TBD
 * Version: 1.0
 *******************************************************************************/
#ifndef __ILRD_HRD26_THREAD_POOL_HPP__
#define __ILRD_HRD26_THREAD_POOL_HPP__
/******************************************************************************/
#include <thread>             //thread
#include <vector>             //vector
#include <memory>             //shared_ptr
#include <chrono>             //chrono
#include <functional>         //function
#include <mutex>              //mutex
#include <condition_variable> //condition variable
/******************************************************************************/
#include "w_pq.hpp"
#include "Itask.hpp"
/******************************************************************************/
namespace ilrd
{
namespace hrd26
{

    using PQ_Func = std::function<bool(std::shared_ptr<ITask>, std::shared_ptr<ITask>)>;

    class ThreadPool
    {
    public:
        // there is a default for num of threads.
        explicit ThreadPool(size_t size_ = std::thread::hardware_concurrency());

        ~ThreadPool();
        // Non-Copyable
        ThreadPool(const ThreadPool &other_) = delete;
        ThreadPool &operator=(const ThreadPool &other_) = delete;

        void AddTask(std::shared_ptr<ITask> task_);

        // threadpool functionalities  
        void Stop();
        void Resume();
        void Suspend();
        void ReSize(std::size_t new_size);

    private:
        WPriorityQueue<std::shared_ptr<ITask>,
                    std::vector<std::shared_ptr<ITask>>, PQ_Func> m_tasks;

        std::vector<std::thread>     m_threads;
        std::size_t                  m_num_of_threads;
        std::mutex                   m_mutex;
        std::condition_variable      m_cond;

        void ThreadsInit(std::size_t num_of_threads);
        void AdministerFunc();

    }; // class ThreadPool
    
class Stoptask : public ITask
{
public:
    Stoptask() : ITask(ADMIN)
    {
        // empty
    }

private:
    void Execute()
    {
        throw *this;
    }
};

class Suspend_Itask : public ITask
{
public:
    Suspend_Itask() : ITask(ADMIN)
    {
        // empty
    }

private:
    void Execute()
    {
        throw *this;
    }
};  
} // namespace hrd26
} // namespace ilrd
/******************************************************************************/
#endif //__ILRD_HRD26_THREAD_POOL_HPP__
