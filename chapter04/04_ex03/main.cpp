#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    double distance = 0;
    std::vector<double> distanceList;
    double sum = 0;

    std::cout << "Please enter a value: ";
    while (std::cin >> distance)
    {
        distanceList.push_back(distance);
        sum += distance;
        std::cout << "Please enter another value: ";
    }

    std::sort(distanceList.begin(), distanceList.end());
    std::cout << "The sum of all distances: " << sum << '\n'
              << "The smallest distance: " << distanceList.front() << '\n'
              << "The greatest distance: " << distanceList.back() << '\n'
              << "The mean distance: " << sum / distanceList.size() << '\n';
}