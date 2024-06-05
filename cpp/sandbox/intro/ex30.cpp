#include <iostream>

class X
{
public:

    X() : m_id(++s_cntr) {}

    int GetId() 
    { 
        std::cout << m_id << std::endl; 
        return m_id;
    }

private:
    float m_id;
    static float s_cntr;
};

float X::s_cntr = 1.2;

int main()
{
    X x1;
    X x2;

    x1.GetId();
    x2.GetId();

    return 0;
}