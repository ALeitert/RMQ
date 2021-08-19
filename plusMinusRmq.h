// Represents a RMQ for sequences that satisfy +_1 property.
// A sequence [x_1, x_2, ..., x_n] satisfies that property if, for all i < n,
// |x_i - x_{i + 1}| = 1. That is, consecutive elements differ by exactly 1.

// Runtime: O(n) | O(1)


#ifndef __PlusMinusRmq_H__
#define __PlusMinusRmq_H__


#include "rmq.hpp"
#include "sparseTableRmq.hpp"


class PlusMinusRMQ : public RMQ<int>
{
    // The numberic type used for the data.
    // Has to be equal to type used for RMQ base class.
    typedef int number;

    // Shortcut to avoid the need for "std::".
    template<typename X> using vector = std::vector<X>;


public:

    // Constructor.
    PlusMinusRMQ(const std::vector<number>& data);

    // Destructor.
    ~PlusMinusRMQ();


    // Pre-processes the data to allow queries.
    void processData();

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const;


private:

    // Performs a query on the given block and given range.
    // Returns the index of the minimum entry in that range with respect to the
    // original data.
    size_t inBlockMin(size_t b, size_t i, size_t j) const;


    // States how large a single block of the data is.
    // Defined as 1/2 * log n.
    size_t blockSize = 0;

    // Since we make the block size a power of two, we store helper for easy
    // division and modulo operations.
    size_t blockDiv = 0;
    size_t blockMod = 0;


    // The minimum of each block (A' in the paper).
    vector<number> blockMinVal;

    // The index of each block's minimum in the original data (B in the paper).
    vector<size_t> blockMinIdx;

    // A RMQ to find the minimum block.
    SparseTableRMQ<number>* tableRmq = nullptr;


    // States for each block, what class it is.
    vector<size_t> blockCls;

    // Allows to determine the minimum in a single block.
    vector<SparseTableRMQ<number>*> classRmq;

    // The data for each class. These are copies of the original data.
    vector<vector<number>> classData;

};

#endif
