// yahelomessi@gmail.com

#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace graph {

    Graph::Graph(int vertices) : numOfVertices(vertices){ //constructor
        adjacencyList = new int**[vertices]; //pointer to array of pointers to [neighbor, weight]
        numOfNeighbors = new int[vertices]; 
        capacities = new int[vertices];

        //initilize vertices
        for(int i=0; i<vertices; i++){
            int initialCapacity = 2;
            numOfNeighbors[i] = 0;
            capacities[i] = initialCapacity;
            adjacencyList[i] = new int*[initialCapacity];
        }
    }

    Graph::Graph(const Graph& other){ //copy constructor
        numOfVertices = other.numOfVertices;

        adjacencyList = new int**[numOfVertices];
        numOfNeighbors = new int[numOfVertices];
        capacities = new int[numOfVertices];

        for(int i = 0; i < numOfVertices; i++){
            numOfNeighbors[i] = other.numOfNeighbors[i];
            capacities[i] = other.capacities[i];
            adjacencyList[i] = new int*[capacities[i]];

            //copy the neighbors one by one
            for(int j = 0; j < numOfNeighbors[i]; j++){
                adjacencyList[i][j] = new int[2];
                adjacencyList[i][j][0] = other.adjacencyList[i][j][0]; //neighbore
                adjacencyList[i][j][1] = other.adjacencyList[i][j][1]; //weight
            }
        }
    }

    Graph::~Graph(){ //destructor
        for(int i=0; i<numOfVertices; i++){
            for (int j = 0; j < numOfNeighbors[i]; j++) {
                delete[] adjacencyList[i][j];
            }
            delete[] adjacencyList[i];
        }

        delete[] adjacencyList;
        delete[] numOfNeighbors;
        delete[] capacities;
    }

    void Graph::addEdge(int src, int dest, int weight){
        if(src < 0 || src >= numOfVertices || dest < 0 || dest >= numOfVertices){
            throw std::invalid_argument("invalid index");
        }

        //add src --> dest
        if(numOfNeighbors[src] == capacities[src]){
            int newCapacity = capacities[src] * 2;
            int** newArr = new int*[newCapacity];

            for(int i = 0; i < numOfNeighbors[src]; i++){
                newArr[i] = adjacencyList[src][i];
            }

            delete[] adjacencyList[src];
            adjacencyList[src] = newArr; 
            capacities[src] = newCapacity; //update capacity
        }

        //add the neighbor dest with weight
        adjacencyList[src][numOfNeighbors[src]] = new int[2];
        adjacencyList[src][numOfNeighbors[src]][0] = dest;
        adjacencyList[src][numOfNeighbors[src]][1] = weight;
        numOfNeighbors[src]++;

        //add dest -> src
        if(numOfNeighbors[dest] == capacities[dest]){
            int newCapacity = capacities[dest] * 2;
            int** newArr = new int*[newCapacity];

            for(int i = 0; i < numOfNeighbors[dest]; i++){
                newArr[i] = adjacencyList[dest][i];
            }

            delete[] adjacencyList[dest];
            adjacencyList[dest] = newArr;
            capacities[dest] = newCapacity; //update capacity
        }

        //add the neighbor src with weight
        adjacencyList[dest][numOfNeighbors[dest]] = new int[2];
        adjacencyList[dest][numOfNeighbors[dest]][0] = src;
        adjacencyList[dest][numOfNeighbors[dest]][1] = weight;
        numOfNeighbors[dest]++;
    }

    void Graph::addDirectedEdge(int src, int dest, int weight){
        if (src < 0 || src >= numOfVertices || dest < 0 || dest >= numOfVertices) {
            throw std::invalid_argument("invalid index");
        }
    
        if(numOfNeighbors[src] == capacities[src]){
            int newCapacity = capacities[src] * 2;
            int** newArr = new int*[newCapacity];
    
            for(int i = 0; i < numOfNeighbors[src]; i++){
                newArr[i] = adjacencyList[src][i];
            }
    
            delete[] adjacencyList[src];
            adjacencyList[src] = newArr;
            capacities[src] = newCapacity;
        }
    
        adjacencyList[src][numOfNeighbors[src]] = new int[2];
        adjacencyList[src][numOfNeighbors[src]][0] = dest;
        adjacencyList[src][numOfNeighbors[src]][1] = weight;
        numOfNeighbors[src]++;
    }
    
    void Graph::removeEdge(int src, int dest){
        bool flag = false; //indicate existence of this edge

        //looking for dest in src's neighbors
        for (int i = 0; i < numOfNeighbors[src]; i++) {
            if (adjacencyList[src][i][0] == dest) {
                delete[] adjacencyList[src][i]; //delete dest
                adjacencyList[src][i] = adjacencyList[src][numOfNeighbors[src] - 1]; //last one insted of dest
                numOfNeighbors[src]--; 
                flag = true;
                break;
            }
        }

        //Looking for src in dest's neighbors
        for (int i = 0; i < numOfNeighbors[dest]; i++) {
            if (adjacencyList[dest][i][0] == src) {
                delete[] adjacencyList[dest][i]; //delete src
                adjacencyList[dest][i] = adjacencyList[dest][numOfNeighbors[dest] - 1]; //last one insted of src
                numOfNeighbors[dest]--;
                flag = true;
                break;
            }
        }

        if(!flag){
            throw std::runtime_error("edge not exist");
        }
    }

    void Graph::print_graph() const {
        for (int i = 0; i < numOfVertices; i++) {
            std::cout << i << ": ";
            for (int j = 0; j < numOfNeighbors[i]; j++) {
                int neighbor = adjacencyList[i][j][0];
                int weight = adjacencyList[i][j][1];
                std::cout << neighbor << "(" << weight << ") ";
            }
            std::cout << std::endl;
        }
    }

    int Graph::getNumVertices() const{
        return numOfVertices;
    }

    const int* Graph::getNeighbors(int vertex) const{
        if(vertex < 0 || vertex >= numOfVertices){
            throw std::invalid_argument("invalid vertex index");
        }

        static int neighbors[100];
        for (int i = 0; i < numOfNeighbors[vertex]; i++) {
            neighbors[i] = adjacencyList[vertex][i][0];
        }
        return neighbors;
    }

    int Graph::dfsNeighbor(int vertex, int index) const {
        if (vertex < 0 || vertex >= numOfVertices) {
            throw std::invalid_argument("invalid vertex index");
        }
        if (index < 0 || index >= numOfNeighbors[vertex]) {
            throw std::invalid_argument("invalid neighbor index");
        }
        return adjacencyList[vertex][index][0]; 
    }
    
    int Graph::getNeighborsCount(int vertex) const{
        if(vertex < 0 || vertex >= numOfVertices){
            throw std::invalid_argument("invalid vertex index");
        }
        return numOfNeighbors[vertex];
    }

    int Graph::getEdgeWeight(int src, int dest) const {
        if(src < 0 || src >= numOfVertices || dest < 0 || dest >= numOfVertices){
            throw std::invalid_argument("invalid index");
        }

        for (int i = 0; i < numOfNeighbors[src]; i++) {
            if (adjacencyList[src][i][0] == dest) {
                return adjacencyList[src][i][1]; //return weight
            }
        }
        throw std::runtime_error("edge not found");
    }

    graph::Edge* Graph::getAllEdges(int& edgeCount) const{
        edgeCount = 0;
        int maxEstimate = numOfVertices * numOfVertices; // klika - worst case
        Edge* edges = new Edge[maxEstimate];

        for(int u = 0; u < numOfVertices; u++){
            for(int i = 0; i < numOfNeighbors[u]; i++){
                int v = adjacencyList[u][i][0]; //neighbore node
                int w = adjacencyList[u][i][1]; // u-v weight

                //prevent double counting(undirected graph)
                if(u < v){
                    edges[edgeCount].src = u;
                    edges[edgeCount].dest = v;
                    edges[edgeCount].weight = w;
                    edgeCount++; 
                }
            }
        }
        return edges;
    }
}
