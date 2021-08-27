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

