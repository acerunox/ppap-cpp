/*
Exercise 01:  Write a program that reads a text file and converts its input to all lower case, producing a new file.
*/

#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::cout << "Enter input file path: ";
    std::string inputFilePath;
    std::cin >> inputFilePath;

    std::ifstream ifs{inputFilePath};
    if (!ifs) 
    {
        std::cerr << "[ERROR] Failed to open input file '" + inputFilePath + "'.\n"; 
        return EXIT_FAILURE;
    }

    std::cout << "Enter output file path: ";
    std::string outputFilePath;
    std::cin >> outputFilePath;

    std::ofstream ofs{outputFilePath};
    if (!ofs) 
    {
        std::cerr << "[ERROR] Failed to open output file '" + outputFilePath + "'.\n"; 
        return EXIT_FAILURE;
    }

    for (char character; ifs.get(character);)
    {
        character = tolower(character);
        ofs << character;
    }
}