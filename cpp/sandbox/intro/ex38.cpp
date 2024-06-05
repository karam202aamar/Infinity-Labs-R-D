#include <iostream>
#include <cstdlib>
#include <exception>
#include <typeinfo>

using namespace std;

struct X
{
    X(){cerr << "x ctor" << endl; throw bad_cast();}
    X(int){cerr << "x ctor (int)" << endl;}
    ~X(){cerr << "x Dtor" << endl;}
};

struct Y
{
    Y(){cerr << "Y ctor" << endl;}
    ~Y(){cerr << "Y ctor" << endl;}
};

class L 
{
    public:
        L():m_x(2){cerr << "L Ctor" << endl;}
        ~L(){cerr << "L Dtor" << endl;}

    private:
        Y m_y;
        X m_x;
};

class M 
{
    public:
        M(){cerr << "M Ctor" << endl;}
        ~M(){cerr << "M Dtor" << endl;}
    private:
        Y m_y;
        X m_x;
};

class N 
{
    public:
        N(){cerr << "N Ctor" << endl;}
        ~N(){cerr << "N Dtor" << endl;}
    private:
        Y m_y;
        X m_x;
};

class J 
{
    public:
        J(){cerr << "J Ctor" << endl;}
        ~J(){cerr << "J Dtor" << endl;delete m_x; delete m_y;}
    private:
        Y *m_y;
        X *m_x;
};

class K 
{
    public:
        K(){cerr << "K Ctor" << endl;m_y = new Y; m_x = new X;}
        ~K(){cerr << "K Dtor" << endl;delete m_x; delete m_y;}
    private:
        Y *m_y;
        X *m_x;
};

int main()
{
    try
    {
        K var1;
    }
    catch(exception& e)
    {
        std::cerr << "exception cout. what: " << e.what() << '\n';
    }
    
    std::cout << "here" << '\n';

    return 0;
}