/*
Drill: Start a program called Test_output.cpp. Declare an integer birth_year and assign it the year you were born
       Output your birth_year in decimal, hexadecimal, and octal form.
       Label each value with the name of the base used.
       Did you line up your output in columns using the tab character? If not, do it.
       Now output your age.
       Was there a problem? What happened? Fix your output to decimal.
       Go back to 2 and cause your output to show the base for each output.
       Try reading as octal, hexadecimal, etc. Run this code with the input: 1234 1234 1234 1234
       Write some code to print the number 1234567.89 three times, first using defaultfloat, then fixed, then scientific forms.
*/

#include <iomanip>
#include <iostream>

int main()
{
    int currentYear = 2020;
    int birthYear = 1835;
    std::cout << std::showbase << "decimal: " << birthYear << "\thex: " << std::hex << birthYear << "\toctal: " << std::oct << birthYear << '\n';
    std::cout << "Age: " << std::dec << currentYear - birthYear << "\n\n";
    
    int a, b, c, d;
    std::cin >> a >> std::oct >> b >> std::hex >> c >> d;
    std::cout << a << '\t' << b << '\t' << c << '\t' << d << "\n\n";

    double number = 1234567.89;
    std::cout << std::defaultfloat << number << std::fixed << '\t' << number << std::scientific << '\t' << number << '\n';
}