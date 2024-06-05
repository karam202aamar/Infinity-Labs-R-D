#include <iostream>

class X
{
public:
    explicit X();
    explicit X(int a_);
    explicit X(int a_, int b_);
    
    operator char() const;
    operator int() const;
    void Print() const;

private:
    int m_a;
};

X::X(): m_a(120) {std::cout << "1 called"<< std::endl;}

X::X(int a_): m_a(a_) {std::cout << "2 called"<< std::endl;}

X::X(int a_, int b_): m_a(a_ + b_) {std::cout << "3 called"<< std::endl;}

X::operator char() const
{
    std::cout << "operator char" << std::endl;
    return 'e';//m_num;
}

X::operator int() const
{
    std::cout << "operator int" << std::endl;
    return 11;//m_num;
}

void X::Print() const
{
    std::cout << "X::Print() " << m_a << std::endl;
}

void Fifi(X x_) 
{
    std::cout << "Fifi() \n" << x_.operator int() << std::endl;
    x_.Print();
}

int main()
{
    X x1(7);
    //X x2;

    //char i = x2.operator char();
    //std::cout << "i " << i << std::endl;
    //Fifi(x2);
    //Fifi(x1);  //1
    //Fifi(X(6));      //2
    //Fifi(9);       //3
    //Fifi(X(3, 1));    //4
    std::cout << "koko \n" << x1 * 3 << std::endl;
    return 0; //5
    
}