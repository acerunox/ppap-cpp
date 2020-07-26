#include "./Reading.hpp"
#include <iostream>

Reading::Reading(int day, int hour, double temperature) : day(day), hour(hour), temperature(temperature) {}

std::ostream &operator<<(std::ostream &os, const Reading &reading)
{
    return os << reading.GetHour() << ' ' << reading.GetTemperature();
}

std::istream &operator>>(std::istream &is, Reading &reading)
{
    char firstChar;
    is >> firstChar;
    if (!is || firstChar != '(')
    {
        is.unget();
        is.clear(std::ios_base::failbit);
        return is;
    }

    int day = 0;
    int hour = 0;
    double temperature = 0.0;
    char lastChar;

    is >> day >> hour >> temperature >> lastChar;
    if (!is || lastChar != ')')
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    reading = Reading{day, hour, temperature};
    return is;
}