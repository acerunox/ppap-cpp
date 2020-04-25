#include <iostream>
#include <string>
#include <vector>

double CalculateValueInUsd(const std::vector<int> &coins)
{
    const std::vector<int> coinTypeInCents { 1, 5, 10, 25, 50, 100 };
    
    double valueInCents = 0;
    for (int i = 0; i < coins.size(); ++i)
    {
        valueInCents += coins[i] * coinTypeInCents[i]; 
    }

    return valueInCents / 100;
}

void PrintOwnedCoins(const std::vector<int> &coins, std::vector<std::string> coinTypes)
{
    for (int i = 0; i < coins.size(); i++)
    {
        if (i == 0 && coins[i] == 1)
        {
            std::cout << "You have " << coins[0] << " penny.\n";
            continue;
        }
        else if (i != 0 && coins[i] == 1)
        {
            coinTypes[i].pop_back();
        }
        std::cout << "You have " << coins[i] << " " << coinTypes[i] << ".\n";
    }
}

int main()
{
    const std::vector<std::string> coinTypes { "pennies", "nickels", "dimes", "quarters", "half dollars", "one-dollar coins" };
    std::vector<int> ownedCoins;

    int coinAmount = 0;
    for (std::string coin : coinTypes)
    {
        std::cout << "How many " << coin << " do you have? ";
        std::cin >> coinAmount;
        ownedCoins.push_back(coinAmount);
    }

    PrintOwnedCoins(ownedCoins, coinTypes);
    std::cout << "The value of all of your coins is equal to $" << CalculateValueInUsd(ownedCoins) << '\n';
}