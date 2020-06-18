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
            int GetYear() const { return year; }
            Month GetMonth() const { return month; }
            int GetDay() const { return day; }

        private:
            int year;
            Month month;
            int day;
    };

    std::ostream &operator<<(std::ostream& os, const Date& date);
}