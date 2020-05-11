#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::pair<std::string, int> FindMode(const std::vector<std::string> &vector)
{
    std::string modeString;
    int modeAmount = 0;
    for (std::string string : vector)
    {
        int currentAmount = std::count(vector.begin(), vector.end(), string);
        if (currentAmount > modeAmount) 
        {
            modeString = string;
            modeAmount = currentAmount;
        }
    }

    return std::make_pair(modeString, modeAmount);
}

int main()
{
    std::vector<std::string> userStrings;

    std::cout << "Enter a series of strings (terminate with /): ";
    std::string input;
    while (std::cin >> input && input != "/") userStrings.push_back(input);

    if (!userStrings.empty())
    {
        auto mode = FindMode(userStrings);
        std::cout << "The mode of this series is '" << mode.first 
                << "' and it appears " << mode.second << " times.\n";

        auto extremes = std::minmax_element(userStrings.begin(), userStrings.end());
        std::cout << "The min of this series is '" << *extremes.first
                << "' and the max is '" << *extremes.second << "'.\n";
    }
    else
    {
        std::cerr << "[ERROR] Cannot find the min, max and mode of empty vector.\n";
        return EXIT_FAILURE;
    }
}