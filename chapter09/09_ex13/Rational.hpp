#pragma once
#include <iostream>

class Rational
{
public:
    Rational();
    Rational(int numerator, int denominator);

    int GetNumerator() const { return numerator; }
    int GetDenominator() const { return denominator; }
    void SetNumerator(int value) { numerator = value; }
    void SetDenominator(int value);
    Rational Shorten();
    double ToDouble() { return numerator / double(denominator); }

private:
    int numerator;
    int denominator;
};

int CalcGreatestDivisor(int a, int b);

Rational operator+ (const Rational &first, const Rational &second);
Rational operator- (const Rational &first, const Rational &second);
Rational operator* (const Rational &first, const Rational &second);
Rational operator/ (const Rational &first, const Rational &second);
bool operator== (const Rational &first, const Rational &second);
bool operator!= (const Rational &first, const Rational &second);
std::ostream &operator<<(std::ostream &os, const Rational &rational);
std::istream &operator>>(std::istream &is, Rational &rational);