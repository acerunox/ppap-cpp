#include "./Chrono.hpp"
#include "../../lib/utilities.h"

namespace Chrono
{
    void InitDay(Date& date, int year, int month, int day) 
    {
        if (month < 1 || month > 12) ThrowError("Invalid month.");
        if (day < 1 || day > 31) ThrowError("Invalid day.");

        date.year = year;
        date.month = month;
        date.day = day;
    }

    void AddDay(Date& date, int amount) 
    {
        if (amount <= 0) ThrowError("Amount of days to add has to be greater than 0.");
        if (date.day + amount > 31) ThrowError("Result exceeds maximum amount of days in month.");

        date.day += amount;
    }

    std::ostream& operator<<(std::ostream& os, const Date& date)
    {
        return os << '(' << date.year << ", " << date.month << ", " << date.day << ')';
    }
}
