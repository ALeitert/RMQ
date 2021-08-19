// Represents a RMQ for sequences that satisfy +_1 property.
// A sequence [x_1, x_2, ..., x_n] satisfies that property if, for all i < n,
// |x_i - x_{i + 1}| = 1. That is, consecutive elements differ by exactly 1.

// Runtime: O(n) | O(1)


#ifndef __PlusMinusRmq_H__
#define __PlusMinusRmq_H__


#include "rmq.hpp"


class PlusMinusRMQ : public RMQ<size_t>
{
public:

    // Constructor.
    PlusMinusRMQ(const std::vector<size_t>& data);

    // Pre-processes the data to allow queries.
    void processData();

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const;


private:

};

#endif
