#include <iostream>
#include "ptr.h"


template<class T>
void f(T a)
{
    T v[200];

    PtrT p(&v[0], v, 200);

    p--;
    //*p = a;

    p++;
    *p = a;

    p++;
    *p = a + 1;

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