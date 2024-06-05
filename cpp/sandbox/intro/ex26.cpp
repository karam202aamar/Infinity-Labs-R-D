#include <cstdio>

class X
{
public:
    explicit X(int a_);
    void Foo();

private: 
    void secret_func();
    int m_a;        
};

X::X(int a_)
    : m_a(a_)
{

}
//FOO inside the class
void X::Foo()
{
    secret_func();
    printf("X::Foo - %d\n", m_a); 
}    
void X::secret_func()
{
    
    printf("secret_func\n");
}

void Foo(const X& x_)
{ 
    //printf("%d\n", x_.m_a); //m_a is private, no access!
    printf("this  Foo cant access\n");
}

int main()
{
    X x1(1);
    //if i define here -> X test; // I GET ERROR CAUSE I DEFINE IT WITH 1 ARGUMENT.
    x1.Foo();
    //printf("%d\n", x1.m_a);//it's a private member.
    Foo(x1);

    return 0;
}

