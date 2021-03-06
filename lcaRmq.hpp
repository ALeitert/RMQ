// Represents an RMQ algorithm that uses LCA.
// Runtime: O(n) | O(1)

#ifndef __LcaRmq_HPP__
#define __LcaRmq_HPP__


#include "lca.hpp"
#include "plusMinusRmq.hpp"
#include "rmq.hpp"


template<typename T>
class LcaRMQ : public RMQ<T>
{
    // Shortcut to avoid the need for "std::".
    template<typename X> using vector = std::vector<X>;

public:

    // Constructor.
    LcaRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }

    // Destructor.
    ~LcaRMQ()
    {
        if (lca != nullptr) delete lca;
    }

    // Pre-processes the data to allow queries.
    void processData()
    {
        Tree t = buildTree();
        lca = new LCA<PlusMinusRMQ<size_t>>(t);
        lca->processData();
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
        return (*lca)(i, j);
    }


private:

    // The LCA algorithm used.
    LCA<PlusMinusRMQ<size_t>>* lca = nullptr;


    // Helper function that builds a Cartesian Tree from the given data.
    Tree buildTree()
    {
        const vector<T> data = this->data;
        const size_t    n    = this->data.size();


        vector<size_t> par(n, Tree::NullNode);

        for (size_t i = 1; i < n; i++)
        {
            size_t lar = i;
            size_t sml = i - 1;

            while (sml != Tree::NullNode && data[i] < data[sml])
            {
                lar = sml;
                sml = par[sml];
            }

            par[lar] = i;
            par[i] = sml;
        }

        return Tree(par);
    }
};

#endif
