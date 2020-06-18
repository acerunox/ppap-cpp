#pragma once
#include <ostream>

namespace Chrono
{
    class Date
    {
        public:
            Date(int year, int month, int day);
            void AddDay(int amount);
            int GetYear() { return year; }
            int GetMonth() { return month; }
            int GetDay() { return day; }

        private:
            int year, month, day;
    };

    /*NOTE: Won't work yet as the getter methods don't return a constant
    std::ostream &operator<<(std::ostream& os, const Date& date);*/
}