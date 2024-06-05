/******************************************************************************
 * Project: PnP - monitors directory for .so files
 * Date: 9/2/23
 * Name: HRD26
 * Reviewer: TBD
 * Version: 0.1
 * ***************************************************************************/ 
#ifndef __ILRD_PNP_HPP__
#define __ILRD_PNP_HPP__

#include <string>               
#include <vector>              
#include <thread>

#include "event_channel.hpp"    

namespace ilrd
{
namespace hrd26
{
//Subject Class
class DirMonitor
{
public:
    DirMonitor(const std::string& dir_path_);
    ~DirMonitor();

    Dispatcher<const std::string&>& GetDispatcher();

private:
    Dispatcher<const std::string&> m_dispatcher;

    std::string                    m_dir_path;

    std::thread                    m_thread;
    void Monitor();
};
//Observer Class
class DLLLoader
{
public:
    DLLLoader(Dispatcher<const std::string&>* dispatcher_);
    ~DLLLoader();

    void Load(const std::string& path_);
    void dummy();
private:
    std::vector<void*>                         m_sm_handlers;
    Callback<const std::string&, DLLLoader>    m_cb;
    
};
} // hrd26
} // ilrd
#endif /* (__ILRD_PNP_HPP__) */


