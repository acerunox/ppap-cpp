/*
Exercise 13: Design and implement a rational number class, Rational.
             A rational number has two parts: a numerator and a denominator, for example, 5/6 (five-sixths, also known as approximately .83333). 
             Look up the definition if you need to.
             Provide assignment, addition, subtraction, multiplication, division, and equality operators.
             Also, provide a conversion to double.
*/

#include "./Rational.hpp"
#include <iostream>
#include <limits.h>
#include <stdexcept>

enum class Option { ADD = '1', SUBTRACT, MULTIPLY, DIVIDE, QUIT = 'q' };

std::istream &operator>>(std::istream &is, Option &option)
{
    char input;
    std::cin >> input;
    
    if (!std::cin)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    option = Option(input);
    return is;
}

Rational GetRational()
{
    std::cout << "Enter rational (a/b): ";
    Rational rational;

    while (!(std::cin >> rational))
    {
        std::cerr << "Please enter a valid rational (a/b): \n";
        std::cin.clear();
        std::cin.ignore(INT_MAX);
    }

    return rational;
}

int main()
{
    while (true)
    {
        std::cout << "\nWhat would you like to do?\n"
                  << "\t1. Add\n"
                  << "\t2. Subtract\n"
                  << "\t3. Multiply\n"
                  << "\t4. Divide\n"
                  << "\tq. Quit\n"
                  << "Choice: ";
        Option option;
        std::cin >> option;
        if (option == Option::QUIT) return EXIT_SUCCESS;

        Rational first = GetRational();
        Rational second = GetRational();
        Rational result;

        switch (option)
        {
        case Option::ADD:
            result = first + second;
            std::cout << first << " + " << second << " = " << result.Shorten() << " = " << result.ToDouble() << '\n';
            break;

        case Option::SUBTRACT:
            result = first - second;
            std::cout << first << " - " << second << " = " << result.Shorten() << " = " << result.ToDouble() << '\n';            
            break;

        case Option::MULTIPLY:
            result = first * second;
            std::cout << first << " * " << second << " = " << result.Shorten() << " = " << result.ToDouble() << '\n';
            break;

        case Option::DIVIDE:
            result = first / second;
            std::cout << first << " / " << second << " = " << result.Shorten() << " = " << result.ToDouble() << '\n';
            break;

        default:
            std::cerr << "[ERROR] Unrecognized option, try again.";
            continue;
        }
    }
}