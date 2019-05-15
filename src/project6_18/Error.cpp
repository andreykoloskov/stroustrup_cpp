#include <iostream>
#include "Error.h"

double Error::error(const std::string &s, int line, Lexer::Symbol *symbol)
{
    symbol->no_of_errors++;
    std::cerr << "error: " << s << " in line " << line << '\n';
    return 1;
}
