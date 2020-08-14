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
        
        Graph_lib::Rectangle rect{Point{100, 100}, 100, 30};
        window.attach(rect);
        Graph_lib::Text text{Point{127, 120}, "Howdy!"};
        window.attach(text);
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}