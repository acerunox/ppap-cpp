/*
Exercise 08: Write a program that reads and stores a series of integers and then computes the sum of the first N integers. 
             First ask for N, then read the values into a vector, then calculate the sum of the first N values.

Exercise 09: Modify the program from exercise 8 to write out an error if the result cannot be represented as an int.

Exercise 10: Modify the program from exercise 8 to use double instead of int. 
             Also, make a vector of doubles containing the N–1 differences between adjacent values and write out that vector of differences.
*/

#include <iostream>
#include <stdexcept>
#include <vector>

double CalcSum(const std::vector<double> &vector, int n)
{
    if (n > vector.size()) throw std::runtime_error("[ERROR] Asked for too many numbers.");
    double sum = 0;
    for (int i = 0; i < n; ++i) sum += vector[i];
    return sum;
}

std::vector<double> CalcDifferences(const std::vector<double> &vector, int n)
{
    if (n > vector.size()) throw std::runtime_error("[ERROR] Asked for too many numbers.");
    std::vector<double> differences;
    double result = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i == 0) result = vector[i] - vector[i+1];
        else if (i == n-1) result = vector[i-1] - vector[i];
        else result = vector[i-1] - vector[i] - vector[i+1];
        differences.push_back(result);
    }
    return differences;
}

void PrintResults(const std::vector<double> &vector, int n)
{
    double sum = CalcSum(vector, n);
    std::cout << "The sum of the first " << n << " numbers (";
    for (int i = 0; i < n; ++i) 
    {
        if (i == n-1) std::cout << vector[i];
        else std::cout << vector[i] << ", ";
    }
    std::cout << ") is " << sum << '\n';

    std::vector<double> differences = CalcDifferences(vector, n);
    for (int i = 0; i < n; ++i) 
    {
        if (i == 0) std::cout << "The difference between " << vector[i] << " and " << vector[i + 1] 
                              << " is equal to " << differences[i] << '\n';
        else if (i == n-1) std::cout << "The difference between " << vector[i - 1] << " and " << vector[i] 
                                     << " is equal to " << differences[i] << '\n';
        else std::cout << "The difference between " << vector[i - 1] << ", " << vector[i] << " and " << vector[i + 1] 
                       << " is equal to " << differences[i] << '\n';;
    }
}

int main()
{
    std::cout << "How many numbers do you want to sum?: ";
    int n = 0;
    std::cin >> n;
    while (n <= 1) 
    {
        std::cerr << "[ERROR] You need at least 2 numbers for sum. Try again: ";
        std::cin >> n;
    }

    std::cout << "Please enter some integers (any non-number to stop): ";
    std::vector<double> numbers;
    double number = 0;
    while (std::cin >> number) numbers.push_back(number);

    try 
    {
        PrintResults(numbers, n);
    }
    catch (std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}