/******************************************************************************/
// Project: RCString Test
// Date: 25.12.2022
// Author: Karam Aamar
// Reviewer: idan 
// Version: 1.0
/******************************************************************************/
#include <iostream> 
#include <cstdio>
#include "SharedPtr.hpp"
/******************************************************************************/
using namespace ilrd;
/******************************************************************************/
static void TestFunctionsIMP();

static void CtorCopyAssignTest();
static void DerefTest(); 
static void BoolTest();
static void ArrowOpTest();
static void EqualUnEqualTest();
/******************************************************************************/
int main()
{
    TestFunctionsIMP();
  
    return 0;
}
/******************************************************************************/
static void TestFunctionsIMP()
{
    //start testing here
    CtorCopyAssignTest();
    DerefTest(); 
    BoolTest();
    ArrowOpTest();
    EqualUnEqualTest();
}
/******************************************************************************/
static void CtorCopyAssignTest()
{
    SharedPtr<int> obj1(new int(10));
    SharedPtr<int> obj2(obj1);
    SharedPtr<int> obj3 = obj2;

    //for delete
    if(2 != obj3.CountFunc())
    {
        std::cout << "fail" << std::endl;
    }
    //delete
    if(10 != *(obj1))
    {
        std::cout << "fail" << std::endl;
    }
    if(10 != *(obj2))
    {
        std::cout << "fail" << std::endl;
    }
    if(10 != *(obj3))
    {
        std::cout << "fail" << std::endl;
    }
}
/******************************************************************************/
static void DerefTest()
{
    SharedPtr<int> obj1(new int(1));
    SharedPtr<int> obj2(new int(2));

    obj1 = obj2;

    if((*obj1) != 2)
    {
        std::cout << "fail" << std::endl;
    }
} 
/******************************************************************************/
static void BoolTest()
{
    SharedPtr<int> obj1(new int(5));
    SharedPtr<int> obj2(NULL);
    
    if(obj2)
    {
        std::cout << "fail" << std::endl;
    }
    if(obj1)
    {
        return;
    }
    std::cout << "fail" << std::endl;
}
/******************************************************************************/
//ArrowOpTest
struct car
{
    int price;
    int year; 
};

static void ArrowOpTest()
{
    SharedPtr<car> ptr(new car());
    
    ptr->price = 100;
    ptr->year = 1997;

    if(ptr->price != 100 && ptr->year != 1997)
    {
        std::cout << "fail" << std::endl;
    } 
}
/******************************************************************************/
static void EqualUnEqualTest()
{
    bool result = false;

    SharedPtr<int> obj1(new int(1));
    SharedPtr<int> obj2(obj1);
    SharedPtr<int> obj3(new int(2));

    result = (obj1 == obj2);
    if(false == result)
    {
        std::cout << "fail" << std::endl;
    }
    result = (obj1 != obj2);
    if(true == result)
    {
        std::cout << "fail" << std::endl;
    }
}
/******************************************************************************/