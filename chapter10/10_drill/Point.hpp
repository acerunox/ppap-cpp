#pragma once
#include <iostream>

class Point
{
public:
    Point(int x = 0, int y = 0);
    int GetX() const { return x; }
    int GetY() const { return y; }

private:
    int x;
    int y;
};

std::istream &operator>> (std::istream &is, Point &point);
std::ostream &operator<< (std::ostream &os, const Point &point);