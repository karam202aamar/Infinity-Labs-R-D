#include <iostream> 
#include <string.h>
#include "string.hpp"
/******************************************************************************/
String::String(const char *str)
{
    /*get the length of the str*/
    size_t len = strlen(str);
    /*allocate memory for m_str*/
    m_str = new char[len + 1];
    /*copy string*/
    memcpy(m_str, str, len);
    /*set NULL terminator*/
    m_str[len] = '\0';
}
/******************************************************************************/
String::String(const String &other_)
{
    /*get the length of the str*/
    size_t len = strlen(other_.m_str);
    /*allocate memory for m_str*/
    m_str = new char[len + 1];
    /*copy string*/
    memcpy(m_str, other_.m_str, len);
    /*set NULL terminator*/
    m_str[len] = '\0';
}
/******************************************************************************/
String::~String()
{
    delete[] m_str;
    m_str = NULL;
}
/******************************************************************************/
const char* String::Cstr() const
{
    return m_str;
}
/******************************************************************************/
std::size_t String::Length() const
{
    return strlen(m_str);
}
/******************************************************************************/
String& String::operator=(const String& other_)
{
    /*get the length of the str*/
    size_t len = strlen(other_.m_str);
    /*Copy the string literal to the m_str.*/
    memcpy(m_str, other_.m_str, len);
    /*set NULL terminator*/
    m_str[len] = '\0';

    return *this;
}
/******************************************************************************/
String& String::operator+=(const String& other)
{
    /*get the length of the str*/
    size_t len = strlen(this->m_str) + strlen(other.m_str) + 1;
    /*allocate tmp_str*/
    char* tmp_str = new char[len];
    
    memcpy(tmp_str, this->m_str, strlen(this->m_str) + 1);
    delete[] this->m_str;

    /*copy the string to the end of the object string*/
    strcat(tmp_str, other.m_str);
    this->m_str = new char[len];
    memcpy(this->m_str, tmp_str, len);
    delete[] tmp_str;

    return *this;
}
/******************************************************************************/
int main()
{
    String str1("hello");
    String str2("world");
    String str3(str1);
    String str4(str2);
    String str5;
    String str6 = "karam";
    str5 = str1;

    std::cout << str1.Cstr() << " the length:" << str1.Length() << std::endl;
    std::cout << str2.Cstr() << " the length:" << str2.Length() << std::endl;
    std::cout << str3.Cstr() << " the length:" << str3.Length() << std::endl;
    std::cout << str4.Cstr() << " the length:" << str4.Length() << std::endl;
    std::cout << "= operator "<< str5.Cstr() << " the length:" << str4.Length() << std::endl;
    
    /*test += operator*/
    str1 += str2;
    std::cout << str1.Cstr() << std::endl;

    return 0; 
}
/******************************************************************************/
//strdup allocation and copying.
//this == &other, this - ptr to object other is passed by reference so we use &




