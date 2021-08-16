// Defines functions to compare the correctnes and runtime of RMQ algorithms.

#ifndef __RmqTest_HPP__
#define __RmqTest_HPP__


#include "rmq.hpp"


class RMQTest
{
    // The numeric type for testing.
    typedef int Num;

    // Used as result when making runtime tests.
    typedef std::pair<size_t, size_t> TimePair;

    // Shortcut for vector class. (Avoids need for "std::" each time.)
    template<typename X> using vector = std::vector<X>;


public:

    // Verifies that two RMQ algorithm create the same result.
    // Randomly picks index pairs and compares the result.
    template<typename S, typename T>
    static bool verifyAlgorithms(size_t dataSize, size_t querries, unsigned seed)
    {
        static_assert(std::is_base_of<RMQ<Num>, S>::value, "S must inherit from RMQ<>.");
        static_assert(std::is_base_of<RMQ<Num>, T>::value, "T must inherit from RMQ<>.");

        // Generade random numbers.
        vector<Num> data = generateData(dataSize, seed);

        // Generate and test algorithms.
        S rmq1(data);
        T rmq2(data);

        rmq1.processData();
        rmq2.processData();

        return verify(rmq1, rmq2, dataSize, querries);
    }

    // Determines the runtime of the given algorithm.
    // Returns the runtime for preprocessing and for querries.
    template<typename T>
    static TimePair getRuntime(size_t dataSize, size_t querries, unsigned seed)
    {
        static_assert(std::is_base_of<RMQ<Num>, T>::value, "T must inherit from RMQ<>.");

        // Generade random numbers.
        vector<Num> data = generateData(dataSize, seed);

        // Run test.
        return getRuntime(T(data), querries);
    }


private:

    // Generates a list of random numbers with the given size.
    static vector<Num> generateData(size_t size, unsigned seed);

    // Verifies that two RMQ algorithm create the same result.
    // Randomly picks index pairs and compares the result.
    static bool verify(const RMQ<Num>& rmq1, const RMQ<Num>& rmq2, size_t dataSize, size_t querries);

    // Meassures the time needed to preprocess and to run queries unsing the
    // given RMQ algorithm.
    static TimePair getRuntime(RMQ<Num>& rmq, size_t querries);
};

#endif
