#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    float *f = new float(12.6);

    if (!f) 
    {
        cout << "failed allocte memory\n"<< endl;
    }

    cout << *f << endl;

    delete f;

    f = new float[15];

    f[14] = 1.1;

    cout << f[14]<< endl;

    delete[] f;

    int *ptr = (int *)malloc(10 * sizeof(int));

    delete ptr;

    int *ptr2 = new int(10);

    free(ptr2);
/******************************************************************************/
    int *ptr5 = (int*)malloc(1000*sizeof(int));
    delete ptr5;

    int *ptr6 = new int[1000];
    free(ptr6);

    return 0;    
}