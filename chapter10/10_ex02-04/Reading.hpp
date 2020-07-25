#pragma once
#include <iostream>

namespace ReadingLib
{
    enum class Unit : char { CELSIUS = 'c', FAHRENHEIT = 'f' };
    std::ostream &operator<<(std::ostream &os, const Unit &unit);
    std::istream &operator>>(std::istream &is, Unit &unit);

    struct Reading
    {
    public:
        Reading() {}
        Reading(int hour, double temperature, Unit unit);
        int GetHour() const { return hour; }
        double GetTemperature() const { return temperature; }
        Unit GetUnit() const { return unit; }

        void Convert(const Unit &newUnit);
    private:
        int hour;
        double temperature;
        Unit unit;
    };

    std::ostream &operator<<(std::ostream &os, const Reading &reading);
    std::istream &operator>>(std::istream &is, Reading &reading);
}