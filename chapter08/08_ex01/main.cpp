/*
Exercise 01: Modify the calculator program from Chapter 7 to make the input stream an explicit parameter (as shown in §8.5.8), rather than simply using cin. 
             Also give the Token_stream constructor (§7.8.2) an istream& parameter so that when we figure out how to make our own istreams (e.g., attached to files), we can use the calculator for those.
*/

#include "Calculator.h"
#include <iostream>
#include <stdexcept>

int main()
{
    std::printf("Please enter expressions.\nType '%s' for help and '%s' to quit.\n", 
                Keys::help.c_str(), Keys::quit.c_str());
    
    Calculator calculator;
    while (true) 
    {
        try 
        {
            std::cout << "> ";
            Option option = calculator.Statement();

            switch (option)
            {
                case Option::QUIT:
                    return EXIT_SUCCESS;

                case Option::HELP:
                    calculator.PrintHelp();
                    break;

                case Option::DECLARE:
                    calculator.DeclareVariable();
                    break;
                
                case Option::CALCULATE:
                {
                    int result = calculator.Calculate();
                    std::cout << "= " << result << '\n';
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