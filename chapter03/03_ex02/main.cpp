#include <iostream>

int main()
{
    const double ratio = 1.609;

    std::cout << "Miles to kilometers converter.\n"
              << "Enter the amount of miles: ";
    double miles = 0;
    std::cin >> miles;

    std::cout << miles << " miles are equal to " << miles * ratio << " kilometers.\n";
}