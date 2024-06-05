#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

struct BadDog: public runtime_error
{
    
    BadDog(const string& s_ = "this is a bad dog"): runtime_error(s_) {}
};

void Fifi()
{
    //throw BadDog("bad pup"); //creates exception that contains this string
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    
    //throw BadDog(); //default print for this bad dog
    Fifi();
    cerr << "Foo after Fifi" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar after Foo" << endl;
}

int main()
{
    try
    {
        Bar();
    }
    
    catch(bad_alloc&)
    {
        cerr << "out of memory! exiting\n";
        
    }
    catch(exception& r)
    {
        cerr << "unknown exception\n" << r.what();
        exit(4);
    }
    
    return 0;
}