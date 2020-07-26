/*
Exercise 05: Write the function print_year() mentioned in §10.11.2.
*/

#include "./Year.hpp"
#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<Year> ReadYearsFromFile(const std::string &filePath)
{
    std::ifstream ifs {filePath};
    if (!ifs) ThrowError("Failed to open input file '" + filePath + "'.");
    
    std::vector<Year> years;
    while (true)
    {
        Year year;
        if (!(ifs >> year)) break;
        years.push_back(year);
    }

    std::cout << "Successfully read " << years.size() << " years of readings.\n";
    return years;
}

void WriteFormattedYearsToFile(const std::string &filePath, const std::vector<Year> &years)
{
    std::ofstream ofs {filePath};
    if (!ofs) ThrowError("Failed to open output file '" + filePath + "'.");

    for (const Year &year : years) PrintYearReadings(ofs, year);
}

int main()
{
    try
    {
        std::cout << "Please enter input file name: ";
        std::string inputFilePath = "chapter10/10_ex05/input.txt";
        std::cin >> inputFilePath;
        std::vector<Year> years = ReadYearsFromFile(inputFilePath);

        std::cout << "Please enter output file name: ";
        std::string outputFilePath = "chapter10/10_ex05/output.txt";
        std::cin >> outputFilePath;
        WriteFormattedYearsToFile(outputFilePath, years);
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}