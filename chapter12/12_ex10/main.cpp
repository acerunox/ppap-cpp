#include "../../lib/graphics/Graph.h"
#include "../../lib/graphics/Simple_window.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace Graph_lib;

enum class Side { LEFT, TOP, RIGHT, BOTTOM };

Point GetMiddlePoint(const Graph_lib::Rectangle &rect, const Side &side)
{
    switch (side)
    {
    case Side::LEFT:
        return Point{rect.point(0).x, rect.point(0).y + rect.height() / 2};

    case Side::TOP:
        return Point{rect.point(0).x + rect.width() / 2, rect.point(0).y};

    case Side::RIGHT:
        return Point{rect.point(0).x + rect.width(), rect.point(0).y + rect.height() / 2};

    case Side::BOTTOM:
        return Point{rect.point(0).x + rect.width() / 2, rect.point(0).y + rect.height()};
    }
}

int main()
{
    try
    {
        Point topLeft{100, 75};
        Simple_window window{topLeft, 712, 570, "File diagram"};
        const int textOffset = 16;

        //Point.h
        Point startRect1{50, 50};
        Graph_lib::Text title1{Point{startRect1.x, startRect1.y - textOffset / 2}, "Point.h:"};
        title1.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect1{startRect1, 155, 30};
        rect1.set_fill_color(Color::yellow);
        Graph_lib::Text text1{Point{startRect1.x + textOffset, startRect1.y + textOffset}, "struct Point { ... };"};
        text1.set_font(Font::helvetica_bold);
        window.attach(title1);
        window.attach(rect1);
        window.attach(text1);

        //FLTK headers
        const int rectOffset = 4;
        Point startRect2{362, 22};
        Graph_lib::Rectangle rect2_1{startRect2, 125, 40};
        rect2_1.set_fill_color(Color::yellow);
        Graph_lib::Rectangle rect2_2{Point{startRect2.x - rectOffset, startRect2.y - rectOffset}, 125, 40};
        rect2_2.set_fill_color(Color::yellow);
        Graph_lib::Rectangle rect2_3{Point{startRect2.x - rectOffset * 2, startRect2.y - rectOffset * 2}, 125, 40};
        rect2_3.set_fill_color(Color::yellow);
        Graph_lib::Text text2{Point{startRect2.x + textOffset, startRect2.y + textOffset}, "FLTK headers"};
        window.attach(rect2_3);
        window.attach(rect2_2);
        window.attach(rect2_1);
        window.attach(text2);

        //FLTK code
        Point startRect3{562, 62};
        Graph_lib::Rectangle rect3_1{startRect3, 105, 40};
        rect3_1.set_fill_color(Color::yellow);
        Graph_lib::Rectangle rect3_2{Point{startRect3.x - rectOffset, startRect3.y - rectOffset}, 105, 40};
        rect3_2.set_fill_color(Color::yellow);
        Graph_lib::Rectangle rect3_3{Point{startRect3.x - rectOffset * 2, startRect3.y - rectOffset * 2}, 105, 40};
        rect3_3.set_fill_color(Color::yellow);
        Graph_lib::Text text3{Point{startRect3.x + textOffset, startRect3.y + textOffset}, "FLTK code"};
        window.attach(rect3_3);
        window.attach(rect3_2);
        window.attach(rect3_1);
        window.attach(text3);

        //Graph.h
        Point startRect4{50, 200};
        Graph_lib::Text title4{Point{startRect4.x, startRect4.y - textOffset / 2}, "Graph.h:"};
        title4.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect4{startRect4, 175, 60};
        rect4.set_fill_color(Color::yellow);
        Graph_lib::Text text4_1{Point{startRect4.x + textOffset, startRect4.y + textOffset}, "// graphing interface:"};
        Graph_lib::Text text4_2{Point{startRect4.x + textOffset, startRect4.y + textOffset * 2}, "struct Shape { ... };"};
        text4_2.set_font(Font::helvetica_bold);
        Graph_lib::Text text4_3{Point{startRect4.x + textOffset, startRect4.y + textOffset * 3}, "..."};
        text4_3.set_font(Font::helvetica_bold);
        window.attach(title4);
        window.attach(rect4);
        window.attach(text4_1);
        window.attach(text4_2);
        window.attach(text4_3);
        
        //Window.h
        Point startRect5{340, 150};
        Graph_lib::Text title5{Point{startRect5.x, startRect5.y - textOffset / 2}, "Window.h:"};
        title5.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect5{startRect5, 175, 60};
        rect5.set_fill_color(Color::yellow);
        Graph_lib::Text text5_1{Point{startRect5.x + textOffset, startRect5.y + textOffset}, "// window interface:"};
        Graph_lib::Text text5_2{Point{startRect5.x + textOffset, startRect5.y + textOffset * 2}, "class Window { ... };"};
        text5_2.set_font(Font::helvetica_bold);
        Graph_lib::Text text5_3{Point{startRect5.x + textOffset, startRect5.y + textOffset * 3}, "..."};
        text5_3.set_font(Font::helvetica_bold);
        window.attach(title5);
        window.attach(rect5);
        window.attach(text5_1);
        window.attach(text5_2);
        window.attach(text5_3);

        //GUI.h
        Point startRect6{492, 250};
        Graph_lib::Text title6{Point{startRect6.x, startRect6.y - textOffset / 2}, "GUI.h:"};
        title6.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect6{startRect6, 175, 60};
        rect6.set_fill_color(Color::yellow);
        Graph_lib::Text text6_1{Point{startRect6.x + textOffset, startRect6.y + textOffset}, "// GUI interface:"};
        Graph_lib::Text text6_2{Point{startRect6.x + textOffset, startRect6.y + textOffset * 2}, "struct In_box { ... };"};
        text6_2.set_font(Font::helvetica_bold);
        Graph_lib::Text text6_3{Point{startRect6.x + textOffset, startRect6.y + textOffset * 3}, "..."};
        text6_3.set_font(Font::helvetica_bold);
        window.attach(title6);
        window.attach(rect6);
        window.attach(text6_1);
        window.attach(text6_2);
        window.attach(text6_3);

        //Graph.cpp
        Point startRect7{20, 350};
        Graph_lib::Text title7{Point{startRect7.x, startRect7.y - textOffset / 2}, "Graph.cpp:"};
        title7.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect7{startRect7, 120, 30};
        rect7.set_fill_color(Color::yellow);
        Graph_lib::Text text7{Point{startRect7.x + textOffset, startRect7.y + textOffset}, "Graph code"};
        text7.set_font(Font::helvetica_bold);
        window.attach(title7);
        window.attach(rect7);
        window.attach(text7);
        
        //Window.cpp
        Point startRect8{225, 300};
        Graph_lib::Text title8{Point{startRect8.x, startRect8.y - textOffset / 2}, "Window.cpp:"};
        title8.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect8{startRect8, 125, 30};
        rect8.set_fill_color(Color::yellow);
        Graph_lib::Text text8{Point{startRect8.x + textOffset, startRect8.y + textOffset}, "Window code"};
        text8.set_font(Font::helvetica_bold);
        window.attach(title8);
        window.attach(rect8);
        window.attach(text8);

        //GUI.cpp
        Point startRect9{525, 350};
        Graph_lib::Text title9{Point{startRect9.x, startRect9.y - textOffset / 2}, "GUI.cpp:"};
        title9.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect9{startRect9, 100, 30};
        rect9.set_fill_color(Color::yellow);
        Graph_lib::Text text9{Point{startRect9.x + textOffset, startRect9.y + textOffset}, "GUI code"};
        text9.set_font(Font::helvetica_bold);
        window.attach(title9);
        window.attach(rect9);
        window.attach(text9);

        //Simple_window.h
        Point startRect10{275, 375};
        Graph_lib::Text title10{Point{startRect10.x, startRect10.y - textOffset / 2}, "Simple_window.h:"};
        title10.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect10{startRect10, 225, 60};
        rect10.set_fill_color(Color::yellow);
        Graph_lib::Text text10_1{Point{startRect10.x + textOffset, startRect10.y + textOffset}, "// window interface:"};
        Graph_lib::Text text10_2{Point{startRect10.x + textOffset, startRect10.y + textOffset * 2}, "class Simple_window { ... };"};
        text10_2.set_font(Font::helvetica_bold);
        Graph_lib::Text text10_3{Point{startRect10.x + textOffset, startRect10.y + textOffset * 3}, "..."};
        text10_3.set_font(Font::helvetica_bold);
        window.attach(title10);
        window.attach(rect10);
        window.attach(text10_1);
        window.attach(text10_2);
        window.attach(text10_3);

        //chapter12.cpp
        Point startRect11{100, 500};
        Graph_lib::Text title11{Point{startRect11.x, startRect11.y - textOffset / 2}, "chapter12.cpp:"};
        title11.set_font(Font::helvetica_bold);
        Graph_lib::Rectangle rect11{startRect11, 225, 60};
        rect11.set_fill_color(Color::yellow);
        Graph_lib::Text text11_1{Point{startRect11.x + textOffset, startRect11.y + textOffset}, "#include \"Graph.h\""};
        text11_1.set_font(Font::helvetica_bold);
        Graph_lib::Text text11_2{Point{startRect11.x + textOffset, startRect11.y + textOffset * 2}, "#include \"Simple_window.h\""};
        text11_2.set_font(Font::helvetica_bold);
        Graph_lib::Text text11_3{Point{startRect11.x + textOffset, startRect11.y + textOffset * 3}, "int main() { ... }"};
        text11_3.set_font(Font::helvetica_bold);
        window.attach(title11);
        window.attach(rect11);
        window.attach(text11_1);
        window.attach(text11_2);
        window.attach(text11_3);

        Graph_lib::Line line1{GetMiddlePoint(rect4, Side::TOP), GetMiddlePoint(rect1, Side::BOTTOM)};   //Graph.h to Point.h
        window.attach(line1);
        Graph_lib::Line line2{GetMiddlePoint(rect4, Side::TOP), GetMiddlePoint(rect2_1, Side::BOTTOM)}; //Graph.h to FLTK headers
        window.attach(line2);
        Graph_lib::Line line3{GetMiddlePoint(rect3_3, Side::LEFT), GetMiddlePoint(rect2_1, Side::RIGHT)};   //FLTK code to FLTK headers
        window.attach(line3);
        Graph_lib::Line line4{GetMiddlePoint(rect6, Side::TOP), GetMiddlePoint(rect2_1, Side::BOTTOM)}; //GUI.h to FLTK headers
        window.attach(line4);
        Graph_lib::Line line5{GetMiddlePoint(rect6, Side::TOP), GetMiddlePoint(rect5, Side::BOTTOM)};   //GUI.h to Window.h
        window.attach(line5);
        Graph_lib::Line line6{GetMiddlePoint(rect5, Side::TOP), GetMiddlePoint(rect2_1, Side::BOTTOM)}; //Window.h to FLTK headers
        window.attach(line6);
        Graph_lib::Line line7{GetMiddlePoint(rect7, Side::TOP), GetMiddlePoint(rect4, Side::BOTTOM)}; //Graph.cpp to Graph.h
        window.attach(line7);
        Graph_lib::Line line8{GetMiddlePoint(rect8, Side::TOP), GetMiddlePoint(rect5, Side::BOTTOM)}; //Window.cpp to Window.h
        window.attach(line8);
        Graph_lib::Line line9{GetMiddlePoint(rect9, Side::TOP), GetMiddlePoint(rect6, Side::BOTTOM)}; //GUI.cpp to GUI.h
        window.attach(line9);
        Graph_lib::Line line10{GetMiddlePoint(rect10, Side::TOP), GetMiddlePoint(rect5, Side::BOTTOM)}; //Simple_window.h to Window.h
        window.attach(line10);
        Graph_lib::Line line11{GetMiddlePoint(rect10, Side::TOP), GetMiddlePoint(rect6, Side::BOTTOM)}; //Simple_window.h to GUI.h
        window.attach(line11);
        Graph_lib::Line line12{GetMiddlePoint(rect11, Side::TOP), GetMiddlePoint(rect4, Side::BOTTOM)}; //chapter12.cpp to Graph.h
        window.attach(line12);
        Graph_lib::Line line13{GetMiddlePoint(rect11, Side::TOP), GetMiddlePoint(rect10, Side::BOTTOM)}; //chapter12.cpp to Simple_window.h
        window.attach(line13);

        window.wait_for_button();
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
}