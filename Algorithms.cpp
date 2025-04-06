// yahelomessi@gmail.com

#include "Algorithms.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include "Graph.hpp"
#include <stdexcept>
#include <limits>
//#include <iostream>

namespace graph{

    graph::Graph Algorithms::bfs(const graph::Graph& g, int source){
        int numVertices = g.getNumVertices();

        if(source < 0 || source >= numVertices){
            throw std::invalid_argument("invalid source vertex");
        }

        graph::Graph tree(numVertices);

        bool* visited = new bool[numVertices];
        for(int i=0; i<numVertices; i++){
            visited[i] = false;
        }

        graph::Queue q(numVertices);

        //insert the source
        q.enqueue(source);
        visited[source] = true;

        //bfs loop
        while(!q.isEmpty()){
            int current = q.dequeue(); //pull the next element

            const int* neighbors = g.getNeighbors(current);
            int neighborCount = g.getNeighborsCount(current);

            //checking each neighbor of current
            for(int i = 0; i < neighborCount; i++){
                int neighbor = neighbors[i];

                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    tree.addEdge(current, neighbor); //new edge, current --- neighbor
                    q.enqueue(neighbor);
                }
            }
        }

        delete[] visited;
        return tree;
    }
    
    static void dfsVisit(const graph::Graph& g, int current, bool* visited, graph::Graph& tree){
        visited[current] = true;
    
        int neighborCount = g.getNeighborsCount(current);
        for (int i = 0; i < neighborCount; i++) {
            int neighbor = g.dfsNeighbor(current, i);
            if (!visited[neighbor]) {
                tree.addEdge(current, neighbor); //tree edge, current --- neighbor
                dfsVisit(g,neighbor,visited,tree); //recursive call
            }
        }
    }
    
    graph::Graph Algorithms::dfs(const graph::Graph& g, int source){
        int numVertices = g.getNumVertices();

        if(source < 0 || source >= numVertices){
            throw std::invalid_argument("invalid source vertex");
        }

        graph::Graph tree(numVertices);
        bool* visited = new bool[numVertices];
        for(int i = 0; i < numVertices; i++){
            visited[i] = false;
        }
        dfsVisit(g,source,visited,tree);

        //keep scan other components(if needed)
        for(int i = 0; i < numVertices; i++){
            if(!visited[i]){
                dfsVisit(g, i, visited, tree);
            }
        }

        delete[] visited;
        return tree;
    }

    graph::Graph Algorithms::dijkstra(const Graph& g, int source){
        int numVertices = g.getNumVertices();

        if(source < 0 || source >= numVertices){
            throw std::invalid_argument("invalid source vertex");
        }

        int* distances = new int[numVertices];
        int* parent = new int[numVertices];
        for(int i = 0; i < numVertices; i++){
            distances[i] = std::numeric_limits<int>::max();
            parent[i] = -1; //intilize all with "no parent"
        }
        distances[source] = 0;

        PriorityQueue pQueue(numVertices);
        pQueue.insert(source,0);

        while(!pQueue.isEmpty()){
            int u = pQueue.extractMin();
            const int* neighbors = g.getNeighbors(u);
            int neighborCount = g.getNeighborsCount(u);

            for(int i = 0; i < neighborCount; i++){
                int v = neighbors[i]; //v is neighbor of u
                int weight = g.getEdgeWeight(u,v); //weight of u---v

                //dijkstra does not support negatives
                if (weight < 0) {
                    delete[] distances;
                    throw std::invalid_argument("Dijkstra does not support negative edge weights");
                }
 
                
                //relaxation
                if(distances[u] + weight < distances[v]){
                    distances[v] = distances[u] + weight;
                    parent[v] = u; //keep the lowest path
               
                //update the priority queue
                if(pQueue.contains(v)){
                    pQueue.decreasePriority(v, distances[v]);
                }else{
                    pQueue.insert(v,distances[v]);
                }
              }
            }
         }

         Graph shortestPath(numVertices);

         for(int v = 0; v < numVertices; v++){
            if(parent[v] != -1){
                int u = parent[v];
                int w = g.getEdgeWeight(u,v);
                shortestPath.addEdge(u,v,w);
            }
         }

        delete[] distances;
        delete[] parent;
        return shortestPath;
    }

    graph::Graph Algorithms::prim(const Graph& g){

        int numVertices = g. getNumVertices();

        if(numVertices == 0){
            throw std::invalid_argument("empty graph");     
        }

        bool* insideTree = new bool[numVertices]; //existence inside the MST
        int* minWeight = new int[numVertices]; //minimum weight to reach i
        int* parent = new int[numVertices]; //from which vertex is it profitable to reach i

        for(int i = 0; i < numVertices; i++){
            insideTree[i] = false;
            minWeight[i] = std::numeric_limits<int>::max();
            parent[i] =-1;
        }

        minWeight[0] = 0;
        PriorityQueue pq(numVertices);
        pq.insert(0,0);

        while(!pq.isEmpty()){
            int u = pq.extractMin();
            insideTree[u] = true;

            const int* neighbors = g.getNeighbors(u);
            int neighborCount = g.getNeighborsCount(u);

            //go through neighbors of u and calculate the weight u---v
            for(int i = 0; i < neighborCount; i++){
                int v = neighbors[i];
                int weight = g.getEdgeWeight(u,v);

                if(!insideTree[v] && weight < minWeight[v]){ //relaxation
                    minWeight[v] = weight;
                    parent[v] = u;
                    //std::cout << "parent[" << v << "] = " << u << " with weight " << weight << std::endl;

                    if(pq.contains(v)){
                        pq.decreasePriority(v,minWeight[v]);
                    }else{
                        pq.insert(v,minWeight[v]);
                    }
                }
            }
        }

        //connectivity check - mst must be conected graph
        for (int i = 0; i < numVertices; i++) {
            if (!insideTree[i]) {
                delete[] insideTree;
                delete[] minWeight;
                delete[] parent;
                throw std::runtime_error("Prim requires a connected graph.");
            }
        }
    

        Graph mst(numVertices); //prim tree - minimum Spanning Tree
        for(int v = 0; v < numVertices; v++){
            if(parent[v] != -1){
                int u = parent[v];
                int w = g.getEdgeWeight(u,v);
                mst.addEdge(u,v,w);
            }
        }

        delete[] insideTree;
        delete[] minWeight;
        delete[] parent;

        return mst;
    }

    graph::Graph Algorithms::kruskal(const Graph& g){

        int numVertices = g.getNumVertices();
        if(numVertices == 0){
            throw std::invalid_argument("empty graph");
        }

        int edgeCount;
        Edge* edges = g.getAllEdges(edgeCount);

        // std::cout << "\n--- All edges sorted by weight (before building MST) ---\n";
        // for (int i = 0; i < edgeCount; i++) {
        //     std::cout << edges[i].src << " - " << edges[i].dest << " (" << edges[i].weight << ")\n";
        // }


        //bubble sort on edges (increasing order)
        for(int i = 0; i < edgeCount - 1; i++){
            for(int j = 0; j < edgeCount - i -1; j++){
                if(edges[j].weight > edges[j+1].weight){
                    Edge temp = edges[j];
                    edges[j] = edges[j+1];
                    edges[j+1] = temp;
                }
            }
        }

        Graph mst(numVertices); //store the result
        UnionFind uf(numVertices);

        for(int i = 0; i < edgeCount; i++){
            int u = edges[i].src;
            int v = edges[i].dest;
            int w = edges[i].weight;

            if(!uf.connected(u,v)){ //u,v not belong to the same connected component
                mst.addEdge(u,v,w); //add edge to mst
                uf.unionSets(u,v); //now belong to the same component
            }
        }

        //connectivity check - mst must be conected graph
        int root = uf.find(0);
        for (int i = 1; i < numVertices; i++) {
            if (uf.find(i) != root) {
                delete[] edges;
                throw std::runtime_error("Kruskal requires a connected graph.");
            }
        }

        delete[] edges;
        return mst;
    }

}
