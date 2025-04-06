yahelomessi@gmail.com  
# Graph Algorithms in C++ (System Programming 2 Assignment 1)

Yahel Omesi  
yahelomessi@gmail.com  


# Project Goal
This project implements an undirected weighted graph using an adjacency list in C++, without STL containers.  
It includes implementations of classic graph algorithms using custom data structures.


# Algorithms & Data Structures:
- BFS -returns a rooted tree from a source node (custom queue)
- DFS -returns a forest that includes only tree edges (recursive call)
- Dijkstra -returns a shortest-path tree from a source node (custom priority queue)
- Prim -returns a minimum spanning tree (custom priority queue)
- Kruskal -returns a minimum spanning tree using Union-Find (custom union find)


# Definitions
- tree = a connected, acyclic graph.
- rooted tree = a tree in which one vertex is designated as the root.
- forest =  a disjoint union of trees.
- tree edge = an edge in the DFS traversal that connects a vertex to an unvisited vertex.
- MST (Minimum Spanning Tree) = a spanning tree of a connected, weighted, undirected graph, such that it connects all the vertices and the sum of weights of the edges is minimized.


# Features
- all classes are inside the graph namespace.
- Custom data structures: `Queue`, `PriorityQueue`, `UnionFind`
- Tested with [doctest](https://github.com/doctest/doctest)
- Checked for memory leaks using `valgrind`


# Implementation Highlights
    Graph Representation:
        each vertex maintains a dynamic array of its neighbors.
        each neighbor is stored as a pair [destination, weight].
        graph supports dynamic resizing of adjacency lists.
        default weight of an edge is 1 if not given.

    Memory Management:
        deep copy implemented in the Graph copy constructor.
        all dynamic memory is properly cleaned using destructors.(verified using valgrind)

    Undirected Weighted Graph:
        all edges are bi-directional by default.
        all algorithms support weights
        ! dijkstra is the only one that does not support edges with negative weight


# Testing
The project includes comprehensive tests with doctest.
Each algorithm is tested for:
1. correct output on small and complex graphs
2. single-node graph
3. disconnected graph (where relevant)
4. self-loops
5. multiple edges with same weight
6. invalid vertex indices (in bfs,dfs,dijkstra)


# Build & Run Instructions
To compile, run, test, and check memory leaks, use the following make commands:

- make all = compiles the main program and creates the executable Main.
- make run = runs the compiled program (./Main).
- make test = compiles & runs the unit tests (based on doctest).
- make valgrind = runs the program with Valgrind to check for memory leaks.
- make clean = deletes the generated binaries (Main, Test).
