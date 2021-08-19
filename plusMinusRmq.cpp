#include "plusMinusRmq.h"

using namespace std;


// Constructor.
PlusMinusRMQ::PlusMinusRMQ(const vector<size_t>& data) :
    RMQ<size_t>(data)
{
    /* Nothing. */
}

// Pre-processes the data to allow queries.
void PlusMinusRMQ::processData()
{
}


// Performs a query on the given data and given range.
// Returns the index of the minimum in that range.
// Behaviour is undefined if the given range is invalid or pre-processing
// has not been done.
size_t PlusMinusRMQ::operator()(size_t i, size_t j) const
{
}
