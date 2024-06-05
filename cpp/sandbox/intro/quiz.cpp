#include <iostream> 
#include <string.h>

class String
{
public:
    String(const char *str = ""); //ctor // argument brirat mhdal 
    //explicit String(const String& other_); //copy ctor
    
    //std::size_t Length() const; //const means that the function will not change the state of the object 
    String& operator=(const String& other_); //assignment
    
    
    const char *Cstr() const;//getter

private:
    char *m_str;
};
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
const char* String::Cstr() const
{
    return m_str;
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
int main()
{
    String str6 = "karam";
   
    std::cout << str6.Cstr() << std::endl;

    return 0; 
}
/******************************************************************************/





