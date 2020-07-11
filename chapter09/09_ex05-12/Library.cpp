#include "./Library.hpp"
#include "./Book.hpp"
#include "./Chrono.hpp"
#include "../../lib/utilities.h"
#include <algorithm>
#include <iostream>

using namespace BookLib;
using Chrono::CurrentDate;

std::istream &operator>>(std::istream& is, TransactionType& type)
{
    std::string input;
    std::cin >> input;
    
    auto iter = std::find(transactionTypesList.begin(), transactionTypesList.end(), input);
    if (iter == transactionTypesList.end()) 
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    else 
    {
        int index = std::distance(transactionTypesList.begin(), iter);
        type = TransactionType(index);
        return is;
    }
}

void Library::AddBook()
{
    std::cout << "Enter ISBN10 or ISBN13: ";
    std::string isbn;
    getline(std::cin, isbn);

    std::cout << "Enter title: ";
    std::string title;
    getline(std::cin, title);

    std::cout << "Enter author: ";
    std::string author;
    getline(std::cin, author);

    std::cout << "List of genres: ";
    for (int i = 0; i < genresList.size(); ++i)
    {
        if (i == genresList.size() - 1) std::cout << genresList[i] << '\n';
        else std::cout << genresList[i] << ", ";
    }

    std::cout << "Enter genre: ";
    Genre genre;
    std::cin >> genre;
    std::cin.ignore();

    std::cout << "Enter date (day-month-year): ";
    Date date;
    try
    {
        std::cin >> date;
        //std::cin.ignore();

        books.push_back(Book{ isbn, title, author, genre, date });
    }
    catch (std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << "\n";
        std::cerr << "[ERROR] Adding a new book has failed.\n";
    }
}

void Library::AddPatron()
{
    std::cout << "Enter name: ";
    std::string name;
    getline(std::cin, name);

    int card_number = 1;    //first patron always has number 1
    if (patrons.size() != 0)
    {
        card_number = patrons.back().GetCardNumber();
        ++card_number;
    }

    patrons.push_back(Patron{ name, card_number });
}

void Library::AddNewTransaction(const TransactionType &type, const Patron &patron, Book *bookPtr)
{
    switch (type)
    {
    case TransactionType::CHECKOUT:
        if (IsOwingFees(patron)) ThrowError("Couldn't check out, patron owes fees.");
        if (bookPtr->IsCheckedOut()) ThrowError("Couldn't check out, book is already checked out.");
        bookPtr->CheckOut();
        break;

    case TransactionType::CHECKIN:
        bookPtr->CheckIn();
        break;

    default:
        ThrowError("Unknown transaction type.");
    }
    
    Book book = *bookPtr;
    transactions.push_back(Transaction{ type, book, patron, CurrentDate() });
}

std::vector<std::string> Library::GetNamesOfPatronsOwingFees() const
{
    std::vector<std::string> names;
    for (const Patron &patron : patrons)
    {
        if (IsOwingFees(patron)) names.push_back(patron.GetName());
    }

    if (names.size() == 0) ThrowError("No patrons are owing fees.");
    else return names;
}

Book *Library::FindBook(const std::string &isbn)
{
    if (books.size() == 0) ThrowError("No books in library.");
    for (Book &book : books)
    {
        if (book.GetIsbn() == isbn) 
        {
            return &book;
        }
    }
    ThrowError("No book with ISBN " + isbn, ".");
}

Patron Library::FindPatron(const int &cardNumber)
{
    if (patrons.size() == 0) ThrowError("No patrons in library.");
    for (const Patron &patron : patrons)
    {
        if (patron.GetCardNumber() == cardNumber) return patron;
    }
    ThrowError("No patron with card number " + cardNumber, ".");
}

void Library::PrintAllTransactions()
{
    if (transactions.size() == 0) 
    {
        std::cerr << "[ERROR] No transactions were made.";
        return;
    }

    for (int i = 0; i < transactions.size(); ++i)
    {
        std::cout << "* Transaction No." << i + 1 << " *\n"
                  << "Type: " << transactionTypesList[int(transactions[i].GetType())] << '\n'
                  << "Date: " << transactions[i].GetDate() << "\n\n"
                  << "-- Book --" << '\n' << transactions[i].GetBook() << '\n'
                  << "-- Patron --" << '\n' << transactions[i].GetPatron() << '\n';
    }
}

Library::Transaction::Transaction(TransactionType type, Book book, Patron patron, Date date) 
                    : type(type), book(book), patron(patron), date(date) {}