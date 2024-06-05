#include <iostream>
using namespace std;

template <typename T>

T Max(T t1, T t2)
{
    return (t1 > t2) ? t1 : t2;
}


int main()
{
    int arr[5] = {2, 1, 0, 3, 4};

    cout << Max<int>(3, 5) << endl;
    cout << Max<double>(3.7 , 8.5) << endl;
    cout << Max<int*>(arr, arr + 2) << endl;
    cout << Max<int>('a', 'b') << endl;
    return 0;
}