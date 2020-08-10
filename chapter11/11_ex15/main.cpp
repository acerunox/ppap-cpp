/*
Exercise 15: Write a program that reads a file of whitespace-separated numbers and outputs a file of numbers using scientific format and precision 8 in four fields of 20 characters per line.
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Enter input file path: ";
    std::string filePath;
    std::cin >> filePath;

    std::ifstream inputStream{filePath};
    if (!inputStream)
    {
        std::cerr << "Failed to open input file '" + filePath + "'.";
        return EXIT_FAILURE;
    }

    std::cout << "Enter output file path: ";
    std::cin >> filePath;

    std::ofstream outputStream{filePath};
    if (!outputStream)
    {
        std::cerr << "Failed to open output file '" + filePath + "'.";
        return EXIT_FAILURE;
    }

    double num;
    std::vector<double> numbers;
    while (inputStream >> num) numbers.push_back(num);

    outputStream << std::scientific << std::setprecision(8);
    for (int i = 0; i < numbers.size(); ++i)
    {
        outputStream << std::setw(20) << numbers[i];
        if ((i + 1) % 4 == 0) outputStream << '\n';
    }
}