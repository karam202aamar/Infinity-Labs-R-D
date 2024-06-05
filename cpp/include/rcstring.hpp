/******************************************************************************/
// Project: RCString Header
// Date: 25.12.2022
// Author: HRD26
// Reviewer: Binyamin Haymann
// Version: 1.0
/******************************************************************************/
#include<iosfwd> /* ostream&, size_t */

#ifndef __RCSTRING_HPP_ILRD__
#define __RCSTRING_HPP_ILRD__

namespace ilrd
{
class RCString
{
//declare class we gonna use  
class CharProxy;

public:
    /* non explicit */RCString(const char *str_ = "");  // Ctor
    RCString(const RCString& other_);                   // Copy
    ~RCString();                                        // Dtor
    RCString& operator=(const RCString& other_); 
    //change 
    CharProxy operator[](std::size_t idx_);
    //print value
    char operator[](std::size_t idx_) const;//idx inside[]
    const char *Cstr() const;
    RCString& operator+=(const RCString& other_);
    //increment the counter of the string 
    void IncrmentCounter();
    //decrement the counter of the string 
    void DecrementCounter();

private:
    
    char *m_str;

    class CharProxy
    {
    public:
        explicit CharProxy(RCString&, std::size_t index);
        CharProxy operator=(char c);
        operator char() const;
    private:
        RCString& m_rcstring;
        std::size_t idx;
    };
}; // class RCString

bool operator==(const RCString& c1_, const RCString& c2_);
bool operator!=(const RCString& c1_, const RCString& c2_);
RCString operator+(const RCString& c1_, const RCString& c2_);
std::ostream& operator<<(std::ostream& os_, const RCString& c_);
//RCString& operator+(const RCString& c1_ , const RCString& c2_);  Adv

size_t Counter(const char* str);

} // namespace ilrd


#endif //__RCSTRING_HPP_ILRD__