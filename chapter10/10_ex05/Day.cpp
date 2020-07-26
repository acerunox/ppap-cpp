#include "./Day.hpp"

Day::Day() : hours(24) 
{
    static int fakeReading = -7777;
    for (int i = 0; i < hours.size(); ++i) hours[i] = fakeReading;
}