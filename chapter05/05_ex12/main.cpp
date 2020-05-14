/*
Exercise 12: Implement a little guessing game called (for some obscure reason) “Bulls and Cows.” 
             The program has a vector of four different integers in the range 0 to 9 (e.g., 1234 but not 1122) and it is the user’s task to discover those numbers by repeated guesses. 
             Say the number to be guessed is 1234 and the user guesses 1359; the response should be “1 bull and 1 cow”, 
             because the user got one digit (1) right and in the right position (a bull) and one digit (3) right but in the wrong position (a cow). 
             The guessing continues until the user gets four bulls, that is, has the four digits correct and in the correct order.
*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Game
{
    public:
        Game();
        void TakeGuess();
        inline bool HasWon();
    private:
        std::vector<int> solution;
        int bulls;
        int cows;

        void CalculateScore(const std::vector<int> &guess);
        void CheckResult();
};

Game::Game() : bulls(0),
               cows(0),
               solution({ 3, 7, 9, 2 }) {}

void Game::TakeGuess()
{
    std::vector<int> guess {};
    std::string input;
    std::getline(std::cin, input);

    int number = 0;
    for (int i = 0; i < input.length(); ++i)
    {
        if (isspace(input[i])) continue;
        else if (!isdigit(input[i])) throw std::runtime_error("[ERROR] Invalid input, only use numbers.");
        else number = input[i] - '0';
        
        if (std::find(guess.begin(), guess.end(), number) != guess.end()) throw std::runtime_error("[ERROR] You have to give 4 different numbers.");
        else guess.push_back(number);
    }
    if (guess.size() > 4) throw std::runtime_error("[ERROR] Your guess has to be exactly 4 digits.");
    
    CalculateScore(guess);
    CheckResult();
}

inline bool Game::HasWon() { return bulls == 4; }

void Game::CalculateScore(const std::vector<int> &guess)
{
    for (int i = 0; i < guess.size(); ++i)
    {
        auto it = std::find(solution.begin(), solution.end(), guess[i]);
        if (it != solution.end())
        {
            int index = std::distance(solution.begin(), it);
            if (i == index) ++bulls;
            else ++cows;
        }
    }
}

void Game::CheckResult()
{
    if (HasWon()) std::cout << "Congratulations, you got 4 bulls and won!\n";
    else 
    {
        std::cout << "You have " << bulls << " bulls and " << cows << " cows.\n";
        
        // Reset bulls and cows for the next round
        bulls = 0;
        cows = 0;
    }
}

int main()
{
    std::cout << "Welcome to the Bulls and Cows game!\n";
    Game game;
    while (!game.HasWon()) 
    {
        try
        {
            std::cout << "Enter four digits: ";
            game.TakeGuess();
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << '\n';
            continue;
        }
    }
}