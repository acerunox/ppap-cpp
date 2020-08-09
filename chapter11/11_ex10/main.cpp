/*
Exercise 10: Write a function vector<string> split(const string& s) that returns a vector of whitespace-separated substrings from the argument s.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string &line)
{
    std::string substring;
    std::istringstream stringStream{line};
    std::vector<std::string> result;

    while (std::getline(stringStream, substring, ' '))
    {
        result.push_back(substring);
    }

    return result;
}

int main()
{
    std::cout << "Enter a string: ";
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> splitInput = Split(input);
}