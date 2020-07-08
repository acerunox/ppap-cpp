#include "./Database.hpp"
#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool Database::IsValidName(const std::string &name)
{
    for (char character : name)
    {
        if (!isalpha(character)) return false;
    }

    return true;
}

void Database::AddNames()
{
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    std::string name;
    while (std::getline(iss, name, ' '))
    {
        if (IsValidName(name)) names.push_back(name);
        else 
        {
            std::cerr << "[ERROR] '" << name << "' is not a valid name.\n";
            continue;
        }
    }
}

void Database::AddAges()
{
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    double age;
    while (iss >> age) ages.push_back(age);
}

void Database::SortNamesAndAges()
{
    if (names.size() != ages.size()) ThrowError("[ERROR] Amount of names and ages must be the same.");
    std::vector<std::string> namesCopy = names;
    std::sort(names.begin(), names.end());

    for (int i = 0; i < names.size(); ++i)
    {
        auto itr = std::find(namesCopy.begin(), namesCopy.end(), names[i]);
        int index = std::distance(namesCopy.begin(), itr);
        namesCopy[index] = "";
        std::swap(namesCopy[index], namesCopy[i]);
        std::swap(ages[index], ages[i]);
    }
}

std::ostream &operator<<(std::ostream &os, const Database &database)
{
    auto names = database.GetNames();
    auto ages = database.GetAges();

    if (names.size() != ages.size()) ThrowError("[ERROR] Amount of names and ages must be the same.");
    for (int i = 0; i < names.size(); ++i)
    {
        os << names[i] << ", " << ages[i] << '\n';
    }
    return os;
}

bool operator==(const Database &first, const Database &second)
{
    return (first.GetNames() == second.GetNames() &&
            first.GetAges() == second.GetAges());
}

bool operator!=(const Database &first, const Database &second)
{
    return !(first == second);
}