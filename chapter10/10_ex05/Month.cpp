#include "./Month.hpp"
#include "./Reading.hpp"
#include "../../lib/utilities.h"
#include <istream>
#include <string>
#include <vector>

Month::Month() : month(-1), days(32) {} //-1 means fake month (data in that month doesn't exist yet), at most 31 days in month (day[0] isn't used ever)

int MonthNameToInt(const std::string &monthName)
{
    const std::vector<std::string> monthInputTable{ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
    
    for (int i = 0; i < monthInputTable.size(); ++i)
    {
        if (monthInputTable[i] == monthName) return i;
    }

    ThrowError("Month '" + monthName + "' doesn't exist.");
}

std::string IntToMonthName(const int &number)
{
    const std::vector<std::string> monthPrintTable{ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

    if (number < 0 || number >= 12) ThrowError("Month index out of [0:11] range.");
    return monthPrintTable[number];
}

std::istream &operator>>(std::istream &is, Month &monthObj)
{
    char firstChar;
    is >> firstChar;
    if (!is || firstChar != '{')
    {
        is.unget();
        is.clear(std::ios_base::failbit);
        return is;
    }

    std::string monthMarker;
    std::string monthName;
    is >> monthMarker >> monthName;
    if (!is || monthMarker != "month") ThrowError("Bad month marker.");
    monthObj.month = MonthNameToInt(monthName);

    Reading reading;
    while (is >> reading)
    {
        monthObj.days[reading.GetDay()].hours[reading.GetHour()] = reading.GetTemperature();
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