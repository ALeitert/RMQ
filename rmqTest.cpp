#include <cstdlib>

#include "rmqTest.h"


// Shortcuts for types.
typedef int Num;
template<typename X> using vector = std::vector<X>;


// Anonymous namespace with helper functions.
namespace
{
    // Computes the logarithm base 2 of the given number.
    inline unsigned LogF(size_t x)
    {
        return (sizeof(unsigned long long) << 3) - __builtin_clzll(x) - 1;
    }
}


// Generates a list of random numbers with the given size.
vector<Num> RMQTest::generateData(size_t size, unsigned seed)
{
    srand(seed);

    size_t maxVal = size * LogF(size);
    size_t shift = maxVal >> 2;


    vector<Num> data(size);

    for (size_t i = 0; i < size; i++)
    {
        data[i] = rand() % maxVal - shift;
    }

    return data;
}
