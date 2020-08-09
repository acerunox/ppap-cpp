#include "./CustomInputStream.hpp"
#include <algorithm>
#include <sstream>
#include <string>

bool CustomInputStream::IsWhitespace(const char &character)
{
    return (whitespace.find(character) != std::string::npos);
}

CustomInputStream::operator bool()
{
    return !(source.fail() || source.bad()) && source.good();
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
        std::string word;
        while (iss >> word)
        {
            if (word.front() == '"')
            {
                result += word + ' ';
                while (iss >> word)
                {
                    if (iss.peek() == EOF) result += word;
                    else result += word + ' ';
                    
                    if (word.back() == '"') break;
                }
            }
            else
            {
                if (!IsCaseSensitive())
                {
                    for (char &character : word) character = std::tolower(character);
                }

                if (EndsWith(word, "n't")) 
                {
                    size_t position = word.find("n't");
                    if (word.find("can", 0, 3) != std::string::npos) 
                    {
                        word.replace(position, 3, "");
                        word.insert(position, "nnot");
                    }
                    else 
                    {
                        word.replace(position, 3, "");
                        word.insert(position, " not");
                    }
                }

                for (int i = 0; i < word.length(); ++i)
                {
                    if (i > 0 && i < word.length() - 1 && word[i] == '-') continue;
                    else if (IsWhitespace(word[i])) word[i] = ' ';
                }
                
                if (iss.peek() == EOF) result += word;
                else result += word + ' ';
            }
        }

        buffer.str(result);
    }

    return *this;
}

bool EndsWith(const std::string &word, const std::string &ending)
{
    if (ending.length() > word.length()) return false;
    return std::equal(ending.rbegin(), ending.rend(), word.rbegin());
}