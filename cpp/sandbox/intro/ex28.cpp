#include <iostream>
using namespace std;

class X;

int operator+(const X& x1_, const X& x2_)
{
    (void)(x1_);
    (void)(x2_);

    return 7;
}
//it can access private members in the class.
ostream& operator<<(ostream& os_, const X& x_); 

class X
{
public:
    bool operator==(const X& o_) const;
private:
    
    friend ostream& operator<<(ostream& os_, const X& x_); 
    int m_a;
};

bool X::operator==(const X& o_) const
{
    return m_a == o_.m_a; 
}

int main()
{
    X x1;
    X x2;

    cout << "x1+x2  " << x1 + x2 <<
            " \nx1==x2:" << (x1 == x2) <<
            " \nx1:    "<< x1 <<
            " \nx2:    "<< x2 << endl;
    return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a; //specify the behavior.
}


