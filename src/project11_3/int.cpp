#include <iostream>

class Int
{
public:
    Int(int x = 0): a(x) {}
	Int(Int& x) { a = x.a; }
	operator int() { return a; }
	Int operator+(Int x) { Int i(a + x.a); return i; }

private:
    int a;
};

int main(int argc, char **argv)
{
	Int x = 2 + 3;
	std::cout << x << std::endl;
    return 0;
}