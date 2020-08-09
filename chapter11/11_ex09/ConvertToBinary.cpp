/*
Exercise 09: Split the binary I/O program from §11.3.2 into two: one program that converts an ordinary text file into binary and one program that reads binary and converts it to text.
             Test these programs by comparing a text file with what you get by converting it to binary and back.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <string>

void TextFileToBinary(const std::string &sourceFile, const std::string &binaryFile)
{
    std::ifstream inputStream{sourceFile, std::ios_base::binary};
    if (!inputStream) ThrowError("Failed to open input file '" + sourceFile + "'.");
    
    std::ofstream outputStream{binaryFile, std::ios_base::binary};
    if (!outputStream) ThrowError("Failed to open output file '" + binaryFile + "'.");

    char character;
    while (inputStream.get(character))
    {
        outputStream.write(AsBytes(character), sizeof(char));
    }
}

int main()
{
    try
    {
        std::cout << "Enter source file path: ";
        std::string sourceFile;
        std::cin >> sourceFile;

        std::cout << "Enter binary file path: ";
        std::string binaryFile;
        std::cin >> binaryFile;

        TextFileToBinary(sourceFile, binaryFile);
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
    }
}