#include "./Token.hpp"
#include <iostream>

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