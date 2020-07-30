/*
Exercise 02: Write a program that given a file name and a word outputs each line that contains that word together with the line number.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int, std::string>> FindLinesWithWordInFile(const std::string &filePath, const std::string &searchedWord)
{
    std::ifstream inputFileStream{filePath};
    if (!inputFileStream) ThrowError("Failed to open input file '" + filePath + "'.\n");

    std::vector<std::pair<int, std::string>> linesWithWord;
    std::string line;
    int lineNumber = 0;
    while(std::getline(inputFileStream, line))
    {
        ++lineNumber;
        std::string currentWord;
        std::istringstream iss{line};
        while (iss >> currentWord)
        {
            if (currentWord == searchedWord)
            {
                linesWithWord.push_back(std::make_pair(lineNumber, line));
                break;
            } else continue;
        }
    }

    return linesWithWord;
}

int main()
{
    try
    {
        std::cout << "Enter input file path: ";
        std::string inputFilePath;
        std::cin >> inputFilePath;

        std::cout << "Enter the word you're looking for: ";
        std::string searchedWord;
        std::cin >> searchedWord;

        std::vector<std::pair<int, std::string>> linesWithWord = FindLinesWithWordInFile(inputFilePath, searchedWord);
        for (const auto lineInfo : linesWithWord)
        {
            std::cout << lineInfo.first << ": " << lineInfo.second << '\n';
        }
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}