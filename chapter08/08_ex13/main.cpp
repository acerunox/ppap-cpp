/*
Exercise 13: Write a function that takes a vector<string> argument and returns a vector<int> containing the number of characters in each string.
             Also find the longest and the shortest string and the lexicographically first and last string.
*/

#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace VectorStringProperties
{
    std::vector<int> CountCharacters(const std::vector<std::string> &vector)
    {
        if (vector.empty()) ThrowError("Cannot count characters of strings in an empty vector.");
        std::vector<int> characterCounts;
        for (const std::string &string : vector)
        {
            characterCounts.push_back(string.length());
        }
        return characterCounts;
    }

    std::string GetLongest(const std::vector<std::string> &vector)
    {
        if (vector.empty()) ThrowError("Cannot get longest string from an empty vector.");
        std::string longest = vector[0];
        for (const std::string &string : vector)
        {
            if (string.length() > longest.length()) longest = string;
        }
        return longest;
    }

    std::string GetShortest(const std::vector<std::string> &vector)
    {
        if (vector.empty()) ThrowError("Cannot get shortest string from an empty vector.");
        std::string shortest = vector[0];
        for (const std::string &string : vector)
        {
            if (string.length() < shortest.length()) shortest = string;
        }
        return shortest;
    }

    std::string GetAlphabeticallyFirst(std::vector<std::string> vector)
    {
        if (vector.empty()) ThrowError("Cannot get alphabetically first string from an empty vector.");
        sort(vector.begin(), vector.end());
        return vector.front();
    }

    std::string GetAlphabeticallyLast(std::vector<std::string> vector)
    {
        if (vector.empty()) ThrowError("Cannot get alphabetically last string from an empty vector.");
        sort(vector.begin(), vector.end());
        return vector.back();
    }
}

using namespace VectorStringProperties;

int main()
{
    try
    {
        std::vector<std::string> example { "misery", "convention", "wave", "flourish", "patch", 
                                           "follow", "deliver", "runner", "cutting", "top" };

        std::vector<int> characterCounts = CountCharacters(example);
        for (int i = 0; i < example.size(); ++i)
        {
            std::cout << example[i] << ": " << characterCounts[i] << '\n';
        }

        std::cout << "Shortest string: " << GetShortest(example) << '\n';
        std::cout << "Longest string: " << GetLongest(example) << '\n';
        std::cout << "Alphabetically first string: " << GetAlphabeticallyFirst(example) << '\n';
        std::cout << "Alphabetically last string: " << GetAlphabeticallyLast(example) << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }
}