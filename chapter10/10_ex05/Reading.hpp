#pragma once
#include <iostream>

struct Reading
{
public:
    Reading() {}
    Reading(int day, int hour, double temperature);
    int GetDay() const { return day; }
    int GetHour() const { return hour; }
    double GetTemperature() const { return temperature; }

private:
    int day;
    int hour;
    double temperature;
};

std::ostream &operator<<(std::ostream &os, const Reading &reading);
std::istream &operator>>(std::istream &is, Reading &reading);