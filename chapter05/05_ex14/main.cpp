/*
Exercise 14: Read (day-of-the-week,value) pairs from standard input. For example: Tuesday 23 Friday 56 Tuesday –3 Thursday 99
             Collect all the values for each day of the week in a vector<int>. Write out the values of the seven day-of-the-weekvectors. Print out the sum of the values in each vector. 
             Ignore illegal days of the week, such as Funday, but accept common synonyms such as Mon and monday. 
             Write out the number of rejected values.
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

bool IsOverflowing(int a, int b) { return (((b > 0) && (a > INT_MAX - b)) || ((b < 0) && (a < INT_MIN - b))); }

struct Day
{
    public:
        Day(std::vector<std::string> names);
        bool IsNameAllowed(const std::string &name);
        void AddValue(int value);
        void PrintValues();
    private:
        std::vector<std::string> allowedNames;
        std::vector<int> values;

        int CalcSum();
};

Day::Day(std::vector<std::string> names) : allowedNames(names) {}

bool Day::IsNameAllowed(const std::string &name)
{
    auto it = std::find(allowedNames.begin(), allowedNames.end(), name);
    return it != allowedNames.end();
}

void Day::AddValue(int value) { values.push_back(value); }

void Day::PrintValues()
{
    int sum = 0;
    std::cout << allowedNames[0] << '\n';   //Use the first allowed name as header
    
    std::cout << std::setw(11) << "Values: ";
    if (values.size() == 0) std::cout << "0\n";
    else
    {
        for (int i = 0; i < values.size(); ++i)
        {
            if (i == values.size() - 1) std::cout << values[i];
            else std::cout << values[i] << ", ";
        }
        std::cout << '\n';
    }
    
    std::cout << std::setw(8) << "Sum: " << CalcSum() << '\n';
}

int Day::CalcSum()
{
    int sum = 0;
    for (int value : values)
    {
        if (IsOverflowing(sum, value)) throw std::runtime_error("[ERROR] Overflow occurred, sum too large to fit in an int.");
        else sum += value;
    }
    return sum;
}

struct DayData
{
    std::string name;
    int value;
};

std::istream &operator>> (std::istream &is, DayData &day)
{
    is >> day.name >> day.value;
    if (!is) is.clear(std::ios_base::failbit);
    return is;
}

std::vector<Day> InitializeWeek()
{
    std::vector<Day> week { Day({ "Monday", "monday", "MONDAY", "mon", "Mon" }),
                            Day({ "Tuesday", "tuesday", "TUESDAY", "tue", "Tue" }),
                            Day({ "Wednesday", "wednesday", "WEDNESDAY", "wed", "Wed" }),
                            Day({ "Thursday", "thursday", "THURSDAY", "thu", "Thu" }),
                            Day({ "Friday", "friday", "FRIDAY", "fri", "Fri" }),
                            Day({ "Saturday", "saturday", "SATURDAY", "sat", "Sat" }),
                            Day({ "Sunday", "sunday", "SUNDAY", "sun", "Sun" }) };
    return week;
}

int main()
{
    std::cout << "Enter your days and values ('q 0' to terminate): ";
    std::vector<Day> week = InitializeWeek();
    int rejectedValues = 0;
    DayData inputDayData;

    while (true)
    {
        std::cin >> inputDayData;
        if (inputDayData.name == "q" && inputDayData.value == 0) break;
        else if (!std::cin) 
        {
            ++rejectedValues;
            continue;
        }
        else 
        {
            for (int i = 0; i < week.size(); ++i)
            {
                if (week[i].IsNameAllowed(inputDayData.name)) 
                {
                    week[i].AddValue(inputDayData.value);
                    break;
                }
                else if (i == week.size() - 1) ++rejectedValues;
            }
        }
    }

    for (Day day : week) 
    {
        try
        {
            day.PrintValues();
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << '\n';
        }
        std::cout << '\n';
    }

    std::cout << "Rejected values: " << rejectedValues << '\n';
}