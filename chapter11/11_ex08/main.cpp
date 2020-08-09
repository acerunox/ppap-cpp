/*
Exercise 08: Use the program from the previous exercise to make a dictionary (as an alternative to the approach in §11.7).
             Run the result on a multi-page text file, look at the result, and see if you can improve the program to make a better dictionary.
*/

#include "../../lib/utilities.h"
#include "./CustomInputStream.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void PrintVectorToFile(const std::vector<std::string> &vector, const std::string &filePath)
{
    std::ofstream outputFile{filePath};
    if (!outputFile) ThrowError("Failed to open output file '" + filePath + "'.");

    for (int i = 0; i < vector.size(); ++i)
    {
        if (i == vector.size() - 1) outputFile << vector[i];
        else outputFile << vector[i] << '\n';
    }
}

int main()
{
    try
    {
        std::cout << "Enter source file path: ";
        std::string sourceFilePath;
        std::cin >> sourceFilePath;
        std::ifstream sourceFileStream{sourceFilePath};

        CustomInputStream inputStream{sourceFileStream, false};
        inputStream.SetWhitespace(".;,?-'\"");

        std::vector<std::string> dictionary;
        std::string line;
        
        while (inputStream >> line)
        {
            std::istringstream stringStream{line};
            for (std::string word; stringStream >> word;)
            {
                if (std::find(dictionary.begin(), dictionary.end(), word) == dictionary.end()) dictionary.push_back(word);
            }
        }

        std::sort(dictionary.begin(), dictionary.end());
        PrintVectorToFile(dictionary, "./dictionary.txt");
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
}