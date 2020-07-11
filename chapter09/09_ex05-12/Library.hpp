#pragma once

#include "./Book.hpp"
#include "./Patron.hpp"
#include "./Chrono.hpp"
#include <string>
#include <vector>

using BookLib::Book;

enum class TransactionType { CHECKOUT, CHECKIN };
static std::vector<std::string> transactionTypesList { "checkout", "checkin" };
std::istream &operator>>(std::istream& is, TransactionType& type);

class Library 
{
public:
    void AddBook();
    void AddPatron();
    void AddNewTransaction(const TransactionType &type, const Patron &patron, Book *bookPtr);
    std::vector<Book> GetBooks() const { return books; }
    std::vector<Patron> GetPatrons() const { return patrons; }
    std::vector<std::string> GetNamesOfPatronsOwingFees() const;
    Book *FindBook(const std::string &isbn);
    Patron FindPatron(const int &cardNumber);
    void PrintAllTransactions();

private:
    struct Transaction
    {
    public:
        Transaction(TransactionType type, Book book, Patron patron, Date date);
        TransactionType GetType() const { return type; }
        Book GetBook() const { return book; }
        Patron GetPatron() const { return patron; }
        Date GetDate() const { return date; }

    private:
        TransactionType type;
        Book book;
        Patron patron;
        Date date;
    };

    std::vector<Book> books;
    std::vector<Patron> patrons;
    std::vector<Transaction> transactions;
};