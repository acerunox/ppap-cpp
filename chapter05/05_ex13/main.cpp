/*
Exercise 13: The program (exercise 12) is a bit tedious because the answer is hard-coded into the program. 
             Make a version where the user can play repeatedly (without stopping and restarting the program) and each game has a new set of four digits.
*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int RandomInRange(int min, int range) { return std::rand() % range + min; }

class Game
{
    public:
        Game();
        void GenerateSolution(int seed);
        void TakeGuess();
        inline bool HasWon();
        bool AskToPlayAgain();
    private:
        std::vector<int> solution;
        int bulls;
        int cows;

        void CalculateScore(const std::vector<int> &guess);
        void CheckResult();
};

Game::Game() : bulls(0),
               cows(0) {}

void Game::GenerateSolution(int seed)
{
    std::vector<int> newSolution;
    std::srand(seed);
    while (newSolution.size() < 4)
    {
        int digit = RandomInRange(0, 10);
        if (std::find(newSolution.begin(), newSolution.end(), digit) != newSolution.end()) continue;
        else newSolution.push_back(digit);
    }
    solution = newSolution;
}

void Game::TakeGuess()
{
    std::vector<int> guess {};
    std::string input;
    std::cin.ignore();
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

bool Game::AskToPlayAgain()
{
    std::cout << "Are you ready to play again? (y/n): ";

    char choice = 'x';
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        bulls = 0;
        cows = 0;
        return true;
    }
    else return false;
}

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

    do
    {
        std::cout << "Enter a seed for random solution: ";
        int seed = 0;
        std::cin >> seed;
        game.GenerateSolution(seed);

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
    } while (game.AskToPlayAgain());
}