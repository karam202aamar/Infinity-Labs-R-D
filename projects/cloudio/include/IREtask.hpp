#ifndef __IRE_TASK_HPP__
#define __IRE_TASK_HPP__

#include "itask.hpp"

namespace ilrd
{
namespace hrd26
{
    
class RETask: public ITask
{
public:

    explicit RETask(Priority priority_ = MED): ITask(priority_) {}
    virtual ~RETask() = default;

private:
    virtual void Execute() = 0;
};

} 
}

#endif //__IRE_TASK_HPP__