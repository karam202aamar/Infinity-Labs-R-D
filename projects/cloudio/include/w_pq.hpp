/*******************************************************************************
* Project: Waiting Priority Queue - represents a priority queue which is thread 
*          safe and supporting waitable pop     
* Date: 02-Feb-2023
* Author: HRD26
* Reviewer: TBD
* Version: 1.0
*******************************************************************************/
#ifndef __ILRD_HRD26_W_PRIORTY_QUEUE_HPP__
#define __ILRD_HRD26_W_PRIORTY_QUEUE_HPP__

#include <mutex>                //std::mutex
#include <condition_variable>   //std::condition_variable
#include <queue>                //std::priority_queue
#include <cstddef>              //std::size_t

namespace ilrd
{

namespace hrd26
{

template<
    typename T,
    typename Container = std::vector<T>,
    typename Compare = std::less<typename Container::value_type>
        >

class WPriorityQueue
{
public:

    explicit WPriorityQueue(const Compare& compare = Compare());

    WPriorityQueue(const WPriorityQueue& other_)= delete;
    WPriorityQueue& operator=(const WPriorityQueue& rhs_)= delete;
    ~WPriorityQueue()= default;

    //Push may throw exception
    void Push(const T& elem_);  
    T Pop();
    bool IsEmpty() const;   
    std::size_t Size() const;
    
private:
    std::priority_queue<T, Container, Compare> m_q;
    std::condition_variable m_cond;
    mutable std::mutex m_mutex;
    
};
/*******************************implementation*********************************/
template<typename T, typename Container, typename Compare>
WPriorityQueue<T, Container, Compare>::WPriorityQueue(const Compare& compare)
                                                                   :m_q(compare)//this how we define pq
{
    //empty
}

template<typename T, typename Container, typename Compare>
void WPriorityQueue<T, Container, Compare>::Push(const T& elem_)
{
    std::lock_guard<std::mutex> lock_guard(m_mutex);

    m_q.push(elem_);

    m_cond.notify_one();
}
template<typename T, typename Container, typename Compare>
T WPriorityQueue<T, Container, Compare>::Pop()
{
    T ret;

    std::unique_lock<std::mutex> lock(m_mutex);  
    //will wait untill the pred(lambda function) return true - if empty() = true
    /*m_cond.wait(lock, [this](){return !this->m_q.empty();}); */
    /*while it's empty wait*/
    while(m_q.empty())
    {
        m_cond.wait(lock);
    }
    
    ret = m_q.top();   
    m_q.pop();
    return ret;
}
template<typename T, typename Container, typename Compare>
bool WPriorityQueue<T, Container, Compare>::IsEmpty() const
{
    //unlock automatically when gets out the scope
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_q.empty();
}
template<typename T, typename Container, typename Compare>
std::size_t WPriorityQueue<T, Container, Compare>::Size() const
{
    //unlock automatically when gets out the scope
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_q.size();
}
/****************************end of implementation*****************************/
} // namespace hrd26
} // namespace ilrd

#endif //__ILRD_HRD26_W_PRIORTY_QUEUE_HPP__

