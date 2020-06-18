#pragma once
#include <ostream>

namespace Chrono
{
    struct Date
    {
        int year, month, day;
    };

    void InitDay(Date& date, int year, int month, int day);
    void AddDay(Date& date, int amount);

    std::ostream &operator<<(std::ostream& os, const Date& date);
}