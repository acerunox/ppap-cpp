/*
Roman Numerals List:
    N =    0
    I =    1
    V =    5
    X =   10
    L =   50
    C =  100
    D =  500
    M = 1000
*/

#pragma once
#include <iostream>
#include <map>
#include <string>

namespace RomanNumeralSystem
{
    enum class RomanSymbol : char { N = 'N', I = 'I', V = 'V', X = 'X', L = 'L', C = 'C', D = 'D', M = 'M' };
    enum class RomanValue : int { N = 0, I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000 };
    const std::map<RomanSymbol, RomanValue> romanTable { {RomanSymbol::N, RomanValue::N},
                                                         {RomanSymbol::I, RomanValue::I}, 
                                                         {RomanSymbol::V, RomanValue::V}, 
                                                         {RomanSymbol::X, RomanValue::X}, 
                                                         {RomanSymbol::L, RomanValue::L}, 
                                                         {RomanSymbol::C, RomanValue::C}, 
                                                         {RomanSymbol::D, RomanValue::D},
                                                         {RomanSymbol::M, RomanValue::M} };

    class RomanInt
    {
    public:
        RomanInt(int intValue = 0) {}
        RomanInt(std::string romanNumber);

        std::string AsRoman() const { return valueAsRoman; }
        int AsInt() const { return valueAsInteger; }
    private:
        std::string valueAsRoman;
        int valueAsInteger;
    };

    int RomanToInt(const std::string &romanNumber);

    std::ostream &operator<<(std::ostream &os, const RomanInt &roman);
    std::istream &operator>>(std::istream &is, RomanInt &roman);
}