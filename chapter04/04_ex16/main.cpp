#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> userNumbers;

    std::cout << "Enter a series of numbers (terminate with a letter): ";
    int number = 0;
    while (std::cin >> number) userNumbers.push_back(number);

    int mode = 0;
    int modeAmount = 0;
    for (int number : userNumbers)
    {
        int currentAmount = std::count(userNumbers.begin(), userNumbers.end(), number);
        if (currentAmount > modeAmount) 
        {
            mode = number;
            modeAmount = currentAmount;
        }
    }

    std::cout << "The mode of this series is " << mode 
              << " and it appears " << modeAmount << " times.\n";
}