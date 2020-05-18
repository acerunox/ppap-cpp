/*
Exercise 04: Define a class Name_value that holds a string and a value. 
             Rework exercise 19 in Chapter 4 to use a vector<Name_value> instead of two vectors.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Person
{
    std::string name;
    int score;
};

std::istream &operator>> (std::istream &is, Person &person)
{
    is >> person.name >> person.score;
    
    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    return is;
}

class Database
{
    public:
        void AddEntry(const Person &person);
        void PrintEntries();
    private:
        std::vector<Person> entries;

        bool IsDuplicate(const Person &person);
};

void Database::AddEntry(const Person &person)
{
    if (IsDuplicate(person))
    {
        std::cerr << "[ERROR] " << person.name << " already exists in database.\n";
        return;
    }
    else entries.push_back(person);    
}

void Database::PrintEntries()
{
    std::cout << "List of all names and scores:\n";
    for (Person person : entries) std::cout << " - " << person.name << ", " << person.score << '\n';
}

bool Database::IsDuplicate(const Person &person)
{
    auto iter = std::find_if(entries.begin(), entries.end(), [&person] (const Person &entry) { return entry.name == person.name; } );
    return iter != entries.end();
}

int main()
{
    Database database;
    Person person;
    
    while (std::cout << "> " && std::cin >> person)
    {
        if (person.name == "NoName" && person.score == 0) break;
        database.AddEntry(person);
    }

    database.PrintEntries();
}