#include <iostream>

using namespace std;

void Foo(int a);
void Foo(int a, int b);
void Foo(int a, int b, float c);

int main()
{
    cout << "1 parameter " << endl;  
    Foo(2);

    cout << "2 parameters" << endl;   
    Foo(4, 6);

    cout << "3 parameters" << endl;  
    Foo(8, 10, 12.5);

    return 0;
}

void Foo(int a, int b, float c)
{
    cout << "a value : " << a << " b value :" << b << " c value :" << c << endl;
}

void Foo(int a, int b)
{
    cout << "a value : " << a << " b value :" << b << endl;
}

void Foo(int a)
{
    cout << "a value : " << a << endl;
}