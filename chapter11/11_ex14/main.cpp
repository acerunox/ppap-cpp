/*
Exercise 14: Write a program that reads a text file and writes out how many characters of each character classification (§11.6) are in the file.
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

enum class Classification { SPACE, ALPHA, DIGIT, XDIGIT, UPPER, LOWER, ALNUM, CNTRL, PUNCT, PRINT, GRAPH };

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

    std::vector<int> counts(11);

    char currentCharacter;
    while (inputStream.get(currentCharacter))
    {
        if (isspace(currentCharacter)) ++counts[int(Classification::SPACE)];
        if (isalpha(currentCharacter)) ++counts[int(Classification::ALPHA)];
        if (isdigit(currentCharacter)) ++counts[int(Classification::DIGIT)];
        if (isxdigit(currentCharacter)) ++counts[int(Classification::XDIGIT)];
        if (isupper(currentCharacter)) ++counts[int(Classification::UPPER)];
        if (islower(currentCharacter)) ++counts[int(Classification::LOWER)];
        if (isalnum(currentCharacter)) ++counts[int(Classification::ALNUM)];
        if (iscntrl(currentCharacter)) ++counts[int(Classification::CNTRL)];
        if (ispunct(currentCharacter)) ++counts[int(Classification::PUNCT)];
        if (isprint(currentCharacter)) ++counts[int(Classification::PRINT)];
        if (isgraph(currentCharacter)) ++counts[int(Classification::GRAPH)];
    }

    std::cout << "Characters classification count:\n"
              << std::setw(14) << "Whitespace: " << counts[int(Classification::SPACE)] << '\n'
              << std::setw(14) << "Alpha: " << counts[int(Classification::ALPHA)] << '\n'
              << std::setw(14) << "Digit: " << counts[int(Classification::DIGIT)] << '\n'
              << std::setw(14) << "Hex digit: " << counts[int(Classification::XDIGIT)] << '\n'
              << std::setw(14) << "Uppercase: " << counts[int(Classification::UPPER)] << '\n'
              << std::setw(14) << "Lowercase: " << counts[int(Classification::LOWER)] << '\n'
              << std::setw(14) << "Alphanumeric: " << counts[int(Classification::ALNUM)] << '\n'
              << std::setw(14) << "Control: " << counts[int(Classification::CNTRL)] << '\n'
              << std::setw(14) << "Punctuation: " << counts[int(Classification::PUNCT)] << '\n'
              << std::setw(14) << "Printable: " << counts[int(Classification::PRINT)] << '\n'
              << std::setw(14) << "Graphic: " << counts[int(Classification::GRAPH)] << '\n';
}