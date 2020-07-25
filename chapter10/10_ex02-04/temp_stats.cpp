#include "./Reading.hpp"
#include "../../lib/utilities.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace ReadingLib;

double CalcReadingsMedian(const std::vector<Reading> &vector)
{
    double median = 0.0;

    std::vector<double> temps;
    for (const Reading &reading : vector) temps.push_back(reading.GetTemperature());
    std::sort(temps.begin(), temps.end());
    
    if (temps.size() % 2 == 0)
    {
        median = (temps[temps.size()/2 - 1] + temps[temps.size()/2]) / 2;
    }
    else median = temps[temps.size()/2];

    return median;
}

double CalcReadingsMean(const std::vector<Reading> &vector)
{
    double sum = 0.0;
    for (const Reading &reading : vector) sum += reading.GetTemperature();

    return sum / vector.size();
}

std::vector<Reading> ReadReadingsFromFile(const std::string &filePath)
{
    std::ifstream ist {filePath};
    if (!ist) ThrowError("Failed to open input file '" + filePath + "'.");
    
    std::vector<Reading> result;
    Reading reading;
    while (ist >> reading) 
    {
        reading.Convert(Unit::FAHRENHEIT);
        result.push_back(reading);
    }
    //if (ist.fail() && !ist.eof()) ThrowError("Failed to read one of the readings.");

    return result;
}

int main()
{
    try
    {
        std::string filePath = "./raw_temps.txt";
        std::vector<Reading> readings = ReadReadingsFromFile(filePath);
        double median = CalcReadingsMedian(readings);
        double mean = CalcReadingsMean(readings);

        std::cout << "Median: " << median << '\n'
                  << "Mean: " << mean << '\n';
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}