#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"

Vector_ref<Graph_lib::Rectangle> InitializeGrid(int rows, int columns, int cellSize)
{
    Vector_ref<Graph_lib::Rectangle> grid;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            grid.push_back(new Graph_lib::Rectangle{Point{j * cellSize, i * cellSize}, cellSize, cellSize});
        }
    }

    return grid;
}

int main()
{
    Point origin{80, 80};
    Simple_window window{origin, 800, 1000, "Grid"};

    int gridSize = 8;
    auto grid = InitializeGrid(gridSize, gridSize, 100);
    for (int i = 0; i < grid.size(); ++i) 
    {
        if (i % (gridSize + 1) == 0) grid[i].set_fill_color(Color::red);
        window.attach(grid[i]);
    }
    
    Vector_ref<Graph_lib::Image> images;
    for (int i = 1; i <= 3; ++i) images.push_back(new Graph_lib::Image{Point{200 * i, 0}, "chapter13/13_drill/logo.jpg", Suffix::jpg});
    for (int i = 0; i < 3; ++i) 
    {
        images[i].set_mask(Point{0, 10}, 200, 200);
        window.attach(images[i]);
    }

    int i = 1;
    Graph_lib::Image checkmark{grid[i].point(0), "chapter13/13_drill/checkmark.jpg", Suffix::jpg};
    window.attach(checkmark);
    while (window.wait_for_button())
    {
        Point checkmarkPosition = checkmark.point(0);
        
        if ((i + 1) % (gridSize + 1) == 0) ++i;
        if (i + 1 >= grid.size()) i = 0;
        Point newCellPosition = grid[i + 1].point(0);
        checkmark.move(newCellPosition.x - checkmarkPosition.x, newCellPosition.y - checkmarkPosition.y);
        ++i;
    }
}