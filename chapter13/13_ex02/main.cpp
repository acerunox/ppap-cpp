#include "./Box.hpp"
#include "../../lib/graphics/Simple_window.h"

int main()
{
    Point origin{100, 100};
    Simple_window window{origin, 600, 600, "Box"};

    Graph_lib::Box box{Point{150, 150}, 300, 300, 0.5};
    box.set_style(Line_style(Line_style::solid, 10));
    box.set_fill_color(Color::red);
    box.set_color(Color::green);
    window.attach(box);
    window.wait_for_button();
}