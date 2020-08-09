#pragma once
#include <iostream>
#include <sstream>
#include <string>

class CustomInputStream
{
public:
    CustomInputStream(std::istream &is, bool caseSensitive = true) : source{is}, caseSensitive{caseSensitive} {}

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

bool EndsWith(const std::string &word, const std::string &ending);