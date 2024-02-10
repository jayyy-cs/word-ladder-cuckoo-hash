#include "Wordset.hpp"

#include <string>

namespace shindler::ics46::project3 {

// returns s, as a number in the given base, mod the given modulus
size_t polynomialHashFunction(const std::string &string, unsigned int base,
                              unsigned int mod) {
    size_t hashValue = 0;
    for (char c : string)
    {
        hashValue = (hashValue * base + (c - 'a' + 1)) % mod;
    }

    return hashValue;
}


}  // namespace shindler::ics46::project3
