// Represents a RMQ that uses a segment tree to run queries.
// Runtime: O(n) | O(log n)

#ifndef __SegTreeRmq_HPP__
#define __SegTreeRmq_HPP__


#include "rmq.hpp"


template<typename T>
class SegTreeRMQ : public RMQ<T>
{
public:

    // Constructor.
    SegTreeRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    void processData()
    {
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
    }
};

#endif
