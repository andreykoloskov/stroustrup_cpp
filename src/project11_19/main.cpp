#include <iostream>
#include "ptr.h"


template<class T>
void f(T a)
{
    T v[200];

    PtrT<int> p(&v[0], v, 200);

    p--;
    //*p = a;
    //int *t = p.operator->();

    p++;
    *p = a;

    p++;
    *p = a + 1;
    int *q = p.operator->();

    std::cout << v[0] << " " << v[1] << std::endl;
}

int main(int argc, char **argv)
{
    try {
        f(5);
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
    return 0;
}
