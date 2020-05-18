/*
Exercise 06: Write a program that checks if a sentence is correct according to the “English” grammar in §6.4.1. 
             Assume that every sentence is terminated by a full stop (.) surrounded by whitespace. 
             For example, birds fly but the fish swim . is a sentence, but birds fly but the fish swim (terminating dot missing) and birds fly but the fish swim. (no space before dot) are not. 
             For each sentence entered, the program should simply respond “OK” or “not OK.” 
             Hint: Don’t bother with tokens; just read into a string using >>.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using WordList = std::vector<std::string>;

class EnglishParser
{
    public:
        EnglishParser(WordList conjunctions, WordList articles, WordList nouns, WordList verbs);
        bool IsSentence();
    private:
        WordList conjunctions;
        WordList articles;
        WordList nouns;
        WordList verbs;

        bool IsConjunction(const std::string &word);
        bool IsArticle(const std::string &word);
        bool IsNoun(const std::string &word);
        bool IsVerb(const std::string &word);
};

EnglishParser::EnglishParser(WordList conjunctions, WordList articles, WordList nouns, WordList verbs)
             : conjunctions(conjunctions), articles(articles), nouns(nouns), verbs(verbs) {}

bool EnglishParser::IsConjunction(const std::string &word)
{
    auto iter = std::find(conjunctions.begin(), conjunctions.end(), word);
    return iter != conjunctions.end();
}

bool EnglishParser::IsArticle(const std::string &word)
{
    auto iter = std::find(articles.begin(), articles.end(), word);
    return iter != articles.end();
}

bool EnglishParser::IsNoun(const std::string &word)
{
    auto iter = std::find(nouns.begin(), nouns.end(), word);
    return iter != nouns.end();
}

bool EnglishParser::IsVerb(const std::string &word)
{
    auto iter = std::find(verbs.begin(), verbs.end(), word);
    return iter != verbs.end();
}

bool EnglishParser::IsSentence()
{
    std::string word;
    std::cin >> word;
    if (IsArticle(word))
    {
        std::cin >> word;
        if (!IsNoun(word)) return false;
    }
    else if (!IsNoun(word)) return false;

    std::cin >> word;
    if (!IsVerb(word)) return false;

    std::cin >> word;
    if (word == ".") return true;
    else if (!IsConjunction(word)) return false;
    else return IsSentence();
}

int main()
{
    WordList conjunctions { "and", "or", "but" };
    WordList articles { "the" };
    WordList nouns { "birds", "fish", "C++" };
    WordList verbs { "rules", "fly", "swim" };

    EnglishParser parser(conjunctions, articles, nouns, verbs);
    while (std::cout << "> " && std::cin)
    {
        if (parser.IsSentence()) std::cout << "OK!\n";
        else std::cout << "Not OK!\n";
    }
}