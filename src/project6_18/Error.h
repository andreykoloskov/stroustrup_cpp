#pragma once

#include <string>
#include "Lexer.h"

namespace Error
{
    struct Zero_divide
    {
        Zero_divide(Lexer::Symbol* symbol) { symbol->no_of_errors++; }
    };

    struct Syntax_error
    {
        const char* p;
        Syntax_error(const char* q, Lexer::Symbol* symbol) { p = q; symbol->no_of_errors++; }
    };

    double error(const std::string& s, int line, Lexer::Symbol* symbol);
}
