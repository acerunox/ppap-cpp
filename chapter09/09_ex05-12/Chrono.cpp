#include "./Chrono.hpp"
#include "../../lib/utilities.h"
#include <time.h>
#include <iostream>
#include <regex>
#include <string>

namespace Chrono
{
    Month &operator++(Month &month)
    {
        if (month == Month::DEC) ThrowError("Cannot add month past December.");
        month = Month(int(month) + 1);
        return month;
    }

    Date::Date() : day(1), month(Month::JAN), year(1970) {}

    Date::Date(int day, Month month, int year) : day(day), month(month), year(year)
    {
        if (!IsDate(day, month, year)) ThrowError("Invalid date.");
        unixTimestamp = CalcUnixTimestampInDays(day, month, year);
    }

    void Date::AddDays(int amount) 
    {
        if (amount <= 0) ThrowError("Amount of days to add has to be greater than 0.");
        if (day + amount > 31) ThrowError("Result exceeds maximum amount of days in month.");

        day += amount;
        unixTimestamp += amount;
    }

    long int CalcUnixTimestampInDays(int day, Month month, int year)
    {
        int daysInNormalYear = 365;
        int daysInLeapYear = 366;
        
        const Date unixEpoch = Date();  //set the date to January 1st, 1970
        
        int startYear = unixEpoch.GetYear();
        Month startMonth = unixEpoch.GetMonth();
        long int result = 0;

        while (year > startYear)    //add all days from each year except the last one
        {
            result += IsLeapYear(startYear) ? daysInLeapYear : daysInNormalYear;
            ++startYear;
        }

        while (int(month) > int(startMonth))    //add all months from last year except the last one
        {
            result += DaysInMonth(startMonth, year);
            ++startMonth;
        }
        result += day - unixEpoch.GetDay(); //add all days remaining from the last month, subtract January 1st to get 

        return result;
    }

    bool IsDate(int day, Month month, int year)   
    {
        if (month < Month::JAN || month > Month::DEC) return false;
        if (day < 1) return false;

        int daysInMonth = 0;

        switch (month)
        {
        case Month::FEB:
            daysInMonth = IsLeapYear(year) ? 29 : 28;
            break;

        case Month::APR: case Month::JUN: case Month::SEP: case Month::NOV:
            daysInMonth = 30;
            break;

        default:
            daysInMonth = 31;
            break;
        }

        if (daysInMonth < day) return false;

        return true;
    }

    bool IsLeapYear(int year)
    {
        return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    int DaysInMonth(Month month, int year)
    {
        int daysInMonth = 0;

        switch (month)
        {
        case Month::FEB:
            if (IsLeapYear(year)) daysInMonth = 29;
            else daysInMonth = 28;
            break;

        case Month::APR: case Month::JUN: case Month::SEP: case Month::NOV:
            daysInMonth = 30;
            break;

        default:
            daysInMonth = 31;
            break;
        }

        return daysInMonth;
    }

    int WeekOfYear(const Date &date)
    {
        Date startDate = Date { 1, Month::JAN, date.GetYear() };
        Date nextSunday = NextSunday(date);

        int weekOfYear = 0;
        while (nextSunday > startDate)
        {
            ++weekOfYear;
            startDate = NextSunday(startDate);  //set startDate to next sunday
        }

        return weekOfYear;
    }

    Weekday DayOfWeek(const Date &date)
    {
        int day = date.GetDay();
        int month = int(date.GetMonth());   //convert Month to int
        int year = date.GetYear();

        //treat January as 13 and February as 14 month of previous year as required by the algorithm
        if (month == int(Month::JAN) || month == int(Month::FEB))
        {
            --year;
            month += 12;
        }

        int zeller = (day + ((13 * (month + 1)) / 5) + year + (year / 4) - (year / 100) + (year / 400)) % 7; //Zeller's congruence, 0 = saturday ... 6 = friday
        int custom_zeller = zeller - 1; //subtract 1, so 0 = sunday ... 5 = friday
        if (custom_zeller == -1) custom_zeller = 6; //after subtracting -1 = saturday, so we have to set it to 6
        return Weekday(custom_zeller);
    }

    Date NextSunday(const Date &date)
    {
        Weekday weekday = DayOfWeek(date);
        Date nextSunday = date;
        nextSunday.AddDays(7 - (int(weekday) % 7));
        return nextSunday;
    }

    Date NextWorkday(const Date &date)
    {
        Date nextWorkday = date;
        
        switch (DayOfWeek(date))
        {
        case Weekday::SUNDAY:
        case Weekday::MONDAY:
        case Weekday::TUESDAY:
        case Weekday::WEDNESDAY:
        case Weekday::THURSDAY:
            nextWorkday.AddDays(1);
            break;
        case Weekday::FRIDAY:
            nextWorkday.AddDays(3);
            break;
        case Weekday::SATURDAY:
            nextWorkday.AddDays(2);
            break;
        }

        return nextWorkday;
    }

    Date CurrentDate()
    {
        std::time_t now = std::time(0);
        std::tm *tstruct = std::localtime(&now);

        //tm_mon returns [0,11], so we have to +1, tm_year returns years since 1900, so we have to +1900
        return Date(tstruct->tm_mday, Month(tstruct->tm_mon + 1), tstruct->tm_year + 1900);
    }

    std::ostream &operator<<(std::ostream& os, const Date& date)
    {
        return os << date.GetDay() << '-' << int(date.GetMonth()) << '-' << date.GetYear();
    }

    std::istream &operator>>(std::istream& is, Date& date)
    {
        std::string input;
        getline(std::cin, input);

        std::regex dateRegex("^([[:d:]]{1,2})[[:blank:]]?[,\-][[:blank:]]?([[:d:]]{1,2})[[:blank:]]?[,\-][[:blank:]]?([[:d:]]{4})$");
        std::smatch match;
        if (std::regex_match(input, match, dateRegex))
        {
            int day = std::stoi(match[1]);
            Month month = Month(std::stoi(match[2]));
            int year = std::stoi(match[3]);

            date = Date(day, month, year);
        }
        else
        {
            is.clear(std::ios_base::failbit);
            return is;
        }
    }

    bool operator>(const Date &first, const Date &second)
    {
        return (first.GetYear() >= second.GetYear() &&
                first.GetMonth() >= second.GetMonth() &&
                first.GetDay() > second.GetDay());
    }
}
