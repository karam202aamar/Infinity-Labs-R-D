#include <iostream>
using namespace std; 

void Foo(const double &v) /*the case is that we can compile this function caus it const we cant change where is the alias is pointing*/
{
    cout << "Foo FUNC = " << v << " address " << &v << endl;
}

void Bar(double &v)/*without cast we get: cannot bind non-const lvalue reference of type ‘double&’ to a value of type ‘int’*/
{
    cout << "BAR FUNC = " << reinterpret_cast<int&>(v) << " address " << &v<< endl;
    
}

int main()
{
    int i = 8;
    int &ip = i;
    ip = 9; 

    cout << "i = " << i << " address " << &i << endl;

    Foo(ip);
    Bar(reinterpret_cast<double&>(ip));

    return 0;
}