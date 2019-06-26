#include <iostream>
#include "ptr.h"

void update(const char *s)
{
    RecPtr p(s);
    p->name = "New";
    std::cout << p->name << std::endl;
}

int main(int argc, char **argv)
{
    update("Update");
    return 0;
}