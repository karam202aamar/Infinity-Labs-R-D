/*******************************************************************************
* Project: Itask - hpp   
* Date: 05-Feb-2023
* Author: HRD26
* Reviewer: TBD
* Version: 1.0
*******************************************************************************/
#ifndef __ILRD_HRD26_ITASK_HPP__
#define __ILRD_HRD26_ITASK_HPP__

namespace ilrd
{
namespace hrd26
{

class ITask
{
public:
    enum Priority{LOW = 0, MED = 1, HIGH = 2, ADMIN = 1000};
    explicit ITask(Priority priority_ = MED);
    virtual ~ITask() = default;
    ITask(const ITask& other_) = default;
    ITask& operator=(const ITask& other_) = default;
    bool operator<(const ITask& other_); 

private:
    virtual void Execute() = 0;
    friend class ThreadPool; //why i need it as a friend
    Priority m_priority;
};


} // namespace hrd26
} // namespace ilrd
#endif //__ILRD_HRD26_ITASK_HPP__




