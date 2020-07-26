#pragma once
#include "./Month.hpp"
#include <iostream>
#include <vector>

struct Year
{
    Year();
    int year;
    std::vector<Month> months;  // [0:11], where 0 = January
};

void PrintYearReadings(std::ostream &os, const Year &year);
std::istream &operator>>(std::istream &is, Year &year);