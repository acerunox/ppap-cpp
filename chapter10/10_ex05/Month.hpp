#pragma once
#include "./Day.hpp"
#include <istream>
#include <string>
#include <vector>

struct Month
{
    Month();
    std::vector<Day> days;  // [1:31], day[0] wasted
    int month;              // [0:11], where 0 = January
};

int MonthNameToInt(const std::string &monthName);
std::string IntToMonthName(const int &number);

std::istream &operator>>(std::istream &is, Month &monthObj);