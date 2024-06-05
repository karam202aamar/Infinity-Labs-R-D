/******************************************************************************
 * Project: 
 * Date: 15/2/23
 * Name: HRD26
 * Reviewer: TBD
 * Version: 0.1
 * ***************************************************************************/ 

namespace ilrd
{
namespace hrd26
{
template<typename Key, typename Args>
class RequestEngine 
{ 
public:
    using createFunc = std::function<std::shared_ptr<RETask>(Args)>;

    RequestEngine(const std::string& dir_path_, 
                  size_t num_of_threads_ = std::thread::hardware_concurrency());

    ~RequestEngine() = default;

    RequestEngine(const RequestEngine& other_) = delete;
    RequestEngine& operator=(const RequestEngine& other_) = delete;
    RequestEngine(RequestEngine&& other_) = delete;
    RequestEngine& operator=(RequestEngine&& other_) = delete;

    void Run();
    void Stop();
    void ConfigTask(const Key& key_, createFunc func_);
    void ConfigInput(std::shared_ptr<IInputSource<Key,Args> > input_);
    

private:
                      
    Factory<Key, RETask, Args>                          m_factory;
                                        
    DirMonitor                                          m_monitor;
                                            
    DLLLoader                                           m_loader;
                                      
    ThreadPool                                          m_threadPool;
    //UNORDEREDMAP(key, shared_ptr to IInputSource)     m_inputs; 
};

}
}