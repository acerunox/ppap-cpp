/*
Exercise 12: Reverse the order of characters in a text file. 
             For example, asdfghjkl becomes lkjhgfdsa. 
             Warning: There is no really good, portable, and efficient way of reading a file backward.
*/

#include "../../lib/utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>

enum class Choice { YES = 'y', NO = 'n' };

std::istream &operator>>(std::istream &is, Choice &choice)
{
    char input;
    is >> input;
    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    input = std::tolower(input);
    choice = Choice(input);
    return is;
}

void ReverseFileContent(const std::string &filePath)
{
    std::ifstream inputStream{filePath, std::ios_base::binary};
    if (!inputStream) ThrowError("Failed to open input file '" + filePath + "'.");

    //Get file length
    inputStream.seekg(0, inputStream.end);
    int fileLength = inputStream.tellg();
    inputStream.seekg(0, inputStream.beg);

    //Set the sizes of chunks
    size_t chunkSize = 1<<12;
    char *chunk = new char[chunkSize];
    
    std::ostringstream result;
    std::ostringstream tempBuffer{std::ios_base::ate};
   
    while (inputStream)
    {
        inputStream.read(chunk, chunkSize);
        size_t count = inputStream.gcount();
        if (!count) break;

        std::string currentChunk {chunk, count};
        std::reverse(currentChunk.begin(), currentChunk.end());
        
        tempBuffer.str(currentChunk);
        tempBuffer << result.str();
        result.str(tempBuffer.str());
    }

    inputStream.close();
    delete[] chunk;

    std::ofstream outputStream{filePath, std::ios_base::binary};
    if (!outputStream) ThrowError("Failed to open output file '" + filePath + "'.");
    
    outputStream << result.str();
}

int main()
{
    try
    {
        std::cout << "Enter the file path: ";
        std::string filePath;
        std::cin >> filePath;

        std::cout << "This might make the file unreadable.\n"
                  << "Are you sure you want to reverse the content of '" << filePath << "'? (y/n): ";
        Choice choice;
        while(std::cin >> choice)
        {
            switch(choice)
            {
            case Choice::YES:
                ReverseFileContent(filePath);
                return EXIT_SUCCESS;

            case Choice::NO:
                return EXIT_SUCCESS;
            
            default:
                std::cout << "Unrecognized choice, please try again (y/n): ";
                continue;
            }
        }
    }
    catch(const std::runtime_error &err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
        return EXIT_FAILURE;
    }
}