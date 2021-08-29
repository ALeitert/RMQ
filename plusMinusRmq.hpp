// Represents a RMQ for sequences that satisfy +_1 property.
// A sequence [x_1, x_2, ..., x_n] satisfies that property if, for all i < n,
// |x_i - x_{i + 1}| = 1. That is, consecutive elements differ by exactly 1.

// Runtime: O(n) | O(1)


#ifndef __PlusMinusRmq_H__
#define __PlusMinusRmq_H__


#include "rmq.hpp"
#include "sparseTableRmq.hpp"


template
<
    typename T,
    // Only allow integer types (excluding bool).
    typename = typename std::enable_if
    <
        std::is_integral<T>::value && !std::is_same<T, bool>::value,
        T
    >::type
>
class PlusMinusRMQ : public RMQ<T>
{
    // Shortcut to avoid the need for "std::".
    template<typename X> using vector = std::vector<X>;


public:

    // Constructor.
    PlusMinusRMQ(const vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }

    // Destructor.
    ~PlusMinusRMQ()
    {
        if (tableRmq != nullptr) delete tableRmq;

        for (SparseTableRMQ<T>*& ptr : classRmq)
        {
            if (ptr != nullptr) delete ptr;
        }
    }


    // Pre-processes the data to allow queries.
    void processData()
    {
        const vector<T> data = this->data;
        const size_t    n    = this->data.size();

        // Determine block size.
        {
            // The paper defines block size as 1/2 log n. We divert from that
            // and use the largerst power of 2 not larger than 1/2 log n.
            // That is, we want the largest k such that
            //     2^k in [1/2 log n, 1/4 log n).
            // Note that this is equivalent to
            //     2^{k + 1} in [log n, 1/2 log n).

            size_t logN = logF(n);
            size_t k    = logF(logN) - 1;

            blockSize = 1 << k;

            blockDiv = k;
            blockMod = blockSize - 1;
        }


        // --- Determine minimum in each block. ---

        size_t blockCount = (n + 1) >> blockDiv;
        {
            blockMinVal.reserve(blockCount);
            blockMinIdx.reserve(blockCount);

            for (size_t b = 0, i = 0; i < n; b++)
            {
                // b: The current block index.
                // i: The current element in data[].

                blockMinVal.push_back(data[i]);
                blockMinIdx.push_back(i);
                i++;

                T& curMin = blockMinVal[b];
                size_t& curIdx = blockMinIdx[b];

                for (size_t j = 1; j < blockSize && i < n; i++, j++)
                {
                    // j: The current index in the current block.

                    if (data[i] < curMin)
                    {
                        curMin = data[i];
                        curIdx = i;
                    }
                }
            }

            // Create RMQ over blocks.
            tableRmq = new SparseTableRMQ<T>(blockMinVal);
            tableRmq->processData();
        }


        // --- Classify blocks. ---

        // Notethat we do not need to handle the last block B as special case as
        // long as we classify it last. If its class is unique, it will be
        // processed automatically. If it has the same class as a previous block,
        // we still only run queries on a range fitting to B which is still
        // equivalent to a query on the earlier block.

        size_t classCount = 1 << (blockSize - 1);

        blockCls.resize(blockCount, 0);
        classRmq.resize(classCount, nullptr);
        classData.resize(classCount);

        for (size_t b = 0; b < blockCount; b++)
        {
            size_t& cls = blockCls[b];

            size_t bSta = b * blockSize;
            size_t bEnd = std::min(bSta + blockSize, n);

            for (size_t i = bSta + 1; i < bEnd; i++, cls <<= 1)
            {
                size_t a = data[i - 1];
                size_t b = data[i];

                // Determine if it is +1 (0) or -1 (1).
                cls |= (((a ^ b) >> 1) ^ a) & 1;
            }

            // Undo last shift.
            cls >>= 1;

            // Has that class an RMQ?
            SparseTableRMQ<T>*& rmqPtr = classRmq[cls];
            if (rmqPtr == nullptr)
            {
                // Create RMQ for class.
                classData[cls] = vector<T>
                (
                    data.begin() + bSta,
                    data.begin() + bEnd
                );
                rmqPtr = new SparseTableRMQ<T>(classData[cls]);
                (*rmqPtr).processData();
            }
        }
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
        // Determine block indices.
        size_t iB = i >> blockDiv;
        size_t jB = j >> blockDiv;

        // Determine indices in block.
        size_t iIdx = i & blockMod;
        size_t jIdx = j & blockMod;

        if (iB == jB)
        {
            // i and j are in the same block.
            return inBlockMin(iB, iIdx, jIdx);
        }


        // i and j are in different blocks.

        size_t iMin = inBlockMin(iB, iIdx, blockMod);
        size_t jMin = inBlockMin(jB, 0, jIdx);
        size_t ijMin = this->minIndex(iMin, jMin);


        // Are blocks adjacent?
        if (iB + 1 == jB) return ijMin;


        // Determine the minimum in the blocks between i and j.
        size_t bIdx = (*tableRmq)(iB + 1, jB - 1);
        size_t bMin = blockMinIdx[bIdx];

        return this->minIndex(ijMin, bMin);
    }


private:

    // Performs a query on the given block and given range.
    // Returns the index of the minimum entry in that range with respect to the
    // original data.
    size_t inBlockMin(size_t b, size_t i, size_t j) const
    {
        // Determine class and RMQ.
        size_t bClass = blockCls[b];
        SparseTableRMQ<T>& rmq = *(classRmq[bClass]);

        return b * blockSize /* starting point of block */ + rmq(i, j);
    }


    // States how large a single block of the data is.
    // Defined as 1/2 * log n.
    size_t blockSize = 0;

    // Since we make the block size a power of two, we store helper for easy
    // division and modulo operations.
    size_t blockDiv = 0;
    size_t blockMod = 0;


    // The minimum of each block (A' in the paper).
    vector<T> blockMinVal;

    // The index of each block's minimum in the original data (B in the paper).
    vector<size_t> blockMinIdx;

    // A RMQ to find the minimum block.
    SparseTableRMQ<T>* tableRmq = nullptr;


    // States for each block, what class it is.
    vector<size_t> blockCls;

    // Allows to determine the minimum in a single block.
    vector<SparseTableRMQ<T>*> classRmq;

    // The data for each class. These are copies of the original data.
    vector<vector<T>> classData;

};

#endif
