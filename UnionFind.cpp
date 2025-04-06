// yahelomessi@gmail.com

#include "UnionFind.hpp"
#include <stdexcept>

namespace graph{
    UnionFind::UnionFind(int n): size(n){
        parent = new int[n];
        rank = new int[n];

        //initialization
        for(int i = 0; i < n; i++){
            parent[i] = i; //each node is its own root
            rank[i] = 0;  //no children
        }
    }

    UnionFind::~UnionFind(){
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int x){

        if(x < 0 || x >= size){
            throw std::invalid_argument("invalid index");
        }

        if(parent[x] != x){
            parent[x] = find(parent[x]); //recursive call
        }

        return parent[x];
    }

    void UnionFind::unionSets(int x, int y){
        int xRoot = find(x);
        int yRoot = find(y);

        if(xRoot == yRoot){ //if they are in the same group - no need to union
            return;
        }


        if(rank[xRoot] < rank[yRoot]){  //connect x to y
            parent[xRoot] = yRoot;
        }else if(rank[xRoot] > rank[yRoot]){  //connect y to x
            parent[yRoot] = xRoot;
        }else{ //equal in height
            parent[yRoot] = xRoot; //connect y to x
            rank[xRoot]++; //update rank
        }


    }

    //returns true if x&y in the same group
    bool UnionFind::connected(int x, int y){
        return find(x) == find(y);
    }

}
