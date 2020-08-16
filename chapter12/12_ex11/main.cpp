#define _USE_MATH_DEFINES
#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace Graph_lib;

std::unique_ptr<Graph_lib::Closed_polyline> GetRegularPolygon(const Point &center, const int &circumradius, const int &n)
{
    double angle = 360 / n;
    double radians = (angle * 2 * M_PI) / 360;
    double currentRadians = radians;
    auto polygonPtr = std::make_unique<Graph_lib::Closed_polyline>();

    for (int i = 0; i < n; ++i)
    {
        int x = center.x + circumradius * std::cos(currentRadians);
        int y = center.y + circumradius * std::sin(currentRadians);
        polygonPtr->add(Point{x, y});
        currentRadians += radians;
    }

    return std::move(polygonPtr);
}

int main()
{
    try
    {
        std::cout << "Enter the number of vertices: ";
        int vertices;
        std::cin >> vertices;

        Point topLeft{100, 75};
        Simple_window window{topLeft, 900, 900, "Polygons"};

        Point center{450, 450};
        double circumradius = 300;
        double radius = circumradius;
        
        Graph_lib::Circle circumcircle{center, circumradius};
        circumcircle.set_color(Color::red);
        window.attach(circumcircle);

        std::vector<std::unique_ptr<Graph_lib::Closed_polyline>> polygons;
        for (int i = vertices; i >= 3; --i)
        {
            polygons.push_back(GetRegularPolygon(center, radius, i));
            double lastRadius = radius;
            double inradius = radius * std::cos(M_PI / i);
            double offset = (lastRadius - inradius) / 2;
            radius = inradius + offset;
            center += Point{offset, 0};
        }

        for (const auto &polygon : polygons) window.attach(*polygon);
        
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}