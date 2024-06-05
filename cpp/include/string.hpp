// Project: String class
// Author: HRD26
// Reviewer: Binyamin Haymann
// Version: 1.0

#ifndef ILRD_HRD26_STRING_HPP
#define ILRD_HRD26_STRING_HPP

class String
{
public:
    String(const char *str = ""); //ctor // argument brirat mhdal 
    explicit String(const String& other_); //copy ctor
    ~String(); //dtor
    std::size_t Length() const; //const means that the function will not change the state of the object 
    String& operator=(const String& other_); //assignment
    
    String& operator+=(const String& other);
    const char *Cstr() const;//getter

private:
    char *m_str;
};

#endif //ILRD_HRD26_STRING_HPP













