#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include <iostream>
#include <stdexcept>

using namespace Graph_lib;

int main()
{
    try
    {
        Point topLeft{100, 75};
        Simple_window window{topLeft, 640, 990, "Mountain"};
        
        Graph_lib::Image image{Point{0, 0}, "chapter12/12_ex09/image.jpg"};
        window.attach(image);

        Graph_lib::Text caption{Point{480, 980}, "Photo by Annie Spratt"};
        caption.set_font(Font::times_italic);
        window.attach(caption);
        
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}