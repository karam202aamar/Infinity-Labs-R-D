#include <iostream>

using namespace std;

int main()
{
    int i = 0;

    cout << "my name is karam "<< i << endl;
    cout << "enter a value for i "<< endl;
    cin >> i;
    cerr << "i = " << i << endl;

    char name[10];
    cout << "enter a new name "<< endl;
    cin >> name;
    cout << "the name is " << name << endl;

    return 0;
}