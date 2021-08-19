// Represents a RMQ without pre-processing by simply iterating over the given
// range.
// Runtime: O(n log n) | O(1)

#ifndef __SparseTableRmq_HPP__
#define __SparseTableRmq_HPP__


#include <algorithm>

#include "log.hpp"
#include "rmq.hpp"


template<typename T>
class SparseTableRMQ : public RMQ<T>
{
    // Shortcut to avoid the need for "std::".
    template<typename X> using vector = std::vector<X>;

public:

    // Constructor.
    SparseTableRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    void processData()
    {
        const vector<T>& data = this-> data;
        const size_t n = data.size();

        // Height of the table is floor(log n) + 1
        size_t tableHeight = logF(n) + 1;

        // We divert from the paper and have the height as first index and
        // length as second. That way, we always use the same vector instead
        // of two different ones; thereby inproving caching and improving the
        // runtime slightly.
        M.resize(tableHeight, vector<size_t>(n));

        for (size_t i = 0; i < n; i++)
        {
            M[0][i] = i;
        }

        for (size_t j = 1; j < tableHeight; j++)
        {
            for (size_t i = 0; i < n; i++)
            {
                // Compare the two ranges below:
                // M[j - 1, i] and M[j - 1, i + 2^{j - 1} - 1]

                // Check that right index is not out of range.
                size_t lIdx = i;
                size_t rIdx = std::min(n - 1, i + (1 << (j - 1)));

                size_t lMin = M[j - 1][lIdx];
                size_t rMin = M[j - 1][rIdx];

                M[j][i] = this->minIndex(lMin, rMin);
            }
        }
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
        // k = floor(log (j − i))
        size_t k = logF(j - i);

        // M[k, i]
        // M[k, j − 2^k + 1]

        size_t min1 = M[k][i];
        size_t min2 = M[k][j - (1 << k) + 1];

        return this->minIndex(min1, min2);
    }


private:

    // Table with minumums in various ranges.
    vector<vector<size_t>> M;
};

#endif
