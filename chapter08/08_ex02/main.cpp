/*
Exercise 02: Write a function print() that prints a vector of ints to cout.
             Give it two arguments: a string for “labeling” the output and a vector.
*/

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

int main()
{
    std::vector<int> numbers { 10, 7, 18, 13, 33, 20, 11 };

    Print(numbers, "Entries");
}