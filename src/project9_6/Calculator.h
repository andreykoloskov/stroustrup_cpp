#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include "Lexer.h"
#include "Parser.h"
#include "Error.h"

class Calculator
{
public:
    void calculate(std::istream* input);
};