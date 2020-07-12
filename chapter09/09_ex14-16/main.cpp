/*
Exercise 14: Design and implement a Money class for calculations involving dollars and cents.
             Arithmetic has to be accurate to the last cent using the 4/5 rounding rule (.5 of a cent rounds up; anything less than .5 rounds down).
             Represent a monetary amount as a number of cents in a long int, but input and output as dollars and cents, e.g., $123.45.

Exercise 15: Refine the Money class by adding a currency (given as a constructor argument).
             Accept a floating-point initializer as long as it can be exactly represented as a long int.
             Don’t accept illegal operations.
             For example, Money*Money doesn’t make sense.
             USD1.23+DKK5.00 makes sense only if you provide a conversion table defining the conversion factor between U.S. dollars (USD) and Danish kroner (DKK).

Exercise 16: Define an input operator (>>) that reads monetary amounts with currency denominations, such as USD1.23 and DKK5.00, into a Money variable.
             Also define a corresponding output operator (<<).
*/

#include "./Money.hpp"
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <stdexcept>

using namespace MoneyLib;

Money GetMoney()
{
    std::cout << "Enter currency and amount (CCY x.xx): ";
    Money money;

    while (!(std::cin >> money))
    {
        std::cerr << "Please enter a valid currency and amount (CCY x.xx): : \n";
        std::cin.clear();
        std::cin.ignore(INT_MAX);
    }

    return money;
}

int main()
{
    Money first = GetMoney();
    Money second = GetMoney();

    std::cout << "First: " << first << '\n';
    std::cout << "Second: " << second << '\n';
    std::cout << '\n';

    try
    {
        std::cout << "Add: " << first + second << '\n';
        std::cout << "Subtract: " << first - second << '\n';
        std::cout << "Multiply first: " << first * 3.3 << '\n';
        std::cout << "Divide first: " << first / 2.8 << '\n';
    }
    catch (const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
        return EXIT_FAILURE;
    }
}