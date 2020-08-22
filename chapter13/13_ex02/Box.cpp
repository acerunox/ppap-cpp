#include "./Box.hpp"
#include "./Arc.hpp"
#include "../../lib/graphics/Graph.h"
#include "../../lib/utilities.h"
#include <cmath>

namespace Graph_lib
{
    Box::Box(Point origin, int width, int height, double roundingRatio) : width(width), height(height)
    {
        if (roundingRatio < 0 || roundingRatio > 1) ThrowError("Rounding ratio has to be between 0 and 1.");
        radius = (width < height) ? width/2 : height/2;
        radius *= roundingRatio;

        for (int i = 0; i < 4; ++i) 
        {
            Point startPoint;
            switch (i)
            {
            case 0:
                startPoint = Point{origin.x + radius, origin.y + radius};
                break;

            case 1:
                startPoint = Point{origin.x + radius, origin.y + height - radius};
                break;

            case 2:
                startPoint = Point{origin.x + width - radius, origin.y + height - radius};
                break;

            case 3:
                startPoint = Point{origin.x + width - radius, origin.y + radius};
                break;
            }
            
            int startAngle = i * 90;
            arcs.push_back(new Graph_lib::Arc{startPoint, radius, startAngle, startAngle + 90});
        }

        for (int i = 0; i < 4; ++i) 
        {
            Point startPoint;
            Point endPoint;
            switch (i)
            {
            case 0:
                startPoint = Point{origin.x, origin.y + radius};
                endPoint = Point{origin.x, origin.y + height - radius};
                break;

            case 1:
                startPoint = Point{origin.x + radius, origin.y + height};
                endPoint = Point{origin.x + width - radius, origin.y + height};
                break;

            case 2:
                startPoint = Point{origin.x + width, origin.y + height - radius};
                endPoint = Point{origin.x + width, origin.y + radius};
                break;

            case 3:
                startPoint = Point{origin.x + width - radius, origin.y};
                endPoint = Point{origin.x + radius, origin.y};
                break;
            }

            lines.add(startPoint, endPoint);
        }
    }

    void Box::draw_lines() const
    {
        if (fill_color().visibility())
        {
            fl_color(fill_color().as_int());
            fl_rectf(lines.point(0).x, lines.point(0).y, width, std::abs(lines.point(0).y - lines.point(4).y));
            fl_rectf(lines.point(7).x, lines.point(7).y, std::abs(lines.point(7).x - lines.point(3).x), height);

            for (int i = 0; i < arcs.size(); ++i) 
            {
                fl_pie(arcs[i].point(0).x, arcs[i].point(0).y, 2 * radius, 2 * radius, arcs[i].GetStartAngle(), arcs[i].GetEndAngle());
            }

            fl_color(color().as_int());	// reset color
        }

        if (color().visibility()) 
        {
            fl_color(color().as_int());
            for (int i = 0; i < arcs.size(); ++i) 
            {
                fl_arc(arcs[i].point(0).x, arcs[i].point(0).y, 2 * radius, 2 * radius, arcs[i].GetStartAngle(), arcs[i].GetEndAngle());
            }

            for (int i=1; i < lines.number_of_points(); i+=2)
            {
			    fl_line(lines.point(i-1).x, lines.point(i-1).y, lines.point(i).x, lines.point(i).y);
            }
	    }
    }
}