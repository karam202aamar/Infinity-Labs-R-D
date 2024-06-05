/******************************************************************************/
// Project: RCString Test
// Date: 25.12.2022
// Author: Karam Aamar
// Reviewer: 
// Version: 1.0
/******************************************************************************/
#include <iostream> 
#include <cstdio>
#include <string.h>
#include "rcstring.hpp"
/******************************************************************************/
using namespace ilrd;
/******************************************************************************/
enum {COUNTER_STRS = 8};
/******************************************************************************/
static void TestFunctionsIMP();
static void CtorTestIMP();
static void AssignTestIMP();
static void CopyTestIMP();
static void EqualUnEqualTestIMP();
//static void PlusOpTestIMP();
static void BracketsTestIMP();
/******************************************************************************/
int main()
{
    TestFunctionsIMP();
    
    return 0;
}
/******************************************************************************/
static void TestFunctionsIMP()
{
    CtorTestIMP();
    AssignTestIMP();
    CopyTestIMP();
    EqualUnEqualTestIMP();
    //PlusOpTestIMP();
    BracketsTestIMP();
}
/******************************************************************************/
static void CtorTestIMP()
{
    const char* str = "hey";

    RCString instance(str);

    if(strcmp(str, instance.Cstr()))
    {
        std::cout<< "CtorTestIMP failed" <<std::endl;
    }
}
/******************************************************************************/
static void AssignTestIMP()
{
    const char* str = "hey";

    RCString instance = str;

    if(strcmp(str, instance.Cstr()))
    {
        std::cout<< "AssignTestIMP failed" <<std::endl;
    }
}
/******************************************************************************/
static void CopyTestIMP()
{ 
    RCString instance1 = "hey";
    RCString instance2(instance1);

    if(strcmp(instance2.Cstr(), instance2.Cstr()))
    {
        std::cout<< "CopyTestIMP failed" <<std::endl;
    }
}
/******************************************************************************/
static void EqualUnEqualTestIMP()
{
    size_t result = 0;

    RCString instance1 = "equal";
    RCString instance2 = "equal";
    RCString instance3 = "unequal";

    result = (instance1 == instance2);

    if(1 != result)
    {
        std::cout<< "EqualUnEqualTestIMP failed" <<std::endl;
    }
    
    result = (instance1 != instance3);

    if(1 != result)
    {
        std::cout<< "EqualUnEqualTestIMP failed" <<std::endl;
    }
}
/******************************************************************************/
#if 0

static void PlusOpTestIMP()
{
    RCString str1 = "hello";
    RCString str2 = "world";
    RCString str3 = "hello world";

    str1 += str2;

    if(strcmp(str1.Cstr(), str3.Cstr()))
    {
        std::cout<< "PlusOpTestIMP failed" <<std::endl;
    }
}
#endif
/******************************************************************************/
static void BracketsTestIMP()
{
    const char *str1 = "karam";
    const char *str_ch = "keram";

    const RCString str2(str1);
    RCString str3(str1);

    if(str2[2] != str1[2])
    {
        std::cout << "BracketsTestIMP failed3"  << std::endl;
    }
    if(str3[2] != str1[2])
    {
        std::cout << "BracketsTestIMP failed2"  << std::endl;
    }

    str3[1] = 'e';

    if(strcmp(str3.Cstr(), str_ch))
    {
        std::cout << "BracketsTestIMP failed1"  << std::endl;
    }
    
}



