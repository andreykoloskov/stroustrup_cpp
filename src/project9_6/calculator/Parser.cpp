#include <sstream>
#include "Parser.h"
#include "Error.h"

double Parser::term(std::istream *input, bool get, Lexer::Symbol *symbol)
{
    double left = prim(input, get, symbol);

    for (;;) {
        switch(symbol->curr_tok) {
            case Lexer::MUL:
                left *= prim(input, true, symbol);
                break;
            case Lexer::DIV:
                if (double d = prim(input, true, symbol)) {
                    left /= d;
                    break;
                }
                throw Error::Zero_divide(symbol);
            default:
                return left;
        }
    }
}

double Parser::prim(std::istream *input, bool get, Lexer::Symbol *symbol)
{
    if (get) {
        Lexer::get_token(input, symbol);
    }

    switch (symbol->curr_tok) {
        case Lexer::NUMBER:
        {
            double v = symbol->number_value;
            Lexer::get_token(input, symbol);
            return v;
        }
        case Lexer::NAME:
        {
            double& v = symbol->table[symbol->string_value];
            if (Lexer::get_token(input, symbol) == Lexer::ASSIGN) {
                v = Parser::expr(input, true, symbol);
            }
            return v;
        }
        case Lexer::FUNCTION:
        {
            if (symbol->functions.find(symbol->string_value) != symbol->functions.end()) {
                std::istringstream in(symbol->functions[symbol->string_value]);

                Lexer::Symbol symbol_in;
                symbol_in.curr_tok = Lexer::PRINT;
                double res = 0;

                while (true) {
                    char c;
                    if (!(in >> c)) {
                        break;
                    }
                    else {
                        in.putback(c);
                    }

                    Lexer::get_token(&in, &symbol_in);
                    if (symbol_in.curr_tok == Lexer::END) {
                        break;
                    }
                    if (symbol_in.curr_tok == Lexer::PRINT) {
                        continue;
                    }
                    res = Parser::expr(&in, false, &symbol_in);
                }

                Lexer::get_token(input, symbol);
                return res;
            }
            else {
                throw Error::Syntax_error("function is not found", symbol);
            }
        }
        case Lexer::MINUS:
            return -prim(input, true, symbol);
        case Lexer::LP:
        {
            double e = Parser::expr(input, true, symbol);
            if (symbol->curr_tok != Lexer::RP) {
                throw Error::Syntax_error("')' expected", symbol);
            }
            Lexer::get_token(input, symbol);
            return e;
        }
        default:
            throw Error::Syntax_error("primary expected", symbol);
    }
}

double Parser::expr(std::istream *input, bool get, Lexer::Symbol *symbol)
{
    double left = Parser::term(input, get, symbol);

    for (;;) {
        switch(symbol->curr_tok) {
            case Lexer::PLUS:
                left += Parser::term(input, true, symbol);
                break;
            case Lexer::MINUS:
                left -= Parser::term(input, true, symbol);
                break;
            default:
                return left;
        }
    }
}

