/******************************************************************************/
// Project: Shared pointer
// Date: 27.12.2022
// Author: KARAM
// Reviewer: IDAN
// Version: 1.0
/******************************************************************************/
#include <iosfwd> /* size_t, ostream */
/******************************************************************************/
#ifndef __SHAREDPTR_HPP_ILRD__
#define __SHAREDPTR_HPP_ILRD__
/******************************************************************************/
namespace ilrd
{

template <class T>
class SharedPtr
{
public:
    SharedPtr(T* ptr = nullptr);                // Ctor
    SharedPtr(SharedPtr& other); // Copy
    SharedPtr& operator=(SharedPtr& other); // Assignment
    ~SharedPtr();                           // Dtor
    T& operator *(); //change value
    T* operator->(); 
    const T& operator *() const; //dereference
    operator bool() const; //return 

    std::size_t CountFunc();

    //casting from class to class 
    //assign to dereference
    //base class
private:
    T *m_ptr;
    std::size_t *counter;

};
/******************************************************************************/
template<class T>
bool operator== (const SharedPtr<T> &c1, const SharedPtr<T>& c2);
template<class T>
bool operator!= (const SharedPtr<T> &c1, const SharedPtr<T> &c2);
/*********************************implementation*******************************/
template <class T>
SharedPtr<T>::SharedPtr(T* ptr)
    :m_ptr(ptr)
    ,counter(new size_t (0))
{
    //empty
}
//////////////////////////////////
template <class T>
SharedPtr<T>::SharedPtr(SharedPtr& other)
{
    m_ptr = other.m_ptr;
    counter = other.counter;
    
    ++*counter;
}
//////////////////////////////////
template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr& other)
{
    //check this counter 
    if(0 == *counter)
    {
        delete counter;
        delete m_ptr;
    }
    else
    {
        --*counter;
    }

    m_ptr = other.m_ptr;
    counter = other.counter;
    ++*counter;

    return *this;
}
//////////////////////////////////
template <class T>
SharedPtr<T>::~SharedPtr()
{
    //DecCounter();
    if(0 < *counter)
    {
        --*counter;
    }
    else
    {
        delete m_ptr;
        delete counter;
        m_ptr = NULL;
    }
}
//////////////////////////////////
template <class T>
std::size_t SharedPtr<T>::CountFunc()
{
    return *counter;
}
//////////////////////////////////
template <class T>
T& SharedPtr<T>::operator *()
{
    return *m_ptr;
}
//////////////////////////////////
template <class T>
const T& SharedPtr<T>::operator *() const
{
    return *m_ptr;
}
//////////////////////////////////
template <class T>
SharedPtr<T>::operator bool() const
{
    return m_ptr;
}
//////////////////////////////////
template <class T>
T* SharedPtr<T>::operator->()
{
    return m_ptr; 
} 
//////////////////////////////////
template<class T>
bool operator== (const SharedPtr<T> &c1, const SharedPtr<T>& c2)
{
    if(&(*c1) == &(*c2))
    {
        return true;
    }
    return false;
}
//////////////////////////////////
template<class T>
bool operator!= (const SharedPtr<T> &c1, const SharedPtr<T> &c2)
{
    return !(&(*c1) == &(*c2));
}
//////////////////////////////////
} // namespace ilrd
#endif //__SHAREDPTR_HPP_ILRD__