#include <cmath>
#include <iostream>

double CalculateDelta(double a, double b, double c) { return b*b - 4*a*c; }

int main()
{
    std::cout << "Quadratic equation solver (ax^2 + bx + c)\n"
              << "Enter your a, b and c: ";
    double a, b, c;
    std::cin >> a >> b >> c;

    double delta = CalculateDelta(a, b, c);

    if (delta < 0) std::cout << "This equation has no roots.\n";
    else if (delta == 0)
    {
        double x1 = -b / (2*a);
        std::cout << "x1: " << x1 << '\n';
    }
    else if (delta > 0)
    {
        double x1 = (-b + sqrt(delta)) / (2*a);
        double x2 = (-b - sqrt(delta)) / (2*a);
        std::cout << "x1: " << x1 << '\n'
                  << "x2: " << x2 << '\n';
    }
}