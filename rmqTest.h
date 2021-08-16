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

    template<typename S, typename T>
    static void verifyAlgorithms(size_t dataSize, size_t querries, int seed)
    {
        static_assert(std::is_base_of<RMQ<Num>, S>::value, "S must inherit from RMQ<>.");
        static_assert(std::is_base_of<RMQ<Num>, T>::value, "T must inherit from RMQ<>.");


    }

    template<typename T>
    static TimePair getRuntime(size_t dataSize, size_t querries, int seed)
    {
        static_assert(std::is_base_of<RMQ<Num>, T>::value, "T must inherit from RMQ<>.");
    }


private:

    // Generates a list of random numbers with the given size.
    static vector<Num> generateData(size_t size);

    // Verifies that two RMQ algorithm create the same result.
    // Randomly picks index pairs and compares the result.
    static bool verify(RMQ<Num>& rmq1, RMQ<Num>& rmq2, size_t querries);

    // Meassures the time needed to preprocess and to run queries unsing the
    // given RMQ algorithm.
    static TimePair getRuntime(RMQ<Num>& rmq, size_t querries);
};

#endif
