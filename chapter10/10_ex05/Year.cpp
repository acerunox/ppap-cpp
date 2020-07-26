#include "./Year.hpp"
#include "./Month.hpp"
#include "../../lib/utilities.h"
#include <iostream>

Year::Year() : months(12) {}

void PrintYearReadings(std::ostream &os, const Year &yearObj)
{
    const int fakeReading = -7777;
    const int fakeMonth = -1;

    os << "Readings for year " << yearObj.year << ":\n";
    for (auto monthObj : yearObj.months)
    {
        if (monthObj.month == fakeMonth) continue;
        os << '\t' << IntToMonthName(monthObj.month) << ":\n";
        for (int i = 1; i < monthObj.days.size(); ++i)
        {
            os << "\t  " << "Day " << i << ":\n";
            for (int j = 0; j < monthObj.days[i].hours.size(); ++j)
            {
                double temperature = monthObj.days[i].hours[j];
                os << "\t    " << "Hour " << j << ":00: ";
                if (temperature == fakeReading) os << "NO DATA\n";
                else os << temperature << '\n';
            }
        }
        os << '\n';
    }
}

std::istream &operator>>(std::istream &is, Year &yearObj)
{
    char firstChar;
    is >> firstChar;
    if (!is || firstChar != '{')
    {
        is.unget();
        is.clear(std::ios_base::failbit);
        return is;
    }

    std::string yearMarker;
    int year;
    is >> yearMarker >> year;
    if (!is || yearMarker != "year") ThrowError("Bad year marker.");
    
    yearObj.year = year;
    while (true)
    {
        Month monthObj;
        if (!(is >> monthObj)) break;
        yearObj.months[monthObj.month] = monthObj;
    }

    is.clear();
    char lastChar;
    is >> lastChar;
    if (!is || lastChar != '}')
    {
        is.unget();
        is.clear(std::ios_base::failbit);
        return is;
    }

    return is;
}
