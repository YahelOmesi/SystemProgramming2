// yahelomessi@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph{

    struct Edge {
        int src;
        int dest;
        int weight;
    };    

    class Graph{

        private:
        int numOfVertices;
        //int** adjacencyList; 
        int*** adjacencyList;
        int* numOfNeighbors;
        int* capacities;

        public:
        Graph(int vertices);
        Graph(const Graph& other);
        ~Graph();

        void addEdge(int src, int dest , int weight = 1);
        void addDirectedEdge(int src, int dest, int weight = 1); //for BFS & DFS
        void removeEdge(int src, int dest);
        void print_graph() const;

        int getNumVertices() const;
        const int* getNeighbors(int vertex) const;
        int dfsNeighbor(int vertex, int index) const;
        int getNeighborsCount(int vertex) const;
        int getEdgeWeight(int src, int dest) const; // new method
        Edge* getAllEdges(int& edgeCount) const;
    };
}

#endif