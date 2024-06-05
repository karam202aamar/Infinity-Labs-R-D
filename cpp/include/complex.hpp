/******************************************************************************/
// Project: Complex class
// Date: 21.12.2022
// Author: karam aamar
// Reviewer: 
// Version: 2.0
/******************************************************************************/
#ifndef ILRD_HRD26_COMPLEX_HPP
#define ILRD_HRD26_COMPLEX_HPP
/******************************************************************************/
#include <cmath> 
#include <cassert>    
/******************************************************************************/
namespace ilrd
{

class Complex
{
public:
    /*non-explicit*/ Complex(double real_ = 0.00, double img_ = 0.00);
    
    //Complex(const Complex& other_) = default;
    //Complex& operator=(const Complex& other_) = default;
    //~Complex() = default;
    
    //Get funcs
    inline double GetReal() const;
    inline double GetImg() const;

    //Set funcs
    inline Complex& SetReal(double real_);
    inline Complex& SetImg(double img_);

    //Operators
    inline Complex& operator+=(const Complex& c_);
    inline Complex& operator-=(const Complex& c_);
    inline Complex& operator*=(const Complex& c_);
    inline Complex& operator/=(const Complex& c_);


private:
    double m_real;
    double m_img;
    
};

inline Complex operator+(const Complex& c1_, const Complex& c2_);
inline Complex operator-(const Complex& c1_, const Complex& c2_);
inline Complex operator*(const Complex& c1_, const Complex& c2_);
inline Complex operator/(const Complex& c1_, const Complex& c2_);

inline bool operator==(const Complex& c1_, const Complex& c2_);
inline bool operator!=(const Complex& c1_, const Complex& c2_);
//input output
std::ostream& operator<<(std::ostream& os_, const Complex& c_);
std::istream& operator>>(std::istream& os_, Complex& c_);

/************ implementation of the function exists in the class **************/
Complex::Complex(double real_, double img_ ): m_real(real_), m_img(img_){}
/******************************************************************************/
/*get function*/
inline double Complex::GetReal() const
{
    return this->m_real;
}
inline double Complex::GetImg() const
{
    return this->m_img;
}
/******************************************************************************/
/*set function*/
inline Complex& Complex::SetReal(double real_)
{
    this->m_real = real_;
    return *this;
}
inline Complex& Complex::SetImg(double img_)
{
    this->m_img = img_;
    return *this;
}
/******************************************************************************/
inline Complex& Complex::operator+=(const Complex& c_)
{
    this->m_real += c_.m_real;
    this->m_img += c_.m_img;
    return *this;
}
/******************************************************************************/                      
inline Complex& Complex::operator-=(const Complex& c_)
{
    this->m_real -= c_.m_real;
    this->m_img -= c_.m_img;
    return *this;
}
/******************************************************************************/                          
inline Complex& Complex::operator*=(const Complex& c_)//(this object * c_)
{
    this->m_real = (this->m_real * c_.GetReal()) - (this->m_img * c_.GetImg());
    this->m_img = (this->m_real * c_.GetImg()) + (this->m_img * c_.GetReal());
    return *this;
}
/******************************************************************************/             
inline Complex& Complex::operator/=(const Complex& c_)
{
    assert((pow(c_.GetReal(), 2)) + (pow(c_.GetImg(), 2)));

    this->m_real = (((this->m_real * c_.GetReal()) + (this->m_img * 
            c_.GetImg())) / ((pow(c_.GetReal(), 2)) + (pow(c_.GetImg(), 2))));
    this->m_img = (((this->m_img * c_.GetReal()) - (this->m_real *
             c_.GetImg())) / ((pow(c_.GetReal(), 2)) + (pow(c_.GetImg(), 2))));
    return *this;
}
/************ implementation of the function exists outside class *************/
inline Complex operator+(const Complex& c1_, const Complex& c2_)
{
    Complex c = c1_;
    c += c2_;
    return c;
}
/******************************************************************************/
inline Complex operator-(const Complex& c1_, const Complex& c2_)
{
    Complex c = c1_;
    c -= c2_;
    return c;
}
/******************************************************************************/
inline Complex operator*(const Complex& c1_, const Complex& c2_)
{
    Complex c = c1_;
    c *= c2_;
    return c;
}
/******************************************************************************/
inline Complex operator/(const Complex& c1_, const Complex& c2_)
{
    Complex c = c1_;
    c /= c2_;
    return c;
}
/******************************************************************************/
inline bool operator==(const Complex& c1_, const Complex& c2_)
{
    if(c1_.GetImg() == c2_.GetImg() && c1_.GetReal() == c1_.GetReal())
    {
        return true;
    }
    return false;
}
/******************************************************************************/
inline bool operator!=(const Complex& c1_, const Complex& c2_)
{
    if(c1_ == c2_)
    {
        return false;
    }
    return true;
}
/******************************************************************************/
inline std::ostream& operator<<(std::ostream& os_, const Complex& c_)//output
{
    return os_<< "z = " << c_.GetReal() << " + " << c_.GetImg() << "i";
}
/******************************************************************************/
inline std::istream& operator>>(std::istream& os_, Complex& c_)//input
{
    double real;
    double img;
    std::cout << "Enter the real num: ";
    os_ >> real;
    std::cout << "Enter the img num: ";
    os_ >> img;
    c_.SetReal(real);
    c_.SetImg(img);

    return os_;
}

} //namespace ilrd
/******************************************************************************/
#endif //ILRD_HRD26_COMPLEX_HPP

