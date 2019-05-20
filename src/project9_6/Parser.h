#pragma once

#include <iostream>
#include "Lexer.h"

namespace Parser
{
    double expr(std::istream*, bool, Lexer::Symbol*);
    double term(std::istream*, bool, Lexer::Symbol*);
    double prim(std::istream*, bool, Lexer::Symbol*);
}
