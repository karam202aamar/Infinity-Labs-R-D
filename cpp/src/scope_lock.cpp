/******************************************************************************/
#include <pthread.h>
#include <iostream>
#include <mutex>
/******************************************************************************/
namespace ilrd_26
{
class Lock
{
    public: 
        virtual ~Lock(){}
        virtual void UnLock() = 0;
        virtual void DoLock() = 0;
};
/******************************************************************************/
class ScopeLock // Composition from class Lock
{
    public: 
        ScopeLock(Lock& Locker);
        ~ScopeLock();
    private:
        Lock& lock_mech;

};

ScopeLock::ScopeLock(Lock& Locker): lock_mech(Locker)
{
    lock_mech.DoLock();
}

ScopeLock::~ScopeLock()
{
    lock_mech.UnLock();
}
/******************************************************************************/
class Mutex: public Lock
{
    public: 
        Mutex(pthread_mutex_t& Locker);
        void UnLock();
        void DoLock();
    private:
        pthread_mutex_t& lock;
};
Mutex::Mutex(pthread_mutex_t& Locker) : lock(Locker)
{
    //empty
}

void Mutex::DoLock()
{
    pthread_mutex_lock(&lock);
    std::cout << "LOCKEDDDDDDDDDDD" << '\n';
}
void Mutex::UnLock()
{
    pthread_mutex_unlock(&lock);
    std::cout << "UNLOCKEDDDDDDDDDDD" << '\n';
}
}
/******************************************************************************/
int main()
{
    //define mutex
    pthread_mutex_t mtx;
    //define Mutex instance
    ilrd_26::Mutex m(mtx);
    //use scope lock class
    ilrd_26::ScopeLock sl(m);

    std::cout << "here at locked place" << '\n';

    return 0;
}
