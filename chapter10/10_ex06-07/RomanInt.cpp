#include "./RomanInt.hpp"
#include "../../lib/utilities.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace RomanNumeralSystem
{
    RomanInt::RomanInt(std::string romanNumber) try : valueAsRoman(romanNumber), valueAsInteger(RomanToInt(romanNumber))
    {
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }

    int RomanToInt(const std::string &romanNumber)
    {
        int result = 0;
        char currentChar;
        std::istringstream sstream {romanNumber};

        while (sstream.get(currentChar))
        {
            auto iter = romanTable.find(RomanSymbol(currentChar));

            if (iter != romanTable.end())
            {
                RomanSymbol currentSymbol = iter->first;
                int currentValue = int(iter->second);
                
                sstream.get(currentChar);
                RomanSymbol nextSymbol = RomanSymbol(currentChar);

                switch (currentSymbol)
                {
                case RomanSymbol::I:    
                    switch(nextSymbol)  //check for IV and IX
                    {
                    case RomanSymbol::V:
                        result += int(RomanValue::V) - currentValue;
                        break;
                
                    case RomanSymbol::X:
                        result += int(RomanValue::X) - currentValue;
                        break;
                    
                    default:
                        sstream.unget();
                        result += currentValue;
                        break;
                    }
                    break;

                case RomanSymbol::X:    
                    switch(nextSymbol)  //check for XL and XC
                    {
                    case RomanSymbol::L:
                        result += int(RomanValue::L) - currentValue;
                        break;
                
                    case RomanSymbol::C:
                        result += int(RomanValue::C) - currentValue;
                        break;
                    
                    default:
                        sstream.unget();
                        result += currentValue;
                        break;
                    }
                    break;

                case RomanSymbol::C:    
                    switch(nextSymbol)  //check for CD and CM
                    {
                    case RomanSymbol::D:
                        result += int(RomanValue::D) - currentValue;
                        break;
                
                    case RomanSymbol::M:
                        result += int(RomanValue::M) - currentValue;
                        break;
                    
                    default:
                        sstream.unget();
                        result += currentValue;
                        break;
                    }
                    break;
                
                default:
                    sstream.unget();
                    result += currentValue;
                    break;
                }
            }
            else ThrowError("Character doesn't exist in the roman numeral system.");
        }

        //if (!sstream && !sstream.eof()) ThrowError("Something went wrong while trying to read the roman number.");
        
        return result;
    }

    std::ostream &operator<<(std::ostream &os, const RomanInt &roman)
    {
        os << roman.AsRoman();
        return os;
    }

    std::istream &operator>>(std::istream &is, RomanInt &roman)
    {
        std::string input;
        is >> input;

        if (!is)
        {
            is.clear(std::ios_base::failbit);
            return is;
        }

        roman = { input };
        return is;
    }
}