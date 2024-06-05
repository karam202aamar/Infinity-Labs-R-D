#include <iostream>
using namespace std;

struct X
{
    explicit X();//default constructor
    explicit X(int a_, int b_ = 8);//in this case if we send X x2(7); then the b value will be 8
    X(const X &other_);
    ~X();
    X& operator=(const X& other_);
    
    int m_a;
    const int m_b;
};

X::X(): m_a(3), m_b(4) // default values
{
    // m_a = 3;
    // m_b = 4;
    cout << "this: " << this <<
            " X default Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_)
{
    cout << "this: " << this <<
            " X int int Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;    
}

X::X(const X& other_ ): m_a(other_.m_a), m_b(other_.m_b)
{
    cout << "this: " << this <<
            " X copy Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;
}

X::~X()
{
    cout << "this(destructor): " << this <<
            " X Dtor Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;
}
X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b;
    cout << "this(set=): " << this <<
            " X assignment operator.m_a: " << m_a <<
            " m_b: " << m_b << endl;
    
    return *this;
}
int main()
{
    X x1;
    X x2(3);
    X x3(7,9);
    X x4(x1);



    x1 = x3;

    cout << "before return 0 automatically the destructor called" << endl;
    return 0;
}
