// yahelomessi@gmail.com

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

int main() {

    //-------------------- BFS & DFS Check--------------------
    graph::Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    std::cout << "Original graph:\n";
    g.print_graph();
    int source = 0;
    graph::Graph bfsTree = graph::Algorithms::bfs(g, source);
    std::cout << "\nBFS tree from source " << source << ":\n";
    bfsTree.print_graph();

    graph::Graph dfsTree = graph::Algorithms::dfs(g, source);
    std::cout << "\nDFS tree from source " << source << ":\n";
    dfsTree.print_graph();
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" ;

    //-------------------- Dijkstra Check--------------------
    graph::Graph weightedGraph(5);
    weightedGraph.addEdge(0, 1, 1);
    weightedGraph.addEdge(0, 2, 2);
    weightedGraph.addEdge(0, 3, 8);
    weightedGraph.addEdge(1, 4, 8);
    weightedGraph.addEdge(2, 4, 2);
    weightedGraph.addEdge(3, 4, 1);

    std::cout << "\nWeighted graph for Dijkstra:\n";
    weightedGraph.print_graph();

    int dijkstraSource = 0;
    graph::Graph dijkstraTree = graph::Algorithms::dijkstra(weightedGraph, dijkstraSource);
    std::cout << "\nDijkstra tree from source " << dijkstraSource << ":\n";
    dijkstraTree.print_graph();
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" ;

     //-------------------- Prim Check --------------------
     graph::Graph weightedGraphForPrim(7);
     weightedGraphForPrim.addEdge(0, 1, 2);
     weightedGraphForPrim.addEdge(0, 2, 3);
     weightedGraphForPrim.addEdge(0, 3, 3);
     weightedGraphForPrim.addEdge(1, 2, 4);
     weightedGraphForPrim.addEdge(1, 4, 3);
     weightedGraphForPrim.addEdge(2, 3, 5);
     weightedGraphForPrim.addEdge(2, 4, 1);
     weightedGraphForPrim.addEdge(2, 5, 6);
     weightedGraphForPrim.addEdge(3, 5, 7);
     weightedGraphForPrim.addEdge(4, 5, 8);
     weightedGraphForPrim.addEdge(5, 6, 9);

 
     std::cout << "\nWeighted graph for Prim:\n";
     weightedGraphForPrim.print_graph();
 
     graph::Graph primTree = graph::Algorithms::prim(weightedGraphForPrim);
     std::cout << "\nPrim MST:\n";
     primTree.print_graph();
     std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" ;


    //-------------------- Kruskal Check --------------------
    graph::Graph kruskalGraph(7);

    kruskalGraph.addEdge(0, 1, 2);
    kruskalGraph.addEdge(0, 2, 3);
    kruskalGraph.addEdge(0, 3, 3);
    kruskalGraph.addEdge(1, 2, 4);
    kruskalGraph.addEdge(1, 4, 3);
    kruskalGraph.addEdge(2, 3, 5);
    kruskalGraph.addEdge(2, 4, 1);
    kruskalGraph.addEdge(3, 5, 7);
    kruskalGraph.addEdge(4, 5, 8);
    kruskalGraph.addEdge(5, 6, 9);

    std::cout << "\nWeighted graph for Kruskal:\n";
    kruskalGraph.print_graph();

    graph::Graph kruskalTree = graph::Algorithms::kruskal(kruskalGraph);
    std::cout << "\nKruskal MST:\n";
    kruskalTree.print_graph();

    return 0;
}


