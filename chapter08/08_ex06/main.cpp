/*
Exercise 06: Write versions of the functions from exercise 5, but with a vector<string>.
*/

#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

void Print(const std::vector<std::string> &vector, const std::string &label)
{
    std::cout << label << ": ";
    for (int i = 0; i < vector.size(); ++i)
    {
        std::cout << vector[i];
        if (i != vector.size() - 1) std::cout << ", ";
    }
    std::cout << '\n';
}

std::vector<std::string> ReverseToNew(const std::vector<std::string> &vector)
{
    if (vector.empty()) ThrowError("[ERROR] Cannot reverse an empty vector.");
    std::vector<std::string> result;
    
    for (int i = vector.size() - 1; i >= 0; --i) result.push_back(vector[i]);
    return result;
}

void ReverseOriginal(std::vector<std::string> &vector)
{
    if (vector.empty()) ThrowError("[ERROR] Cannot reverse an empty vector.");
    
    for (int i = 0; i < vector.size() / 2; ++i)
    {
        std::swap(vector[i], vector[vector.size() - 1 - i]);
    }
}

int main()
{
    std::vector<std::string> words { "one", "three", "five", "seven", "nine" };
    Print(words, "Original");

    std::vector<std::string> reverse = ReverseToNew(words);
    Print(reverse, "Reverse to new vector");

    ReverseOriginal(words);
    Print(words, "Reversed original");
}