/*
Exercise 02: The following program takes in a temperature value in Celsius and converts it to Kelvin. This code has many errors in it.
             Find the errors, list them, and correct the code.

Exercise 03: Absolute zero is the lowest temperature that can be reached; it is –273.15°C, or 0K. 
             The above program, even whencorrected, will produce erroneous results when given a temperature below this. 
             Place a check in the main program that will produce an error if a temperature is given below –273.15°C.
*/

#include <iostream>

double ctok(double c)
{
    double k = c + 273.15;
    return k;
}

int main()
{
    try 
    {
        const double absZero = -273.15;

        double c = 0;
        std::cin >> c;
        if (c < absZero) throw std::runtime_error("[ERROR] Temperature cannot be lower than absolute zero.");
        double k = ctok(c);
        std::cout << k << '\n';
    }
    catch (std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}