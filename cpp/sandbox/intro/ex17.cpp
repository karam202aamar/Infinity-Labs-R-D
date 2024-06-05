#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T>

void Foo(T t)
{
    cout << t << " generic Foo for " << typeid(t).name() << endl;
}

void Foo(int t)
{
    cout << t << " specialized Foo (int param)" << endl;
}

int main()
{
    Foo(4.4);
    Foo(5);
    Foo(6);
    Foo<double>(6.6);
    Foo<int>(5);
    Foo<char>('a');

    return 0;
}