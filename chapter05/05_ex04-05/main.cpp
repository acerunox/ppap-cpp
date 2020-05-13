/*
Exercise 04: Do exercise 3 again, but this time handle the error inside ctok().

Exercise 05: Add to the program so that it can also convert from Kelvin to Celsius.
*/

#include <iostream>

double ctok(double c)
{
    const double absZero = -273.15; //in celsius
    if (c < absZero) throw std::runtime_error("[ERROR] Temperature cannot be lower than absolute zero.");
    
    double k = c + 273.15;
    return k;
}

double ktoc(double k)
{
    const double absZero = -273.15; //in celsius
    if (k < 0) throw std::runtime_error("[ERROR] Temperature cannot be lower than absolute zero.");

    double c = absZero + k;
    return c;
}

int main()
{
    std::cout << "Temperature converter:\n"
        << " 1. Convert Celsius to Kelvin\n"
        << " 2. Convert Kelvin to Celsius\n";
    try 
    {
        int choice = 0;
        while(std::cout << "> " && std::cin >> choice)
        {
            std::cout << ">> ";
            switch(choice)
            {
                case 1:
                {
                    double c = 0;
                    std::cin >> c;
                    double k = ctok(c);
                    std::cout << k << '\n';
                    break;
                }

                case 2:
                {
                    double k = 0;
                    std::cin >> k;
                    double c = ktoc(k);
                    std::cout << c << '\n';
                    break;
                }

                default:
                    std::cerr << "[ERROR] Unknown input. Try again.\n";
                    continue;
            }
        }
    }
    catch (std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}