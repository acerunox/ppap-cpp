/*
Exercise 05: Write a program that reads strings and for each string outputs the character classification of each character, as defined by the character classification functions presented in §11.6.
             Note that a character can have several classifications.
*/

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void PrintCharacterClassification(const char &character)
{
    std::ostringstream output;
    
    if (isprint(character))
    {
        output << "printable, ";

        if (isspace(character)) output << "whitespace";
        else if (ispunct(character)) output << "graphic, punctuation";
        else if (isalpha(character))
        {
            output << "graphic, alphanumeric, letter, ";
            if (isxdigit(character)) output << "hexadecimal digit, ";

            if (isupper(character)) output << "uppercase";
            else output << "lowercase";
        }
        else if (isdigit(character))
        {
            if (isxdigit(character)) output << "graphic, alphanumeric, digit, hexadecimal digit";
            else output << "graphic, alphanumeric, digit";
        }
    }
    else output << "not printable";
    
    std::cout << output.str();
}

int main()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        std::cout << '\'' << input << "' character classification is:\n";
        for (const char &character : input)
        {
            std::cout << std::setw(8) << '\'' << character << '\'' << ": ";
            PrintCharacterClassification(character);
            std::cout << '\n';
        }
    }
}