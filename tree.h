// Represents a rooted tree.

#ifndef __Tree_H__
#define __Tree_H__


#include <vector>


struct EulerTour
{
    // The sequence of nodes visited during an Euler tour.
    std::vector<size_t> E;

    // The level (distance to root + 1) of each node in the Euler tour.
    std::vector<size_t> L;

    // The index of a node's last occourance in the Euler tour.
    std::vector<size_t> R;
};


class Tree
{
    // Shortcut to avoid the need for "std::".
    template<typename X> using vector = std::vector<X>;

    // Represents a null pointer.
    const size_t NullNode = -1;


public:

    // Default constructor.
    // Creates an empty tree.
    Tree();

    // Constructor.
    Tree(const vector<size_t>& parList);

    // Constructor.
    Tree(vector<size_t>&& parList);


    // Returns the parent's ID of the given node.
    size_t operator()(size_t uId) const;

    // Returns the children of the given node.
    const vector<size_t>& operator[](size_t uId) const;


    // Computes an Euler tour of the tree.
    EulerTour eulerTour() const;


private:

    // The ID of the root node.
    size_t root = NullNode;

    // The parents of each node.
    vector<size_t> parents;

    // The children of each node.
    vector<vector<size_t>> children;


    // Helper function for constructors.
    void buildChildren();

};

#endif
