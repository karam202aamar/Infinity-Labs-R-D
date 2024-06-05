#include <iostream>

class Test_class
{
public:

    Test_class(double value1 = 0.00, double value2 = 0.00, double value3 = 0.00);
    //Complex(const Complex& other_) = default;
    //Complex& operator=(const Complex& other_) = default;
    //~Complex() = default;
    
    //Get funcs
    double Getvalue1() const;
    double Getvalue2() const;
    double Getvalue3() const;

private:
    double value1;
    double value2;
    double value3;
};

Test_class::Test_class(double value1_, double value2_, double value3_): value1(value1_), value2(value2_), value3(value3_){}

double Test_class::Getvalue1() const
{
    return value1;
}
double Test_class::Getvalue2() const
{
    return value2;
}
double Test_class::Getvalue3() const
{
    return value3;
}
/******************************************************************************/
int main()
{
    Test_class test1{1,1,1};
    Test_class test2(test1);
    std::cout << test2.Getvalue1() << test2.Getvalue2() <<
                                             test2.Getvalue3() << std::endl;
    return 0;
}