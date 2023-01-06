# Range Minimum Query

For the *range minimum query* (RMQ) problem, we are given an array *A* of size *n* and two indices *i* and *j* with 0 ≤ *i* ≤ *j* < *n*.
We then want to determine the smallest element in { *A*[*i*], *A*[*i* + 1], ..., *A*[*j*] }.
The program implements different RMQ algorithms.
They are mostly taken from [1].

The algorithms all have two parts to it: a pre-processing and query.
The pre-processing processes the given array *A* and then stores results that allow for a faster query.
The query then determines the minimum in the specified rang with the help of the pre-processing results.
Subsequently, these algorithms have two runtimes.
We rite that the runtime of an algorithm is in < O( *f*(*n*) ), O( *g*(*n*) )> time if the pre-processing runs in O( *f*(*n*) ) time, and a single query runs in O( *g*(*n*) ) time.


## Implemented Algorithms

  * **No Pre-Processing.**
    As the name suggests, this algorithm does not do any pre-processing at all.
    Subsequently, it iterate over the requested range of *A* in each query.
    Runtime: < O(0), O( *j* - *i* ) >.

  * **Naive.**
    This is a straight forward implementation of an RMQ algorithm.
    It computes all *n*^2 possible results and stores them in a table *T*.
    A query then simply reads the value out of *T*[*i*][*j*].
    Runtime: < O(*n*^2), O(1) >.

  * **Segment Tree.**
    This algorithms builds a full binary tree on top of *A* which has the elements of *A* as leaves.
    Each node *u* then stores the minimum of all leaves that have *u* as ancestor.
    Such a tree is called [Segment Tree](https://en.wikipedia.org/wiki/Segment_tree).
    It allows to run queries in logarithmic time by searching for *i* and *j* in the tree.
    Runtime: < O(*n*), O(log *n*) >.

  * **Cache-Oblivious Segment Tree.**
    This algorithm works overall the same way as the Segment Tree algorithm above.
    The difference, however, is the way the nodes are stored in memory.
    They follow a *van Emde Boas layout* as described in [2, 3].
    Although the overall runtime is the same (asymptotically), there are asymptotically fewer cache misses when accessing nodes, leading to an overall better performance.
    Runtime: < O(*n*), O(log *n*) >.

  * **Sparse Table.**
    This algorithm is similar to the naive implementation in the sense that it computes a lookup table.
    That table, however, is much smaller.
    It only stores log *n* many rows, resulting in O(*n* log *n*) total memory usage.
    At the same time, it still allows to perform a query in constant time (although with non-trivial operations).
    Runtime: < O(*n* log *n*), O(1) >.

  * **±1 RMQ.**
    Consider an [Euler tour](https://en.wikipedia.org/wiki/Euler_tour_technique) over a tree where we store the height of each node whenever we encounter it.
    In the resulting sequence, subsequent elements differ by either +1 or -1.
    That is called the *±1 restriction*, and the goal of this algorithm is to make use of that restriction.
    The overall approach is similar to the Sparse Table.
    However, the given array *A* is first split into small blocks of size (log *n*) / 2.
    Given that small size, and the strong restrictions for the input, there are only sqrt(*n*) different blocks possible.
    The properties allow the following overall runtime: < O(*n*), O(1) >.


## Lowest Common Ancestor

We also implemented an algorithm that computes the lowest common ancestor of two nodes in a tree.
The algorithm uses an Euler tour of the given tree and then performs a RMQ on that tour as described in [1].
For that it can use any of the RMQ algorithms described above.


## References

[1] M.A. Bender, M. Farach-Colton:
    The LCA Problem Revisited.
    LATIN 2000, LNCS 1776, 88-94, 2000.

[2] M.A. Bender, E.D. Demaine, M. Farach-Colton:
    Cache-Oblivious B-Trees.
    SIAM J. Comput. 35(2), 341-358, 2005.

[3] H. Prokop:
    Cache-oblivious algorithms.
    Master’s thesis, MIT, June 1999.
