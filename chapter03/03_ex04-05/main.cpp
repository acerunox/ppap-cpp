#include <iostream>

double InputValue()
{
    double value = 0;
    std::cin >> value;
    return value;
}

void PrintComparison(const double &val1, const double &val2)
{
    if (val1 > val2) 
    {
        std::cout << val1 << " is larger than " << val2 << ".\n"
                  << val2 << " is smaller than " << val1 << ".\n";
    }
    else if (val2 > val1)
    {
        std::cout << val2 << " is larger than " << val1 << ".\n"
                  << val1 << " is smaller than " << val2 << ".\n";
    }
    else std::cout << val1 << " and " << val2 << " are equal.\n";
}

int main()
{
    std::cout << "Enter the first value: ";
    double val1 = InputValue();

    std::cout << "Enter the second value: ";
    double val2 = InputValue();

    PrintComparison(val1, val2);
    std::cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << ".\n"
              << "The difference of " << val1 << " and " << val2 << " is " << val1 - val2 << ".\n"
              << "The product of " << val1 << " and " << val2 << " is " << val1 * val2 << ".\n"
              << "The ratio of " << val1 << " and " << val2 << " is " << val1 / val2 << ".\n";
}