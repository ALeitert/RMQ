// Represents the base class for all RMQ algorithms.

#ifndef __RMQ_HPP__
#define __RMQ_HPP__


#include <vector>


template<typename T>
class RMQ
{
public:

    // Constructor.
    RMQ(const std::vector<T>& data) : data(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    virtual void processData() = 0;

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    virtual size_t operator()(size_t i, size_t j) const = 0;


protected:

    // The sequence to run queries against.
    const std::vector<T>& data;
};

#endif
