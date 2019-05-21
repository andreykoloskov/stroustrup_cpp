#include "calculator/Calculator.h"

int main(int argc, char *argv[])
{
    std::istream *input;
	
    switch(argc) {
        case 1:
            input = &std::cin;
            break;
        default:
            input = new std::istringstream(argv[1]);
            break;
    }
	
	Calculator calc;
	calc.calculate(input);

    if (input != &std::cin) {
        delete input;
    }

    return 0;
}