void __attribute__ ((constructor)) func_to_run(void);
#include <iostream>
#include "factory.hpp"
#include "singleton.hpp"
#include "Itask.hpp"

using namespace ilrd::hrd26;

class TestTask: public ITask
{
public:
    TestTask() = default;
    ~TestTask() = default;
    void Execute()
    {
        std::cout << "execute" << std::endl;
    }
    static std::shared_ptr<TestTask> Create(int num_)
    {
        std::cout << "create" << std::endl;
        return std::shared_ptr<TestTask>(new TestTask());
    }
};

void func_to_run(void)
{
    TestTask test_task;
    std::cout << "func_to_run" << std::endl;
    
    Factory<std::string,ITask,int> *factory = Singleton<Factory<std::string,ITask,int>>::GetInstance();
    std::cout << factory << std::endl;
    factory->Add("test_task", TestTask::Create);
}
