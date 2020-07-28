#include "./TokenStream.hpp"
#include "./Token.hpp"
#include "../../lib/utilities.h"
#include <iostream>

TokenStream::TokenStream(std::istream &instream) : isBufferFull(false), buffer(CalculatorSymbol::ZERO), inputStream(instream)  {}

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
                while (inputStream.get(character) && (isalpha(character) || isdigit(character) 
                       || character == char(CalculatorSymbol::UNDERSCORE) || character == char(CalculatorSymbol::DOT) || character == char(CalculatorSymbol::SLASH)));
                
                inputStream.unget();

                if (input == Keywords::declaration) return Token(CalculatorSymbol::DECLARE);
                if (input == Keywords::from) return Token(CalculatorSymbol::FROM);
                if (input == Keywords::to) return Token(CalculatorSymbol::TO);
                if (input == Keywords::constant) return Token(CalculatorSymbol::CONST);
                if (input == Keywords::squareRoot) return Token(CalculatorSymbol::SQUARE_ROOT);
                if (input == Keywords::power) return Token(CalculatorSymbol::POWER);
                if (input == Keywords::logarithm) return Token(CalculatorSymbol::LOGARITHM);
                if (input == Keywords::quit) return Token(CalculatorSymbol::QUIT);
                if (input == Keywords::help) return Token(CalculatorSymbol::HELP);
                return Token(CalculatorSymbol::NAME, input);
            }
            else ThrowError(char(symbol) + " is not an allowed symbol.");
    }
}

void TokenStream::Putback(const Token &token)
{
    if (isBufferFull) ThrowError("Buffer already full.");
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
    while (inputStream >> currentSymbol)
    {
        if (currentSymbol == symbol) return;
    }
}