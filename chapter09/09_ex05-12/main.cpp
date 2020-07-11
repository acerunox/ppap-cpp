/*
Exercise 05: This exercise and the next few require you to design and implement a Book class, such as you can imagine as part of software for a library.
             Class Book should have members for the ISBN, title, author, and copyright date.
             Also store data on whether or not the book is checked out.
             Create functions for returning those data values.
             Create functions for checkinga book in and out.
             Do simple validation of data entered into a Book; for example, accept ISBNs only of the form n-n-n-x where n is an integer and x is a digit or a letter.
             Store an ISBN as a string.

Exercise 06: Add operators for the Book class.
             Have the == operator check whether the ISBN numbers are the same for two books.
             Have != also compare the ISBN numbers.
             Have a << print out the title, author, and ISBN on separate lines.

Exercise 07: Create an enumerated type for the Book class called Genre.
             Have the types be fiction, nonfiction, periodical, biography, and children.
             Give each book a Genre and make appropriate changes to the Book constructor and member functions.

Exercise 08: Create a Patron class for the library.
             The class will have a user’s name, library card number, and library fees (if owed). 
             Have functions that access this data, as well as a function to set the fee of the user.
             Have a helper function that returns a Boolean (bool) depending on whether or not the user owes a fee.

Exercise 09: Create a Library class. Include vectors of Books and Patrons.
             Include a struct called Transaction. Have it include a Book, a Patron, and a Date from the chapter. Make a vector of Transactions.
             Create functions to add books to the library, add patrons to the library, and check out books.
             Whenever a user checks out a book, have the library make sure that both the user and the book are in the library. If they aren’t, report an error.
             Then check to make sure that the user owes no fees. If the user does, report an error.
             If not, create a Transaction, and place it in the vector of Transactions.
             Also write a function that will return a vector that contains the names of all Patrons who owe fees.

Exercise 10: Implement leapyear() from §9.8.

Exercise 11: Design and implement a set of useful helper functions for the Date class.
             Functions such as next_workday() (assume that any day that is not a Saturday or a Sunday is a workday)
             and week_of_year() (assume that week 1 is the week with January 1 in it and that the first day of a week is a Sunday).

Exercise 12: Change the representation of a Date to be the number of days since January 1, 1970 (known as day 0), represented as a long int, and re-implement the functions from §9.8.
             Be sure to reject dates outside the range we can represent that way (feel free to reject days before day 0, i.e., no negative days).
*/

#include "./Library.hpp"
#include "./Chrono.hpp"
#include <iostream>
#include <string>

using Chrono::Date;
using BookLib::Book;
using BookLib::Genre;

int main()
{
    try
    {
        Library library;
        std::cout << "Welcome to the library!\n";
        
        const std::string separator = "-------------------------";
        enum class Choice { ADDBOOK = '1', ADDPATRON, ADDTRANSACTION, GETBOOKS, GETPATRONS, GETNAMES, GETTRANSACTIONS, QUIT = 'q' };

        do
        {
            std::cout << "What do you wish to do?\n"
                      << "\t1. Add new book to library.\n"
                      << "\t2. Add new patron to library.\n"
                      << "\t3. Add new transaction.\n"
                      << "\t4. Get a list of books in library.\n"
                      << "\t5. Get a list of patrons in library.\n"
                      << "\t6. Get a list of names of patrons owing fees.\n"
                      << "\t7. Get a list of all transactions.\n"
                      << "\t'q' to quit\n";
            std::cout << "Enter your choice: ";

            char userChoice;
            std::cin >> userChoice;
            std::cin.ignore();

            switch (userChoice)
            {
            case char(Choice::ADDBOOK):
                library.AddBook();
                break;
                
            case char(Choice::ADDPATRON):
                library.AddPatron();
                break;

            case char(Choice::ADDTRANSACTION):
                std::cout << "Do you want to checkout or checkin?: ";
                TransactionType type;
                std::cin >> type;
                if (!std::cin)
                {
                    std::cerr << "[ERROR] Unrecognized option, try again.\n";
                    continue;
                }
                std::cin.ignore();

                try
                {
                    std::string bookIsbn;
                    std::cout << "Please enter book's ISBN: ";
                    std::cin >> bookIsbn;

                    int patronCardNumber = 1;
                    std::cout << "Please enter patron's card number: ";
                    std::cin >> patronCardNumber;

                    library.AddNewTransaction(TransactionType(type), library.FindPatron(patronCardNumber), library.FindBook(bookIsbn));
                    break;
                }
                catch (const std::exception &err)
                {
                    std::cerr << "[ERROR] " << err.what() << '\n';
                    std::cerr << "[ERROR] Adding transaction has failed, try again.\n";
                    continue;
                }

                break;

            case char(Choice::GETBOOKS):
            {
                std::cout << "\n---- LIST OF BOOKS ----\n";
                std::vector<Book> books = library.GetBooks();
                for (const auto& book : books) std::cout << book << '\n'; 
                std::cout << separator;
                break;
            }

            case char(Choice::GETPATRONS):
            {
                std::cout << "\n---- LIST OF PATRONS ----\n";
                std::vector<Patron> patrons = library.GetPatrons();
                for (const auto& patron : patrons) std::cout << patron << '\n'; 
                std::cout << separator;
                break;
            }

            case char(Choice::GETNAMES):
                try
                {
                    std::cout << "\n---- LIST OF PATRONS WITH FEES ----\n";
                    std::vector<std::string> names = library.GetNamesOfPatronsOwingFees();
                    for (const auto& name : names) std::cout << name << '\n'; 
                    std::cout << separator;
                    break;
                }
                catch(const std::exception &err)
                {
                    std::cerr << "[ERROR] " << err.what() << '\n';
                    std::cerr << "[ERROR] Returning a list of names has failed, try again.\n";
                    continue;
                }

            case char(Choice::GETTRANSACTIONS):
                std::cout << "\n---- LIST OF TRANSACTIONS ----\n";
                library.PrintAllTransactions();
                break;

            case char(Choice::QUIT):
                return EXIT_SUCCESS;

            default:
                std::cerr << "[ERROR] Unrecognized choice, try again.\n";
                continue;
            }
            std::cout << '\n';
        } while (true);
    }
    catch(const std::exception &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
        return EXIT_FAILURE;
    }
}