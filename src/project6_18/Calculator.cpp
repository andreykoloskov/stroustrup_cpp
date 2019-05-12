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

double expr(std::istream *, bool);
double term(std::istream *, bool);
double prim(std::istream *, bool);
Token_value get_token(std::istream *);
double error(const std::string& s, int line);
std::istream *input;

Token_value curr_tok = PRINT;
double number_value;
std::string string_value;
std::map<std::string, double> table;
std::map<std::string, std::string> functions;
int no_of_errors;

double term(std::istream *input, bool get)
{
    double left = prim(input, get);

    for (;;) {
        switch(curr_tok) {
            case MUL:
                left *= prim(input, true);
                break;
            case DIV:
                if (double d = prim(input, true)) {
                    left /= d;
                    break;
                }
                return error("divide by 0", __LINE__);
            default:
                return left;
        }
    }
}

double prim(std::istream *input, bool get)
{
    if (get) {
        get_token(input);
    }

    switch (curr_tok) {
        case NUMBER:
        {
            double v = number_value;
            get_token(input);
            return v;
        }
        case NAME:
        {
            double& v = table[string_value];
            if (get_token(input) == ASSIGN) {
                v = expr(input, true);
            }
            return v;
        }
        case FUNCTION:
        {
            if (functions.find(string_value) != functions.end()) {
                std::istringstream in(functions[string_value]);

                Token_value curr_tok_in = curr_tok;
                double number_value_in = number_value;
                std::string string_value_in = string_value;
                std::map<std::string, double> table_in = table;

                curr_tok = PRINT;
                number_value = 0;
                string_value.clear();
                table.clear();

                double res = 0;

                while (true) {
                    char c;
                    if (!(in >> c)) {
                        break;
                    }
                    else {
                        in.putback(c);
                    }

                    get_token(&in);
                    if (curr_tok == END) {
                        break;
                    }
                    if (curr_tok == PRINT) {
                        continue;
                    }
                    res = expr(&in, false);
                }

                curr_tok = curr_tok_in;
                number_value = number_value_in;
                string_value = string_value_in;
                table = table_in;

                get_token(input);

                return res;
            }
            else {
                return error("function is not found", __LINE__);
            }
        }
        case MINUS:
            return -prim(input, true);
        case LP:
        {
            double e = expr(input, true);
            if (curr_tok != RP) {
                return error("')' expected", __LINE__);
            }
            get_token(input);
            return e;
        }
        default:
            return error("primary expected", __LINE__);
    }
}

double expr(std::istream *input, bool get)
{
    double left = term(input, get);

    for (;;) {
        switch(curr_tok) {
            case PLUS:
                left += term(input, true);
                break;
            case MINUS:
                left -= term(input, true);
                break;
            default:
                return left;
        }
    }
}

Token_value get_token(std::istream *input)
{
    char ch = 0;

    do {
        if (!input->get(ch)) {
            return curr_tok = END;
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';': case '\n':
            return  curr_tok = PRINT;
        case 0:
            return curr_tok = END;
        case '*': case '/': case '+': case '-':
        case '(': case ')': case '=':
            return curr_tok = Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            input->putback(ch);
            *input >> number_value;
            return curr_tok = NUMBER;
        default:
            if (isalpha(ch)) {
                string_value = ch;
                while (input->get(ch) && isalnum(ch)) {
                    string_value.push_back(ch);
                }
                if (ch == '{') {
                    std::string functionBody;
                    while (input->get(ch) && ch != '}') {
                        functionBody.push_back(ch);
                    }

                    if (ch != '}') {
                        error("wrong function definition", __LINE__);
                        return curr_tok = PRINT;
                    }

                    functions[string_value] = functionBody;
                    string_value.clear();
                    return get_token(input);
                }
                else if (ch == '(') {
                    input->get(ch);
                    if (ch == ')') {
                        return curr_tok = FUNCTION;
                    }
                    else {
                        error("wrong function call", __LINE__);
                        return curr_tok = PRINT;
                    }
                }

                input->putback(ch);
                return curr_tok = NAME;
            }
            error("bad token", __LINE__);
            return curr_tok = PRINT;
    }
}

double error(const std::string &s, int line)
{
    no_of_errors++;
    std::cerr << "error: " << s << " in line " << line << '\n';
    return 1;
}

int main(int argc, char *argv[])
{
    switch(argc) {
        case 1:
            input = &std::cin;
            break;
        case 2:
            input = new std::istringstream(argv[1]);
            break;
        default:
            error("too many arguments", __LINE__);
            return 1;
    }

    table["pi"] = 3.14;
    table["e"] = 2.71;

    while (*input) {
        get_token(input);
        if (curr_tok == END) {
            break;
        }
        if (curr_tok == PRINT) {
            continue;
        }
        std::cout << expr(input, false) << '\n';
    }

    if (input != &std::cin) {
        delete input;
    }

    return no_of_errors;
}