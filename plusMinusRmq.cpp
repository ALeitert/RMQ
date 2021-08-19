#include "plusMinusRmq.h"

#include "log.hpp"


// Constructor.
PlusMinusRMQ::PlusMinusRMQ(const vector<number>& data) :
    RMQ<number>(data)
{
    /* Nothing. */
}

// Pre-processes the data to allow queries.
void PlusMinusRMQ::processData()
{
    const vector<number> data = this->data;
    const size_t    n    = this->data.size();

    // Determine block size.
    {
        // The paper defines block size as 1/2 log n. We divert from that
        // slightly and use the largerst power of 2 not larger than 1/2 log n.
        // That is, we want the largest k such that
        //     2^k in [1/2 log n, 1/4 log n).
        // Note that his is equivalent to
        //     2^{k + 1} in [log n, 1/2 log n).

        size_t logN = logF(n);
        size_t k    = logF(logN) - 1;

        blockSize = 1 << k;

        blockDiv = k;
        blockMod = blockSize;
    }
}


// Performs a query on the given data and given range.
// Returns the index of the minimum in that range.
// Behaviour is undefined if the given range is invalid or pre-processing
// has not been done.
size_t PlusMinusRMQ::operator()(size_t i, size_t j) const
{
}
