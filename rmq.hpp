// Represents the base class for all RMQ algorithms.

#ifndef __RMQ_HPP__
#define __RMQ_HPP__


#include <vector>


template<typename T>
class RMQ
{
public:

    // The sequence to run queries against.
    const std::vector<T>& data;


    // Constructor.
    RMQ(const std::vector<T>& data) : data(data) { /* Nothing. */ }

    // Destructor.
    // Does not do anything but is still recommended.
    // See https://stackoverflow.com/a/1123159.
    virtual ~RMQ() { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    virtual void processData() { };

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    virtual size_t operator()(size_t, size_t) const { return 0; };


protected:

    // Determines which of these indices stores the smaller value.
    size_t minIndex(size_t i, size_t j) const
    {
        if (data[i] < data[j]) return i;
        else return j;
    }
};

#endif
