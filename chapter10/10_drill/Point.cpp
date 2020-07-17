#include "./Point.hpp"
#include <iostream>

Point::Point(int x, int y) : x(x), y(y) {}

std::istream &operator>> (std::istream &is, Point &point)
{
    int x = 0;
    int y = 0;
    char separator;
    const char comma = ',';

    is >> x >> separator >> y;
    if (!is || separator != comma)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    point = Point(x, y);
    return is;
}

std::ostream &operator<< (std::ostream &os, const Point &point)
{
    return os << point.GetX() << ',' << point.GetY();
}