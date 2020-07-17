/*
Drill: Start a program to work with points, discussed in §10.4.
       Begin by defining the data type Point that has two coordinate members x and y.
       Prompt the user to input seven (x,y) pairs. 
       As the data is entered, store it in a vector of Points called original_points.
       Print the data in original_points to see what it looks like.
       Open an ofstream and output each point to a file named mydata.txt.
       Close the ofstream and then open an ifstream for mydata.txt.
       Read the data from mydata.txt and store it in a new vector called processed_points.
       Print the data elements from both vectors.
       Compare the two vectors and print Something's wrong! if the number of elements or the values of elements differ.
*/

#include "./Point.hpp"
#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void InputPoints(std::vector<Point> &points, int amount)
{
    while (points.size() < amount)
    {
        std::cout << "Please enter a point (x, y): ";
        Point point;
        std::cin >> point;

        if (!std::cin)
        {
            std::cerr << "[ERROR] Something went wrong with input!\n";
            std::cin.clear();
        }
        else points.push_back(point);
    }
}

void WritePointsToFile(const std::vector<Point> &points, const std::string &fileName)
{
    std::ofstream ost{ fileName };
    if (!ost) ThrowError("Unable to open output file '" + fileName, "'.");

    for (int i = 0; i < points.size(); ++i) 
    {
        if (i == points.size() - 1) ost << points[i];
        else ost << points[i] << '\n';
    }
}

std::vector<Point> ReadPointsFromFile(const std::string &fileName)
{
    std::ifstream ist{ fileName };
    if (!ist) ThrowError("Unable to open input file '" + fileName, "'.");
    
    Point point;
    std::vector<Point> processedPoints;
    while (ist >> point) processedPoints.push_back(point);

    return processedPoints;
}

int main()
{
    try
    {
        std::vector<Point> originalPoints;
        InputPoints(originalPoints, 7);

        std::cout << "\nInputted points:\n";
        for (const Point &point : originalPoints) std::cout << point << '\n';

        std::string fileName = "chapter10/10_drill/mydata.txt";

        WritePointsToFile(originalPoints, fileName);
        std::vector<Point> processedPoints = ReadPointsFromFile(fileName);

        if (processedPoints.size() != originalPoints.size())
        {
            std::cerr << "[ERROR] Vectors are not equal.";
            return EXIT_FAILURE;
        }
        else
        {
            std::cout << "\nOriginal points:\n";
            for (const Point &point : originalPoints) std::cout << point << '\n';
            std::cout << "\nProcessed points:\n";
            for (const Point &point : processedPoints) std::cout << point << '\n';
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}