#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>

enum Token_value
{
   NAME,        NUMBER,       END,
   PLUS='+',    MINUS='-',    MUL='*',   DIV='/',
   PRINT=';',   ASSIGN='=',   LP='(',    RP=')'
};

double expr(bool);
double term(bool);
double prim(bool);
Token_value get_token();
double error(const std::string& s);
std::istream *input;

Token_value curr_tok = PRINT;
double number_value;
std::string string_value;
std::map<std::string, double> table;
int no_of_errors;

double term(bool get)
{
   double left = prim(get);

   for (;;) {
      switch(curr_tok) {
         case MUL:
            left *= prim(true);
            break;
         case DIV:
            if (double d = prim(true)) {
               left /= d;
               break;
            }
            return error("divide by 0");
         default:
            return left;
      }
   }
}

double prim(bool get)
{
   if (get) {
      get_token();
   }

   switch (curr_tok) {
      case NUMBER:
      {
         double v = number_value;
         get_token();
         return v;
      }
      case NAME:
      {
         double& v = table[string_value];
         if (get_token() == ASSIGN) {
            v = expr(true);
         }
         return v;
      }
      case MINUS:
         return -prim(true);
      case LP:
      {
         double e = expr(true);
         if (curr_tok != RP) {
            return error("')' expected");
         }
         get_token();
         return e;
      }
      default:
         return error("primary expected");
   }
   
}

double expr(bool get)
{
   double left = term(get);

   for (;;) {
      switch(curr_tok) {
         case PLUS:
            left += term(true);
            break;
         case MINUS:
            left -= term(true);
            break;
         default:
            return left;
      }
   }
}

Token_value get_token()
{
   char ch = 0;
   //std::cin >> ch;

   do {
      if (!std::cin.get(ch)) {
         return curr_tok = END;
      }
   } while (ch != '\n' && isspace(ch));

   switch (ch) {
      case ';':
      case '\n':
         return  curr_tok = PRINT;
      case 0:
         return curr_tok = END;
      case '*':
      case '/':
      case '+':
      case '-':
      case '(':
      case ')':
      case '=':
         return curr_tok = Token_value(ch);
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
      case '.':
         std::cin.putback(ch);
         std::cin >> number_value;
         return curr_tok = NUMBER;
      default:
         if (isalpha(ch)) {
            string_value = ch;
            while (std::cin.get(ch) && isalnum(ch)) {
               string_value.push_back(ch);
            }
            std::cin.putback((ch));
            return curr_tok = NAME;
         }
         error("bad token");
         return curr_tok = PRINT;
   }
}

double error (const std::string &s)
{
   no_of_errors++;
   std::cerr << "error: " << s << '\n';
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
         error("too many arguments");
         return 1;
   }

   table["pi"] = 3.14;
   table["e"] = 2.71;

   while (*input) {
      get_token();
      if (curr_tok == END) {
         break;
      }
      if (curr_tok == PRINT) {
         continue;
      }
      std::cout << expr(false) << '\n';
   }

   if (input != &std::cin) {
      delete input;
   }

   return no_of_errors;
}