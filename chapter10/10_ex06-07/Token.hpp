#pragma once
#include <iostream>
#include <string>

enum class CalculatorSymbol { ZERO = '0', NAME = 'A', NUMBER = 'N', 
                              DECLARE = 'D', CONST = 'C', POWER = 'P', SQUARE_ROOT = 'S', LOGARITHM = 'L', COMMA = ',',
                              UNDERSCORE = '_', EQUALS = '=', PRINT = ';', QUIT = 'Q', HELP = 'H',
                              OPEN_PARENTHESES = '(', CLOSED_PARENTHESES = ')', OPEN_CURLY = '{', CLOSED_CURLY = '}', 
                              PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', FACTORIAL = '!' };

std::istream &operator>> (std::istream &is, CalculatorSymbol &symbol);
std::ostream &operator<< (std::ostream &os, const CalculatorSymbol &symbol);

struct Token
{
    Token(CalculatorSymbol kind) : kind(kind), value(0) {}
    Token(CalculatorSymbol kind, int value) : kind(kind), value(value) {}
    Token(CalculatorSymbol kind, std::string name) : kind(kind), name(name) {}

    CalculatorSymbol kind;
    int value;
    std::string name;
};