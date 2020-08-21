#include "./Arc.hpp"
#include "../../lib/graphics/Simple_window.h"

int main()
{
    Point origin{100, 100};
    Simple_window window{origin, 600, 600, "Arc"};

    Graph_lib::Arc arc{Point{300, 300}, 100, 90, 270};
    window.attach(arc);
    window.wait_for_button();
}