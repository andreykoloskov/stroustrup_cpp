#include <iostream>
#include "assoc.h"

int main(int argc, char **argv)
{
    std::string buf;
    Assoc vec;
    int cnt = 0;
    while (cnt++ < 3 && std::cin >> buf) vec[buf]++;
    vec.printAll();
    return 0;
}