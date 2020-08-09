/*
Exercise 09: Split the binary I/O program from §11.3.2 into two: one program that converts an ordinary text file into binary and one program that reads binary and converts it to text.
             Test these programs by comparing a text file with what you get by converting it to binary and back.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <string>

void BinaryToTextFile(const std::string &binaryFile, const std::string &outputFile)
{
    std::ifstream inputStream{binaryFile, std::ios_base::binary};
    if (!inputStream) ThrowError("Failed to open input file '" + binaryFile + "'.");
    
    std::ofstream outputStream{outputFile, std::ios_base::binary};
    if (!outputStream) ThrowError("Failed to open output file '" + outputFile + "'.");

    char character;
    while (inputStream.read(AsBytes(character), sizeof(char)))
    {
        outputStream << character;
    }
}

int main()
{
    try
    {
        std::cout << "Enter binary file path: ";
        std::string binaryFile;
        std::cin >> binaryFile;

        std::cout << "Enter output file path: ";
        std::string outputFile;
        std::cin >> outputFile;

        BinaryToTextFile(binaryFile, outputFile);
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
    }
}