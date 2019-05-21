#include "Lexer.h"
#include "Error.h"

Lexer::Token_value Lexer::get_token(std::istream *input, Lexer::Symbol *symbol)
{
    char ch = 0;

    do {
        if (!input->get(ch)) {
            return symbol->curr_tok = Lexer::END;
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';': case '\n':
            return symbol->curr_tok = Lexer::PRINT;
        case 0:
            return symbol->curr_tok = Lexer::END;
        case '*': case '/': case '+': case '-':
        case '(': case ')': case '=':
            return symbol->curr_tok = Lexer::Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            input->putback(ch);
            *input >> symbol->number_value;
            return symbol->curr_tok = Lexer::NUMBER;
        default:
            if (isalpha(ch)) {
                symbol->string_value = ch;
                while (input->get(ch) && isalnum(ch)) {
                    symbol->string_value.push_back(ch);
                }
                if (ch == '{') {
                    std::string functionBody;
                    while (input->get(ch) && ch != '}') {
                        functionBody.push_back(ch);
                    }

                    if (ch != '}') {
                        symbol->curr_tok = Lexer::PRINT;
                        throw Error::Syntax_error("bad token", symbol);
                    }

                    symbol->functions[symbol->string_value] = functionBody;
                    symbol->string_value.clear();
                    return Lexer::get_token(input, symbol);
                }
                else if (ch == '(') {
                    input->get(ch);
                    if (ch == ')') {
                        return symbol->curr_tok = Lexer::FUNCTION;
                    }
                    else {
                        symbol->curr_tok = Lexer::PRINT;
                        throw Error::Syntax_error("bad token", symbol);
                    }
                }

                input->putback(ch);
                return symbol->curr_tok = Lexer::NAME;
            }
            symbol->curr_tok = Lexer::PRINT;
            throw Error::Syntax_error("bad token", symbol);
    }
}
