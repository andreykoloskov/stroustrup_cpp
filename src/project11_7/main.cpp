#include <iostream>
#include "String.h"

String f(String a, String b)
{
    a[2] = 'x';
    char c = b[3];
    std::cout << "in f: " << a << ' ' << b << ' ' << c << '\n';
    return a;
}

int main(int argc, char **argv)
{
    String x, y;
    std::cout << "Please enter two strings\n";
    std::cin >> x >> y;
    std::cout << "input: " << x << ' ' << y << '\n';

    String z = x;
    y = f(x, y);
    if (x != z) std::cout << "x corrupted!\n";

    x[0] = '!';
    if (x == z) std::cout << "write failed!\n";
    std::cout << "exit: " << x << ' ' << y << ' ' << z << '\n';

    return 0;
}