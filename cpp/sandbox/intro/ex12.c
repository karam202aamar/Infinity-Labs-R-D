#include <iostream>

using namespace std;

void Foo()
{
    cout << "void\n";
};
void Foo(int a)
{
    cout << "int " << a << endl;
};
void Foo(char a) 
{
    cout << "char " << a << endl;
};
void Foo(char *a) 
{
    cout << "ptr " << a << endl;
};
void Foo(float a) 
{
    cout << "float " << a << endl;
};

int main()
{
    int b = 1;
    char a = 'k';
    char c[4] = "hey";
    float d = 2.2;

    cout << endl; 
    Foo();

    cout << endl;  
    Foo(a);

    cout << endl;  
    Foo(b);

    cout << endl;  
    Foo(c);

    cout << endl;  
    Foo(d);    

    cout << endl;  


    return 0;
}
