#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include <iostream>
#include <stdexcept>

using namespace Graph_lib;

int main()
{
    try
    {
        Point topLeft{100, 100};
        Simple_window window{topLeft, 600, 400, "My window"};
        
        Graph_lib::Rectangle rect{Point{100, 100}, 100, 50};
        rect.set_color(Color::blue);
        window.attach(rect);

        Graph_lib::Polygon poly;
        poly.add(Point{250, 100});
        poly.add(Point{250, 150});
        poly.add(Point{350, 150});
        poly.add(Point{350, 100});
        poly.set_color(Color::red);
        window.attach(poly);
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}