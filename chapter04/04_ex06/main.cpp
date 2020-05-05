#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> numbersAsWords { "zero", "one", "two", "three", "four",
                                              "five", "six", "seven", "eight", "nine" };
    
    std::string userInput;
    int number = 0;
    
    while (std::cout << "> " && std::cin >> userInput)
    {
        std::istringstream iss(userInput);
        if (iss >> number)
        {
            if (number < numbersAsWords.size()) 
            {
                std::cout << userInput << " as word is " << numbersAsWords[number] << ".\n";
            } else std::cerr << "[ERROR] Unrecognized number, try again.\n";
        }
        else 
        {
            auto it = std::find(numbersAsWords.begin(), numbersAsWords.end(), userInput);
            if (it != numbersAsWords.end())
            {
                std::cout << userInput << " as number is " << std::distance(numbersAsWords.begin(), it) << ".\n";
            } else std::cerr << "[ERROR] Unrecognized word, try again.\n";
        }
    }
}