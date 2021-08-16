// Represents a RMQ that uses a segment tree to run queries.
// Runtime: O(n) | O(log n)

#ifndef __SegTreeRmq_HPP__
#define __SegTreeRmq_HPP__


#include "rmq.hpp"


template<typename T>
class SegTreeRMQ : public RMQ<T>
{
public:

    // Constructor.
    SegTreeRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    void processData()
    {
        // Shortcut to access data.
        const std::vector<T>& data = this->data;
        const size_t n = data.size();


        // --- Build tree. ---

        // Determine size.
        size_t treeSize = n;
        for
        (
            size_t laySz = n;
            laySz > 1;
            laySz = (laySz + 1) >> 1, treeSize += laySz
        ) { }

        tree.resize(treeSize);

        // Build bottom layer.
        for (size_t i = 0; i < n; i++)
        {
            Node& node = tree[treeSize - n + i];
            node.minIdx = i;
            node.frIdx = i;
            node.toIdx = i;
        }

        // Build tree bottom-up.
        for
        (
            size_t qSize = n, qStart = treeSize - n;
            qSize > 1;
            qSize = (qSize + 1) >> 1, qStart -= qSize
        )
        {
            // Outer loop has one iteration per layer.

            //  qSize: The number of nodes in the previous layer.
            // qStart: The index of the first (i.e. left-most) node of the
            //         previous layer in tree[].

            for
            (
                size_t nPtr = qStart - ((qSize + 1) >> 1), qPtr = qStart;
                qPtr < qSize + qStart;
                nPtr++, qPtr += 2
            )
            {
                // The inner loop iterates over the nodes in the layer below and
                // "creates" the nodes of the current layer.

                // nPtr: The index in tree[] of the "new" node.
                // qPtr: The index in tree[] of the new node's first child.

                Node& node = tree[nPtr];

                node.left = &tree[qPtr];
                node.frIdx = node.left->frIdx;
                node.toIdx = node.left->toIdx;
                node.minIdx = node.left->minIdx;

                // Still one more element?
                if (qPtr + 1 < qSize + qStart)
                {
                    node.right = &tree[qPtr + 1];
                    node.toIdx = node.right->toIdx;
                    node.minIdx = this->minIndex(node.minIdx, node.right->minIdx);
                }
            }
        }
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
    }


private:

    struct Node
    {
        Node* left  = nullptr;
        Node* right = nullptr;

        // The index range represented by the node.
        size_t frIdx = -1;
        size_t toIdx = -1;

        size_t minIdx = -1;
    };

    // Stores the nodes of the segment tree.
    std::vector<Node> tree;

};

#endif
