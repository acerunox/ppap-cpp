/*
Exercise 03: Create a vector of Fibonacci numbers and print them using the function from exercise 2.
             To create the vector, write a function, fibonacci(x,y,v,n), where integers x and y are ints, v is an empty vector<int>, and n is the number of elements to put into v;
*/

#include "../../lib/utilities.h"
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

void Fibonacci(const int &x, const int &y, std::vector<int> &vector, const int &amount)
{
    if (x == 0 && y == 0) ThrowError("[ERROR] At least one number has to be greater than 0.");
    if (amount <= 0) ThrowError("[ERROR] Ask for at least one number.");

    vector.push_back(x);
    if (amount == 1) return;
    vector.push_back(y);

    for (int i = 2; i < amount; ++i) vector.push_back(vector[i - 2] + vector[i - 1]);
}

int main()
{
    std::vector<int> sequence;

    Fibonacci(1, 2, sequence, 10);
    Print(sequence, "Sequence");
}