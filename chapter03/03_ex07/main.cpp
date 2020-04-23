#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Please enter three strings, separated by space: ";
    std::string str1, str2, str3;
    std::cin >> str1 >> str2 >> str3;
    std::vector<std::string> sequence{ str1, str2, str3 };
    
    std::sort(sequence.begin(), sequence.end());
    std::cout << sequence[0] << ", " << sequence[1] << ", " << sequence[2] << '\n';
}