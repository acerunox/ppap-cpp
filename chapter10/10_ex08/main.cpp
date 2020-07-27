/*
Exercise 08: Write a program that accepts two file names and produces a new file that is the contents of the first file followed by the contents of the second;
             That is, the program concatenates the two files.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>

void CopyFileContent(const std::string &fileName, std::ostream &outputStream)
{
    std::ifstream inputStream {fileName};
    if (!inputStream) ThrowError("Failed to open input file '" + fileName + "'.");

    char buffer;
    while (inputStream.get(buffer)) outputStream << buffer;
    if (!inputStream && !inputStream.eof()) ThrowError("Failure while reading '" + fileName + "' content.");
}

int main()
{
    std::cout << "Enter first input file name: ";
    std::string firstInputFile;
    std::cin >> firstInputFile;
    
    std::cout << "Enter second input file name: ";
    std::string secondInputFile;
    std::cin >> secondInputFile;

    std::cout << "Enter output file name: ";
    std::string outputFile;
    std::cin >> outputFile;

    try
    {
        std::ofstream outputStream {outputFile};
        if (!outputStream) throw std::runtime_error("Failed to open output file '" + outputFile + "'.");
        CopyFileContent(firstInputFile, outputStream);
        CopyFileContent(secondInputFile, outputStream);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
        return EXIT_FAILURE;
    }
}