/*
Exercise 07: Write a program that can calculate x for a quadratic equation. 
             Create a function that prints out the roots of a quadratic equation, given a, b, c. 
             When the program detects an equation with no real roots, have it print out a message.
*/

#include <cmath>
#include <iostream>
#include <stdexcept>

void PrintRoots(double a, double b, double c)
{
    if (a == 0) throw std::runtime_error("[ERROR] 'a' in quadratic equation cannot be equal to 0.");
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) std::cout << "This equation has no roots.\n";
    else if (discriminant == 0)
    {
        double x1 = -b / (2*a);
        std::cout << "x1: " << x1 << '\n';
    }
    else if (discriminant > 0)
    {
        double x1 = (-b + sqrt(discriminant)) / (2*a);
        double x2 = (-b - sqrt(discriminant)) / (2*a);
        std::cout << "x1: " << x1 << '\n'
                  << "x2: " << x2 << '\n';
    }
}

int main()
{
    std::cout << "Quadratic equation solver (ax^2 + bx + c)\n"
              << "Enter your a, b and c: ";
    double a, b, c;
    std::cin >> a >> b >> c;

    try
    {
        PrintRoots(a, b, c);
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
    }
}