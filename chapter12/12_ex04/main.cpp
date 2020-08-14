#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Graph_lib;

int main()
{
    try
    {
        Point topLeft{100, 100};
        Simple_window window{topLeft, 600, 400, "My window"};
        
        int rectangleHeight = 100;
        int rectangleWidth = 100;
        int xOffset = 0;
        int yOffset = 0;
        Color currentColor = Color::white;
        std::vector<std::unique_ptr<Graph_lib::Rectangle>> grid;
        
        for (int i = 0; i < 9; ++i)
        {
            if (i % 2 == 0) currentColor = Color::white;
            else currentColor = Color::red;

            if (i != 0 && i % 3 == 0) 
            {
                yOffset += rectangleHeight;
                xOffset = 0;
            }
            Point startingPoint{50 + xOffset, 50 + yOffset};

            auto rectPtr = std::make_unique<Graph_lib::Rectangle>(startingPoint, rectangleWidth, rectangleHeight);
            rectPtr->set_fill_color(currentColor);
            grid.push_back(std::move(rectPtr));
            xOffset += rectangleWidth;
        }

        for (const auto &rect : grid) window.attach(*rect);
        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}