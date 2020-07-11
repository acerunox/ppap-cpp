#include "./Book.hpp"
#include "./Chrono.hpp"
#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

using Chrono::Date;

namespace BookLib
{
    std::ostream &operator<<(std::ostream &os, const Genre &genre)
    {
        if (int(genre) >= genresList.size()) ThrowError("Genre doesn't exist.");
        else return os << genresList[int(genre)];
    }

    std::istream &operator>>(std::istream &is, Genre &genre)
    {
        std::string input;
        std::cin >> input;
        
        auto iter = std::find(genresList.begin(), genresList.end(), input);
        if (iter == genresList.end()) 
        {
            is.clear(std::ios_base::failbit);
            return is;
        }
        else 
        {
            int index = std::distance(genresList.begin(), iter);
            genre = Genre(index);
            return is;
        }
    }

    Book::Book(std::string isbn, std::string title, std::string author, Genre genre, Date date)
        : isbn(isbn), title(title), author(author), genre(genre), copyrightDate(date), isCheckedOut(false)
    {
        if(!IsIsbnValid(isbn)) ThrowError("ISBN is not valid.");
    }

    bool Book::IsIsbnValid(const std::string &isbn)
    {
        std::regex isbnRegex("^(?:(?=.{17}$)([[:d:]]{3})-([[:d:]]{1,5})-([[:d:]]{1,7})-([[:d:]]){1,6}-([[:alnum:]])|(?=.{13}$)([[:d:]]{1,5})-([[:d:]]{1,7})-([[:d:]]){1,6}-([[:alnum:]]))$");
        return std::regex_match(isbn, isbnRegex);
    }

    std::ostream &operator<<(std::ostream &os, const Book &book)
    {
        return os << "Title: " << book.GetTitle() << '\n'
                << "Author: " << book.GetAuthor() << '\n'
                << "Genre: " << book.GetGenre() << '\n'
                << "Copyright date: " << book.GetCopyrightDate() << '\n'
                << "ISBN: " << book.GetIsbn() << '\n';
    }

    bool operator==(const Book &first, const Book &second) { return first.GetIsbn() == second.GetIsbn(); }

    bool operator!=(const Book &first, const Book &second) { return !(first == second); }
}