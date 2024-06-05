#include <iostream> // cout

class X
{
public:
    virtual ~X() {std::cout << "X dtor" << std::endl;}
    

private:
    double m_a; 
};

class Y: public X
{
public:
    Y(int m_b = 0):m_b(m_b),m_b2(0),m_b1(0){};
private:
    int m_b;
    int m_b2;
    int m_b1;
};

int main()
{
    X *xp = new Y[5];
    //X *xp = new Y(5);
    Y* yp = static_cast<Y*>(xp); //without this cast you cannot release the memory for xp
    
    //delete xp;
    return 0;
}
