// yahelomessi@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace graph;

//TEST BFS
TEST_CASE("BFS on simple connected graph") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    Graph bfsTree = Algorithms::bfs(g, 0);

    CHECK(bfsTree.getNeighborsCount(0) == 1); //1
    CHECK(bfsTree.getNeighborsCount(1) == 2); //0,2
    CHECK(bfsTree.getNeighborsCount(2) == 2); //1,3
    CHECK(bfsTree.getNeighborsCount(3) == 1); //2
}

TEST_CASE("BFS on graph with a cycle") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); //cycle: 0-1-2-0
    g.addEdge(2, 3);

    Graph bfsTree = Algorithms::bfs(g, 0);

    int totalEdges = 0;
    for (int i = 0; i < 4; i++) {
        totalEdges += bfsTree.getNeighborsCount(i);
    }
    CHECK(totalEdges / 2 == 3); //need to be only 3 edges 
}

TEST_CASE("BFS on disconnected graph") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4); //disconnected component

    Graph bfsTree = Algorithms::bfs(g, 0);

    CHECK(bfsTree.getNeighborsCount(3) == 0);
    CHECK(bfsTree.getNeighborsCount(4) == 0);
}

TEST_CASE("BFS starting from non-zero node") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    Graph bfsTree = Algorithms::bfs(g, 2);

    CHECK(bfsTree.getNeighborsCount(2) == 2);
    CHECK(bfsTree.getNeighborsCount(0) == 1); 
} 

TEST_CASE("BFS on single-node graph") {
    Graph g(1);
    Graph bfsTree = Algorithms::bfs(g, 0);

    CHECK(bfsTree.getNumVertices() == 1);
    CHECK(bfsTree.getNeighborsCount(0) == 0);
}

TEST_CASE("BFS throws for invalid source") {
    Graph g(3);
    CHECK_THROWS_AS(Algorithms::bfs(g, 5), std::invalid_argument);
    CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::invalid_argument);
}

//TEST DFS
TEST_CASE("DFS on simple path") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    Graph dfsTree = Algorithms::dfs(g, 0);

    CHECK(dfsTree.getNeighborsCount(0) == 1); //1
    CHECK(dfsTree.getNeighborsCount(1) == 2); //0,2
    CHECK(dfsTree.getNeighborsCount(2) == 2); //1,3
    CHECK(dfsTree.getNeighborsCount(3) == 1); //2
}

TEST_CASE("DFS on graph with a cycle") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); //cycle
    g.addEdge(2, 3);

    Graph dfsTree = Algorithms::dfs(g, 0);

    int edgeCount = 0;
    for (int i = 0; i < 4; i++) {
        edgeCount += dfsTree.getNeighborsCount(i);
    }

    CHECK(edgeCount / 2 == 3); //only 3 tree edges
}

TEST_CASE("DFS on disconnected graph (forest)") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4); //disconnected from 0

    Graph dfsTree = Algorithms::dfs(g, 0);

    //we have 2 components
    CHECK(dfsTree.getNeighborsCount(3) == 1);
    CHECK(dfsTree.getNeighborsCount(4) == 1);
}

TEST_CASE("DFS starting from node 2") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    Graph dfsTree = Algorithms::dfs(g, 2);

    CHECK(dfsTree.getNeighborsCount(2) == 2); //only tree edges
    CHECK(dfsTree.getNeighborsCount(0) == 1); 
}

TEST_CASE("DFS on single-node graph") {
    Graph g(1);
    Graph dfsTree = Algorithms::dfs(g, 0);

    CHECK(dfsTree.getNumVertices() == 1);
    CHECK(dfsTree.getNeighborsCount(0) == 0);
}

TEST_CASE("DFS throws for invalid source") {
    Graph g(3);
    CHECK_THROWS_AS(Algorithms::dfs(g, 5), std::invalid_argument);
    CHECK_THROWS_AS(Algorithms::dfs(g, -1), std::invalid_argument);
}

//TEST DIJKSTRA
TEST_CASE("Dijkstra - simple direct edge") {
    Graph g(2);
    g.addEdge(0, 1, 5);

    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.getEdgeWeight(0, 1) == 5);
    CHECK(tree.getNeighborsCount(1) == 1);
}

