/*
Exercise 11: Write a function that finds the smallest and the largest element of a vector argument and also computes the mean and the median.
             Do not use global variables.
             Either return a struct containing the results or pass them back through reference arguments.
*/

#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <vector>

struct VectorProperties
{
    public:
        VectorProperties(const std::vector<int> &vector);
        int min;
        int max;
        double mean;
        double median;

    private:
        void ComputeProperties(std::vector<int> vector);
};

VectorProperties::VectorProperties(const std::vector<int> &vector)
{
    ComputeProperties(vector);
}

void VectorProperties::ComputeProperties(std::vector<int> vector)
{
    std::sort(vector.begin(), vector.end());
    min = vector.front();
    max = vector.back();

    double sum = 0.0;
    for (const int &number : vector) sum += number;
    mean = sum / vector.size();

    if (vector.size() % 2 == 0)
    {
        median = (vector[vector.size() / 2 - 1] + vector[vector.size() / 2]) / 2.0;
    }
    else median = vector[vector.size() / 2];
}

int main()
{
    std::vector<int> numbers{ 53, 9843, 231, 4352, 33, 94, 21234, 2 };
    VectorProperties numbersProperties { numbers };

    for (int i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i];
        if (i != numbers.size() - 1) std::cout << ", ";
    }

    std::cout << "\n\nProperties:\n"
        << "Min: " << numbersProperties.min << '\n'
        << "Max: " << numbersProperties.max << '\n'
        << "Mean: " << numbersProperties.mean << '\n'
        << "Median: " << numbersProperties.median << '\n';
}