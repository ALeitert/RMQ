#include "plusMinusRmq.h"

#include "log.hpp"


// Constructor.
PlusMinusRMQ::PlusMinusRMQ(const vector<number>& data) :
    RMQ<number>(data)
{
    /* Nothing. */
}

// Destructor.
PlusMinusRMQ::~PlusMinusRMQ()
{
    if (tableRmq != nullptr) delete tableRmq;
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


    // --- Determine minimum in each block. ---

    size_t blockCount = (n + 1) >> blockDiv;
    {
        // The minimum of each block (A' in the paper).
        vector<number> blockMinVal;

        blockMinVal.reserve(blockCount);
        blockMinIdx.reserve(blockCount);

        for (size_t b = 0, i = 0; i < n; b++)
        {
            // b: The current block index.
            // i: The current element in data[].

            blockMinVal.push_back(data[i]);
            blockMinIdx.push_back(i);
            i++;

            number& curMin = blockMinVal[b];
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
        tableRmq = new SparseTableRMQ<size_t>(blockMinVal);
        tableRmq->processData();
    }


    // --- Classify blocks. ---

    // Notethat we do not need to handle the last block B as special case as
    // long as we classify it last. If its class is unique, it will be processed
    // automatically. If it has the same class as a previous block, we
    // still only run queries on a range fitting to B which is still equivalent
    // to a query on the earlier block.

    size_t classCount = 1 << (blockSize - 1);

    blockCls.resize(blockCount, 0);
    classRmq.resize(classCount, nullptr);

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
    }
}


// Performs a query on the given data and given range.
// Returns the index of the minimum in that range.
// Behaviour is undefined if the given range is invalid or pre-processing
// has not been done.
size_t PlusMinusRMQ::operator()(size_t i, size_t j) const
{
}
