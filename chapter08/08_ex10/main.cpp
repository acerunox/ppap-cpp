/*
Exercise 10: Write a function maxv() that returns the largest element of a vector argument.
*/

#include "../../lib/utilities.h"
#include <iostream>
#include <limits.h>
#include <vector>

int MaxV(const std::vector<int> &vector)
{
    if (vector.size() == 0) ThrowError("[ERROR] Vector cannot be empty.");
    
    int max = INT_MIN;
    for (const int &value : vector)
    {
        if (value > max) max = value;
    }
    return max;
}

int main()
{
    std::vector<int> numbers{ 2342, 432, 12, 5433, 99142, 32, 1, 349533 };
    std::cout << MaxV(numbers) << '\n';
}