#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<double> temps;
    for (double temp; std::cin >> temp;) temps.push_back(temp);

    double sum = 0;
    for (int x : temps) sum += x;
    std::cout << "Average temperature: " << sum/temps.size() << '\n';

    std::sort(temps.begin(), temps.end());
    std::cout << "Median temperature: ";
    
    double median = 0;
    if (temps.size() % 2 == 0)
    {
        median = (temps[temps.size() / 2 - 1] + temps[temps.size() / 2]) / 2;
    }
    else median = temps[temps.size() / 2];

    std::cout << median << '\n';
}