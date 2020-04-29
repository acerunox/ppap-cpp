#include <iostream>

int main()
{
    double value1 = 0;
    double value2 = 0;
    char oper = 'x';

    std::cout << "Enter your equation: ";
    while (std::cin >> value1 >> oper >> value2)
    {
        switch(oper)
        {
            case '+':
                std::cout << "The sum of " << value1 << " and " << value2 
                          << " is " << value1 + value2 << '\n';
                break;
                
            case '-':
                std::cout << "The difference between " << value1 << " and " << value2 
                          << " is " << value1 - value2 << '\n';
                break;

            case '*':
                std::cout << "The product of " << value1 << " and " << value2 
                          << " is " << value1 * value2 << '\n';
                break;

            case '/':
                if (value2 == 0) 
                {
                    std::cerr << "[ERROR] Cannot divide by 0.";
                    continue;
                }
                else 
                {
                    std::cout << "The quotient of " << value1 << " and " << value2 
                              << " is " << value1 + value2 << '\n';
                    break;
                }
            
            default:
                std::cerr << "[ERROR] Unrecognized operator.";
                break;
        }
        std::cout << "Enter your equation: ";
    }   
}