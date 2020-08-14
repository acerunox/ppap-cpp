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
        Simple_window window{topLeft, x_max() + 100, y_max() + 100, "My window"};
        
        Graph_lib::Rectangle rect{Point{50, 50}, 400, 200};
        rect.set_color(Color::blue);
        window.attach(rect);
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}