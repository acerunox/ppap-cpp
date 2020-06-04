/*
Exercise 07: Read five names into a vector<string> name, then prompt the user for the ages of the people named and store the ages in a vector<double> age.
             Then print out the five (name[i],age[i]) pairs.
             Sort the names (sort(name.begin(),name.end())) and print out the (name[i],age[i]) pairs. 
             Then, do that exercise again but allowing an arbitrary numberof names.
*/

#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Database
{
    public:
        void AddNames();
        void AddAges();
        void SortNamesAndAges();
        void PrintNamesAndAges();

    private:
        std::vector<std::string> names;
        std::vector<double> ages;

        bool IsValidName(const std::string &name);
};

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

void Database::PrintNamesAndAges()
{
    if (names.size() != ages.size()) ThrowError("[ERROR] Amount of names and ages must be the same.");
    for (int i = 0; i < names.size(); ++i)
    {
        std::cout << names[i] << ", " << ages[i] << '\n';
    }
}

int main()
{
    try 
    {
        Database database;

        database.AddNames();
        database.AddAges();

        std::cout << "\nUnsorted: " << '\n';
        database.PrintNamesAndAges();

        database.SortNamesAndAges();
        std::cout << "\nSorted: " << '\n';
        database.PrintNamesAndAges();
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}