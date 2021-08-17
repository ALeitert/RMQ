#include <chrono>
#include <cstdlib>

#include "rmqTest.h"

using namespace std;
using namespace std::chrono;


// Shortcuts for types.
typedef int Num;
typedef std::pair<size_t, size_t> TimePair;


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
bool RMQTest::verify(const RMQ<Num>& rmq1, const RMQ<Num>& rmq2, size_t dataSize, size_t queries)
{
    const vector<Num>& data = rmq1.data;

    for (size_t q = 0; q < queries; q++)
    {
        size_t i = rand() % dataSize;
        size_t j = rand() % (dataSize - 1);

        if (i <= j) j++;
        if (i > j) swap(i, j);

        size_t min1 = rmq1(i, j);
        size_t min2 = rmq2(i, j);

        if (data[min1] != data[min2]) return false;
    }

    return true;
}

// Meassures the time needed to preprocess and to run queries unsing the
// given RMQ algorithm.
TimePair RMQTest::getRuntime(RMQ<Num>& rmq, size_t dataSize, size_t queries)
{
    // Preprocessing
    size_t pTime = 0;
    {
        auto start = high_resolution_clock::now();

        rmq.processData();

        auto end = high_resolution_clock::now();
        pTime = duration_cast<milliseconds>(end - start).count();
    }

    // Queries
    size_t qTime = 0;
    {
        auto start = high_resolution_clock::now();

        for (size_t q = 0; q < queries; q++)
        {
            size_t i = rand() % dataSize;
            size_t j = rand() % (dataSize - 1);

            if (i <= j) j++;
            if (i > j) swap(i, j);

            rmq(i, j);
        }

        auto end = high_resolution_clock::now();
        qTime = duration_cast<milliseconds>(end - start).count();
    }

    return TimePair(pTime, qTime);
}
