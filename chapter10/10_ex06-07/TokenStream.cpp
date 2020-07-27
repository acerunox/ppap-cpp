#include "./TokenStream.hpp"
#include "./Token.hpp"
#include "./RomanInt.hpp"
#include "../../lib/utilities.h"
#include <iostream>

using RomanNumeralSystem::RomanSymbol;
using RomanNumeralSystem::RomanInt;

TokenStream::TokenStream() : isBufferFull(false), buffer(CalculatorSymbol::ZERO) {}

Token TokenStream::Get()
{
    if (isBufferFull)
    {
        isBufferFull = false;
        return buffer;
    }

    char charSymbol;
    do
    {
        std::cin.get(charSymbol);
        if (charSymbol == '\n') return Token(CalculatorSymbol::PRINT);
    } while (isspace(charSymbol));

    switch (charSymbol)
    {
        case char(CalculatorSymbol::PRINT):
        case char(CalculatorSymbol::OPEN_PARENTHESES): case char(CalculatorSymbol::CLOSED_PARENTHESES): 
        case char(CalculatorSymbol::OPEN_CURLY): case char(CalculatorSymbol::CLOSED_CURLY):
        case char(CalculatorSymbol::COMMA): case char(CalculatorSymbol::EQUALS):
        case char(CalculatorSymbol::PLUS): case char(CalculatorSymbol::MINUS): case char(CalculatorSymbol::MULTIPLY): case char(CalculatorSymbol::DIVIDE): case char(CalculatorSymbol::FACTORIAL): 
            return Token(CalculatorSymbol(charSymbol));

        case char(RomanSymbol::M): case char(RomanSymbol::D): case char(RomanSymbol::C): case char(RomanSymbol::L):
        case char(RomanSymbol::X): case char(RomanSymbol::V): case char(RomanSymbol::I): case char(RomanSymbol::N):
        {
            std::cin.unget();
            RomanInt roman;
            std::cin >> roman;
            return Token(CalculatorSymbol::NUMBER, roman.AsInt());
        }

        default:
            char character = char(charSymbol);
            if (isalpha(character))
            {
                std::string input;
                do 
                {
                    input += character;
                }
                while (std::cin.get(character) && (isalpha(character) || isdigit(character) || character == char(CalculatorSymbol::UNDERSCORE)));
                std::cin.unget();

                if (input == Keys::declaration) return Token(CalculatorSymbol::DECLARE);
                if (input == Keys::constant) return Token(CalculatorSymbol::CONST);
                if (input == Keys::squareRoot) return Token(CalculatorSymbol::SQUARE_ROOT);
                if (input == Keys::power) return Token(CalculatorSymbol::POWER);
                if (input == Keys::logarithm) return Token(CalculatorSymbol::LOGARITHM);
                if (input == Keys::quit) return Token(CalculatorSymbol::QUIT);
                if (input == Keys::help) return Token(CalculatorSymbol::HELP);
                return Token(CalculatorSymbol::NAME, input);
            }
            else ThrowError(charSymbol + " is not an allowed symbol.");
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
    while (std::cin >> currentSymbol)
    {
        if (currentSymbol == symbol) return;
    }
}