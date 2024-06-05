// Project: RCString CPP
// Date: 25.12.2022
// Author: Karam Aamar
// Reviewer: 
// Version: 1.0
/******************************************************************************/
#include <cstring> //memcpy, strlen, strcmp
#include <ostream> //ostream
#include <cstddef> //std::size_t
#include <cassert> //assert

#include "rcstring.hpp"
/******************************************************************************/
enum {COUNTER_STRS = 8};
/******************************************************************************/
namespace ilrd
{

RCString::RCString(const char *str_)
{
    assert(str_);
    std::size_t memcpy_len = strlen(str_) + 1;
    /*allocate new location*/
    char* new_str = new char[memcpy_len + COUNTER_STRS];
    /*cast to init*/
    *(reinterpret_cast<size_t*>(new_str)) = 1;
    /*point to the beginning of the str*/
    new_str += COUNTER_STRS;
    /*memcpy to copy the str*/
    memcpy(new_str, str_, memcpy_len);
    /*point to the new location*/
    m_str = new_str;
}
/******************************************************************************/
RCString::RCString(const RCString& other_)
{
    assert(other_.m_str != NULL);
    this->m_str = other_.m_str;
    IncrmentCounter();
}
/******************************************************************************/
RCString::~RCString()
{
    assert(m_str != NULL);

    if(1 == Counter(this->m_str))
    {
        delete [] (m_str - COUNTER_STRS);
        m_str = NULL;
    }
    else
    {
        /*decrement*/
        DecrementCounter();
    }
}
/******************************************************************************/
RCString& RCString::operator=(const RCString& other_)
{
    assert(m_str);
    assert(other_.m_str);
    
    //if it's single string that no one points to:
    if(1 == Counter(m_str))
    {
        //delete
        delete [] (m_str - COUNTER_STRS);
    }
    else
    {
        //decrement the old value.
        DecrementCounter();
    }
    //assign
    m_str = other_.m_str;
    IncrmentCounter();

    return *this;
}
/******************************************************************************/
const char* RCString::Cstr() const
{
    assert(m_str);
    return m_str;
}
/******************************************************************************/
void RCString::IncrmentCounter()
{
    assert(m_str);
    /*get to the meta-data*/
    m_str -= COUNTER_STRS;
    /*increment the counter of the str*/
    *(reinterpret_cast<size_t*>(m_str)) += 1;
    /*point to the relevant str*/
    m_str += COUNTER_STRS;
}
/******************************************************************************/
void RCString::DecrementCounter()
{
    assert(m_str);
    /*decrement the counter of the str*/
    *(reinterpret_cast<size_t*>(m_str - COUNTER_STRS)) -= 1;
    /*point to the relevant str*/
    m_str += COUNTER_STRS;
}
/******************************************************************************/
size_t Counter(const char* str)
{
    return *(reinterpret_cast<const size_t*>(str - COUNTER_STRS));
}
/******************************************************************************/
bool operator==(const RCString& c1_, const RCString& c2_)
{
    assert(c1_.Cstr());
    assert(c2_.Cstr());

    if(0 == strcmp(c1_.Cstr(), c2_.Cstr()))
    {
        return true;
    }
    return false;
}
/******************************************************************************/
bool operator!=(const RCString& c1_, const RCString& c2_)
{
    assert(c1_.Cstr());
    assert(c2_.Cstr());
    if(0 == strcmp(c1_.Cstr(), c2_.Cstr()))
    {
        return false;
    }
    return true;
}
/******************************************************************************/
std::ostream& operator<<(std::ostream& os_, const RCString& c_)
{
    assert(c_.Cstr());
    return os_<< "the string is: " << c_.Cstr() << std::endl;
}

/******************************************************************************/
char RCString::operator[](std::size_t idx_) const
{
    assert(m_str);
    assert(idx_ <= strlen(m_str));

    return this->m_str[idx_];
}
/******************************************************************************/
RCString::CharProxy RCString::operator[](std::size_t idx_)
{
    assert(idx_ <= strlen(m_str));
    //replace it with chp
    CharProxy chp(*this, idx_);
    return chp;
}
/******************************************************************************/
RCString::CharProxy::CharProxy(RCString& str, size_t index): 
                                                   m_rcstring(str), idx(index)
{
    //empty
}
/******************************************************************************/
RCString::CharProxy::operator char() const
{
    assert(idx <= strlen(m_rcstring.m_str));
    return m_rcstring.m_str[idx];
}
/******************************************************************************/
RCString::CharProxy RCString::CharProxy::operator=(char c)
{
    if(1 != Counter(m_rcstring.m_str))
    {
        this->m_rcstring.DecrementCounter();
        char *tmp = new char[strlen(m_rcstring.m_str) + 1 + COUNTER_STRS];
        memcpy(tmp, (m_rcstring.m_str - COUNTER_STRS), (strlen(m_rcstring.m_str)
                                                           + 1 + COUNTER_STRS));
        tmp[idx] = c;
        m_rcstring.m_str = tmp;
        
        return *this;
    }
    m_rcstring.m_str[idx] = c;
    return *this;
}
/******************************************************************************/
#if 0
RCString operator+(const RCString& c1_, const RCString& c2_)
{
    RCString new_RCString(c1_);
    new_RCString += c2_;
    return new_RCString;
}
/******************************************************************************/

char& RCString::operator[](std::size_t idx_)
{
    //check the counter of the string
    if(1 == Counter(this->m_str))
    {
        //allocate new string 
        char* new_str = new char[strlen(m_str) + 1];
        //copy & change the char
        memcpy(new_str, this->m_str, strlen(this->m_str));
        new_str[strlen(m_str)] = '\0';
        //delete old one
        delete [] m_str; 
        this->m_str = new_str;
        //return
        return new_str[idx_];
    }
    //decrement
    DecrementCounter(this->m_str); 
    //allocate new string
    char* new_str = new char[strlen(m_str) + 1];
    //copy & change the char
    memcpy(new_str, this->m_str, strlen(this->m_str));
    new_str[strlen(m_str)] = '\0';
    this->m_str = new_str;
    //return
    return new_str[idx_];
}

/******************************************************************************/
RCString& RCString::operator+=(const RCString& other_)
{
    //allocate new string
    char* new_str = new char[strlen(m_str) + 1 + strlen(other_.m_str) + 1];
    //copy both strs
    memcpy(new_str, m_str, strlen(m_str));
    memcpy(new_str + (strlen(m_str) + 1), other_.Cstr(), strlen(other_.Cstr()));
    //null terminator 
    new_str[strlen(m_str) + 1 + strlen(other_.m_str)] = '\0';
    //delete old str
    delete [] (m_str - COUNTER_STRS);
    //pointto new str
    m_str = new_str;
    return *this;
}
#endif
}
/******************************************************************************/
