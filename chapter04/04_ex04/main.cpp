#include <iostream>
#include <stdexcept>

class Game
{
    public:
        Game();
        void Play();
    private:
        int tries;
        int minValue;
        int maxValue;
};

Game::Game() 
{
    std::cout << "How many tries does the computer get?: ";
    std::cin >> tries;
    while (tries <= 0) 
    {
        std::cerr << "[ERROR] The amount of tries has to be greater than 0. Try again: ";
        std::cin >> tries;
    }
    
    std::cout << "What's the minimal value in game?: ";
    std::cin >> minValue;

    std::cout << "What's the maximal value in game?: ";
    std::cin >> maxValue;
    while (maxValue < minValue) 
    {
        std::cerr << "[ERROR] Max value cannot be lower than the min value. Try again: ";
        std::cin >> maxValue;
    }
}

void Game::Play() 
{
    int currentMaxValue = maxValue;
    int currentMinValue = minValue;
    char playerAnswer = 'x';

    while (currentMaxValue > currentMinValue && tries > 0)
    {
        int midValue = (currentMinValue + currentMaxValue) / 2;
        std::cout << "Is your number greater than " << midValue << " (y/n)?: ";
        std::cin >> playerAnswer;
        while (playerAnswer != 'y' && playerAnswer != 'n')
        {
            std::cerr << "Wrong answer, please only use either 'y' or 'n'! Try again: ";
            std::cin >> playerAnswer;
        }

        if (playerAnswer == 'y') currentMinValue = midValue + 1;
        else if (playerAnswer == 'n') currentMaxValue = midValue;
        --tries;
    }
    
    std::cout << "I think I know! It's probably " << currentMaxValue << "!\n";
}

int main()
{
    Game game;
    game.Play();
}