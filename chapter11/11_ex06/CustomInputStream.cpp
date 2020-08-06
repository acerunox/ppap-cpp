#include "./CustomInputStream.hpp"
#include <sstream>
#include <string>

bool CustomInputStream::IsWhitespace(const char &character)
{
    return (whitespace.find(character) != std::string::npos);
}

CustomInputStream &CustomInputStream::operator>>(std::string &string)
{
    while (!std::getline(buffer, string))
    {
        if (buffer.bad() || !source.good()) return *this;
        buffer.clear();

        std::string line;
        getline(source, line);
        std::istringstream iss{line};

        std::string result;
        char character; 
        while (iss.get(character))
        {
            if (character == '\"')
            {
                if (IsWhitespace(character)) character = ' ';
                result += character;
                while (iss.get(character))
                {
                    if (character == '\"')
                    {
                        if (IsWhitespace(character)) character = ' ';
                        break;
                    } 
                    else result += character;
                }
            }
            else if (IsWhitespace(character)) character = ' ';
            else if (!IsCaseSensitive()) character = std::tolower(character);
            result += character;
        }

        buffer.str(result);
    }

    return *this;
}