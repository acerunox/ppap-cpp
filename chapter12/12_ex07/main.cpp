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
        Simple_window window{topLeft, 900, 800, "My window"};
        
        Graph_lib::Rectangle rect{Point{300, 300}, 300, 300};
        rect.set_fill_color(Color::yellow);
        window.attach(rect);

        Graph_lib::Rectangle chimney{Point{500, 150}, 60, 100};
        chimney.set_fill_color(Color::black);
        window.attach(chimney);

        Graph_lib::Open_polyline roof;
        roof.add(Point{300, 300});
        roof.add(Point{450, 100});
        roof.add(Point{600, 300});
        roof.set_fill_color(Color::red);
        window.attach(roof);

        Graph_lib::Rectangle leftWindow{Point{320, 320}, 50, 75};
        leftWindow.set_fill_color(Color::white);
        window.attach(leftWindow);

        Graph_lib::Rectangle rightWindow{Point{530, 320}, 50, 75};
        rightWindow.set_fill_color(Color::white);
        window.attach(rightWindow);

        Graph_lib::Rectangle door{Point{420, 500}, 60, 100};
        door.set_fill_color(Color::black);
        window.attach(door);
        
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}