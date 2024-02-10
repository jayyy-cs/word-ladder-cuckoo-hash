#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP

#include <algorithm>
#include <string>
#include <type_traits>


namespace shindler::ics46::project3 {

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc.

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
[[nodiscard]] size_t polynomialHashFunction(const std::string &string,
                                            unsigned base, unsigned mod);

// These are value template parameters. You can pass in a value rather than a
// type into the parameter and use its value. This allows them to be set
// dynamically rather than having static constants within the class.
// Think of them as class constants (you can just use them like a variables
// named H1, H2, and EvictThreshold)
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
class BaseWordSet {
   private:
    size_t sizeChecker;
    size_t capacityChecker;
    std::string* table1;
    std::string* table2;
    

   public:
    explicit BaseWordSet(size_t initialCapacity);
    ~BaseWordSet();

    // You do not need to worry about implementing these. They are only
    // here to ensure that we let the compiler know these functions
    // should not exist.
    BaseWordSet(const BaseWordSet &) = delete;
    BaseWordSet(BaseWordSet &&) = delete;
    BaseWordSet &operator=(const BaseWordSet &) = delete;
    BaseWordSet &operator=(BaseWordSet &&) = delete;

    // adds the given string to the WordSet, so that any
    // future calls to contains(s) will return true, unless that is later
    // removed.
    void resize(); //resize and rehash

    bool isPrime(size_t num); //helper function to check if num is prime

    void insert(const std::string &string);

    [[nodiscard]] bool contains(const std::string &string) const;

    // return how many distinct strings are in the set
    [[nodiscard]] size_t size() const noexcept;

    // return how large the underlying array is.
    [[nodiscard]] size_t capacity() const noexcept;

    void erase(const std::string &string);
};

// You Should not use anything within the _impl namespace in your code.
// Instead reference the H1, H2, and EvictThreshold template parameters
namespace _impl {
const static unsigned int BASE_H1 = 37;
const static unsigned int BASE_H2 = 41;
const unsigned int BASE_EVICTION_THRESHOLD = 5;
}  // namespace _impl

// Add a usings statement with the default values for the project.
using WordSet =
    BaseWordSet<_impl::BASE_H1, _impl::BASE_H2, _impl::BASE_EVICTION_THRESHOLD>;

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::BaseWordSet(size_t initialCapacity)
: sizeChecker(0), capacityChecker(initialCapacity), table1(new std::string[initialCapacity]), table2(new std::string[initialCapacity])
{
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::~BaseWordSet() {
    delete[] table1;
    delete[] table2;
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::resize(){

    size_t newCapacity {2*capacityChecker};

    while(!isPrime(newCapacity))
    {
        newCapacity++;
    }

    std::string* newTable1 = new std::string[newCapacity];
    std::string* newTable2 = new std::string[newCapacity];

    for(size_t i = 0; i < capacityChecker; ++i)
    {

        if(!table1[i].empty())
        {
            size_t hashValue1 = polynomialHashFunction(table1[i], H1, newCapacity);
            size_t hashValue2 = polynomialHashFunction(table1[i], H2, newCapacity);

            while(!newTable1[hashValue1].empty())
            {
                std::swap(newTable1[hashValue1], table1[i]);
                hashValue2 = polynomialHashFunction(table1[i], H2, newCapacity);
                std::swap(newTable2[hashValue2], table1[i]);
                hashValue1 = polynomialHashFunction(table1[i], H1, newCapacity);
            }

            newTable1[hashValue1] = table1[i];
        }

        if(!table2[i].empty())
        {
            size_t hashValue1 = polynomialHashFunction(table2[i], H1, newCapacity);
            size_t hashValue2 = polynomialHashFunction(table2[i], H2, newCapacity);

            while(!newTable1[hashValue1].empty())
            {
                std::swap(newTable1[hashValue1], table2[i]);
                hashValue2 = polynomialHashFunction(table2[i], H2, newCapacity);
                std::swap(newTable2[hashValue2], table2[i]);
                hashValue1 = polynomialHashFunction(table2[i], H1, newCapacity);
            }

            newTable1[hashValue1] = table2[i];
        }

    }

    capacityChecker = newCapacity;

    delete[] table1;
    delete[] table2;
    table1 = newTable1;
    table2 = newTable2;

}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::isPrime(size_t num){
    if (num <= 1)
    {
        return false;
    }
        
    for (size_t i = 2; i * i <= num; i++)
    {
         if (num % i == 0)
        {
            return false;
        }
    }
    return true;

}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::insert(const std::string &string) {

    if(!contains(string))
    {
        size_t hashValue1 = polynomialHashFunction(string, H1, capacityChecker);
        size_t hashValue2 = polynomialHashFunction(string, H2, capacityChecker);
        size_t evictions = 0;
        std::string new_string {string};

        while (evictions < EvictThreshold)
        {
            if(evictions >= EvictThreshold)
            {
                break;
            }
            if (table1[hashValue1].empty())
            {
                table1[hashValue1] = new_string;
                ++sizeChecker;
                return;
            }
            
            std::swap(table1[hashValue1], new_string);
            ++evictions;

            hashValue2 = polynomialHashFunction(new_string, H2, capacityChecker);

            if(evictions >= EvictThreshold)
            {
                break;
            }
            if (table2[hashValue2].empty() && evictions < EvictThreshold)
            {
                table2[hashValue2] = new_string;
                ++sizeChecker;
                return;
            }

            std::swap(table2[hashValue2], new_string);
            ++evictions;

            hashValue1 = polynomialHashFunction(new_string, H1, capacityChecker);
        }

        resize();
        insert(new_string);
    }
    
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::contains(
    const std::string &string) const {

    size_t hashValue1 = polynomialHashFunction(string, H1, capacityChecker);
    size_t hashValue2 = polynomialHashFunction(string, H2, capacityChecker);

    return (table1[hashValue1] == string || table2[hashValue2] == string);
}

// return how many distinct strings are in the set
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::size() const noexcept {
    return sizeChecker;
}

// return how large the underlying array is.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::capacity() const noexcept {
    return capacityChecker;
}

// removes this word if it is in the wordset.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::erase(const std::string &string) {
    if(contains(string))
    {
        size_t hashValue1 = polynomialHashFunction(string, H1, capacityChecker);
        size_t hashValue2 = polynomialHashFunction(string, H2, capacityChecker);

        if(table1[hashValue1] == string)
        {
            table1[hashValue1].clear();
        }
        else if(table2[hashValue2] == string)
        {
            table2[hashValue2].clear();
        }
        --sizeChecker;
    }
    
}

}  // namespace shindler::ics46::project3

#endif
