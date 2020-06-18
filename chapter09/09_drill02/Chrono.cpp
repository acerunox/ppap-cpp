#include "./Chrono.hpp"
#include "../../lib/utilities.h"

namespace Chrono
{
    Date::Date(int year, int month, int day) : year(year), month(month), day(day)
    {
        if (month < 1 || month > 12) ThrowError("Invalid month.");
        if (day < 1 || day > 31) ThrowError("Invalid day.");
    }

    void Date::AddDay(int amount) 
    {
        if (amount <= 0) ThrowError("Amount of days to add has to be greater than 0.");
        if (day + amount > 31) ThrowError("Result exceeds maximum amount of days in month.");

        day += amount;
    }

    std::ostream& operator<<(std::ostream& os, const Date& date)
    {
        return os << '(' << date.year << ", " << date.month << ", " << date.day << ')';
    }
}
