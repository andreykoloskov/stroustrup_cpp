#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>

enum Token_value
{
    NAME,        FUNCTION,     NUMBER,       END,
    PLUS='+',    MINUS='-',    MUL='*',   DIV='/',
    PRINT=';',   ASSIGN='=',   LP='(',    RP=')'
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

double expr(std::istream*, bool, Symbol*);
double term(std::istream*, bool, Symbol*);
double prim(std::istream*, bool, Symbol*);
Token_value get_token(std::istream*, Symbol*);
double error(const std::string& s, int line, Symbol*);

double term(std::istream *input, bool get, Symbol *symbol)
{
    double left = prim(input, get, symbol);

    for (;;) {
        switch(symbol->curr_tok) {
            case MUL:
                left *= prim(input, true, symbol);
                break;
            case DIV:
                if (double d = prim(input, true, symbol)) {
                    left /= d;
                    break;
                }
                return error("divide by 0", __LINE__, symbol);
            default:
                return left;
        }
    }
}

double prim(std::istream *input, bool get, Symbol *symbol)
{
    if (get) {
        get_token(input, symbol);
    }

    switch (symbol->curr_tok) {
        case NUMBER:
        {
            double v = symbol->number_value;
            get_token(input, symbol);
            return v;
        }
        case NAME:
        {
            double& v = symbol->table[symbol->string_value];
            if (get_token(input, symbol) == ASSIGN) {
                v = expr(input, true, symbol);
            }
            return v;
        }
        case FUNCTION:
        {
            if (symbol->functions.find(symbol->string_value) != symbol->functions.end()) {
                std::istringstream in(symbol->functions[symbol->string_value]);

                Symbol symbol_in;
                symbol_in.curr_tok = PRINT;
                double res = 0;

                while (true) {
                    char c;
                    if (!(in >> c)) {
                        break;
                    }
                    else {
                        in.putback(c);
                    }

                    get_token(&in, &symbol_in);
                    if (symbol_in.curr_tok == END) {
                        break;
                    }
                    if (symbol_in.curr_tok == PRINT) {
                        continue;
                    }
                    res = expr(&in, false, &symbol_in);
                }

                get_token(input, symbol);
                return res;
            }
            else {
                return error("function is not found", __LINE__, symbol);
            }
        }
        case MINUS:
            return -prim(input, true, symbol);
        case LP:
        {
            double e = expr(input, true, symbol);
            if (symbol->curr_tok != RP) {
                return error("')' expected", __LINE__, symbol);
            }
            get_token(input, symbol);
            return e;
        }
        default:
            return error("primary expected", __LINE__, symbol);
    }
}

double expr(std::istream *input, bool get, Symbol *symbol)
{
    double left = term(input, get, symbol);

    for (;;) {
        switch(symbol->curr_tok) {
            case PLUS:
                left += term(input, true, symbol);
                break;
            case MINUS:
                left -= term(input, true, symbol);
                break;
            default:
                return left;
        }
    }
}

Token_value get_token(std::istream *input, Symbol *symbol)
{
    char ch = 0;

    do {
        if (!input->get(ch)) {
            return symbol->curr_tok = END;
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';': case '\n':
            return symbol->curr_tok = PRINT;
        case 0:
            return symbol->curr_tok = END;
        case '*': case '/': case '+': case '-':
        case '(': case ')': case '=':
            return symbol->curr_tok = Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            input->putback(ch);
            *input >> symbol->number_value;
            return symbol->curr_tok = NUMBER;
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
                        error("wrong function definition", __LINE__, symbol);
                        return symbol->curr_tok = PRINT;
                    }

                    symbol->functions[symbol->string_value] = functionBody;
                    symbol->string_value.clear();
                    return get_token(input, symbol);
                }
                else if (ch == '(') {
                    input->get(ch);
                    if (ch == ')') {
                        return symbol->curr_tok = FUNCTION;
                    }
                    else {
                        error("wrong function call", __LINE__, symbol);
                        return symbol->curr_tok = PRINT;
                    }
                }

                input->putback(ch);
                return symbol->curr_tok = NAME;
            }
            error("bad token", __LINE__, symbol);
            return symbol->curr_tok = PRINT;
    }
}

double error(const std::string &s, int line, Symbol *symbol)
{
    symbol->no_of_errors++;
    std::cerr << "error: " << s << " in line " << line << '\n';
    return 1;
}

int main(int argc, char *argv[])
{
    std::istream *input;
    Symbol symbol;
    symbol.curr_tok = PRINT;

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
            error("too many arguments", __LINE__, &symbol);
            return 1;
    }

    while (*input) {
        get_token(input, &symbol);
        if (symbol.curr_tok == END) {
            break;
        }
        if (symbol.curr_tok == PRINT) {
            continue;
        }
        std::cout << expr(input, false, &symbol) << '\n';
    }

    if (input != &std::cin) {
        delete input;
    }

    return symbol.no_of_errors;
}