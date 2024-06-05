#include <iostream>
using namespace std;

struct X
{
    explicit X();
    explicit X(int a_, int b_ = 8);
    ~X();
    X(const X &other_);
    X &operator=(const X &other_);

    int m_a;
    const int m_b;
};

struct  Y
{
    X m_x;
    int m_i;
};

X::X(): m_a(3), m_b(4) // default
{
    // m_a = 3;
    // m_b = 4;
    cout << "this: " << this <<
            " X default Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_)//set the values a & b in m_a & m_b
{
    cout << "this: " << this <<
            " X int int Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;    
}

X::X(const X &other_): m_a(other_.m_a), m_b(other_.m_b)//copy struct
{
    cout << "this: " << this <<
            " X copy Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;
}

X& X::operator=(const X &other_)//destructor
{
    m_a = other_.m_a;
    // m_b = other_.m_b;
    cout << "this: " << this <<
            " X assignment operator.m_a: " << m_a <<
            " m_b: " << m_b << endl;
    
    return *this;
}

X::~X()
{
    cout << "this: " << this <<
            " X Dtor Ctor.m_a: " << m_a <<
            " m_b: " << m_b << endl;
}

int main()
{
    X x1;
    X x2(7);
    X *px = new X(x2);
    X x3(9, 10);
    X x4(x1);
   // X* xp = new X[10];

    x1 = x3;

    delete px;
    px = 0;
    // delete[] xp;
    // xp = 0;

    cout << "y prints:" << endl;

    Y y1;
    y1.m_x.m_a = 250;
    //y1.m_x.m_b = 750;
    Y y2(y1);
    Y y3;

    y3 = y1;

    return 0;
}