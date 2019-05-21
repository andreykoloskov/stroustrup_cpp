#include "Calculator.h"

void Calculator::calculate(std::istream* input)
{
    Lexer::Symbol symbol;
    symbol.curr_tok = Lexer::PRINT;

    symbol.table["pi"] = 3.14;
    symbol.table["e"] = 2.71;


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
}
