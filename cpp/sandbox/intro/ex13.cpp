/***********************************************************/
#include <iostream>
/***********************************************************/
namespace useless //we gonna use it
{
    u_int g_wasteful[400];
    extern int g_nottthere;
    void Foo(){std::cout << "useless" << std::endl;}

    namespace wasteoftime
    {
        void Foo(){std::cout << "wasteoftime" << std::endl;}
    } // namespace wasteoftime
    
} // namespace usless
/***********************************************************/
namespace stupid
{
    void Foo() {std::cout << "stupid" << std::endl;}
    void Bar() {}
    void DoNothing(unsigned int) {}
} // namespace stupid
/***********************************************************/
namespace useless
{
    void DoNothing(int) {}
} // namespace useless
/***********************************************************/
using namespace useless;
/***********************************************************/
namespace comeon = useless::wasteoftime;
/***********************************************************/
void DoMoreStuff()
{
    comeon::Foo();//prints: waste of time
    Foo();//prints: useless

    /*now this function do nothing*/
    using namespace stupid;

    Bar(); 
    DoNothing(g_wasteful[3] + 1);
}
/***********************************************************/
namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
} // namespace useless
/***********************************************************/
int main()
{
    DoMoreStuff();

    return 0;
}
/***********************************************************/
