/*
Exercise 01: Write a program that produces the sum of all the numbers in a file of whitespace-separated integers.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> GetIntegersFromFile(const std::string &fileName)
{
    std::ifstream ist{ fileName };
    if (!ist)
    {
        ist.clear();
        ThrowError("[ERROR] Failed to open input file '" + fileName, "'.");
    }

    std::vector<int> integers;
    int number = 0;
    while (ist >> number) integers.push_back(number);

    return integers;
}

int CalcSum(const std::vector<int> &vector)
{
    int sum = 0;
    for (int i : vector) sum += i;
    return sum;
}

int main()
{
    try
    {
        std::cout << "Enter path to file: ";
        std::string fileName;
        std::cin >> fileName;
        std::vector<int> integers = GetIntegersFromFile(fileName);

        std::cout << "Sum of integers in file '" << fileName << "': " << CalcSum(integers) << '\n';
    }
    catch (std::invalid_argument &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}