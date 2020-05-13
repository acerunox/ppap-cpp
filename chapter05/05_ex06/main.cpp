/*
Exercise 06: Write a program that converts from Celsius to Fahrenheit and from Fahrenheit to Celsius.
*/

#include <iomanip>
#include <iostream>

double ConvertToCelsius(double fahrenheit)
{
    const double absZero = -459.67; //in fahrenheit
    if (fahrenheit < absZero) throw std::runtime_error("[ERROR] Temperature cannot be lower than absolute zero.");

    return (fahrenheit - 32) * 5.0/9.0;
}

double ConvertToFahrenheit(double celsius)
{
    const double absZero = -273.15; //in celsius
    if (celsius < absZero) throw std::runtime_error("[ERROR] Temperature cannot be lower than absolute zero.");

    return celsius * 9.0/5.0 + 32;
}

int main()
{
    try
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Temperature converter:\n"
        << " 1. Convert Celsius to Fahrenheit\n"
        << " 2. Convert Fahrenheit to Celsius\n";

        int choice = 0;
        while (std::cout << "> " && std::cin >> choice)
        {
            std::cout << ">> ";
            switch(choice)
            {
                case 1:
                {
                    double celsius = 0;
                    std::cin >> celsius;
                    double fahrenheit = ConvertToFahrenheit(celsius);
                    std::cout << fahrenheit << '\n';
                    break;
                }

                case 2:
                {
                    double fahrenheit = 0;
                    std::cin >> fahrenheit;
                    double celsius = ConvertToFahrenheit(fahrenheit);
                    std::cout << celsius << '\n';
                    break;
                }

                default:
                    std::cerr << "[ERROR] Unknown input. Try again.\n";
                    continue;
            }
        }
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
    
}