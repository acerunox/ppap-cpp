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
        
        Graph_lib::Rectangle rect{Point{50, 50}, x_max() * 2/3, y_max() * 3/4};
        rect.set_fill_color(Color::blue);
        window.attach(rect);
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}