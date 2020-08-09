/*
Exercise 07: Modify the program from the previous exercise so that it replaces don't with do not, can't with cannot, etc.
             leaves hyphens within words intact and converts all characters to lower case.
*/

#include "./CustomInputStream.hpp"
#include <iostream>
#include <string>

int main()
{
    CustomInputStream inputStream{std::cin, false};
    inputStream.SetWhitespace(".;,?-'");

    std::string line;
    inputStream >> line;
    std::cout << std::noskipws << line << '\n';
}