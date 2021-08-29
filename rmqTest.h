// Defines functions to compare the correctnes and runtime of RMQ algorithms.

#ifndef __RmqTest_HPP__
#define __RmqTest_HPP__


#include <chrono>

#include "lca.hpp"
#include "rmq.hpp"
#include "plusMinusRmq.hpp"


using namespace std::chrono;


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


    // Meassures the time needed to preprocess and to run queries unsing the
    // given RMQ algorithm.
    template<typename T>
    static TimePair getAncestorRuntime(size_t treeSize, size_t queries, unsigned seed)
    {
        static_assert(std::is_base_of<RMQ<size_t>, T>::value, "T must inherit from RMQ<size_t>.");

        Tree tree = generateTree(treeSize, seed);
        LCA<T> lca(tree);


        // Preprocessing
        size_t pTime = 0;
        {
            auto start = high_resolution_clock::now();

            lca.processData();

            auto end = high_resolution_clock::now();
            pTime = duration_cast<milliseconds>(end - start).count();
        }

        // Queries
        size_t qTime = 0;
        {
            auto start = high_resolution_clock::now();

            for (size_t q = 0; q < queries; q++)
            {
                size_t uId = rand() % treeSize;
                size_t vId = (uId + 1 + (rand() % (treeSize - 1))) % treeSize;

                lca(uId, vId);
            }

            auto end = high_resolution_clock::now();
            qTime = duration_cast<milliseconds>(end - start).count();
        }

        return TimePair(pTime, qTime);
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
