/*
Exercise 09: Write a program that reads digits and composes them into integers. 
             For example, 123 is read as the characters 1, 2, and 3. 
             The program should output 123 is 1 hundred and 2 tens and 3 ones. 
             The number should be output as an int value.
             Handle numbers with one, two, three, or four digits.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool IsInputValid(const std::string &input)
{
    if (input.length() > 4) return false;
    else
    {
        auto iter = std::find_if(input.begin(), input.end(), [](char character) { return std::isdigit(character); });
        return iter != input.end();
    }
}

int StringToInt(const std::string &input)
{
    int place = 1;
    int result = 0;

    for (int i = input.length() - 1; i >= 0; --i)
    {
        result += (input[i] - '0') * place;
        place *= 10;
    }

    return result;
}

void PrintPlaceValue(const std::string &numberString)
{
    const std::vector<std::string> units { "thousands", "hundreds", "tens", "ones" };

    int startingUnit = units.size() - numberString.length();
    for (int i = 0; i < numberString.length(); ++i)
    {
        std::string unit = units[startingUnit + i];
        if (numberString[i] == '1') unit.pop_back();
        
        if (i == numberString.length() - 1) std::cout << numberString[i] << ' ' << unit;
        else std::cout << numberString[i] << ' ' << unit << " and ";
    }
    std::cout << '\n';
}

int main()
{
    std::string input;
    std::cin >> input;

    if (IsInputValid(input)) 
    {
        int number = StringToInt(input);
        std::cout << number << " is ";
        PrintPlaceValue(input);
    }
    else
    {
        std::cerr << "[ERROR] Your number has to be <= 4 digits.";
        return EXIT_FAILURE;
    }
    
}