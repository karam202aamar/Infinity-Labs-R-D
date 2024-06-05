/*******************************************************************************
* Project: pnp - cpp  
* Date: 
* Author: karam
* Reviewer: 
* Version: 1.0
*******************************************************************************/
#include <sys/inotify.h>
#include <filesystem>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <dlfcn.h>
#include <sys/select.h>
#include <fcntl.h>
#include <cstring>
/******************************************************************************/
#include "pnp.hpp"

namespace ilrd
{
namespace hrd26
{
/*************************************IMP**************************************/ 
int          EXIT_FLAG      = 1;
const size_t EVENT_SIZE     = sizeof(struct inotify_event);
const size_t EVENT_LEN      = 10000;
/************************************MONITOR***********************************/
DirMonitor::DirMonitor(const std::string& path_): m_dir_path(path_), 
                                    m_thread(std::thread([&](){ Monitor(); }))
{
    //empty
}

DirMonitor::~DirMonitor()
{
    int exit_fd = open("exit", O_CREAT | O_RDWR);

    if (-1 == exit_fd)
    {
        std::cout << "Error" << std::endl;
    }

    if (close(exit_fd))
    {
       std::cout << "Error" << std::endl;
    }

    if (remove("exit"))
    {
        std::cout << "Error" << std::endl;
    }

    m_thread.join();
}

Dispatcher<const std::string&>&  DirMonitor::GetDispatcher()
{
    return m_dispatcher;
}

void DirMonitor::Monitor()
{
    int inotifyFD = inotify_init();
    
    
    if (inotifyFD < 0)
    {
        std::cout << "Error initializing inotify" << std::endl; 
        return;
    }
    
    int watchDescriptor = inotify_add_watch(inotifyFD, m_dir_path.c_str(),
                                             /* IN_MODIFY | */ IN_CREATE/* | IN_MOVE */); 
    if (watchDescriptor < 0) 
    {
        std::cerr << "Error adding watch" << std::endl;
        return;
    }
    
    char buffer[EVENT_LEN] = {0};

    while (EXIT_FLAG)
    {        
       
        int length = read(inotifyFD, buffer, EVENT_LEN); 
        
        if (length < 0)
        {
            std::cout << "ERROR read failed" << std::endl; 
        }

        int i = 0;

        while (i < length) 
        {     
            struct inotify_event *event = (struct inotify_event*)&buffer[i];     
            
            if (event->len) 
            {
                if (event->mask & IN_CREATE || event->mask & IN_MODIFY || 
                                                        event->mask & IN_MOVE) 
                {
                    if (!strcmp("exit", event->name))
                    {
                        EXIT_FLAG = 0;
                        break;
                    }
                    else
                    {
                        
                        std::string msg = m_dir_path + "/"+ event->name;
                        std::cout << msg << std::endl;
                        m_dispatcher.NotifyAll(msg);
                        
                        break;
                    }
                }           
            }
            
            i += EVENT_SIZE + event->len;
        }
    }
}

/************************************DLLOADER**********************************/

DLLLoader::DLLLoader(Dispatcher<const std::string&>* dispatcher_): 
                        m_cb(dispatcher_, *this, &DLLLoader::Load, &DLLLoader::dummy)
{
    //empty
}

DLLLoader::~DLLLoader()
{
    for (auto& cb : m_sm_handlers) 
    {
        if (dlclose(cb))
        {
            std::cout << "dlclose failed" << std::endl;
        }        
    }
}

void DLLLoader::Load(const std::string& path_)
{
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    void* fd = dlopen(path_.c_str(), RTLD_LAZY);
    if (!fd)
    {
        std::cout << "FD failed" << std::endl;
    }
    else
    {
        m_sm_handlers.push_back(fd);
    }
}
void DLLLoader::dummy()
{
    //empty
}
}//hrd26
}//ilrd