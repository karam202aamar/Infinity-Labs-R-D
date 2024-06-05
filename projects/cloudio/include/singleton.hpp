/*******************************************************************************
 * Date : 30/01/23
 * Author : HRD26
 * Reviwer : TBD
 * Project : Singleton - ensure a single object of type <T>
*******************************************************************************/
#ifndef __ILRD_HRD26_SINGLETON_HPP__
#define __ILRD_HRD26_SINGLETON_HPP__

#include <mutex> 
#include <atomic>

namespace ilrd
{
namespace hrd26
{

template<typename T>
class Singleton
{
public:
    static T* GetInstance();
    
    explicit Singleton() = delete;
    Singleton(const Singleton& other_) = delete;
    Singleton& operator=(const Singleton& other_) = delete;
    ~Singleton() = delete;

private:
    static std::atomic<T*> s_instance;
    static std::mutex s_mutex;

    class SingletonDestroyer
    {
    public:
        SingletonDestroyer();
        ~SingletonDestroyer();
        
        SingletonDestroyer(const SingletonDestroyer& other_)= delete;
        SingletonDestroyer& operator=(const SingletonDestroyer& other_)= delete;  
    };
};

template<typename T>
Singleton<T>::SingletonDestroyer::SingletonDestroyer() {}

template<typename T>
Singleton<T>::SingletonDestroyer::~SingletonDestroyer()
{
    delete s_instance;
}

template<typename T>
std::atomic<T*> Singleton<T>::s_instance;

template<typename T>
std::mutex Singleton<T>::s_mutex;

template<typename T>
T* Singleton<T>::GetInstance()
{
    
    T* tmp = s_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);

    if(!tmp) 
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        tmp = s_instance.load(std::memory_order_relaxed);
    
        if(!tmp) 
        {
            tmp = new T;
            std::atomic_thread_fence(std::memory_order_release);
            s_instance.store(tmp, std::memory_order_relaxed);
            static SingletonDestroyer destroyer; 
        }
    }
    return tmp;
}

} // namespace hrd26
} // namespace ilrd
#endif//__ILRD_HRD26_SINGLETON_HPP__




