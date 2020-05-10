#include <iostream>
#include <vector>

int main()
{
    std::cout << "Input max value: ";
    int max = 1;
    std::cin >> max;

    std::vector<bool> primeFlags(max, true);

    int smallestPrime = 2;
    for (int p = smallestPrime; p*p <= max; ++p)
    {
        if (primeFlags[p])
        {
            for (int i = p*p; i <= max; i += p) primeFlags[i] = false;
        }
    }

    for (int i = smallestPrime; i <= primeFlags.size(); ++i)
    {
        if (primeFlags[i]) std::cout << i << '\n';
    }
}