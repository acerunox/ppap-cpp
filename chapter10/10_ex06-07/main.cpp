/*
Exercise 06: Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
             Provide Roman_int with an as_int() member that returns the int value.

Exercise 07: Make a version of the calculator from Chapter 7 that accepts Roman numerals rather than the usual Arabic ones, for example, XXI + CIV == CXXV.
*/

#include "./Calculator.hpp"
#include "./Token.hpp"
#include <iostream>

using CalculatorLib::Calculator;

int main()
{
    std::cout << "Please enter expressions.\n"
              << "Type 'help' for help and 'quit' to quit.\n";
    
    Calculator calculator;
    while (true) 
    {
        try 
        {
            std::cout << "> ";
            Token token = calculator.GetToken();
            while (token.kind == CalculatorSymbol::PRINT) token = calculator.GetToken();  // "Eat" print characters until next expression
            if (token.kind == CalculatorSymbol::QUIT) return EXIT_SUCCESS;
            
            switch (token.kind)
            {
                case CalculatorSymbol::HELP:
                    calculator.PrintHelp();
                    break;

                case CalculatorSymbol::DECLARE:
                    calculator.DeclareVariable();
                    break;
                
                default:
                {
                    calculator.PutbackToken(token);
                    int result = 0;
                    result = calculator.Calculate();
                    std::cout << char(CalculatorSymbol::EQUALS) << ' ' << result << '\n';
                }
            }
        }
        catch (const std::runtime_error &err) 
        {
            std::cerr << err.what() << '\n'; 
            calculator.ClearErrors();
        }
    }
}