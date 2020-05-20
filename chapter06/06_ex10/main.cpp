/*
Exercise 10: Design a program that asks users for two numbers, asks them whether they want to calculate permutations or combinations, and prints out the result.
             This program should have error checking.
             Make sure that all erroneous inputs will generate good error messages.
*/
#include <iostream>
#include <limits.h>
#include <stdexcept>

enum class Choice { PERMUTATION = 'p', COMBINATION = 'c', QUIT = 'q' };

std::istream &operator>> (std::istream &is, Choice &choice)
{
    char input;
    is >> input;

    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    choice = Choice(input);
    return is;
}

bool IsOverflowing(int a, int b)
{
    return ((a > INT_MAX / b) || (a < INT_MIN / b));
}

int Factorial(int value)
{
    int result = 1;
    if (value == 0) return 1;
    else if (value < 0) throw std::runtime_error("[ERROR] Cannot calculate factorial from negative number.");

    for (int i = value; i > 0; --i)
    {
        if (IsOverflowing(result, i)) throw std::runtime_error("[ERROR] Overflow occurred while calculating factorial.");
        result *= i;
    }

    return result;
}

int CalculatePermutations(int a, int b)
{
    return Factorial(a) / Factorial(a - b);
} 

int CalculateCombinations(int a, int b)
{
    return CalculatePermutations(a, b) / Factorial(b);
}

int main()
{
    try
    {
        std::cout << "Available choices:\n";
        std::printf("%5c - permutation\n%5c - combination\n%5c - quit\n", 
                    char(Choice::PERMUTATION), char(Choice::COMBINATION), char(Choice::QUIT));
        Choice choice;

        int a = 0;
        int b = 0;
        while (std::cout << "> " && std::cin >> choice)
        {
            switch (choice)
            {
                case Choice::PERMUTATION:
                    std::cout << ">> ";
                    std::cin >> a >> b;
                    if (!std::cin) 
                    {
                        std::cerr << "[ERROR] Invalid input.\n";
                        continue;
                    }
                    
                    std::printf("P(%i, %i) = %i\n", a, b, CalculatePermutations(a, b));
                    break;

                case Choice::COMBINATION:
                    std::cout << "> ";
                    std::cin >> a >> b;
                    if (!std::cin) 
                    {
                        std::cerr << "[ERROR] Invalid input.\n";
                        continue;
                    }

                    std::printf("C(%i, %i) = %i\n", a, b, CalculateCombinations(a, b));
                    break;

                case Choice::QUIT:
                    return EXIT_SUCCESS;

                default:
                    std::cerr << "Unrecognized choice, try again.\n";
                    break;
            }
        }
    }
    catch(const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
}