#pragma once
#include <iostream>
#include <sstream>
#include <string>

class CustomInputStream
{
public:
    CustomInputStream(std::istream &is) : source{is}, caseSensitive{true} {}

    void SetWhitespace(const std::string &newWhitespace) { whitespace = newWhitespace; }
    void AddToWhitespace(const char &character) { whitespace += character; }
    bool IsWhitespace(const char &character);
    void SetCaseSensitivity(bool caseSensitivity) { caseSensitive = caseSensitivity; }
    bool IsCaseSensitive() const { return caseSensitive; }

    CustomInputStream &operator>>(std::string &string);
    operator bool();
private:
    std::istream &source;
    std::istringstream buffer;
    std::string whitespace;
    bool caseSensitive;
};