#pragma once
#include "../../lib/graphics/fltk.h"
#include "../../lib/graphics/Graph.h"

namespace Graph_lib
{
    struct Arc : Shape
    {
    public:
        Arc(Point point, int radius, double startAngle, double endAngle);
        void draw_lines() const;

        Point GetCenter() const { return {point(0).x + radius, point(0).y + radius}; }
        void SetRadius(double newRadius) { radius = newRadius; }
        int GetRadius() const { return radius; }
        int GetStartAngle() const { return startAngle; }
        int GetEndAngle() const { return endAngle; }
    private:
        int radius;
        double startAngle;
        double endAngle;
    };
}