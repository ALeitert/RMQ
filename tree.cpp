#include "tree.h"


using namespace std;


// Default constructor.
// Creates an empty tree.
Tree::Tree() { /* Nothing. */ }

// Constructor.
Tree::Tree(const vector<size_t>& parList) :
    parents(parList)
{
    buildChildren();
}

// Constructor.
Tree::Tree(vector<size_t>&& parList) :
    parents(move(parList))
{
    buildChildren();
}


// Returns the parent's ID of the given node.
size_t Tree::operator()(size_t uId) const
{
    return parents[uId];
}

// Returns the children of the given node.
const vector<size_t>& Tree::operator[](size_t uId) const
{
    return children[uId];
}


// Computes an Euler tour of the tree.
EulerTour Tree::eulerTour() const
{
    const size_t n = parents.size();

    EulerTour result;
    result.E.reserve(2 * n - 1);
    result.L.reserve(2 * n - 1);
    result.R.resize(n);

    // Helpers to compute DFS
    vector<size_t> chIdx(n, 0);
    vector<size_t> stack;


    // Push
    stack.push_back(root);

    while (stack.size() > 0)
    {
        size_t vId = stack.back();
        size_t& cIdx = chIdx[vId];


        result.R[vId] = result.E.size();
        result.E.push_back(vId);
        result.L.push_back(stack.size());


        if (cIdx < children[vId].size())
        {
            const size_t& childId = children[vId][cIdx];

            // Push
            stack.push_back(childId);
            cIdx++;
        }
        else
        {
            // All neighbours checked, backtrack.
            stack.pop_back();
        }
    }

    return result;
}


// Helper function for constructor.
void Tree::buildChildren()
{
    children.resize(parents.size());

    for (size_t uId = 0; uId < parents.size(); uId++)
    {
        size_t pId = parents[uId];

        if (pId == NullNode)
        {
            root = uId;
        }
        else
        {
            children[pId].push_back(uId);
        }
    }
}

