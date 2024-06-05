/******************************************************************************/
#include <iostream> 
#include "complex.hpp"
/******************************************************************************/
void TestFuncIMP();

void PlusEqualIMP();
void PlusPlusIMP();

void SubEqualIMP();
void SubSubIMP();

void MultiEqualIMP();
void MultiMultiIMP();

void DivEqualIMP();
void DivDivIMP();

void EqualNotEqualIMP();
void CinCoutIMP();

void Test();
/******************************************************************************/
using namespace ilrd;
/******************************************************************************/
int main()
{
    TestFuncIMP();

    return 0;
}
/******************************************************************************/
void TestFuncIMP()
{
    PlusEqualIMP();
    PlusPlusIMP();
    SubEqualIMP();
    SubSubIMP();
    MultiEqualIMP();
    MultiMultiIMP();
    DivEqualIMP();
    DivDivIMP();
    EqualNotEqualIMP();
    //CinCoutIMP();
    Test();
}
/******************************************************************************/
void PlusEqualIMP()
{
    Complex obj1(1, 1);
    Complex obj2(2, 2);
    
    obj1 += obj2;

    if(obj1.GetImg() != 3 && obj1.GetReal() != 3)
    {
        std::cout << "FAIL " << std::endl;
    }
    
}
/******************************************************************************/
void PlusPlusIMP()
{
    Complex obj1(1, 1);
    Complex obj2(2, 2);
    Complex obj3;

    obj3 = obj1 + obj2;

    if(obj3.GetImg() != 3 && obj3.GetReal() != 3)
    {
        std::cout << "FAIL " << std::endl;
    }
}
/******************************************************************************/
void SubEqualIMP()
{
    Complex obj1(2, 2);
    Complex obj2(1, 1);

    obj1 -= obj2;

    if(obj1.GetImg() != 1 && obj1.GetReal() != 1)
    {
        std::cout << "FAIL " << std::endl;
    }
}
/******************************************************************************/
void SubSubIMP()
{
    Complex obj1(1, 1);
    Complex obj2(2, 2);
    Complex obj3;

    obj3 = obj2 - obj1;

    if(obj3.GetImg() != 1 && obj3.GetReal() != 1)
    {
        std::cout << "FAIL " << std::endl;
    }
}
/******************************************************************************/
void MultiEqualIMP()
{
    Complex obj1(1, 1);
    Complex obj2(2, 2);

    obj1 *= obj2;

    if(obj1.GetImg() != 4 && obj1.GetReal() != 0)
    {
        std::cout << "FAIL " << std::endl;
    }
}
/******************************************************************************/
void MultiMultiIMP()
{
    Complex obj1(1, 1);
    Complex obj2(2, 2);
    Complex obj3;

    obj3 = obj2 * obj1;

    if(obj3.GetImg() != 4 && obj3.GetReal() != 0)
    {
        std::cout << "FAIL " << std::endl;
    }
}
/******************************************************************************/
void DivEqualIMP()
{
    Complex num1(3, 5);
    Complex num2(2, 7);

    num1 /= num2;

    if((double)(41 / 53) - num1.GetReal() > 0.05 ||
                                      (double)(-11 / 53) - num1.GetImg() > 0.05)
    {
        std::cout << "FAIL" << std::endl;
    }
}
/******************************************************************************/
void DivDivIMP()
{
    Complex obj1(3, 5);
    Complex obj2(2, 7);
    Complex obj3;

    obj3 = obj1 / obj2;

    if((double)(41 / 53) - obj3.GetReal() > 0.05 ||
                                      (double)(-11 / 53) - obj3.GetImg() > 0.05)
    {
        std::cout << "FAIL" << std::endl;
    }
}
/******************************************************************************/
void EqualNotEqualIMP()
{
    Complex obj1(1, 1);
    Complex obj2(2, 2);
    Complex obj3(1, 1);

    if(obj1 != obj3)
    {
        std::cout << "FAIL" << std::endl;
    }
    if(obj1 == obj2)
    {
        std::cout << "FAIL" << std::endl;
    }
}   
/******************************************************************************/
void CinCoutIMP()
{
    Complex obj1;

    std::cin >> obj1;

    std::cout << obj1 << std::endl;
}
/******************************************************************************/

void Test()
{
    Complex obj = (2,4,6);

    std::cout << "ordinary print" << std::endl;
    std::cout << "print of the obj: " << std::endl;

    std::cout << "real:" << obj.GetReal() << std::endl;
    std::cout << "img:" << obj.GetImg() << std::endl;
    //we have a definition for printing obj:
    std::cout << obj << std::endl;
}