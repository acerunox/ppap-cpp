#include "./Reading.hpp"
#include "../../lib/utilities.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace ReadingLib;

void GenerateTestReadings(const std::string &filePath, int amount, const Unit &unit)
{
    std::ofstream ost {filePath};
    if (!ost) ThrowError("Failed to open output file '" + filePath + "'.");
    ost << std::fixed << std::setprecision(1);

    int hour = 0;
    const int hoursInDay = 24;
    int i = 0;
    while (i < amount)
    {
        if (i % hoursInDay == 0) hour = 0;  //after every 24 hours start a new day
        double temperature = std::round(RandomInRange(-20.0, 40.0) * 10) / 10;  // random temperature in range of [-20, 40] rounded to first digit
        Reading reading{hour, temperature, unit};
        if (i == amount - 1) ost << reading;
        else ost << reading << '\n';
        
        ++i;
        ++hour;
    }
}

int main()
{
    try
    {
        std::string filePath = "./raw_temps.txt";
        GenerateTestReadings(filePath, 50, Unit::CELSIUS);
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}