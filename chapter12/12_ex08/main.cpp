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
        Simple_window window{topLeft, 370, 280, "My window"};
        
        int radius = 40;
        Line_style ringStyle = Line_style{Line_style::solid, 5};
        
        Graph_lib::Circle ring1{Point{90, 100}, radius};
        ring1.set_style(ringStyle);
        ring1.set_color(Color::blue);
        window.attach(ring1);

        Graph_lib::Circle ring2{Point{180, 100}, radius};
        ring2.set_style(ringStyle);
        ring2.set_color(Color::black);
        window.attach(ring2);

        Graph_lib::Circle ring3{Point{270, 100}, radius};
        ring3.set_style(ringStyle);
        ring3.set_color(Color::red);
        window.attach(ring3);

        Graph_lib::Circle ring4{Point{135, 140}, radius};
        ring4.set_style(ringStyle);
        ring4.set_color(Color::yellow);
        window.attach(ring4);

        Graph_lib::Circle ring5{Point{225, 140}, radius};
        ring5.set_style(ringStyle);
        ring5.set_color(Color::green);
        window.attach(ring5);
        
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}