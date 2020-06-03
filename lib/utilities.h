#include <stdexcept>
#include <string>

inline void ThrowError(std::string message) { throw std::runtime_error(message); }
inline void ThrowError(std::string first, std::string second) { throw std::runtime_error(first + second); }