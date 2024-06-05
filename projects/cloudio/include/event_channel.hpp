/*******************************************************************************
* Project: Event Channel 
* Date: 08-Feb-2023
* Author: HRD 26
* Reviewer: 
* Version: 1.0
*******************************************************************************/
#include <list>       //std::list
#include <functional> //std::functional

#ifndef __ILRD_HRD26_EVENT_CHANNEL_HPP__
#define __ILRD_HRD26_EVENT_CHANNEL_HPP__

namespace ilrd
{
namespace hrd26
{
template <typename MSG>
class ICallback;

template <typename MSG>
class Dispatcher
{
public:
    explicit Dispatcher() = default;
    ~Dispatcher();
    Dispatcher(const Dispatcher& other) = delete;
    Dispatcher &operator= (const Dispatcher& other) = delete;

    void NotifyAll(const MSG& msg);

private:
    friend class ICallback<MSG>;

    std::list<ICallback<MSG>*> m_cb_list; 
    void Register(ICallback<MSG>* cb);
    void UnRegister(ICallback<MSG>* cb);
};

/******************************************************************************/
template <typename MSG>
class ICallback
{
public:
    explicit ICallback(Dispatcher<MSG>* dp);
    virtual ~ICallback();
    ICallback(const ICallback& other) = delete;
    ICallback& operator=(const ICallback& other) = delete;

    virtual void Notify(const MSG& msg) = 0;
    virtual void EndService() = 0;
private:
    Dispatcher<MSG>* m_dp;
protected:
    bool m_not_registered;
}; //class ICallback

/******************************************************************************/
template <typename MSG, typename OBS> 
class Callback : public ICallback<MSG>
{
public:
    using stop_func = void (OBS::*)();
    using do_action = void (OBS::*)(const MSG& msg);

    explicit Callback(Dispatcher<MSG>* dp,
                      OBS& obs,
                      do_action action,
                      stop_func stop = nullptr);
    ~Callback();
    
    Callback(const Callback& other) = delete;
    Callback& operator=(const Callback& other) = delete;

    void Notify(const MSG& msg);
    void EndService();
    
private:
    OBS& m_obs;
    do_action m_da;
    stop_func m_sf;
}; //class Callback
/*********************************implmentation********************************/
/**********************************Dispatcher**********************************/
template <typename MSG>
void Dispatcher<MSG>::Register(ICallback<MSG>* cb)
{
    m_cb_list.push_back(cb);
}

template <typename MSG>
void Dispatcher<MSG>::UnRegister(ICallback<MSG>* cb)
{
    m_cb_list.remove(cb);
}

template <typename MSG>
void Dispatcher<MSG>::NotifyAll(const MSG& msg)
{
    for(ICallback<MSG>* iter : m_cb_list)
    {
        /*we us nothify that belong to ICallback*/
        (iter)->Notify(msg);
    }
}

template <typename MSG>
Dispatcher<MSG>::~Dispatcher()
{
    while(!m_cb_list.empty())
    {
        m_cb_list.back()->EndService();
        m_cb_list.pop_back(); 
    }
}

/***********************************ICallback**********************************/
template <typename MSG>
ICallback<MSG>::ICallback(Dispatcher<MSG>* dp) : m_dp(dp), m_not_registered(true)
{
    m_dp->Register(this);
}
template <typename MSG>
ICallback<MSG>::~ICallback()
{
    if(m_not_registered)
    {
        m_dp->UnRegister(this);
    }   
}
/***********************************Callback***********************************/
template <typename MSG, typename OBS>
Callback<MSG, OBS>::Callback(Dispatcher<MSG>* dp,
                  OBS& obs, do_action action, stop_func stop) :
                  ICallback<MSG>(dp), m_obs(obs), m_da(action), m_sf(stop)
{
    //empty
}

template <typename MSG, typename OBS>
Callback<MSG, OBS>::~Callback()
{
    //empty
}

template <typename MSG, typename OBS>
void Callback<MSG, OBS>::Notify(const MSG& msg)
{
    (m_obs.*m_da)(msg);
}

template <typename MSG, typename OBS>
void Callback<MSG, OBS>::EndService()
{
    ICallback<MSG>::m_not_registered = false;
    if(m_sf)
    {
        (m_obs.*m_sf)();
    }
}
/*****************************End Of Implmentation*****************************/
} //namespace hrd26
} //namespace ilrd

#endif //__ILRD_HRD26_EVENT_CHANNEL_HPP__