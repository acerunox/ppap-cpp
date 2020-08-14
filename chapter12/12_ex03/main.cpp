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
        
        Graph_lib::Open_polyline firstInitial; // "S"
        firstInitial.add(Point{350, 50});
        firstInitial.add(Point{300, 50});
        firstInitial.add(Point{275, 75});
        firstInitial.add(Point{275, 100});
        firstInitial.add(Point{300, 125});
        firstInitial.add(Point{325, 125});
        firstInitial.add(Point{350, 150});
        firstInitial.add(Point{350, 175});
        firstInitial.add(Point{325, 200});
        firstInitial.add(Point{275, 200});
        firstInitial.set_color(Color::dark_green);
        firstInitial.set_style(Line_style{Line_style::solid, 4});
        window.attach(firstInitial);

        Graph_lib::Open_polyline secondInitial; // "M"
        secondInitial.add(Point{400, 200});
        secondInitial.add(Point{400, 50});
        secondInitial.add(Point{450, 100});
        secondInitial.add(Point{500, 50});
        secondInitial.add(Point{500, 200});
        secondInitial.set_color(Color::red);
        secondInitial.set_style(Line_style{Line_style::solid, 4});
        window.attach(secondInitial);

        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}