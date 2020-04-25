#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cout << "Please enter the spelled out digit (in lowercase): ";
    std::string digitAsWord;
    std::cin >> digitAsWord;

    std::vector<std::string> allowedWords { "zero", "one", "two", "three", "four" };

    int digit = -1;
    int startingNumber = 0;
    for (int i = startingNumber; i < allowedWords.size(); ++i)
    {
        if (digitAsWord == allowedWords[i])
        {
            digit = i;
            break;
        }
    }

    if (digit != -1) std::cout << digitAsWord << " is " << digit << ".\n";
    else std::cout << "I don't know that number!\n";
}