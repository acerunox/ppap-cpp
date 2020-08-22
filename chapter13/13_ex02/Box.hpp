#pragma once
#include "./Arc.hpp"
#include "../../lib/graphics/Graph.h"
#include <vector>

namespace Graph_lib
{
    struct Box : Shape
    {
    public:
        Box(Point origin, int width, int height, double roundingRatio);
        void draw_lines() const;

    private:
        Vector_ref<Graph_lib::Arc> arcs;
        Lines lines;
        int width;
        int height;
        int radius;
    };
}