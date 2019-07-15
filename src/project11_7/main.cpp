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

    for (auto it = x.begin(); it != x.end(); ++it)
       std::cout << *it;
    std::cout << std::endl;

    for (auto it = x.begin(); it != x.end(); it++)
       std::cout << *it;
    std::cout << std::endl;

    auto it = x.begin();
    ++it;
    *it = 'a';

    std::cout << x << std::endl;

    String p = "Hello world!";
    String t = p(2, 3);
    std::cout << p << " : " << t << std::endl;

    return 0;
}