#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter operation and two operands (separated by space): ";
    std::string operation;
    double operand1 = 0;
    double operand2 = 0;
    std::cin >> operation >> operand1 >> operand2;

    std::cout << operand1 << ' ' << operation << ' ' << operand2 << " = ";
    if (operation == "+" || operation == "plus") std::cout << operand1 + operand2 << '\n';
    else if (operation == "-" || operation == "minus") std::cout << operand1 - operand2 << '\n';
    else if (operation == "*" || operation == "mul") std::cout << operand1 * operand2 << '\n';
    else if (operation == "/" || operation == "div") std::cout << operand1 / operand2 << '\n';
    else std::cerr << "Something went wrong!\n";
}