#include "./Rational.hpp"
#include "../../lib/utilities.h"
#include <iostream>

Rational::Rational() {}

Rational::Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator)
{
    if (denominator == 0) ThrowError("Denominator cannot be 0.");
}

void Rational::SetDenominator(int value)
{
    if (value == 0) ThrowError("Denominator cannot be set to 0.");
    else denominator = value;
}

Rational Rational::Shorten()
{
    int greatestDivisor = CalcGreatestDivisor(GetNumerator(), GetDenominator());
    Rational result(GetNumerator() / greatestDivisor, GetDenominator() / greatestDivisor);
    return result;
}

int CalcGreatestDivisor(int a, int b)
{
    while (b != 0)
    {
        int modulo = a % b;
        a = b;
        b = modulo;
    }

    return a;
}

Rational operator+ (const Rational &first, const Rational &second)
{
    return Rational(first.GetNumerator() * second.GetDenominator() + first.GetDenominator() * second.GetNumerator(), 
                    first.GetDenominator() * second.GetDenominator());
}

Rational operator- (const Rational &first, const Rational &second)
{
    return Rational(first.GetNumerator() * second.GetDenominator() - first.GetDenominator() * second.GetNumerator(),
                    first.GetDenominator() * second.GetDenominator());
}

Rational operator* (const Rational &first, const Rational &second)
{
    return Rational(first.GetNumerator() * second.GetNumerator(), first.GetDenominator() * second.GetDenominator());
}

Rational operator/ (const Rational &first, const Rational &second)
{
    if (first.GetDenominator() * second.GetNumerator() == 0) ThrowError("Cannot divide by 0.");
    return Rational(first.GetNumerator() * second.GetDenominator(), first.GetDenominator() * second.GetNumerator());
}

bool operator== (const Rational &first, const Rational &second)
{
    return (first.GetNumerator() * second.GetDenominator() == first.GetDenominator() * second.GetNumerator());
}

bool operator!= (const Rational &first, const Rational &second)
{
    return !(first == second);
}

std::ostream &operator<<(std::ostream &os, const Rational &rational)
{
    return os << rational.GetNumerator() << "/" << rational.GetDenominator();
}

std::istream &operator>>(std::istream &is, Rational &rational)
{
    int numerator = 0;
    int denominator = 1;
    char slash = '/';
    
    is >> numerator >> slash >> denominator;
    if (!is >> numerator || slash != '/' || !is >> denominator)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    try
    {
        rational.SetDenominator(denominator);
        rational.SetNumerator(numerator);
    }
    catch (const std::exception &err)
    {
        is.clear(std::ios_base::failbit);
        std::cerr << "[ERROR] " << err.what() << '\n';
        std::cerr << "[ERROR] Input to rational has failed." << '\n';
    }

    return is;
}