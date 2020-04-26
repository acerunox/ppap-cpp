#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <string>
#include <vector>

bool IsUnitValid(const std::string &unit)
{
    const std::vector<std::string> allowedUnits { "cm", "m", "in", "ft" };
    for (int i = 0; i < allowedUnits.size(); ++i)
    {
        if (unit == allowedUnits[i]) return true;
    }
    return false;
}

struct Ratio 
{
    static constexpr double cmToM = 0.01;
    static constexpr double inToM = 0.0254;
    static constexpr double ftToM = 0.3048;
};

double ConvertToMeters(double value, std::string initialUnit)
{

    if (initialUnit == "cm") return value * Ratio::cmToM;
    else if (initialUnit == "m") return value;
    else if (initialUnit == "in") return value * Ratio::inToM;
    else if (initialUnit == "ft") return value * Ratio::ftToM;
    else throw std::runtime_error("[ERROR] Unknown initial unit during conversion.");
}

int main()
{
    double value = 0;
    std::string unit = "";
    double smallestValue = INT_MAX;
    double largestValue = INT_MIN;
    double convertedValue = 0;
    double sum = 0;
    int amountOfValues = 0;
    std::vector<double> valuesList;

    std::cout << "Enter your value and unit (cm, m, in, ft): ";
    while (std::cin >> value)
    {
        std::getline(std::cin, unit);
        if (IsUnitValid(unit))
        {
            try 
            {
                convertedValue = ConvertToMeters(value, unit);
            }
            catch (std::runtime_error &err)
            {
                std::cerr << err.what() << '\n';
                continue;
            }
        }
        else
        {
            std::cout << "Invalid unit!\nPlease try again: ";
            continue;
        }

        valuesList.push_back(convertedValue);
        sum += convertedValue;
        ++amountOfValues;

        if (convertedValue > largestValue) 
        {
            largestValue = convertedValue;
            std::cout << "The largest so far.\n";
        }
        else if (convertedValue < smallestValue) 
        {
            smallestValue = convertedValue;
            std::cout << "The smallest so far.\n";
        }

        std::cout << "Enter your value and unit (cm, m, in, ft): ";
    }

    std::cout << "\nThe smallest value was: " << smallestValue << "m.\n"
              << "The largest value was: " << largestValue << "m.\n"
              << "Number of values given: " << amountOfValues << ".\n"
              << "The sum of all values: " << sum << "m.\n"
              << "List of all values: ";

    std::sort(valuesList.begin(), valuesList.end());
    for (int i = 0; i < valuesList.size(); ++i)
    {
        if (i != 0) std::cout << ", ";
        std::cout << valuesList[i];
    }
    std::cout << '\n';
}