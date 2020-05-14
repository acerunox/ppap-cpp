/*
Exercise 11: Write a program that writes out the first so many values of the Fibonacci series. 
             The next number of the series is the sum of the two previous ones. 
             Find the largest Fibonacci number that fits in an int.
*/

#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <vector>

enum class Choice { GENERATE_FIB = 1, LARGEST_FIB };
std::istream &operator>> (std::istream &is, Choice &choice)
{
    int input = 0;
    is >> input;
    if(!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    choice = Choice(input);
    return is;
}

bool IsOverflowing(int a, int b)
{
    return ((b > 0) && (a > INT_MAX - b)) ||
           ((b < 0) && (a < INT_MIN - b));
}

int FindLargestFibonacci()
{
    std::vector<int> fibonacci { 1, 1 };    //has to be initialized to 2 values
    while (!IsOverflowing(fibonacci[fibonacci.size() - 1], fibonacci[fibonacci.size() - 2]))
    {
        fibonacci.push_back(fibonacci[fibonacci.size() - 1] + fibonacci[fibonacci.size() - 2]);
    }
    return fibonacci.back();
}

std::vector<int> GenerateFibonacciSequence(int n)
{
    if (n <= 0) throw std::runtime_error("[ERROR] 'n' has to be greater than 0.");
    std::vector<int> fibonacci { 1, 1 };    //has to be initialized to 2 values
    for (int i = 2; i < n; ++i)
    {
        if (IsOverflowing(fibonacci[i - 1], fibonacci[i - 2]))
        {
            std::cerr << "[ERROR] Overflow occured. Maximum number reached.\n";
            break;
        }
        else
        {
            fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);
        }
    }
    return fibonacci;
}

int main()
{
    std::cout << "What do you want to do?\n"
              << "\t1. Generate Fibonacci sequence to N numbers.\n"
              << "\t2. Find the largest Fibonacci number.\n"
              << "> ";
    try
    {
        Choice userChoice;
        std::cin >> userChoice;
        switch (userChoice)
        {
            case Choice::GENERATE_FIB:
            {
                std::cout << "How many Fibonacci numbers do you want to find?: ";
                int n = 0;
                std::cin >> n;
                std::vector<int> fibonacci = GenerateFibonacciSequence(n);

                for (int i = 0; i < fibonacci.size(); ++i)
                {
                    if (i == fibonacci.size() - 1) std::cout << fibonacci[i];
                    else std::cout << fibonacci[i] << ", ";
                }
                std::cout << '\n';
                break;
            }

            case Choice::LARGEST_FIB:
            {
                std::cout << "Largest Fibonacci number fitting in an int is: " << FindLargestFibonacci() << '\n';
                break;
            }

            default:
                std::cerr << "[ERROR] Unrecognized option!\n";
                return EXIT_FAILURE;
        }
    }
    catch(const std::runtime_error& err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
    
}