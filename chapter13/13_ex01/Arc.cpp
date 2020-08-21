#include "./Arc.hpp"
#include "../../lib/graphics/Graph.h"

namespace Graph_lib
{
    Arc::Arc(Point point, int radius, double startAngle, double endAngle) : radius(radius), startAngle(startAngle + 90), endAngle(endAngle + 90)
    {
        add(Point{point.x - radius, point.y - radius});
    }

    void Arc::draw_lines() const
    {
        if (color().visibility()) 
        {
            fl_color(color().as_int());
            fl_arc(point(0).x, point(0).y, 2 * radius, 2 * radius, startAngle, endAngle);
	    }
    }
}