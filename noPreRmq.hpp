// Represents a RMQ without pre-processing by simply iterating over the given
// range.
// Runtime: O(1) | O(k)

#ifndef __NoPreRmq_HPP__
#define __NoPreRmq_HPP__


#include "rmq.hpp"


template<typename T>
class NoPreRMQ : public RMQ<T>
{
public:

    // Constructor.
    NoPreRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    void processData() { /* Nothing. */ }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
        // First entry is default minimum.
        size_t minIdx = i;

        for (size_t idx = i + 1; idx <= j; idx++)
        {
            minIdx = this->minIndex(minIdx, idx);
        }

        return minIdx;
    }
};

#endif
