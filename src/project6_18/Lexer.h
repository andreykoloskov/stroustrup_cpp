#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <string>

namespace Lexer
{
    enum Token_value
    {
        NAME, FUNCTION, NUMBER, END,
        PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
        PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
    };

    struct Symbol
    {
        Token_value curr_tok;
        double number_value;
        std::string string_value;
        std::map<std::string, double> table;
        std::map<std::string, std::string> functions;
        int no_of_errors;
    };

    Token_value get_token(std::istream*, Symbol*);
}

