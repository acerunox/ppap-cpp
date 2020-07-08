#pragma once
#include <string>
#include <vector>

class Database
{
    public:
        void AddNames();
        void AddAges();
        void SortNamesAndAges();
        std::vector<std::string> GetNames() const { return names; }
        std::vector<double> GetAges() const { return ages; }

    private:
        std::vector<std::string> names;
        std::vector<double> ages;

        bool IsValidName(const std::string &name);
};

std::ostream &operator<<(std::ostream &os, const Database &database);
bool operator==(const Database &first, const Database &second);
bool operator!=(const Database &first, const Database &second);