#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Please enter three integers, separated by space: ";
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    std::cin >> val1 >> val2 >> val3;
    std::vector<int> sequence{ val1, val2, val3 };
    
    std::sort(sequence.begin(), sequence.end());
    std::cout << sequence[0] << ", " << sequence[1] << ", " << sequence[2] << '\n';
}