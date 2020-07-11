#pragma once

#include "./Chrono.hpp"
#include <iostream>
#include <string>
#include <vector>

using Chrono::Date;

namespace BookLib
{
    enum class Genre { FICTION, NONFICTION, PERIODICAL, BIOGRAPHY, CHILDREN };
    static std::vector<std::string> genresList { "fiction", "nonfiction", "periodical", "biography", "children" };

    std::ostream &operator<<(std::ostream &os, const Genre &genre);
    std::istream &operator>>(std::istream &is, Genre &genre);

    class Book
    {
    public:
        Book(std::string isbn, std::string title, std::string author, Genre genre, Date copyrightDate);

        std::string GetIsbn() const { return isbn; }
        std::string GetTitle() const { return title; }
        std::string GetAuthor() const { return author; }
        Genre GetGenre() const { return genre; }
        Date GetCopyrightDate() const { return copyrightDate; }
        bool IsCheckedOut() const { return isCheckedOut; }

        void CheckOut() { isCheckedOut = true; }
        void CheckIn() { isCheckedOut = false; }

    private:
        std::string isbn;
        std::string title;
        std::string author;
        Genre genre;
        Date copyrightDate;
        bool isCheckedOut;

        bool IsIsbnValid(const std::string &isbn);
    };

    std::ostream &operator<<(std::ostream &os, const Book &book);
    bool operator==(const Book &first, const Book &second);
    bool operator!=(const Book &first, const Book &second);
}