#include <iostream>

void swap_v(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_r(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

/*
NOTE: won't compile, because of assigning to a const variable inside the body

void swap_cr(const int &a, const int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
*/

int main()
{
    int x = 7;
    int y = 9;
    swap_r(x, y);
    std::cout << x << ", " << y << '\n';
    swap_v(7, 9);
    std::cout << x << ", " << y << '\n';
    
    const int cx = 7;
    const int cy = 9;
    swap_v(cx, cy);
    std::cout << cx << ", " << cy << '\n';
    swap_v(7.7, 9.9);
    std::cout << cx << ", " << cy << '\n';
    
    double dx = 7.7;
    double dy = 9.9;
    swap_v(dx, dy);
    std::cout << dx << ", " << dy << '\n';
    swap_v(7.7, 9.9);
    std::cout << dx << ", " << dy << '\n';
}