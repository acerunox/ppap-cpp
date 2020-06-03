#pragma once
#include <iostream>
#include <string>

enum class CalculatorSymbol { ZERO = '0', ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOT = '.', 
                              NAME = 'A', NUMBER = 'N', 
                              DECLARE = 'D', CONST = 'C', POWER = 'P', SQUARE_ROOT = 'S', LOGARITHM = 'L', COMMA = ',',
                              UNDERSCORE = '_', EQUALS = '=', PRINT = ';', QUIT = 'Q', HELP = 'H',
                              OPEN_PARENTHESES = '(', CLOSED_PARENTHESES = ')', OPEN_CURLY = '{', CLOSED_CURLY = '}', 
                              PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', FACTORIAL = '!' };

std::istream &operator>> (std::istream &is, CalculatorSymbol &symbol);
std::ostream &operator<< (std::ostream &os, const CalculatorSymbol &symbol);

namespace Keys
{
    const std::string declaration = "let";
    const std::string constant = "const";
    const std::string squareRoot = "sqrt";
    const std::string power = "pow";
    const std::string logarithm = "log";
    const std::string quit = "quit";
    const std::string help = "help";
};

struct Token
{
    CalculatorSymbol kind;
    int value;
    std::string name;

    Token(CalculatorSymbol kind) : kind(kind), value(0) {}
    Token(CalculatorSymbol kind, int value) : kind(kind), value(value) {}
    Token(CalculatorSymbol kind, std::string name) : kind(kind), name(name) {}
};

class TokenStream
{
    public:
        TokenStream();
        TokenStream(std::istream &is);
        Token Get();
        void Putback(const Token &token);
        void ClearUntilSymbol(const CalculatorSymbol &symbol);
    private:
        std::istream &inputStream;
        bool isBufferFull;
        Token buffer;
};