/*
Exercise 05: Write two functions that reverse the order of elements in a vector<int>.
             The first reverse function should produce a new vector with the reversed sequence, leaving its original vector unchanged.
             The other reverse function should reverse the elements of its vector without using any other vectors.
*/

#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <vector>

void Print(const std::vector<int> &numbers, const std::string &label)
{
    std::cout << label << ": ";
    for (int i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i];
        if (i != numbers.size() - 1) std::cout << ", ";
    }
    std::cout << '\n';
}

std::vector<int> ReverseToNew(const std::vector<int> &vector)
{
    if (vector.empty()) ThrowError("[ERROR] Cannot reverse an empty vector.");
    std::vector<int> result;
    
    for (int i = vector.size() - 1; i >= 0; --i) result.push_back(vector[i]);
    return result;
}

void ReverseOriginal(std::vector<int> &vector)
{
    if (vector.empty()) ThrowError("[ERROR] Cannot reverse an empty vector.");
    
    for (int i = 0; i < vector.size() / 2; ++i)
    {
        std::swap(vector[i], vector[vector.size() - 1 - i]);
    }
}

int main()
{
    std::vector<int> numbers { 1, 3, 5, 7, 9 };
    Print(numbers, "Original");

    std::vector<int> reverse = ReverseToNew(numbers);
    Print(reverse, "Reverse to new vector");

    ReverseOriginal(numbers);
    Print(numbers, "Reversed original");
}