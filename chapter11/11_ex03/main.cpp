/*
Exercise 03: Write a program that removes all vowels from a file (“disemvowels”). For example, Once upon a time! becomes nc pn tm!.
*/

#include "../../lib/utilities.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

void CopyFile(const std::string &inputFilePath, const std::string &outputFilePath, bool shouldRemoveInputFile = false)
{
    std::ifstream source{inputFilePath, std::ios::binary};
    if (!source) ThrowError("Failed to open input file '" + inputFilePath + "'.\n");

    std::ofstream destination{outputFilePath, std::ios::binary};
    if (!destination) ThrowError("Failed to open output file '" + outputFilePath + "'.\n");

    destination << source.rdbuf();
    if (shouldRemoveInputFile) 
    {
        source.close();
        if(std::remove(inputFilePath.c_str()) != 0)
        {
            std::cerr << "Failed to delete the input file!";
        }
    }
}

void DisemvowelWord(std::string &word)
{
    const std::string vowels = "aeiou";

    for (const char &vowel : vowels)
    {
        while (auto iter = word.find(vowel))
        {
            if (iter == std::string::npos) break;
            else word.replace(iter, 1, "");
        }
    }
}

void DisemvowelFile(const std::string &filePath)
{
    std::ifstream inputFileStream{filePath};
    if (!inputFileStream) ThrowError("Failed to open input file '" + filePath + "'.\n");

    enum class Choice { YES = 'y', NO = 'n'};
    std::cout << "Are you sure you want to disemvowel this file? ALL CONTENT WILL BE REPLACED (y/n): ";
    char userChoice;
    while(std::cin >> userChoice)
    {
        switch (Choice(userChoice))
        {
        case Choice::YES:
        {
            const std::string tempFilePath = "./temp.txt";
            std::ofstream tempOutput{tempFilePath};
            std::string word;
            while (inputFileStream >> word) 
            {
                DisemvowelWord(word);
                if (inputFileStream.peek() != std::ios_base::eofbit) tempOutput << word << ' ';
                else tempOutput << word;
            }

            tempOutput.close();
            inputFileStream.close();
            CopyFile(tempFilePath, filePath, true);
            return;
        }
        
        case Choice::NO:
            std::cout << "Terminating program...\n";
            return;

        default:
            std::cerr << "Please type either 'y' for yes or 'n' for no: ";
            continue;
        }
    }
}

int main()
{
    try
    {
        std::cout << "Enter input file path: ";
        std::string inputFilePath;
        std::cin >> inputFilePath;

        DisemvowelFile(inputFilePath);
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
    
}