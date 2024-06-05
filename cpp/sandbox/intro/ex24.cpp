#include <iostream>
using namespace std;

struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{}


void X::Inc()
{
    ++m_a;
    ++m_b; 
    cout << "X::Inc values" << " a: " << m_a <<" b: " << m_b << endl;
    cout << "this " << this << endl;               
}

void X::Dec()
{
    --m_a;
    --m_b;  
    cout << "X::Dec values" << " a: " << m_a <<" b: " << m_b << endl;
    cout << "this " << this << endl;                    
}

void Inc(X x)
{
   ++x.m_a;
   ++x.m_b;
   cout << "this is func INC values" << " m_a: " << x.m_a <<" m_b: " << x.m_b << endl;
}

int main()
{
    X x1(7, -55);
    X x2(x1);

    x1.Inc();
    x1.Inc();
    x2.Dec();

    Inc(x1);

    return 0;
}
