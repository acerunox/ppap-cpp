#include "TokenStream.h"
#include "../../lib/utilities.h"
#include <iostream>
#include <sstream>

std::istream &operator>> (std::istream &is, CalculatorSymbol &symbol)
{
    char input;
    do
    {
        is.get(input);
        if (input == '\n') 
        {
            symbol = CalculatorSymbol::PRINT;
            return is;
        }
    } while (isspace(input));
    
    
    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    symbol = CalculatorSymbol(input);
    return is;
}

std::ostream &operator<< (std::ostream &os, const CalculatorSymbol &symbol)
{
    return os << char(symbol);
}

TokenStream::TokenStream() : isBufferFull(false), buffer(CalculatorSymbol::ZERO), inputStream(std::cin) {}

TokenStream::TokenStream(std::istream &is) : isBufferFull(false), buffer(CalculatorSymbol::ZERO), inputStream(is) {}

Token TokenStream::Get()
{
    if (isBufferFull)
    {
        isBufferFull = false;
        return buffer;
    }

    CalculatorSymbol symbol;
    inputStream >> symbol;

    switch (symbol)
    {
        case CalculatorSymbol::PRINT:
        case CalculatorSymbol::OPEN_PARENTHESES: case CalculatorSymbol::CLOSED_PARENTHESES: 
        case CalculatorSymbol::OPEN_CURLY: case CalculatorSymbol::CLOSED_CURLY:
        case CalculatorSymbol::COMMA: case CalculatorSymbol::EQUALS:
        case CalculatorSymbol::PLUS: case CalculatorSymbol::MINUS: case CalculatorSymbol::MULTIPLY: case CalculatorSymbol::DIVIDE: case CalculatorSymbol::FACTORIAL: 
            return Token(symbol);

        case CalculatorSymbol::DOT:
        case CalculatorSymbol::ZERO: case CalculatorSymbol::ONE: case CalculatorSymbol::TWO: case CalculatorSymbol::THREE: case CalculatorSymbol::FOUR:
        case CalculatorSymbol::FIVE: case CalculatorSymbol::SIX: case CalculatorSymbol::SEVEN: case CalculatorSymbol::EIGHT: case CalculatorSymbol::NINE:
        {
            inputStream.putback(char(symbol));
            int value = 0;
            inputStream >> value;
            return Token(CalculatorSymbol::NUMBER, value);
        }

        default:
            char character = char(symbol);
            if (isalpha(character))
            {
                std::string input;
                do 
                {
                    input += character;
                }
                while (inputStream.get(character) && (isalpha(character) || isdigit(character) || character == char(CalculatorSymbol::UNDERSCORE)));
                inputStream.unget();

                if (input == Keys::declaration) return Token(CalculatorSymbol::DECLARE);
                if (input == Keys::constant) return Token(CalculatorSymbol::CONST);
                if (input == Keys::squareRoot) return Token(CalculatorSymbol::SQUARE_ROOT);
                if (input == Keys::power) return Token(CalculatorSymbol::POWER);
                if (input == Keys::logarithm) return Token(CalculatorSymbol::LOGARITHM);
                if (input == Keys::quit) return Token(CalculatorSymbol::QUIT);
                if (input == Keys::help) return Token(CalculatorSymbol::HELP);
                return Token(CalculatorSymbol::NAME, input);
            }
            else
            {
                std::ostringstream outStream;
                outStream << "[ERROR] " << char(symbol) << " is not an allowed symbol.";
                ThrowError(outStream.str());
            }
    }
}

void TokenStream::Putback(const Token &token)
{
    if (isBufferFull) ThrowError("[ERROR] Buffer already full.");
    isBufferFull = true;
    buffer = token;
}

void TokenStream::ClearUntilSymbol(const CalculatorSymbol &symbol)
{
    if (isBufferFull && buffer.kind == symbol)
    {
        isBufferFull = false;
        return;
    }
    isBufferFull = false;
    
    CalculatorSymbol currentSymbol;
    while (std::cin >> currentSymbol)
    {
        if (currentSymbol == symbol) return;
    }
}