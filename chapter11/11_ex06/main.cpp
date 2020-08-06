/*
Exercise 06: Write a program that replaces punctuation with whitespace.
             Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
             Don’t modify characters within a pair of double quotes (").
             For example, “- don't use the as-if rule.” becomes “ don t use the as if rule ”.
*/

#include "./CustomInputStream.hpp"
#include <iostream>
#include <string>

int main()
{
    CustomInputStream inputStream{std::cin};
    inputStream.SetWhitespace(".;,?-'");

    std::string line;
    inputStream >> line;
    std::cout << std::noskipws << line << '\n';
}