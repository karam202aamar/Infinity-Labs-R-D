#include <iostream>
#include <chrono>

#include "thread_pool.hpp"

using namespace ilrd::hrd26;

static int counter = 0;

class AddOnes: public ITask
{
    public:
        void Execute() 
        {
            ++counter;
        }
};
 
int main()
{
    std::shared_ptr<ITask> ptr_to_func(new AddOnes);

    ThreadPool thread_pool_instance;

    thread_pool_instance.AddTask(ptr_to_func);
    thread_pool_instance.AddTask(ptr_to_func);
    thread_pool_instance.AddTask(ptr_to_func);
    thread_pool_instance.AddTask(ptr_to_func);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if(4 != counter)
    {
        std::cout << "FAILED" << std::endl;
    }
    /*suspend threads*/
    thread_pool_instance.Suspend(); 

    std::this_thread::sleep_for(std::chrono::seconds(1));

    /*add another 4 tasks*/
    thread_pool_instance.AddTask(ptr_to_func);
    thread_pool_instance.AddTask(ptr_to_func);
    thread_pool_instance.AddTask(ptr_to_func);
    thread_pool_instance.AddTask(ptr_to_func);
    
    if(4 != counter)
    {
        std::cout << "FAILED" << std::endl;
    }
    /*resume threads work*/
    thread_pool_instance.Resume();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if(8 != counter)
    {
        std::cout << "FAILED" << std::endl;
    }

    //resize
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}