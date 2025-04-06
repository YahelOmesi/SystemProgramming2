// yahelomessi@gmail.com

namespace graph{
    class UnionFind{
        private:
        int* parent; //the root of a groop
        int* rank; //the depth of sub-tree
        int size;

        public: 
        UnionFind(int n);
        ~UnionFind();

        int find(int x); //return x's root
        void unionSets(int x, int y);
        bool connected(int x, int y); //return yes if they are in the same group
    };
}