/*
Exercise 13: Reverse the order of words (defined as whitespace-separated strings) in a file. 
             For example, Norwegian Blue parrot becomes parrot Blue Norwegian. 
             You are allowed to assume that all the strings from the file will fit into memory at once.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>

enum class Choice { YES = 'y', NO = 'n' };

std::istream &operator>>(std::istream &is, Choice &choice)
{
    char input;
    is >> input;
    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    input = std::tolower(input);
    choice = Choice(input);
    return is;
}

void ReverseOrderInFile(const std::string &filePath)
{
    std::ifstream inputStream{filePath};
    if (!inputStream) ThrowError("Failed to open input file '" + filePath + "'.");

    std::ostringstream result;
    std::ostringstream tempBuffer{std::ios_base::ate};

    std::string word;
    while(inputStream >> word)
    {
        while (isspace(inputStream.peek())) word += inputStream.get();
        if (inputStream.peek() == EOF && !isspace(word.back())) word += ' ';
        tempBuffer.str(word);
        tempBuffer << result.str();
        result.str(tempBuffer.str());
    }
    inputStream.close();

    std::ofstream outputStream{filePath};
    if (!outputStream) ThrowError("Failed to open output file '" + filePath + "'.");
    
    outputStream << result.str();
}

int main()
{
    try
    {
        std::cout << "Enter the file path: ";
        std::string filePath;
        std::cin >> filePath;

        std::cout << "This might make the file unreadable.\n"
                  << "Are you sure you want to reverse the order of words in '" << filePath << "'? (y/n): ";
        Choice choice;
        while(std::cin >> choice)
        {
            switch(choice)
            {
            case Choice::YES:
                ReverseOrderInFile(filePath);
                return EXIT_SUCCESS;

            case Choice::NO:
                return EXIT_SUCCESS;
            
            default:
                std::cout << "Unrecognized choice, please try again (y/n): ";
                continue;
            }
        }
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
        return EXIT_FAILURE;
    }
}