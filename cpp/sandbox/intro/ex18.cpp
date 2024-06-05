#include <iostream>
using namespace std; 

void func(int &t)
{
    t = 10;
    
}
int main()
{
    int i = 8;
    int &ip = i;
    ip = 9; 

    cout << "aliasing i value: " << i << endl;
    cout << "sizeof alias is: " << sizeof(ip) << endl;

    func(i);
    cout << "func " << i << endl;

    char c = 'a';
    char &cp = c;
    cp = 'b';

    cout << "aliasing c value: " <<cp << endl;
    cout << "sizeof alias is: " << sizeof(cp) << endl;

    return 0;
}