// Represents a RMQ without pre-processing by simply iterating over the given
// range.

#ifndef __NoPreRmq_H__
#define __NoPreRmq_H__


#include "rmq.h"


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
        // Shortcut to access data.
        const std::vector<T>& data = this->data;

        // First entry is default minimum.
        size_t minIdx = i;

        for (size_t idx = i + 1; idx <= j; idx++)
        {
            if (data[idx] < data[minIdx])
            {
                minIdx = idx;
            }
        }

        return minIdx;
    }
};

#endif
