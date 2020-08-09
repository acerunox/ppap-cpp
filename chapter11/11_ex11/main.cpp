/*
Exercise 11: Write a function vector<string> split(const string& s, const string& w) that returns a vector of whitespace-separated substrings from the argument s.
             Whitespace is defined as “ordinary whitespace” plus the characters in w.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string &line, const std::string &whitespace)
{
    std::string lineCopy = line;
    for (char &character : lineCopy)
    {
        if (whitespace.find(character) != std::string::npos) character = ' ';
    }

    std::istringstream stringStream{lineCopy};
    std::string substring;
    std::vector<std::string> result;

    while (stringStream >> substring)
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

    std::vector<std::string> splitInput = Split(input, ",.");
}