#include <iostream>
#include <cmath>

int CalculateNumberOfSquares(int targetRice)
{
    int currentSquare = 0;
    int currentRice = 0;
    int sumRice = currentRice;

    while (sumRice < targetRice)
    {
        ++currentSquare;
        currentRice = pow(2, currentSquare - 1);
        sumRice += currentRice;
    }

    return currentSquare;
}

int CalculateSumOfRice(int targetSquare)
{
    int currentRice = 0;
    int sumRice = currentRice;

    for (int i = 1; i <= targetSquare; ++i)
    {
        currentRice = pow(2, i - 1);
        sumRice += currentRice;    
    }
    
    return sumRice;
}

int main()
{
    int choice = 0;
    std::cout << "1. How many squares for X grains of rice?\n" <<
                 "2. How many grains of rice in X squares?\n" <<
                 "Enter your choice (1 or 2): ";
    
    while (std::cin >> choice)
    {
        switch(choice)
        {
            case 1:
            {
                std::cout << "\nHow much rice?: ";
                int riceAmount = 0;
                std::cin >> riceAmount;

                std::cout << "You will need " << CalculateNumberOfSquares(riceAmount) 
                          << " squares for that many grains of rice.\n";
                break;
            }
                

            case 2:
            {
                std::cout << "\nHow many squares?: ";
                int numberOfSquares = 0;
                std::cin >> numberOfSquares;

                std::cout << "You will need " << CalculateSumOfRice(numberOfSquares)
                          << " squares for that many grains of rice.\n";
                break;
            }

            default:
                std::cerr << "Unknown choice! Please choose 1 or 2: ";
                continue;
        }

        std::cout << "\nEnter your choice (1 or 2): ";
    }
}