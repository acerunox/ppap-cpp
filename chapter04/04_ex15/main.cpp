#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "How many primes to find?: ";
    int n = 1;
    std::cin >> n;

    const int smallestPrime = 2;
    std::vector<int> primes;
    int currentNumber = 2;

    while (primes.size() < n)
    {
        std::vector<bool> primeFlags;
        for (int p = smallestPrime; p*p <= currentNumber; ++p)
        {
            if (currentNumber % p != 0) primeFlags.push_back(true);
            else primeFlags.push_back(false);
        }
        
        if (std::all_of(primeFlags.begin(), primeFlags.end(), [](bool isPrime) { return isPrime == true; })) 
        { 
            primes.push_back(currentNumber); 
        }
        ++currentNumber;
    }

    for (int prime : primes)
    {
        std::cout << prime << '\n';
    }
}