TEST_CASE("Dijkstra - choose shortest path") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 10);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.getEdgeWeight(0, 1) == 1);
    CHECK(tree.getEdgeWeight(1, 2) == 1);
    CHECK(tree.getEdgeWeight(2, 3) == 1);
    CHECK_THROWS(tree.getEdgeWeight(0, 2)); // 0-1-2 cheaper then 0-2
}

TEST_CASE("Dijkstra - disconnected graph") {
    Graph g(3);
    g.addEdge(0, 1, 1);

    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.getEdgeWeight(0, 1) == 1);
    CHECK(tree.getNeighborsCount(2) == 0); //node 2 is unconnected
}

TEST_CASE("Dijkstra - ignore a self loop") {
    Graph g(2);
    g.addEdge(0, 0, 100); //self loop
    g.addEdge(0, 1, 2);

    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.getEdgeWeight(0, 1) == 2);
    CHECK_THROWS(tree.getEdgeWeight(0, 0)); //loop should not appear
}

TEST_CASE("Dijkstra - equal weight edges") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);

    Graph tree = Algorithms::dijkstra(g, 0);

    //the 0 -- 3 will cost 2
    CHECK(tree.getNeighborsCount(3) == 1);
    CHECK((tree.getEdgeWeight(1, 3) == 1 || tree.getEdgeWeight(2, 3) == 1));
}

TEST_CASE("Dijkstra - throws for invalid source") {
    Graph g(3);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 5), std::invalid_argument);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, -1), std::invalid_argument);
}

//TEST PRIM
TEST_CASE("Prim - simple triangle graph") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10); //this edge should not enter mst

    Graph mst = Algorithms::prim(g);

    CHECK(mst.getEdgeWeight(0, 1) == 1);
    CHECK(mst.getEdgeWeight(1, 2) == 2);
    CHECK_THROWS(mst.getEdgeWeight(0, 2)); 
}

TEST_CASE("Prim - disconnected graph should throw") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1); //doiffrent component

    CHECK_THROWS(Algorithms::prim(g));
}

TEST_CASE("Prim - equal weight options") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);

    Graph mst = Algorithms::prim(g);

    CHECK(mst.getNeighborsCount(0) == 3); //1,2,3 connected to 0
}

TEST_CASE("Prim - ignore a self loop") {
    Graph g(3);
    g.addEdge(0, 0, 50); //self loop
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);

    Graph mst = Algorithms::prim(g);

    CHECK(mst.getEdgeWeight(0, 1) == 1);
    CHECK(mst.getEdgeWeight(1, 2) == 2);
    CHECK_THROWS(mst.getEdgeWeight(0, 0)); //loop should not appear
}

TEST_CASE("Prim - ignores expensive edge") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 100); 

    Graph mst = Algorithms::prim(g);

    CHECK(mst.getEdgeWeight(0, 1) == 1);
    CHECK(mst.getEdgeWeight(1, 2) == 1);
    CHECK_THROWS(mst.getEdgeWeight(0, 2));
}


//TEST KRUSKAL
TEST_CASE("Kruskal - simple triangle graph") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10); //this edge should not enter mst

    Graph mst = Algorithms::kruskal(g);

    CHECK(mst.getEdgeWeight(0, 1) == 1);
    CHECK(mst.getEdgeWeight(1, 2) == 2);
    CHECK_THROWS(mst.getEdgeWeight(0, 2));
}

TEST_CASE("Kruskal - disconnected graph should throw") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1); //diffrent components
    CHECK_THROWS(Algorithms::kruskal(g));
}

TEST_CASE("Kruskal - equal weight options") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);

    Graph mst = Algorithms::kruskal(g);

    CHECK(mst.getNeighborsCount(0) == 3); //1,2,3 connected to 0
}

TEST_CASE("Kruskal - ignore a self loop") {
    Graph g(3);
    g.addEdge(0, 0, 50); //self loop
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);

    Graph mst = Algorithms::kruskal(g);

    CHECK(mst.getEdgeWeight(0, 1) == 1);
    CHECK(mst.getEdgeWeight(1, 2) == 2);
    CHECK_THROWS(mst.getEdgeWeight(0, 0)); //loop should not appear
}

TEST_CASE("Kruskal - ignores expensive edge") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 100); 

    Graph mst = Algorithms::kruskal(g);

    CHECK(mst.getEdgeWeight(0, 1) == 1);
    CHECK(mst.getEdgeWeight(1, 2) == 1);
    CHECK_THROWS(mst.getEdgeWeight(0, 2));
}

