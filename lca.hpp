// Defines an algorithm to find the lowest common ancestor of two nodes in a
// tree using a given RMQ algorithm.


#ifndef __LCA_HPP__
#define __LCA_HPP__

#include "rmq.hpp"
#include "tree.h"


template
<
    typename T,
    // Only allow integer types (excluding bool).
    typename = typename std::enable_if
    <
        std::is_base_of<RMQ<size_t>, T>::value,
        T
    >::type
>
class LCA
{

public:

    // Default constructor.
    LCA() = default;

    LCA(const Tree& tree) : tree(tree) { }

    ~LCA()
    {
        if (rmqPtr != nullptr) delete rmqPtr;
    }


    // Pre-processes the data to allow queries.
    void processTree()
    {
        et = tree.eulerTour();
        rmqPtr = new T(et.L);
        rmqPtr->processData();
    };

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t uId, size_t vId) const
    {
        const size_t& rU = et.R[uId];
        const size_t& rV = et.R[vId];

        // Ensure that i <= j.
        size_t i = std::min(rU, rV);
        size_t j = std::max(rU, rV);

        // Sometimes slightly faster.
        // size_t i = rV ^ ((rU ^ rV) & -(rU < rV)); // min(rV, rU)
        // size_t j = rU ^ ((rU ^ rV) & -(rU < rV)); // max(rV, rU)

        // LCA(u, v) = E[rmq(R[u], R[v])]
        T& rmq = *rmqPtr;
        return et.E[rmq(i, j)];
    };

private:

    const Tree& tree;

    EulerTour et;

    T* rmqPtr = nullptr;

};

#endif
