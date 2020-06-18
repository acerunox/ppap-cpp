#pragma once
#include <ostream>

namespace Chrono
{
    enum class Month { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

    class Date
    {
        public:
            Date(int year, Month month, int day);
            void AddDay(int amount);
            int GetYear() { return year; }
            Month GetMonth() { return month; }
            int GetDay() { return day; }

        private:
            int year;
            Month month;
            int day;
    };

    /*NOTE: Won't work yet as the getter methods don't return a constant
    std::ostream &operator<<(std::ostream& os, const Date& date);*/
}