#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int value = 0;
    std::cin >> value;

    if (value % 2 == 0) std::cout << "The value " << value << " is even.\n";
    else std::cout << "The value " << value << " is odd.\n";
}