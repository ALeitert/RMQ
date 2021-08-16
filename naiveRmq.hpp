// Represents a RMQ with an almost naive preprocessing.
// Runtime: O(n^2) | O(1)

#ifndef __NaiveRmq_HPP__
#define __NaiveRmq_HPP__


#include "rmq.hpp"


template<typename T>
class NaiveRMQ : public RMQ<T>
{
    // Shortcut for vector class. (Avoids need for "std::" each time.)
    template<typename X> using vector = std::vector<X>;

public:

    // Constructor.
    NaiveRMQ(const vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    void processData()
    {
        const size_t n = this->data.size();

        table.clear();
        table.resize(n, vector<size_t>(n));


        // --- Compute all results. ---

        for (size_t i = 0; i < n; i++)
        {
            // Base case.
            table[i][i] = i;

            for (size_t j = i + 1; j < n; j++)
            {
                // Recursive call.
                size_t minIdx = this->minIndex(table[i][j - 1], j);

                table[i][j] = minIdx;
                table[j][i] = minIdx;
            }
        }
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
        return table[i][j];
    }


private:

    // Look-up table containing the processed data.
    vector<vector<size_t>> table;
};

#endif
