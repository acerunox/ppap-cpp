#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

void Calculate(int value1, int value2, char oper)
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
                    throw std::runtime_error("[ERROR] Cannot divide by 0.");
                }
                else 
                {
                    std::cout << "The quotient of " << value1 << " and " << value2 
                              << " is " << value1 + value2 << '\n';
                    break;
                }
            
            default:
                throw std::runtime_error("[ERROR] Unrecognized operator.");
        }
}

int ConvertStringToNumber(const std::string &string)
{
    std::vector<std::string> numbersAsWords { "zero", "one", "two", "three", "four",
                                              "five", "six", "seven", "eight", "nine" };
    
    int number = 0;
    std::istringstream iss(string);

    if (iss >> number)
    {
        if (number < numbersAsWords.size()) return number;
        else throw std::runtime_error("[ERROR] Unrecognized number, try again.");
    }
    else 
    {
        auto it = std::find(numbersAsWords.begin(), numbersAsWords.end(), string);
        if (it != numbersAsWords.end())
        {
            return std::distance(numbersAsWords.begin(), it);
        } else throw std::runtime_error("[ERROR] Unrecognized word, try again.");
    }
}

int main()
{
    std::string userInput;
    while (std::cout << "> ")
    {        
        try
        {
            std::cin >> userInput;
            int value1 = ConvertStringToNumber(userInput);

            char oper = 'x';
            std::cin >> oper;

            std::cin >> userInput;
            int value2 = ConvertStringToNumber(userInput);

            Calculate(value1, value2, oper);
        }
        catch(std::runtime_error &err)
        {
            std::cerr << err.what() << '\n';
            std::cout << "Do you want to continue (y/n)?: ";
            char choice = 'y';
            std::cin >> choice;
            
            if (choice == 'y') continue;
            else break;
        }
    }
}