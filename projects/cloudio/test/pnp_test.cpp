#include <iostream> // cout
#include <chrono> // seconds
#include <thread> // this_thread

#include "factory.hpp"
#include "Itask.hpp"
#include "pnp.hpp"

using namespace ilrd::hrd26;

int main(void)
{
    DirMonitor dir_mon("/home/karam/Desktop/infintylab/git/projects/cloudio/plugins");

    Factory<std::string,ITask,int> *factory = Singleton<Factory<std::string,ITask,int>>::GetInstance();

    std::cout << factory << std::endl;
    
    DLLLoader loader(&(dir_mon.GetDispatcher()));
    
    std::this_thread::sleep_for(std::chrono::seconds(3)); 
    
    return 0;
}
