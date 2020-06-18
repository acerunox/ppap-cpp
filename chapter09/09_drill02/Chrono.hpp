#pragma once
#include <ostream>

namespace Chrono
{
    struct Date
    {
        Date(int year, int month, int day);
        int year, month, day;

        void AddDay(int amount);
    };

    std::ostream &operator<<(std::ostream& os, const Date& date);
}