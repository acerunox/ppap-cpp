#define _USE_MATH_DEFINES
#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include "../../lib/utilities.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace Graph_lib;

int sgn(double number)
{
    if (number > 0) return 1;
    else if (number == 0) return 0;
    else return -1;
}

std::unique_ptr<Graph_lib::Closed_polyline> Superellipse(const Point &center, int a, int b, double m, double n, int numberOfPoints)
{
    if (m <= 0 || n <= 0) ThrowError("'m' and 'n' parameters have to be greater than 0.");
    auto polylinePtr = std::make_unique<Graph_lib::Closed_polyline>();

    for (double theta = 0; theta < 2 * M_PI; theta += 2 * M_PI / numberOfPoints)
    {
        int x = std::pow(std::abs(std::cos(theta)), 2/m) * a * sgn(std::cos(theta));
        int y = std::pow(std::abs(std::sin(theta)), 2/n) * b * sgn(std::sin(theta));
        polylinePtr->add(Point{x + center.x, y + center.y});
    }

    return std::move(polylinePtr);
}

int main()
{
    try
    {
        Point topLeft{100, 75};
        Simple_window window{topLeft, 400, 400, "Superellipse"};
        Point center{window.x_max() / 2, window.y_max() / 2};
        
        auto polylinePtr1 = Superellipse(center, 150, 150, 0.7, 0.7, 100);
        polylinePtr1->set_color(Color::red);
        window.attach(*polylinePtr1);
        
        auto polylinePtr2 = Superellipse(center, 150, 150, 0.6, 0.6, 100);
        polylinePtr2->set_color(Color::yellow);
        window.attach(*polylinePtr2);
        
        auto polylinePtr3 = Superellipse(center, 150, 150, 0.5, 0.5, 100);
        polylinePtr3->set_color(Color::green);
        window.attach(*polylinePtr3);

        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}