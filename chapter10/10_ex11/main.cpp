/*
Exercise 11: Write a program that produces the sum of all the whitespace-separated integers in a text file. For example, bears: 17 elephants 9 end should output 26.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> ReadIntegersFromFile(const std::string &filePath)
{
    std::ifstream inputStream {filePath};
    if (!inputStream) ThrowError("Failed to open input file '" + filePath + "'.");

    std::vector<int> integers;
    std::string word;
    int number = 0;

    while (inputStream >> word)
    {
        std::istringstream iss(word);
        if (iss >> number) integers.push_back(number);
        else continue;
    }

    return integers;
}

int CalcSum(const std::vector<int> &integers)
{
    int sum = 0;
    for (const int &number : integers) sum += number;
    return sum;
}

int main()
{
    try
    {
        std::cout << "Enter input file path: ";
        std::string filePath;
        std::cin >> filePath;

        std::vector<int> integers = ReadIntegersFromFile(filePath);
        std::cout << CalcSum(integers);
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}