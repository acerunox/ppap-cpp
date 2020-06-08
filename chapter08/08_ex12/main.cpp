/*
Exercise 12: Improve print_until_s() from §8.5.2. Test it.
             Then, write a print_until_ss() that prints until it sees a second occurrence of its quit argument.
*/

#include <iostream>
#include <string>
#include <vector>

void PrintUntilKeyword(const std::vector<std::string> &vector, const std::string &keyword)
{
    for (const std::string &element : vector)
    {
        if (element == keyword) return;
        else std::cout << element << '\n';
    }
}

void PrintUntilDoubleKeyword(const std::vector<std::string> &vector, const std::string &keyword)
{
    int keywordCount = 0;
    for (const std::string &element : vector)
    {
        if (element == keyword)
        {
            ++keywordCount;
            if (keywordCount >= 2) return;
        }
        else std::cout << element << '\n';
    }
}

int main()
{
    std::string keyword = "quit";
    std::vector<std::string> example{ "this1", "is", "an23",  "example", "sentence" };
    std::vector<std::string> exampleWithKeyword{ "this1", "is", "an23", keyword, "example", "sentence" };
    std::vector<std::string> exampleWithDoubleKeyword{ "this1", "is", "an23", keyword, "example", keyword, "sentence" };
    
    PrintUntilKeyword(example, keyword);
    std::cout << '\n';

    PrintUntilKeyword(exampleWithKeyword, keyword);
    std::cout << '\n';

    PrintUntilDoubleKeyword(exampleWithKeyword, keyword);
    std::cout << '\n';

    PrintUntilDoubleKeyword(exampleWithDoubleKeyword, keyword);
    std::cout << '\n';
}