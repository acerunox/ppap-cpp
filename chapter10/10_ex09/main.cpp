/*
Exercise 09: Write a program that takes two files containing sorted whitespace-separated words and merges them, preserving order.
*/

#include "../../lib/utilities.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void ReadFileToVector(const std::string &fileName, std::vector<std::string> &vector, char delimiter)
{
    std::ifstream inputStream {fileName};
    if (!inputStream) ThrowError("Failed to open input file '" + fileName + "'.");
    
    std::string buffer;
    while (std::getline(inputStream, buffer, delimiter)) vector.push_back(buffer);
}

void WriteVectorToFile(const std::string &fileName, const std::vector<std::string> &vector)
{
    std::ofstream outputStream {fileName};
    if (!outputStream) ThrowError("Failed to open output file '" + fileName + "'.");

    for (int i = 0; i < vector.size(); ++i) 
    { 
        if (i != vector.size() - 1) outputStream << vector[i] << ' ';
        else outputStream << vector[i];
    }
}

int main()
{
    try
    {
        std::vector<std::string> wordList;

        std::cout << "Enter first input file name: ";
        std::string fileName;
        std::cin >> fileName;
        ReadFileToVector(fileName, wordList, ' ');

        std::cout << "Enter second input file name: ";
        std::cin >> fileName;
        ReadFileToVector(fileName, wordList, ' ');

        std::cout << "Enter output file name: ";
        std::cin >> fileName;

        std::sort(wordList.begin(), wordList.end());
        WriteVectorToFile(fileName, wordList);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
        return EXIT_FAILURE;
    }
}