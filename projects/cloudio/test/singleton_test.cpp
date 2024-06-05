#include <iostream> //std::cout
#include <thread>   //std::thread

#include "singleton.hpp" //ilrd::hrd26::Singleton<>
/******************************************************************************/
using std::cout;
using namespace ilrd::hrd26;
/******************************************************************************/
class TestClass
{
public:
    TestClass(){cout<< "SINGLETON CREATED\n";}
    ~TestClass(){cout<< "SINGLETON DESTROYED\n";}
private:
};
/******************************************************************************/
static void CtorDtorTest(void);
static void GetAddress(TestClass** x_);
/******************************************************************************/
int main(void)
{
    CtorDtorTest();

   return 0;
}
/******************************************************************************/
static void CtorDtorTest(void)
{
    TestClass* x1 = nullptr;
    TestClass* x2 = nullptr;
    TestClass* x3 = nullptr;

    std::thread first(GetAddress, &x1);
    std::thread second(GetAddress, &x2);
    std::thread third(GetAddress, &x3);

    first.join();
    second.join();
    third.join();

    if(x1 != x2 && x1 != x3 && x3 != x2)
    {
        cout<<"not same address\n";
        cout<<(void*)x1<<"\n";
        cout<<(void*)x2<<"\n";
        cout<<(void*)x3<<"\n";
    }
} 
/******************************************************************************/
static void GetAddress(TestClass** x_)
{
    *x_ = Singleton<TestClass>::GetInstance(); 
} 
/******************************************************************************/
