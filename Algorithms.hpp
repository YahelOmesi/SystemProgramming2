// yahelomessi@gmail.com

#include "Graph.hpp"
#include "Queue.hpp"

namespace graph{
    class Algorithms{
        public:
        static graph::Graph bfs(const graph::Graph& g, int source);
        static graph::Graph dfs(const graph::Graph& g, int source);
        static graph::Graph dijkstra(const graph::Graph& g, int source);
        static Graph prim(const Graph& g);
        static Graph kruskal(const Graph& g);

        };
    }
