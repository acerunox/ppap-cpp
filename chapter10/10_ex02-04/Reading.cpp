#include "./Reading.hpp"
#include <iostream>

namespace ReadingLib
{
    std::ostream &operator<<(std::ostream &os, const Unit &unit)
    {
        return os << char(unit);
    }

    std::istream &operator>>(std::istream &is, Unit &unit)
    {
        char input;
        is >> input;
        
        if (!is)
        {
            is.clear(std::ios_base::failbit);
            return is;
        }

        unit = Unit(input);
        return is;
    }

    Reading::Reading(int hour, double temperature, Unit unit) : hour(hour), temperature(temperature), unit(unit) {}

    void Reading::Convert(const Unit &newUnit)
    {
        if (unit == newUnit) return;

        switch (newUnit)
        {
        case Unit::CELSIUS:
            if (unit == Unit::FAHRENHEIT) temperature = (temperature - 32) * 5 / 9.0;
            break;

        case Unit::FAHRENHEIT:
            if (unit == Unit::CELSIUS) temperature = (temperature * 9 / 5.0) + 32;
            break;
        }
        
        unit = newUnit;
    }

    std::ostream &operator<<(std::ostream &os, const Reading &reading)
    {
        return os << reading.GetHour() << ' ' << reading.GetTemperature() << reading.GetUnit();
    }

    std::istream &operator>>(std::istream &is, Reading &reading)
    {
        int hour = 0;
        double temperature = 0.0;
        Unit unit;

        is >> hour >> temperature >> unit;
        if (!is)
        {
            is.clear(std::ios_base::failbit);
            return is;
        }

        reading = Reading{hour, temperature, unit};
        return is;
    }
}