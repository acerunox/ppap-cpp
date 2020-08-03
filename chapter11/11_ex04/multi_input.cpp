/*
Exercies 04: Write a program called multi_input.cpp that prompts the user to enter several integers in any combination of octal, decimal, or hexadecimal, using the 0 and 0x base suffixes;
             interprets the numbers correctly; and converts them to decimal form.
             Then your program should output the values in properly spaced columns.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int main()
{
    std::cout << "Enter a series of numbers in hex, octal or decimal (CTRL+C to stop): ";
    
    std::string input;
    std::string baseName;

    std::ostringstream outputStream;

    while (std::cin >> input)
    {
        std::istringstream inputStream{input};
        inputStream.unsetf(std::ios::dec);
        inputStream.unsetf(std::ios::hex);
        inputStream.unsetf(std::ios::oct);

        if (!inputStream)
        {
            outputStream << "[ERROR] Failed to read a value from input.\n";
            continue;
        }

        std::string basePrefix;
        if (input.length() >= 2) basePrefix = input.substr(0, 2);

        if (input.length() != 1 && basePrefix[0] == '0')
        {
            if (basePrefix[1] == 'x') baseName = "hexadecimal";
            else baseName = "octal";
        }
        else baseName = "decimal";

        int value = 0;
        inputStream >> value;

        outputStream << std::setw(16) << input << ' ' << std::setw(13) << baseName << " converts to " << std::dec << value << " decimal.\n";
    }

    std::cout << outputStream.str();
}