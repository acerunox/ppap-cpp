#pragma once

#include <random>
#include <stdexcept>
#include <string>

inline void ThrowError(std::string message) { throw std::runtime_error(message); }
inline void ThrowError(std::string first, std::string second) { throw std::runtime_error(first + second); }

inline double RandomInRange(const double &min, const double & max)
{
    std::random_device randomDevice;
    std::mt19937 mtEngine{randomDevice()};
    std::uniform_real_distribution<double> distribution{ min, max };
    return distribution(mtEngine);
}

inline int RandomInRange(const int &min, const int &max)
{
    std::random_device randomDevice;
    std::mt19937 mtEngine{randomDevice()};
    std::uniform_int_distribution<int> distribution{ min, max };
    return distribution(mtEngine);
}