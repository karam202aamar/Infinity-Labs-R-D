#include <iostream>

class B
{
public:
    B(int a_ = 8) : m_a(a_) { std::cout << "B::Ctor" << std::endl; }
    virtual ~B() { std::cout << "B::Dtor" << std::endl; }

    virtual void Print1() const;
    void Print2() const;
    virtual void Print3() const;
    int m_p;

private:
    int m_a;
};

void B::Print1() const
{
    std::cout << "B::print1 B::m_a - " << m_a << std::endl;
}

void B::Print2() const
{
    std::cout << "B::print2" << std::endl;
}

void B::Print3() const
{
    std::cout << "B::print3" << std::endl;
}

class X : public B
{
public:
    X() : m_b(0) { std::cout << "X::Ctor" << std::endl; }

    ~X() { std::cout << "X::Dtor" << std::endl; }

    virtual void Print1() const
    {
        std::cout << "X::Print1::m_b " << m_b << std::endl;

        B::Print1();

        std::cout << "X::Print1 end" << std::endl;
    }

    virtual void Print2() const { std::cout << "X::Print2" << std::endl; }

private:
    int m_b;
};

int main()
{
    B *b1 = new B;
    B *b2 = new X;

    std::cout << std::endl
              << "main  b1" << std::endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();
    
        std::cout <<  std::endl << "main  b2" << std::endl;
        b2->Print1();
        b2->Print2();
        b2->Print3();

        X* xx = static_cast<X*>(b2);
        std::cout <<  std::endl << "main  xx" << std::endl;
        xx->Print1();
        xx->Print2();
        b2->Print2();

        delete b1;
        delete b2; 

    return 0;
}
