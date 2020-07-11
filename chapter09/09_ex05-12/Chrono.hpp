#pragma once
#include <iostream>

namespace Chrono
{
    enum class Weekday { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
    enum class Month { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
    Month &operator++(Month &month);

    class Date
    {
        public:
            Date();
            Date(int day, Month month, int year);

            void AddDays(int amount);
            int GetDay() const { return day; }
            Month GetMonth() const { return month; }
            int GetYear() const { return year; }

        private:
            int day;
            Month month;
            int year;
            long int unixTimestamp;
    };

    long int CalcUnixTimestampInDays(int day, Month month, int year);
    bool IsDate(int day, Month month, int year);
    bool IsLeapYear(int year);
    int DaysInMonth(Month month, int year);
    int WeekOfYear(const Date &date);
    Weekday DayOfWeek(const Date &date);
    Date NextSunday(const Date &date);
    Date NextWorkday(const Date &date);
    Date CurrentDate();

    std::ostream &operator<<(std::ostream& os, const Date& date);
    std::istream &operator>>(std::istream& is, Date& date);
    bool operator>(const Date &first, const Date &second);
}