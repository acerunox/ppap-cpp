/*
Exercise 16: Write a program to read a file of whitespace-separated numbers and output them in order (lowest value first), one value per line.
             Write a value only once, and if it occurs more than once write the count of its occurrences on its line.
*/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Enter input file path: ";
    std::string filePath;
    std::cin >> filePath;

    std::ifstream inputStream{filePath};
    if (!inputStream)
    {
        std::cerr << "Failed to open input file '" + filePath + "'.";
        return EXIT_FAILURE;
    }

    int num;
    std::vector<int> numbers;
    while (inputStream >> num) numbers.push_back(num);
    std::sort(numbers.begin(), numbers.end());
    
    int i = 0;
    while (i < numbers.size())
    {
        int count = std::count(numbers.begin(), numbers.end(), numbers[i]);
        if (count == 1) std::cout << std::setw(3) << numbers[i] << '\n';
        else std::cout << std::setw(3) << numbers[i] << std::setw(6) << count << '\n';
        i += count;
    }
}