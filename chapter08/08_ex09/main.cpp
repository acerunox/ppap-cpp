/*
Exercise 09: Write a function that given two vector<double>s price and weight computes a value (an “index”) that is the sum of all price[i]*weight[i].
             Make sure to have weight.size()==price.size().
*/

#include "../../lib/utilities.h"
#include <iostream>
#include <vector>

double ComputePriceWeightIndex(const std::vector<double> &prices, const std::vector<double> &weights)
{
    if (prices.size() != weights.size()) ThrowError("[ERROR] Amount of prices and weights has to be the same.");
    
    double sum = 0;
    for (int i = 0; i < prices.size(); ++i)
    {
        sum += prices[i] * weights[i];
    }
    return sum;
}

int main()
{
    std::vector<double> prices{ 5, 10, 13, 9, 21 };
    std::vector<double> weights{ 1, 2, 3, 5, 7 };
    try
    {
        std::cout << ComputePriceWeightIndex(prices, weights) << '\n';
    }
    catch (std::runtime_error& err)
    {
        std::cerr << err.what() << '\n';
    }
}