/*
Drill: Define a Date called today initialized to June 25, 1978. 
       Then, define a Date called tomorrow and give it a value by copying today into it and increasing its day by one using add_day(). 
       Finally, output today and tomorrow using a << defined as in §9.8.
       Your check for a valid date may be very simple. 
       Feel free to ignore leap years. 
       However, don’t accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range. 
       Test each version with at least one invalid date (e.g., 2004, 13, –5).

       Use the version from §9.4.3
*/
#include "./Chrono.hpp"
#include <iostream>

using namespace Chrono;

int main()
{
    try
    {
        Date today {1978, 6, 25};
        Date tomorrow = today;
        tomorrow.AddDay(1);
        /*NOTE: Won't work yet as the getter methods don't return a constant
        std::cout << "Today: " << today << '\n';
        std::cout << "Tomorrow: " << tomorrow << '\n';*/
        Date invalidDate{ 2004, 13, -5 };
    }
    catch(const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }
} 