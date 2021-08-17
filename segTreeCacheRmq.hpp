// Represents a RMQ that uses a cache-oblivious segment tree to run queries.
// Runtime: O(n) | O(log n)

#ifndef __SegTreeCacheRmq_HPP__
#define __SegTreeCacheRmq_HPP__


#include <limits>

#include "rmq.hpp"


template<typename T>
class SegTreeCacheRMQ : public RMQ<T>
{
    // Used similar to a null pointer.
    static constexpr size_t InvalidIndex = std::numeric_limits<size_t>::max();

    // Shortcut to avoid the need for "std::".
    template<typename X> using vector = std::vector<X>;

    // A node of the tree.
    struct Node
    {
        Node* left  = nullptr;
        Node* right = nullptr;

        size_t toIdx  = InvalidIndex;
        size_t minIdx = InvalidIndex;
    };


public:

    // Constructor.
    SegTreeCacheRMQ(const std::vector<T>& data) : RMQ<T>(data) { /* Nothing. */ }


    // Pre-processes the data to allow queries.
    void processData()
    {
        const size_t n = this->data.size();

        // Height is ceil(log n) + 1.
        size_t height = (sizeof(unsigned long long) << 3) - __builtin_clzll(n - 1) + 1;

        // We build a full binary tree and cut nodes later.
        size_t treeSize = (1 << height) - 1;
        tree.resize(treeSize, Node());

        // Indices of the leafs.
        vector<size_t> leafIndices;
        leafIndices.reserve(treeSize);

        {
            vector<size_t> leafStack;
            leafStack.reserve(1 << (height >> 1));

            // Build tree structure recursively.
            buildTree(0, height, leafIndices, leafStack);
        }

        // The structure of the tree is build.
        // We need to add data and cut unwanted edges.

        // Initialise leaves.
        for (size_t i = 0; i < n; i++)
        {
            size_t idx = leafIndices[i];
            Node& node = tree[idx];

            node.toIdx = i;
            node.minIdx = i;
        }

        // Leaves that we do not keep.
        for (size_t i = n; i < leafIndices.size(); i++)
        {
            size_t idx = leafIndices[i];
            Node& node = tree[idx];

            node.minIdx = InvalidIndex;
        }

        // Process tree bottom up.
        for (size_t i = tree.size() - 1; i < tree.size(); i--)
        {
            Node& node = tree[i];

            // Skip leaves.
            if (node.left == nullptr) continue;

            // Left valid?
            if (node.left->minIdx == InvalidIndex)
            {
                // No valid children.
                // Flag as invalid and continue with next.
                node.minIdx = InvalidIndex;
                continue;
            }

            node.toIdx = node.left->toIdx;
            node.minIdx = node.left->minIdx;


            // Right valid?
            if (node.right->minIdx == InvalidIndex)
            {
                // No. Remove pointer and continue.
                node.right = nullptr;
                continue;
            }

            node.toIdx = node.right->toIdx;
            node.minIdx = this->minIndex(node.minIdx, node.right->minIdx);
        }
    }

    // Performs a query on the given data and given range.
    // Returns the index of the minimum in that range.
    // Behaviour is undefined if the given range is invalid or pre-processing
    // has not been done.
    size_t operator()(size_t i, size_t j) const
    {
        size_t minIdx = i;
        const Node* node = &tree[0];

        // Go down until paths to i and j split.
        for (;;)
        {
            if (j <= node->left->toIdx)
            {
                // Go left.
                node = node->left;
            }
            else if (i > node->left->toIdx)
            {
                // Go right.
                node = node->right;
            }
            else
            {
                // Split paths.
                break;
            }
        }

        // Go down left and search for i.
        for (const Node* iNode = node->left;;)
        {
            if (iNode->left == nullptr)
            {
                // Base case.
                minIdx = this->minIndex(minIdx, iNode->minIdx);
                break;
            }

            if (i <= iNode->left->toIdx)
            {
                // Get minimum from right node ...
                minIdx = this->minIndex(minIdx, iNode->right->minIdx);

                // ... and go left.
                iNode = iNode->left;
            }
            else
            {
                // Go right.
                iNode = iNode->right;
            }
        }

        // Go down right and search for j.
        for (const Node* jNode = node->right;;)
        {
            if (jNode->toIdx == j)
            {
                // Base case.
                minIdx = this->minIndex(minIdx, jNode->minIdx);
                break;
            }

            if (j <= jNode->left->toIdx)
            {
                // Go left.
                jNode = jNode->left;
            }
            else
            {
                // Get minimum from left node ...
                minIdx = this->minIndex(minIdx, jNode->left->minIdx);

                // ... and go right.
                jNode = jNode->right;
            }
        }

        return minIdx;
    }


private:

    // Stores the nodes of the segment tree.
    std::vector<Node> tree;

    // Recursively builds tree.
    void buildTree(size_t rootIdx, size_t height, vector<size_t>& leafIndices, vector<size_t>& leafStack)
    {
        if (height == 1)
        {
            leafIndices.push_back(rootIdx);
            return;
        }


        size_t topHeight = height >> 1;
        size_t botHeight = (height + 1) >> 1;

        // Build upper part
        buildTree(rootIdx, topHeight, leafIndices, leafStack);


        size_t topSize = (1 << topHeight) - 1;
        size_t botSize = (1 << botHeight) - 1;

        size_t topLeaves = (topSize + 1) >> 1;
        size_t leafEnd = leafIndices.size();
        size_t leafSta = leafEnd - topLeaves;

        // Move top-leaves onto stack.
        for (size_t ptr = leafSta; ptr < leafEnd; ptr++)
        {
            leafStack.push_back(leafIndices[ptr]);
        }

        // Remove top-leaves from list.
        leafIndices.resize(leafSta);


        // Update pointers; they now refer to the stack.
        leafEnd = leafStack.size();
        leafSta = leafEnd - topLeaves;

        for
        (
            size_t
                ptr = leafSta,
                chIdx = rootIdx + topSize
            ;
                ptr < leafEnd
            ;
                ptr++
        )
        {
            size_t pIdx = leafStack[ptr];
            size_t lIdx = chIdx; chIdx += botSize;
            size_t rIdx = chIdx; chIdx += botSize;


            Node& pNode = tree[pIdx];
            Node& lNode = tree[lIdx];
            Node& rNode = tree[rIdx];

            pNode.left  = &lNode;
            pNode.right = &rNode;

            buildTree(lIdx, botHeight, leafIndices, leafStack);
            buildTree(rIdx, botHeight, leafIndices, leafStack);
        }

        // Remove top leaves from stack.
        leafStack.resize(leafSta);
    }
};

#endif
