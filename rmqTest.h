// Defines functions to compare the correctnes and runtime of RMQ algorithms.

#ifndef __RmqTest_HPP__
#define __RmqTest_HPP__


#include "rmq.hpp"
#include "plusMinusRmq.hpp"


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
    static bool verifyAlgorithms(size_t dataSize, size_t queries, unsigned seed)
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

        return verify(rmq1, rmq2, dataSize, queries);
    }


    // Determines the runtime of the given algorithm.
    // Returns the runtime for preprocessing and for queries.
    template<typename T>
    static TimePair getRuntime(size_t dataSize, size_t queries, unsigned seed)
    {
        static_assert(std::is_base_of<RMQ<Num>, T>::value, "T must inherit from RMQ<>.");

        // Generade random numbers.
        vector<Num> data = generateData(dataSize, seed);

        // Run test.
        T rmq(data);
        return getRuntime(rmq, dataSize, queries);
    }


    // Verifies that two RMQ algorithm create the same result.
    // Randomly picks index pairs and compares the result.
    template<typename T>
    static bool verifyPlusMinus(size_t dataSize, size_t queries, unsigned seed)
    {
        static_assert(std::is_base_of<RMQ<Num>, T>::value, "T must inherit from RMQ<>.");

        // Generade random numbers.
        vector<Num> data = generatePlusMinus(dataSize, seed);

        // Generate and test algorithms.
        PlusMinusRMQ<Num> rmq1(data);
        T rmq2(data);

        rmq1.processData();
        rmq2.processData();

        return verify(rmq1, rmq2, dataSize, queries);
    }

    // Determines the runtime of the given algorithm.
    // Returns the runtime for preprocessing and for queries.
    static TimePair getPlusMinusRuntime(size_t dataSize, size_t queries, unsigned seed)
    {
        // Generade random numbers.
        vector<Num> data = generatePlusMinus(dataSize, seed);

        // Run test.
        PlusMinusRMQ<Num> rmq(data);
        return getRuntime(rmq, dataSize, queries);
    }


private:

    // Generates a list of random numbers with the given size.
    static vector<Num> generateData(size_t size, unsigned seed);

    // Generates a list of random numbers that satisfy the +-1 property.
    static vector<Num> generatePlusMinus(size_t size, unsigned seed);

    // Generates a random tree of the given size.
    static Tree generateTree(size_t size, unsigned seed);


    // Verifies that two RMQ algorithm create the same result.
    // Randomly picks index pairs and compares the result.
    static bool verify(const RMQ<Num>& rmq1, const RMQ<Num>& rmq2, size_t dataSize, size_t queries);

    // Meassures the time needed to preprocess and to run queries unsing the
    // given RMQ algorithm.
    static TimePair getRuntime(RMQ<Num>& rmq, size_t dataSize, size_t queries);
};

#endif
