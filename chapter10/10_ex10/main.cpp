/*
Exercise 10: Add a command from x to the calculator from Chapter 7 that makes it take input from a file x.
             Add a command to y to the calculator that makes it write its output (both standard output and error output) to file y.
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

                case CalculatorSymbol::TO:
                    calculator.WriteToFile();
                    break;

                case CalculatorSymbol::FROM:
                    calculator.ReadFromFile(std::cout);
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