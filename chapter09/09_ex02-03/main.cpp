/*
Exercise 02: Design and implement a Name_pairs class holding (name,age) pairs where name is a string and age is a double.
             Represent that as a vector<string> (called name) and a vector<double> (called age) member.
             Provide an input operation read_names() that reads a series of names.
             Provide a read_ages() operation that prompts the user for an age for each name.
             Provide a print() operation that prints out the (name[i],age[i]) pairs (one per line) in the order determined by the name vector.
             Provide a sort() operation that sorts the name vector in alphabetical order and reorganizes the age vector to match.
             Implement all “operations” as member functions

Exercise 03: Replace Name_pair::print() with a (global) operator << and define == and != for Name_pairs.

NOTE: I basically did this exercise before in the same way as described here, so I just copied the code and changed some things.
      Name_pairs is Database instead.
*/

#include "Database.hpp"
#include <iostream>
#include <stdexcept>

int main()
{
    try 
    {
        Database database;

        database.AddNames();
        database.AddAges();

        std::cout << "\nUnsorted: " << '\n' << database;

        database.SortNamesAndAges();
        std::cout << "\nSorted: " << '\n' << database;
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}