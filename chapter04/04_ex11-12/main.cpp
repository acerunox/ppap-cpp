#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> primes { 2 };

    std::cout << "Input max value: ";
    int max = 0;
    std::cin >> max;

    for (int i = 2; i <= max; ++i)
    {
        bool isPrime = false;
        
        for (int prime : primes)
        {
            if (i % prime == 0) 
            {
                isPrime = false;
                break;
            }
            else isPrime = true;
        }

        if (isPrime) primes.push_back(i);
    }

    for (int prime : primes)
    {
        std::cout << prime << '\n';
    }
}