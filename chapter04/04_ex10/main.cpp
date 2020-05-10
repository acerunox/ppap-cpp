#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

enum class Status { LOSS = -1, TIE, WIN };
enum class Choice { ROCK = 1, PAPER, SCISSORS };

std::istream &operator>>(std::istream &is, Choice &choice)
{
    int input = 0;
    if(!(is >> input) || input <= 0 || input > 3)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    choice = Choice(input);
}

std::ostream &operator<<(std::ostream &os, const Choice &choice)
{ 
    switch(choice)
    {
        case Choice::ROCK:
            return os << "rock";

        case Choice::PAPER:
            return os << "paper";

        case Choice::SCISSORS:
            return os << "scissors";

        default:
            return os;
    }
}

class Game
{
    public:
        Game(int pointsToWin);
        void Play();
    private:
        int pointsToWin;
        int playerPoints;
        Choice playerChoice;
        
        int cpuPoints;
        Choice cpuChoice;
        int currentCpuPool;
        
        Choice GetCpuChoice();
        Status GetRoundResult(Choice playerChoice, Choice cpuChoice);
};

Game::Game(int pointsToWin) : pointsToWin(pointsToWin), 
                              playerPoints(0), 
                              cpuPoints(0) {}

Choice Game::GetCpuChoice()
{
    std::vector<std::vector<Choice>> cpuChoicePool { { Choice::ROCK, Choice::SCISSORS, Choice::PAPER },
                                                     { Choice::SCISSORS, Choice::ROCK, Choice::SCISSORS },
                                                     { Choice::PAPER, Choice::PAPER, Choice::ROCK } };

    int cpuChoiceNumber = int(cpuChoice);
    if (currentCpuPool >= 2 || currentCpuPool < 0) { currentCpuPool = 0; }
    cpuChoiceNumber >= 2 ? cpuChoiceNumber = 0 : ++cpuChoiceNumber;
    return cpuChoicePool[currentCpuPool][cpuChoiceNumber];
}

Status Game::GetRoundResult(Choice playerChoice, Choice cpuChoice)
{
    if (playerChoice == Choice::ROCK && cpuChoice == Choice::SCISSORS ||
        playerChoice == Choice::PAPER && cpuChoice == Choice::ROCK ||
        playerChoice == Choice::SCISSORS && cpuChoice == Choice::PAPER)
        {
            return Status::WIN;
        }
    else if (playerChoice == cpuChoice) return Status::TIE;
    else return Status::LOSS;
}

void Game::Play()
{
    int currentCpuPool = 0;

    while (playerPoints < pointsToWin && cpuPoints < pointsToWin)
    {
        std::cout << "\nPlease enter your choice (1 - rock, 2 - paper, 3 - scissors): ";
        std::cin >> playerChoice;
        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cerr << "Unknown choice, try again.\n";
            continue;
        }

        cpuChoice = GetCpuChoice();

        switch(GetRoundResult(playerChoice, cpuChoice))
        {
            case Status::LOSS:
                std::cout << "You lost this round!\n";
                ++cpuPoints;
                break;

            case Status::TIE:
                std::cout << "It's a tie!\n";
                --currentCpuPool;
                break;

            case Status::WIN:
                std::cout << "You won this round!\n";
                ++currentCpuPool;
                ++playerPoints;
                break;
            
            default:
                std::cerr << "[ERROR] Unknown round result!";
                continue;
        }

        std::cout << "You chose " << playerChoice << " and your opponent chose " << cpuChoice << ".\n";
    }

    std::cout << "\nThe game is over! ";
    if (playerPoints >= pointsToWin)
    {
        std::cout << "You have earned " << playerPoints 
                  << " points and won the game, congratulations!\n";
    }
    else if (cpuPoints >= pointsToWin)
    {
        std::cout << "Your opponent has earned " << cpuPoints 
                  << " points and you lost the game, better luck next time!\n";
    }
}

int main()
{
    Game game{3};
    std::cout << "This is Rock, Paper, Scissors! Press ENTER when you're ready to play.";
    std::cin.get();

    game.Play();
}