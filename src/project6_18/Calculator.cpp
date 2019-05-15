#include <iostream>
#include <sstream>
#include <map>
#include "Lexer.h"
#include "Parser.h"
#include "Error.h"

int main(int argc, char *argv[])
{
    std::istream *input;
    Lexer::Symbol symbol;
    symbol.curr_tok = Lexer::PRINT;

    symbol.table["pi"] = 3.14;
    symbol.table["e"] = 2.71;

    switch(argc) {
        case 1:
            input = &std::cin;
            break;
        case 2:
            input = new std::istringstream(argv[1]);
            break;
        default:
            Error::error("too many arguments", __LINE__, &symbol);
            return 1;
    }

    while (*input) {
        try {
            Lexer::get_token(input, &symbol);
            if (symbol.curr_tok == Lexer::END) {
                break;
            }
            if (symbol.curr_tok == Lexer::PRINT) {
                continue;
            }
            std::cout << Parser::expr(input, false, &symbol) << '\n';
        }
        catch (Error::Syntax_error e) {
            std::cerr << "syntax error: " << e.p << '\n';
            if (symbol.curr_tok != Lexer::PRINT) {
                continue;
            }
        }
    }

    if (input != &std::cin) {
        delete input;
    }

    return symbol.no_of_errors;
}