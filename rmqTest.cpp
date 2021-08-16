#include <cstdlib>

#include "rmqTest.h"

using namespace std;


// Shortcuts for types.
typedef int Num;


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

// Verifies that two RMQ algorithm create the same result.
// Randomly picks index pairs and compares the result.
bool RMQTest::verify(const RMQ<Num>& rmq1, const RMQ<Num>& rmq2, size_t dataSize, size_t querries)
{
    for (size_t q = 0; q < querries; q++)
    {
        size_t i = rand() % dataSize;
        size_t j = rand() % (dataSize - 1);

        if (i <= j) j++;
        if (i > j) swap(i, j);

        size_t min1 = rmq1(i, j);
        size_t min2 = rmq2(i, j);

        if (min1 != min2) return false;
    }

    return true;
}
