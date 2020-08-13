#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        Point topLeft{100, 100};
        Simple_window window{topLeft, 600, 400, "My window"};
        window.wait_for_button();

        Axis xAxis{Axis::x, Point{40, 350}, 300, 15, "x axis"};
        window.attach(xAxis);
        window.wait_for_button();

        Axis yAxis{Axis::y, Point{40, 350}, 300, 15, "y axis"};
        window.attach(yAxis);
        window.wait_for_button();

        Function sine{sin, 0, 50, Point{40, 175}, 1000, 50, 50};
        window.attach(sine);
        window.wait_for_button();

        Graph_lib::Polygon poly;
        poly.add(Point{350, 200});
        poly.add(Point{350, 100});
        poly.add(Point{400, 200});

        poly.set_color(Color::blue);
        poly.set_style(Line_style::dashdot);
        window.attach(poly);
        window.wait_for_button();

        Graph_lib::Rectangle rect{Point{200, 200}, 100, 50};
        window.attach(rect);
        window.wait_for_button();

        Closed_polyline polyRect;
        polyRect.add(Point{100, 50});
        polyRect.add(Point{200, 50});
        polyRect.add(Point{200, 100});
        polyRect.add(Point{100, 100});
        polyRect.add(Point{200, 150});
        window.attach(polyRect);
        window.wait_for_button();

        rect.set_fill_color(Color::red);
        poly.set_style(Line_style(Line_style::dash, 4));
        polyRect.set_style(Line_style(Line_style::dashdotdot, 2));
        polyRect.set_color(Color::magenta);
        window.wait_for_button();

        Text text{Point{250,400}, "Hello world!"};
        text.set_font(Font::times_bold);
        text.set_font_size(24);
        window.attach(text);
        window.wait_for_button();

        Image image{Point{100,50}, "chapter12/12_drill/logo.jpg"};
        window.attach(image);
        window.wait_for_button();

        image.move(350, 100);
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}