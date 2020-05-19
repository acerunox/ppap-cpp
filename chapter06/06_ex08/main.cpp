/*
Exercise 08: Redo the “Bulls and Cows” game from exercise 12 in Chapter 5 to use four letters rather than four digits.
*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Game
{
    public:
        Game(std::vector<char> solution);
        void TakeGuess();
        inline bool HasWon();
    private:
        std::vector<char> solution;
        int bulls;
        int cows;

        void CalculateScore(const std::vector<char> &guess);
        void CheckResult();
};

Game::Game(std::vector<char> solution) : bulls(0),
                                         cows(0),
                                         solution(solution) {}

void Game::TakeGuess()
{
    std::vector<char> guess {};
    std::string input;
    std::getline(std::cin, input);

    char letter = 0;
    for (int i = 0; i < input.length(); ++i)
    {
        if (isspace(input[i])) continue;
        else if (!isalpha(input[i])) throw std::runtime_error("[ERROR] Invalid input, only use letters.");
        else letter = input[i];
        
        if (std::find(guess.begin(), guess.end(), letter) != guess.end()) throw std::runtime_error("[ERROR] You have to give 4 different letters.");
        else guess.push_back(std::tolower(letter));
    }
    if (guess.size() > 4) throw std::runtime_error("[ERROR] Your guess has to be exactly 4 letters.");
    
    CalculateScore(guess);
    CheckResult();
}

inline bool Game::HasWon() { return bulls == 4; }

void Game::CalculateScore(const std::vector<char> &guess)
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
    Game game({ 'a', 'g', 'x', 'd' });
    while (!game.HasWon()) 
    {
        try
        {
            std::cout << "Enter four letters: ";
            game.TakeGuess();
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << '\n';
            continue;
        }
    }
}