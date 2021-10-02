// Represents an RMQ algorithm that uses LCA.
// Runtime: O(n) | O(1)

#ifndef __LcaRmq_HPP__
#define __LcaRmq_HPP__


#include "rmq.hpp"


template<typename T>
class LcaRMQ : public RMQ<T>
{
public:

    // Constructor.
    LcaRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }

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
        return -1;
    }
};

#endif
