#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> names;
    std::vector<int> scores;

    std::string input;
    std::string inputName = "NoName";
    int inputScore = 0;
    
    while (std::cout << "> " && std::getline(std::cin, input) && input != "NoName 0")
    {
        std::istringstream iss(input);
        
        if (iss >> inputScore)
        {
            std::vector<int> indices;
            auto startIterator = scores.begin();
            while (startIterator != scores.end())
            {
                auto iter = std::find(startIterator, scores.end(), inputScore);
                if (iter != scores.end())
                {
                    indices.push_back(std::distance(scores.begin(), iter));
                    startIterator = iter + 1;
                } 
                else 
                {
                    std::cerr << "[ERROR] Score not found.\n";
                    break;
                }
            }
            
            if (indices.size() > 0)
            {
                std::cout << "People that have " << inputScore << " points:\n";
                for (auto index : indices) std::cout << " - " << names[index] << '\n';
            }
        } else iss.clear();
        
        if (iss >> inputName)
        {
            if (iss >> inputScore)
            {
                if (std::find(names.begin(), names.end(), inputName) != names.end()) 
                {
                    std::cerr << "[ERROR] Name already exists.\n";
                    continue;
                }

                names.push_back(inputName);
                scores.push_back(inputScore);
                std::cout << "Added '" << inputName << "' with " << inputScore << " points.\n";
            }
            else
            {
                iss.clear();
                auto iter = std::find(names.begin(), names.end(), inputName);
                if (iter != names.end())
                {
                    int index = std::distance(names.begin(), iter);
                    std::cout << inputName << " has " << scores[index] << " points.\n";
                } else std::cerr << "[ERROR] Name not found.\n";
            }
        }
    }

    if (names.size() == scores.size())
    {
        std::cout << "List of all names and scores:\n";
        for (int i = 0; i < names.size(); ++i)
        {
            std::cout << " - " << names[i] << ", " << scores[i] << '\n';
        }
    }
}